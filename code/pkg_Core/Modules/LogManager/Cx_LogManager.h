#pragma once

#include <Ix_LogManager.h>

class Cx_LogManager
	: public Ix_LogManager
{
protected:
	Cx_LogManager();
	virtual ~Cx_LogManager();

protected:
	virtual bool RegisterObserver(ILogObserver* observer);
	virtual void UnRegisterObserver(ILogObserver* observer);
	virtual bool PushGroup(LPCWSTR pszMsg, LPCWSTR pszExtra);
	virtual bool PopGroup();
	virtual bool WriteLog(kLogType nType, LPCWSTR pszMsg, 
		LPCWSTR pszExtra, LPCSTR pszFile, long nLine);
	virtual bool WriteLog(kLogType nType, LPCSTR pszMsg, 
		LPCSTR pszExtra, LPCSTR pszFile, long nLine);
	virtual int CrtDbgReport(LPCSTR szMsg, LPCSTR szFile, long nLine);

private:
	LPCSTR TrimFileName(LPCSTR pszFile);
	bool CheckMsgParam(std::wstring& wstrMsg, std::wstring& wstrExtra, 
		std::wstring& wstrModule, std::wstring& wstrID, 
		LPCWSTR pszMsg, LPCWSTR pszExtra);

private:
	typedef std::vector<ILogObserver*>::iterator ObserverIt;
	std::vector<ILogObserver*>		m_arrObserver;
	long							m_nGroupLevel;
};
