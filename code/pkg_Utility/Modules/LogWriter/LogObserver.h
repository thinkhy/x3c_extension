#pragma once

#include <ILogObserver.h>

#include <log4cplus/logger.h>
using namespace log4cplus;

class CLogObserver : public CLogObserverImpl
{
public:
	CLogObserver();
	virtual ~CLogObserver();

protected:
	virtual void OnPushGroup(long nLevel, 
		const std::wstring& wstrMsg, const std::wstring& wstrExtra, 
		const std::wstring& wstrModule, const std::wstring& wstrID);
	virtual void OnPopGroup(long nLevel);
	virtual void OnWriteLog(int nType, 
		const std::wstring& wstrMsg, const std::wstring& wstrExtra, 
		const std::wstring& wstrModule, const std::wstring& wstrID, 
		const std::wstring& wstrFile, long nLine);

private:
	Logger GetLogger();
	void InitLogFile();
	void MakerInitVars();
	void WritePropFile(LPCWSTR pszFileName);

private:
	std::wstring	m_wstrPath;			// 日志文件目录，末尾有斜杠号
	std::wstring	m_wstrAppName;		// 应用标识名称
	bool			m_bInited;			// 是否已初始化了日志文件
	long			m_nGroupLevel;		// 当前日志组的级别
};
