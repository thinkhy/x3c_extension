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

#ifndef _X3_LOGWRITER_LOGOBSERVER_H
#define _X3_LOGWRITER_LOGOBSERVER_H

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
	std::wstring	m_wstrPath;			// ��־�ļ�Ŀ¼��ĩβ��б�ܺ�
	std::wstring	m_wstrAppName;		// Ӧ�ñ�ʶ����
	bool			m_bInited;			// �Ƿ��ѳ�ʼ������־�ļ�
	long			m_nGroupLevel;		// ��ǰ��־��ļ���
};

#endif // _X3_LOGWRITER_LOGOBSERVER_H
