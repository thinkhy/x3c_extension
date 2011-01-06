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

/*! \file Cx_CfgDatabase.h
 *  \brief �������ݿ���ʵ�ʵ���� Cx_CfgDatabase
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.9.25
 */
#ifndef _X3_CONFIGDB_CFGDATABASE_H
#define _X3_CONFIGDB_CFGDATABASE_H

#include <Ix_ConfigData.h>
#include <Ix_ConfigTransaction.h>
#include "Ix_InitDatabase.h"
#include "Ix_SQLParser.h"

class Cx_CfgRecordset;

//! ���ݿ���ʵ�ʵ����
class Cx_CfgDatabase
	: public Ix_ConfigData
	, public Ix_ConfigTransaction
	, public Ix_InitDatabase
{
public:
	//! ���캯��
	Cx_CfgDatabase();

	//! �����������Զ��ر����ݿ�
	virtual ~Cx_CfgDatabase();

public:
	//! ִ��SQL��䣬���ؼ�¼��
	_RecordsetPtr ExecuteSQL(LPCTSTR sql, LPCSTR file, long line);

	//! ��������һ���Ӱ�������
	long GetRecordsAffected();

	//! �õ�һ����������ֶ�(����)���¼�¼ID
	bool GetRecordNewID(ULONG& newid, const std::wstring& table, 
		const std::wstring& field);

	//! ����һ��SELECT��䣬��ѯ��¼����
	bool GetRecordCount(long& count, const std::wstring& sqlSelect);

	//! ִ��SQL��䣬���ؼ�¼��
	ConfigIOSection OpenRecordset(const std::wstring& sqlSelect);

	//! ����SQLָ������
	Ix_SQLParser* GetSQLParser();

protected:
	//! �ر����ݿ�����
	void CloseConnection();

	//! �����սڵ����
	void CreateNullSection(Cx_Interface<Ix_ConfigSection>& pIFSec);

protected:
	_ConnectionPtr		m_pCon;				//!< ���ݿ����Ӷ���
	Ix_SQLParser*		m_pSQLParser;		//!< SQLָ������
	long				m_nRecordsAffected;	//!< ����һ���Ӱ�������
	long				m_nModifiedCount;	//!< ���ݿ��¼�Ķ�����

protected:
	// Ix_InitDatabase
	virtual bool OpenConnection(const std::wstring& connection, 
		Ix_SQLParser* pSQLParser);

	// From Ix_ConfigTransaction
	virtual void BeginTransaction();
	virtual bool EndTransaction();
	virtual ULONG GetModifiedCount();

// From Ix_ConfigData
protected:
	//! ִ��SQL��䣬���ؼ�¼��
	/*! �����������ڶ�ȡ������¼������ʹ�ü�¼���� GetSectionByIndex() ���б�����ȡ���� GetSectionByIndex() �Ĵ���ʾ����
		\param sqlSelect SQL��䣬�ԡ�SELECT ����ʼ��������FROM �����ɰ�����ѯ����������������
		\param ignore ���Ա�����
		\return ��¼������ Cx_CfgRecordset ��ն��� Cx_CfgDbSection
	*/
	ConfigIOSection GetSection(LPCWSTR sqlSelect, bool ignore = true);

	//! ִ��SQL���Ͳ�ѯ���������ؼ�¼��
	/*! �����������ڸ��ݱ���������Ҳ��޸ļ�¼�����磺 \code
	CConfigIOSection secRecordset(pIFDb->GetSection(NULL, L"book", L"id", 1));
	CConfigIOSection secRec(secRecordset.GetSectionByIndex(L"", 0));
	secRec->SetString(L"title", L"test3");
	secRec->SetString(L"create_time", L"@CURDATE()");
	secRec->SetDate(L"update_date", 2010, 3, 10);
	VERIFY(CConfigTransaction(Cx_Ptr(secRec.P())).Submit());
		\endcode
		\param nullP ����ΪNULL
		\param sqlSelect SQL��䣬�ԡ�SELECT ����ʼ��������FROM �����ɰ�����ѯ�����������
		\param field ��ѯ�����еĵ�һ���Ƚ��ֶ�
		\param condValue field��Ӧ��ֵ�������ڲ�ѯ�бȽ����
		\param ignore ���Ա�����
		\return ��¼������ Cx_CfgRecordset ��ն��� Cx_CfgDbSection
	*/
	ConfigIOSection GetSection(
		Ix_ConfigSection* nullP, LPCWSTR sqlSelect, 
		LPCWSTR field, ULONG condValue, 
		bool ignore = true);

	//! ִ��SQL���Ͳ�ѯ���������ؼ�¼��
	/*! �����������ڶ�ȡ������¼������ʹ�ü�¼���� GetSectionByIndex() ���б�����ȡ���� GetSectionByIndex() �Ĵ���ʾ����
		\param nullP ����ΪNULL
		\param sqlSelect SQL��䣬�ԡ�SELECT ����ʼ��������FROM �����ɰ�����ѯ�����������
		\param field ��ѯ�����еĵ�һ���Ƚ��ֶ�
		\param condValue field��Ӧ��ֵ�������ڲ�ѯ�бȽ����
		\param ignore ���Ա�����
		\return ��¼������ Cx_CfgRecordset ��ն��� Cx_CfgDbSection
	*/
	ConfigIOSection GetSection(
		Ix_ConfigSection* nullP, LPCWSTR sqlSelect, 
		LPCWSTR field, LPCWSTR condValue, 
		bool ignore = true);

	//! ִ��SQL���Ͳ�ѯ���������ؼ�¼��
	/*!
		\param nullP ����ΪNULL
		\param sqlSelect SQL��䣬�ԡ�SELECT ����ʼ��������FROM �����ɰ�����ѯ�����������
		\param field ��ѯ�����еĵ�һ���Ƚ��ֶ�
		\param condValue field��Ӧ��ֵ�������ڲ�ѯ�бȽ����
		\param fieldName2 ��ѯ�����еĵڶ����Ƚ��ֶΣ�Ϊ������Ը�����
		\param condValue2 fieldName2��Ӧ��ֵ�������ڲ�ѯ�бȽ���ȣ�fieldName2�ǿ�ʱ��Ч
		\param ignore ���Ա�����
		\return ��¼������ Cx_CfgRecordset ��ն��� Cx_CfgDbSection
	*/
	ConfigIOSection GetSection(
		Ix_ConfigSection* nullP, LPCWSTR sqlSelect, 
		LPCWSTR field, LPCWSTR condValue, 
		LPCWSTR fieldName2, LPCWSTR condValue2, 
		bool ignore = true);

	//! ִ��SQL���Ͳ�ѯ���������ؼ�¼��
	/*!
		\param nullP ����ΪNULL
		\param sqlSelect SQL��䣬�ԡ�SELECT ����ʼ��������FROM �����ɰ�����ѯ�����������
		\param field ��ѯ�����еĵ�һ���Ƚ��ֶ�
		\param condValue field��Ӧ��ֵ�������ڲ�ѯ�бȽ����
		\param fieldName2 ��ѯ�����еĵڶ����Ƚ��ֶΣ�Ϊ������Ը�����
		\param condValue2 fieldName2��Ӧ��ֵ�������ڲ�ѯ�бȽ���ȣ�fieldName2�ǿ�ʱ��Ч
		\param ignore ���Ա�����
		\return ��¼������ Cx_CfgRecordset ��ն��� Cx_CfgDbSection
	*/
	ConfigIOSection GetSection(
		Ix_ConfigSection* nullP, LPCWSTR sqlSelect, 
		LPCWSTR field, ULONG condValue, 
		LPCWSTR fieldName2, ULONG condValue2, 
		bool ignore = true);

	//! ���ؼ�¼���ļ�¼����
	/*! ����ʾ���� \code
	CConfigIOSection secRecordset(pIFDb->GetSection(NULL, L"book", L"id", 1));
	if (1 == secRecordset.GetSectionCount(L"")) { }
		\endcode
		\param pRecordset ��¼������ͨ�� GetSection() �õ���
		\param ignore ���Ա�����
		\return ��¼����
	*/
	long GetSectionCount(Ix_ConfigSection* pRecordset, LPCWSTR ignore);

	//! ����һ����¼����ָ����ŵļ�¼����
	/*! ���������ڶԼ�¼�����б�����ȡ������ʾ���� \code
	CConfigIOSection secRecordset(pIFDb->GetSection(
		L"SELECT id,title FROM article WHERE id=4"));
	for (long iRec = 0; iRec < 99; iRec++)
	{
		CConfigIOSection secRec(secRecordset.GetSectionByIndex(L"", iRec));
		if (!secRec->IsValid())
			break;
		ULONG nID = secRec->GetUInt32(L"id");
		std::wstring wstrName = secRec->GetString(L"title");
	}
		\endcode
		\param pRecordset ��¼������ͨ�� GetSection() �õ���
		\param ignore ���Ա�����
		\param index ��¼����ţ�ȡֵ����Ϊ0����¼���ĵ�ǰ��š���ǰ���+1
		\return ��¼���� Cx_CfgRecord ,��Ϊ��
	*/
	ConfigIOSection GetSectionByIndex(
		Ix_ConfigSection* pRecordset, LPCWSTR ignore, long index);

	//! ����һ���¼�¼�������ø����ֶε�ֵ
	/*! ��ʱ��δ�����ݿ������Ӽ�¼��
		����ʹ�� \@NEWID ���ĳ���ֶ�ȡֵΪ(���ID+1)�����磺 \code
	CConfigIOSection secRec(pIFDb->AddSection(NULL, L"table"));
	secNewRec->SetString(L"id", L"@NEWID");
	secNewRec->SetString(L"title", L"test12");
	VERIFY(CConfigTransaction(Cx_Ptr(secNewRec.P())).Submit());
	ULONG nID = secNewRec->GetUInt32(L"id");
		\endcode
		\param nullP ����ΪNULL
		\param table ���ݿ���������硰book��
		\return �¼�¼���� Cx_CfgRecord
	*/
	ConfigIOSection AddSection(Ix_ConfigSection* nullP, LPCWSTR table);

	//! ��֧�ֱ�����
	bool RemoveSection(Ix_ConfigSection*);

	//! ɾ��ָ�������ļ�¼
	/*! ����ʾ���� \code
	pIFDb->RemoveChildren(NULL, L"book", L"type", L"sometype");
		\endcode
		\param nullP ����ΪNULL
		\param table ���ݿ����
		\param field ��ѯ�����еĵ�һ���Ƚ��ֶΣ�ͨ���������ֶ�
		\param condValue field��Ӧ��ֵ�������ڲ�ѯ�бȽ����
		\return ɾ���ļ�¼��
	*/
	long RemoveChildren(Ix_ConfigSection* nullP, LPCWSTR table, 
		LPCWSTR field = L"", LPCWSTR condValue = L"");

	//! ɾ��ָ�������ļ�¼
	/*! ����ʾ���� \code
	pIFDb->RemoveChildren(NULL, L"book", L"id", 1);
		\endcode
		\param nullP ����ΪNULL
		\param table ���ݿ����
		\param field ��ѯ�����еĵ�һ���Ƚ��ֶΣ�ͨ���������ֶ�
		\param condValue field��Ӧ��ֵ�������ڲ�ѯ�бȽ����
		\return ɾ���ļ�¼��
	*/
	long RemoveChildren(Ix_ConfigSection* nullP, LPCWSTR table, 
		LPCWSTR field, ULONG condValue);

	//! �õ�һ�����ݽڵ����һ���ڵ�(��������֧��)
	ConfigIOSection GetParentSection(Ix_ConfigSection*);
};

#endif // _X3_CONFIGDB_CFGDATABASE_H
