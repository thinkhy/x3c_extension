#include "stdafx.h"
#include "Cx_FileTransaction.h"
#include "FileTransaction.h"

static long s_nLevel = 0;

Cx_FileTransaction::Cx_FileTransaction()
{
	m_lLevel = InterlockedIncrement(&s_nLevel);
	if (1 == m_lLevel)
	{
		CFileTransactions::Instance().Reset();
	}
}

Cx_FileTransaction::~Cx_FileTransaction()
{
	ASSERT(m_lLevel == s_nLevel);
	if (0 == InterlockedDecrement(&s_nLevel))
	{
		CFileTransactions::Instance().EndTransaction(true);
	}
}

void Cx_FileTransaction::Rollback()
{
	CFileTransactions::Instance().EndTransaction(false);
}

long Cx_FileTransaction::GetLevel() const
{
	return m_lLevel;
}

bool Cx_FileTransaction::IsRollbacking() const
{
	return CFileTransactions::Instance().IsRollbacking();
}

bool Cx_FileTransaction::DeletePathFile(LPCWSTR pszFileName, bool bRecycle)
{
	Cx_Interface<Ix_FileUtility> pIFUtility(CLSID_FileUtility);

	if (NULL == pszFileName || 0 == pszFileName[0]
		|| !pIFUtility->IsPathFileExists(pszFileName))
		return true;

	if (CFileTransactions::Instance().IsRollbacking())
	{
		LOG_ERROR2(LOGHEAD L"IDS_DELETEFILE_ROLLBACK", pszFileName);
		return false;
	}

	std::wstring wstrPath = pIFUtility->GetPathOfFile(pszFileName);
	std::wstring wstrName = pIFUtility->GetFileName(pszFileName);

	WCHAR szTmpFile[MAX_PATH] = { 0 };

	for (int i = 1; i < 1000; i++)
	{
		swprintf_s(szTmpFile, MAX_PATH, L"%s~%s.~%d", 
			wstrPath.c_str(), wstrName.c_str(), i);
		if (!pIFUtility->IsPathFileExists(szTmpFile))
			break;
	}

	bool bRet = pIFUtility->RenamePathFile(pszFileName, szTmpFile);
	if (bRet)
	{
		CFileTransactions::Instance().AddStep(
			new CTransDeleteFile(szTmpFile, bRecycle), 
			new CTransRenameFile(szTmpFile, pszFileName));
	}
	else
	{
		LOG_ERROR2(LOGHEAD L"IDS_DELFILE_FAIL", pszFileName);
		CFileTransactions::Instance().EndTransaction(false);
	}

	return bRet;
}
