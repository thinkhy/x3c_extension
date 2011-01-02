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
