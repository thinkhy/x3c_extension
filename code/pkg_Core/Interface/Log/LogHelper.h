/*! \file LogHelper.h
 *  \brief ������־����� LOG_WARNING �Ⱥ�� CAutoLogGroup
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_LOG_LOGHELPER_H_
#define X3_LOG_LOGHELPER_H_

#include "XComPtr.h"
#include "Ix_LogManager.h"

#pragma warning (push, 1)
#include <sstream>		// std::wostringstream
#pragma warning (pop)

// LOG_DEBUG(msg)
// LOG_DEBUG2(name, extra)
// LOG_INFO(msg)
// LOG_INFO2(name, extra)
// LOG_WARNING(msg)
// LOG_WARNING2(name, extra)
// LOG_ERROR(msg)
// LOG_ERROR2(name, extra)
// LOG_FATAL(msg)
// LOG_FATAL2(name, extra)
// LOG_EVENT_ANSI(name, extra, type, file, line)
//
// void RegisterLogObserver(ILogObserver* observer)
// void UnRegisterLogObserver(ILogObserver* observer)
// CAutoLogGroup(msg)


//! ���������Ϣ
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\param msg Ҫ�������Ϣ��Ϊ����������ֵ��Unicode�ַ���(������ANSI��)��
		�������@��ͷ���ϡ�Module:StrID����ʽ���Զ���Ϊ���ػ�����
*/
#define LOG_DEBUG(msg)	\
	LOG_EVENT_(msg, kLogType_Debug, __FILE__, __LINE__)


//! ���������Ϣ�͸�����Ϣ
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\param name Unicode�ַ�������@��ͷ���ϡ�Module:StrID����ʽ
	\param extra ���ӵ���������Ϣ��Ϊ����������ֵ��Unicode�ַ���(������ANSI��)
*/
#define LOG_DEBUG2(name, extra)		\
	LOG_EVENT_2(name, extra, kLogType_Debug, __FILE__, __LINE__)


//! �����ͨ��Ϣ
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\param msg Ҫ�������Ϣ��Ϊ����������ֵ��Unicode�ַ���(������ANSI��)��
		�������@��ͷ���ϡ�Module:StrID����ʽ���Զ���Ϊ���ػ�����
*/
#define LOG_INFO(msg)	\
	LOG_EVENT_(msg, kLogType_Info, __FILE__, __LINE__)


//! �����ͨ��Ϣ�͸�����Ϣ
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\param name Unicode�ַ�������@��ͷ���ϡ�Module:StrID����ʽ
	\param extra ���ӵ���������Ϣ��Ϊ����������ֵ��Unicode�ַ���(������ANSI��)
*/
#define LOG_INFO2(name, extra)	\
	LOG_EVENT_2(name, extra, kLogType_Info, __FILE__, __LINE__)


//! ���������Ϣ
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\param msg Ҫ�������Ϣ��Ϊ����������ֵ��Unicode�ַ���(������ANSI��)��
		�������@��ͷ���ϡ�Module:StrID����ʽ���Զ���Ϊ���ػ�����
*/
#define LOG_WARNING(msg)		\
	LOG_EVENT_(msg, kLogType_Warning, __FILE__, __LINE__)


//! ���������Ϣ�͸�����Ϣ
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\param name Unicode�ַ�������@��ͷ���ϡ�Module:StrID����ʽ
	\param extra ���ӵ���������Ϣ��Ϊ����������ֵ��Unicode�ַ���(������ANSI��)
*/
#define LOG_WARNING2(name, extra)	\
	LOG_EVENT_2(name, extra, kLogType_Warning, __FILE__, __LINE__)


//! ���������Ϣ
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\param msg Ҫ�������Ϣ��Ϊ����������ֵ��Unicode�ַ���(������ANSI��)��
		�������@��ͷ���ϡ�Module:StrID����ʽ���Զ���Ϊ���ػ�����
*/
#define LOG_ERROR(msg)	\
	LOG_EVENT_(msg, kLogType_Error, __FILE__, __LINE__)


//! ���������Ϣ�͸�����Ϣ
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\param name Unicode�ַ�������@��ͷ���ϡ�Module:StrID����ʽ
	\param extra ���ӵ���������Ϣ��Ϊ����������ֵ��Unicode�ַ���(������ANSI��)
*/
#define LOG_ERROR2(name, extra)		\
	LOG_EVENT_2(name, extra, kLogType_Error, __FILE__, __LINE__)


//! ������ش�����Ϣ
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\param msg Ҫ�������Ϣ��Ϊ����������ֵ��Unicode�ַ���(������ANSI��)��
		�������@��ͷ���ϡ�Module:StrID����ʽ���Զ���Ϊ���ػ�����
*/
#define LOG_FATAL(msg)		\
	LOG_EVENT_(msg, kLogType_Fatal, __FILE__, __LINE__)


//! ������ش�����Ϣ�͸�����Ϣ
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\param name Unicode�ַ�������@��ͷ���ϡ�Module:StrID����ʽ
	\param extra ���ӵ���������Ϣ��Ϊ����������ֵ��Unicode�ַ���(������ANSI��)
*/
#define LOG_FATAL2(name, extra)		\
	LOG_EVENT_2(name, extra, kLogType_Fatal, __FILE__, __LINE__)

//! ע����־����۲���
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\param observer Ҫע��Ĺ۲���
	\return �Ƿ�ע��ɹ�
	\see UnRegisterLogObserver
*/
inline bool RegisterLogObserver(ILogObserver* observer)
{
	Cx_Interface<Ix_LogManager> pIFManager(CLSID_LogManager);
	if (pIFManager.IsNotNull())
	{
		return pIFManager->RegisterObserver(observer);
	}
	return false;
}

//! ע����־����۲���
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\see RegisterLogObserver
*/
inline void UnRegisterLogObserver(ILogObserver* observer)
{
	Cx_Interface<Ix_LogManager> pIFManager(CLSID_LogManager);
	if (pIFManager.IsNotNull())
	{
		pIFManager->UnRegisterObserver(observer);
	}
}

//! �Զ���ʼһ����־�ĸ����࣬�����ں����ж���ֲ�����
/*!
	\ingroup _GROUP_PLUGIN_LOG_
*/
class CAutoLogGroup
{
public:
	//! ���캯�����Զ���ʼ�µ�һ����־
	/*!
		\param msg ��־������֣��������@��ͷ���ϡ�Module:StrID����ʽ���Զ���Ϊ���ػ�����
		\param extra ���ӵ���������Ϣ
	*/
	CAutoLogGroup(LPCWSTR msg, LPCWSTR extra = NULL)
	{
		Cx_Interface<Ix_LogManager> pIFManager(CLSID_LogManager);
		if (pIFManager.IsNotNull())
		{
			pIFManager->PushGroup(msg, extra);
		}
	}
	//! �����������Զ�����һ����־
	~CAutoLogGroup()
	{
		Cx_Interface<Ix_LogManager> pIFManager(CLSID_LogManager);
		if (pIFManager.IsNotNull())
		{
			pIFManager->PopGroup();
		}
	}
};

#pragma warning(disable:4127)	// conditional expression is constant

#define LOG_EVENT_(msg, type, file, line)					\
	do {														\
	Cx_Interface<Ix_LogManager> pIFManager(CLSID_LogManager);	\
	if (pIFManager.IsNotNull())									\
	{															\
		std::wostringstream buf;								\
		buf << msg;											\
		pIFManager->WriteLog(type, buf.str().c_str(), L"", file, line);	\
	}} while (0)

#define LOG_EVENT_2(name, extra, type, file, line)	\
	do {														\
	Cx_Interface<Ix_LogManager> pIFManager(CLSID_LogManager);	\
	if (pIFManager.IsNotNull())									\
	{															\
		std::wostringstream buf;								\
		buf << extra;										\
		pIFManager->WriteLog(type, name, buf.str().c_str(), file, line);	\
	}} while (0)

//! ���ANSI������־��Ϣ
/*!
	\ingroup _GROUP_PLUGIN_LOG_
	\param name ANSI�ַ�������@��ͷ���ϡ�Module:StrID����ʽ
	\param extra ���ӵ���������Ϣ��Ϊ����������ֵ��ANSI�ַ���
	\param type ��־���ͣ��� kLogType
	\param file Դ�����ļ���, һ��ȡΪ __FILE__
	\param line Դ�����к�, һ��ȡΪ __LINE__
*/
#define LOG_EVENT_ANSI(name, extra, type, file, line)	\
	do {														\
	Cx_Interface<Ix_LogManager> pIFManager(CLSID_LogManager);	\
	if (pIFManager.IsNotNull())									\
	{															\
		std::ostringstream buf;								\
		buf << extra;										\
		pIFManager->WriteLog(type, name, buf.str().c_str(), file, line);	\
	}} while (0)

#endif // X3_LOG_LOGHELPER_H_
