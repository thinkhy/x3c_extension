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

/*! \file Ix_LogManager.h
 *  \brief ������־�������Ľӿ� Ix_LogManager
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_LOG_ILOGMANAGER_H_
#define X3_LOG_ILOGMANAGER_H_

#include "Ix_Object.h"

//! ��־����
enum kLogType
{
	kLogType_Debug,		//!< ������Ϣ
	kLogType_Info,		//!< ��ͨ��Ϣ
	kLogType_Warning,	//!< ������Ϣ
	kLogType_Error,		//!< ������Ϣ
	kLogType_Fatal		//!< ���ش���
};

interface ILogObserver;

const XCLSID CLSID_LogManager("bbf48a97-9aef-4368-9dc0-2d2937c326ec");

//! ��־�������ӿ�
/*! �ýӿڹ� RegisterLogObserver, CAutoLogGroup, LOG_WARNING ��ʹ�á�
	\interface Ix_LogManager
	\ingroup _GROUP_PLUGIN_LOG_
	\see CLSID_LogManager, Ix_StringTable
*/
interface Ix_LogManager
{
	//! ע����־����۲���
	/*!
		\param observer Ҫע��Ĺ۲���
		\return �Ƿ�ע��ɹ�
		\see RegisterLogObserver, UnRegisterObserver
	*/
	virtual bool RegisterObserver(ILogObserver* observer) = 0;

	//! ע����־����۲���
	/*!
		\param observer Ҫע���Ĺ۲���
		\see UnRegisterLogObserver, RegisterObserver
	*/
	virtual void UnRegisterObserver(ILogObserver* observer) = 0;

	//! ��ʼ�µ�һ����־
	/*!
		\param msg ��־������֣��������@��ͷ���ϡ�Module:StrID����ʽ���Զ���Ϊ���ػ�����
		\param extra ���ӵ���������Ϣ
		\return �Ƿ�ִ�гɹ�
		\see CAutoLogGroup, PopGroup
	*/
	virtual bool PushGroup(LPCWSTR msg, LPCWSTR extra) = 0;

	//! ����һ����־
	/*!
		\return �Ƿ�ִ�гɹ�
		\see CAutoLogGroup, PushGroup
	*/
	virtual bool PopGroup() = 0;

	//! �����־��Ϣ
	/*!
		\param type ��־����
		\param msg ��Ϣ���֣��������@��ͷ���ϡ�Module:StrID����ʽ���Զ���Ϊ���ػ�����
		\param extra ���ӵĿ�ѡ���֣�����������ӵ���������Ϣ
		\param file Դ�����ļ���, __FILE__
		\param line Դ�����к�, __LINE__
		\return �Ƿ�ִ�гɹ�
		\see LOG_WARNING, LOG_WARNING2, LOG_ERROR, LOG_ERROR2
	*/
	virtual bool WriteLog(kLogType type, LPCWSTR msg, 
		LPCWSTR extra, LPCSTR file, long line) = 0;

	//! �����־��Ϣ(ANSI��)
	/*!
		\param type ��־����
		\param msg ��Ϣ���֣��������@��ͷ���ϡ�Module:StrID����ʽ���Զ���Ϊ���ػ�����
		\param extra ���ӵĿ�ѡ���֣�����������ӵ���������Ϣ
		\param file Դ�����ļ���, __FILE__
		\param line Դ�����к�, __LINE__
		\return �Ƿ�ִ�гɹ�
		\see LOG_WARNING, LOG_WARNING2, LOG_ERROR, LOG_ERROR2
	*/
	virtual bool WriteLog(kLogType type, LPCSTR msg, 
		LPCSTR extra, LPCSTR file, long line) = 0;

	//! ��ʾ���Դ�����Ϣ���� XCrtDbgReport() ����
	virtual int CrtDbgReport(LPCSTR msg, LPCSTR file, long line) = 0;
};

#endif // X3_LOG_ILOGMANAGER_H_
