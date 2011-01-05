// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// https://sourceforge.net/projects/x3c/
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "StdAfx.h"
#include "Cx_CfgDatabase.h"
#include <Cx_SimpleObject.h>
#include "Cx_CfgRecordset.h"
#include "Cx_CfgRecord.h"
#include "DbFunc.h"

#define Cx_Section Cx_Interface<Ix_ConfigSection>

Cx_CfgDatabase::Cx_CfgDatabase()
{
	m_nRecordsAffected = 0;
	m_nModifiedCount = 0;
	m_pSQLParser = NULL;
}

Cx_CfgDatabase::~Cx_CfgDatabase()
{
	CloseConnection();
	SafeCall(m_pSQLParser, Release());
}

bool Cx_CfgDatabase::OpenConnection(const std::wstring& connection, 
									Ix_SQLParser* pSQLParser)
{
	bool bRet = false;
	HRESULT hr;

	m_pSQLParser = pSQLParser;

	try
	{
		if (NULL == m_pCon)
		{
			if (FAILED(hr = m_pCon.CreateInstance(__uuidof(Connection))))
			{
				LOG_ERROR(LOGHEAD L"IDS_CREATEINSTANCE_FAIL");
				_com_util::CheckError(hr);
			}
		}

		m_pCon->ConnectionTimeout = 5;
		m_pCon->ConnectionString = connection.c_str();

		if (FAILED(hr = m_pCon->raw_Open(NULL, NULL, NULL, adConnectUnspecified)))
		{
			LOG_ERROR(LOGHEAD L"IDS_CONNECT_FAIL");
			_com_issue_errorex(hr, m_pCon, __uuidof(m_pCon));
		}

		bRet = true;
	}
	CATCH_DB_STR_ERROR;

	return bRet;
}

void Cx_CfgDatabase::CloseConnection()
{
	if (NULL != m_pCon)
    {
        try
        {
            m_pCon->Close();
        }
        catch (...)
        {
        }
        m_pCon = NULL;
    }
}

#define EXECUTESQL(sql)	ExecuteSQL(sql, __FILE__, __LINE__)

_RecordsetPtr Cx_CfgDatabase::ExecuteSQL(LPCTSTR sql, LPCSTR file, long line)
{
	_RecordsetPtr pRs = NULL;
	_variant_t vRecords;

    try
    {
		m_nRecordsAffected = 0;
        pRs = m_pCon->Execute(sql, &vRecords, -1);
		m_nRecordsAffected = vRecords.lVal;
		m_nModifiedCount += m_nRecordsAffected;
		TRACE2("> ConfigDB ExecuteSQL: %s , Affected=%ld\n", sql, m_nRecordsAffected);
    }
    catch (_com_error &e)
    {
        DbFunc::PrintComError(e, file, line, sql);
        throw CString();
    }

    return pRs;
}

long Cx_CfgDatabase::GetRecordsAffected()
{
	return m_nRecordsAffected;
}

Ix_SQLParser* Cx_CfgDatabase::GetSQLParser()
{
	return m_pSQLParser;
}

bool Cx_CfgDatabase::GetRecordNewID(ULONG& newid, const std::wstring& table, 
									const std::wstring& field)
{
	CString sql;

	sql.Format(L"SELECT max(%s) FROM %s", field.c_str(), table.c_str());
	newid = 0;

	try
	{
		_RecordsetPtr pRs = EXECUTESQL(sql);
		if (pRs->adoEOF)
			newid = 1;
		else
			newid = 1 + DbFunc::GetLong(pRs->GetFields()->GetItem(0L)->GetValue());
	}
	CATCH_DB_STR_ERROR;

	return newid != 0;
}

bool Cx_CfgDatabase::GetRecordCount(long& count, const std::wstring& sqlSelect)
{
	ASSERT_MESSAGE(StrStrIW(sqlSelect.c_str(), L"SELECT ") == sqlSelect.c_str(), 
		"The SQL command must contains 'SELECT' keyword.");
	ASSERT_MESSAGE(StrStrIW(sqlSelect.c_str(), L"FROM ") != NULL, 
		"The SQL command must contains 'FROM' keyword.");

	std::wstring wstrSQL(L"SELECT count(*) ");
	wstrSQL += StrStrIW(sqlSelect.c_str(), L"FROM ");

	try
	{
		_RecordsetPtr pRs = EXECUTESQL(wstrSQL.c_str());
		count = DbFunc::GetLong(pRs->GetFields()->GetItem(0L)->GetValue());
		return true;
	}
	CATCH_DB_STR_ERROR;

	count = 0;
	return false;
}

void Cx_CfgDatabase::CreateNullSection(Cx_Interface<Ix_ConfigSection>& pIFSec)
{
	Cx_SimpleObject<Cx_CfgDbSection>::Create(pIFSec)->InitializeNullObject(this);
}

static std::wstring EnsureSQLHasSelect(const std::wstring& sql)
{
	if (DbFunc::IsDBName(sql.c_str()))
	{
		std::wstring sqlSelect(L"SELECT * FROM ");
		sqlSelect += sql;
		return sqlSelect;
	}

	ASSERT_MESSAGE(StrStrIW(sql.c_str(), L"SELECT ") == sql.c_str(), 
		"The SQL command must contains 'SELECT' keyword.");

	return sql;
}

Cx_Section Cx_CfgDatabase::OpenRecordset(const std::wstring& sqlSelect)
{
	Cx_Interface<Ix_ConfigSection> pIFRet;
	Cx_CfgRecordset* pRecordset = Cx_SimpleObject<Cx_CfgRecordset>::Create(pIFRet);

	pRecordset->InitializeBySQL(this, EnsureSQLHasSelect(sqlSelect));

	return pIFRet;
}

Cx_Section Cx_CfgDatabase::GetSection(LPCWSTR sqlSelect, bool)
{
	return OpenRecordset(sqlSelect);
}

Cx_Section Cx_CfgDatabase::GetSection(Ix_ConfigSection* pParent, LPCWSTR sqlSelect, 
									  LPCWSTR field, ULONG condValue, bool)
{
	return GetSection(pParent, sqlSelect, field, condValue, L"", 0L);
}

Cx_Section Cx_CfgDatabase::GetSection(Ix_ConfigSection* pParent, LPCWSTR pszNodeName, 
									  LPCWSTR field, LPCWSTR pszAttrValue, bool)
{
	return GetSection(pParent, pszNodeName, field, pszAttrValue, L"", L"");
}

Cx_Section Cx_CfgDatabase::GetSection(Ix_ConfigSection* pParent, LPCWSTR sqlSelect, 
									  LPCWSTR field, LPCWSTR condValue, 
									  LPCWSTR field2Name, LPCWSTR condValue2, bool)
{
	ASSERT_MESSAGE(NULL == pParent, "Database::GetSection(pParent, ...): pParent must be NULL");
	
	std::wostringstream sql;

	sql << EnsureSQLHasSelect(sqlSelect);

	if (StrStrIW(sqlSelect, L"WHERE ") != NULL)
	{
		sql << L" AND ";
	}
	else
	{
		sql << L" WHERE ";
	}

	ASSERT_MESSAGE(DbFunc::IsDBName(field), "Invalid field name.");
	sql << field << L"='" << condValue << L"'";

	if (*field2Name != 0)
	{
		ASSERT_MESSAGE(DbFunc::IsDBName(field2Name), "Invalid field name.");
		sql << field2Name << L"='" << condValue2 << L"'";
	}

	return OpenRecordset(sql.str());
}

Cx_Section Cx_CfgDatabase::GetSection(Ix_ConfigSection* pParent, LPCWSTR sqlSelect, 
									  LPCWSTR field, ULONG condValue, 
									  LPCWSTR field2Name, ULONG condValue2, bool)
{
	ASSERT_MESSAGE(NULL == pParent, "Database::GetSection(pParent, ...): pParent must be NULL");
	
	std::wostringstream sql;

	sql << EnsureSQLHasSelect(sqlSelect);

	if (StrStrIW(sqlSelect, L"WHERE ") != NULL)
	{
		sql << L" AND ";
	}
	else
	{
		sql << L" WHERE ";
	}

	ASSERT_MESSAGE(DbFunc::IsDBName(field), "Invalid field name.");
	sql << field << L"=" << condValue;

	if (*field2Name != 0)
	{
		ASSERT_MESSAGE(DbFunc::IsDBName(field2Name), "Invalid field name.");
		sql << L" AND " << field2Name << L"=" << condValue2;
	}

	return OpenRecordset(sql.str());
}

long Cx_CfgDatabase::GetSectionCount(Ix_ConfigSection* pParent, LPCWSTR)
{
	Cx_CfgRecordset* pRecordset = dynamic_cast<Cx_CfgRecordset*>(pParent);
	ASSERT_MESSAGE(pRecordset != NULL, "Database::GetSectionCount(pParent, ...): "
		"pParent must be recordset object returnd by GetSection()");

	return pRecordset->GetRecordCount();
}

Cx_Section Cx_CfgDatabase::GetSectionByIndex(Ix_ConfigSection* pParent, LPCWSTR, long nIndex)
{
	Cx_CfgRecordset* pRecordset = dynamic_cast<Cx_CfgRecordset*>(pParent);
	ASSERT_MESSAGE(pRecordset != NULL, "Database::GetSectionByIndex(pParent, ...): "
		"pParent must be recordset object returnd by GetSection()");

	Cx_Interface<Ix_ConfigSection> pIFRet;
	Cx_CfgRecord* pRecord = NULL;

	if (pRecordset->SetCurIndex(nIndex))
	{
		try
		{
			_RecordsetPtr pRs = pRecordset->GetCurRecord();
			if (pRs != NULL && !pRs->adoEOF)
			{
				pRecord = Cx_SimpleObject<Cx_CfgRecord>::Create(pIFRet);
				pRecord->InitializeForRead(this, pRs, pRecordset->GetSQLCommand());
			}
		}
		CATCH_DB_STR_ERROR;
	}

	if (NULL == pRecord)
	{
		CreateNullSection(pIFRet);
	}

	return pIFRet;
}

Cx_Section Cx_CfgDatabase::AddSection(Ix_ConfigSection* pParent, LPCWSTR table)
{
	ASSERT_MESSAGE(NULL == pParent, "Database::AddSection(pParent, ...): pParent must be NULL");
	ASSERT_MESSAGE(DbFunc::IsDBName(table), "Invalid table name.");

	Cx_Interface<Ix_ConfigSection> pIFRet;
	Cx_CfgRecord* pRecord = Cx_SimpleObject<Cx_CfgRecord>::Create(pIFRet);

	pRecord->InitializeForAdd(this, table);

	return pIFRet;
}

bool Cx_CfgDatabase::RemoveSection(Ix_ConfigSection*)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Database::RemoveSection(Ix_ConfigSection*)]");
	return false;
}

Cx_Section Cx_CfgDatabase::GetParentSection(Ix_ConfigSection*)
{
	ASSERT_MESSAGE(0, "The function is not supportable. [Database::GetParentSection(Ix_ConfigSection*)]");
	return Cx_Section();
}

long Cx_CfgDatabase::RemoveChildren(Ix_ConfigSection* pParent, LPCWSTR table, 
									LPCWSTR field, LPCWSTR condValue)
{
	ASSERT_MESSAGE(NULL == pParent, "Database::RemoveChildren(pParent, ...): pParent must be NULL");
	ASSERT_MESSAGE(DbFunc::IsDBName(table), "Invalid table name.");
	ASSERT_MESSAGE(DbFunc::IsDBName(field), "Invalid field name.");

	std::wostringstream sql;

	sql << L"DELETE FROM " << table << L" WHERE ";
	sql << field << L"='" << condValue << L"'";

	try
	{
		_RecordsetPtr pRs = EXECUTESQL(sql.str().c_str());
		return m_nRecordsAffected;
	}
	CATCH_DB_STR_ERROR;

	return 0;
}

long Cx_CfgDatabase::RemoveChildren(Ix_ConfigSection* pParent, LPCWSTR table, 
									LPCWSTR field, ULONG condValue)
{
	ASSERT_MESSAGE(NULL == pParent, "Database::RemoveChildren(pParent, ...): pParent must be NULL");
	ASSERT_MESSAGE(DbFunc::IsDBName(table), "Invalid table name.");
	ASSERT_MESSAGE(DbFunc::IsDBName(field), "Invalid field name.");

	std::wostringstream sql;

	sql << L"DELETE FROM " << table << L" WHERE ";
	sql << field << L"=" << condValue;

	try
	{
		_RecordsetPtr pRs = EXECUTESQL(sql.str().c_str());
		return m_nRecordsAffected;
	}
	CATCH_DB_STR_ERROR;

	return 0;
}

void Cx_CfgDatabase::BeginTransaction()
{
	ASSERT_MESSAGE(0, "The function is not supportable. Please use Record::BeginTransaction().");
}

bool Cx_CfgDatabase::EndTransaction()
{
	ASSERT_MESSAGE(0, "The function is not supportable. Please use Record::EndTransaction().");
	return false;
}

ULONG Cx_CfgDatabase::GetModifiedCount()
{
	return m_nModifiedCount;
}
