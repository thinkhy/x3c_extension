/*! \file ILogObserver.h
 *  \brief ������־����۲��ߵĽӿ� ILogObserver
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_LOG_ILOGOBSERVER_H_
#define X3_LOG_ILOGOBSERVER_H_

#include "Ix_Object.h"

//! ��־����۲��ߵĽӿ�
/*! ʹ�� RegisterLogObserver(ILogObserver*)ע��۲��ߣ�
	ʹ�� UnRegisterLogObserver ע���۲���
	\interface ILogObserver
	\ingroup _GROUP_PLUGIN_LOG_
	\see RegisterLogObserver, UnRegisterLogObserver, CLogObserverImpl
*/
interface ILogObserver
{
	//! ��ʼ�µ�һ����־
	/*!
		\param level �µ�һ����־����ţ���1��ʼ
		\param msg ����Ϣ���ѱ��ػ�
		\param extra ���ӵ���������Ϣ
		\param module ģ����
		\param idname ��ID����
	*/
	virtual void OnPushGroup(long level, 
		const std::wstring& msg, const std::wstring& extra, 
		const std::wstring& module, const std::wstring& idname) = 0;

	//! ����һ����־
	/*!
		\param level Ҫ������һ����־����ţ�����Ӧ�� OnPushGroup ֵͬ
	*/
	virtual void OnPopGroup(long level) = 0;

	//! ��Ӧ��־��Ϣ�����֪ͨ
	/*!
		\param type ��־����, kLogType ö��ֵ
		\param msg ��־������Ϣ���ѱ��ػ�
		\param extra ���ӵ���������Ϣ
		\param module ģ����
		\param idname ��ID����
		\param file Դ�����ļ���
		\param line Դ�����к�
	*/
	virtual void OnWriteLog(int type, 
		const std::wstring& msg, const std::wstring& extra, 
		const std::wstring& module, const std::wstring& idname, 
		const std::wstring& file, long line) = 0;
};

//! ��־����۲��ߵ�Ĭ��ʵ��
/*!
	\ingroup _GROUP_PLUGIN_LOG_
*/
class CLogObserverImpl : public ILogObserver
{
public:
	CLogObserverImpl() {}
	virtual ~CLogObserverImpl() {}

	virtual void OnPushGroup(long level, 
		const std::wstring& msg, const std::wstring& extra, 
		const std::wstring& module, const std::wstring& idname)
	{
		level; msg; extra; module; idname;
	}

	virtual void OnPopGroup(long level)
	{
		level;
	}

	virtual void OnWriteLog(int type, 
		const std::wstring& msg, const std::wstring& extra, 
		const std::wstring& module, const std::wstring& idname, 
		const std::wstring& file, long line)
	{
		type; msg; extra; module; idname; file; line;
	}
};

#endif // X3_LOG_ILOGOBSERVER_H_
