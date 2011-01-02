/*! \file Ix_TempFolder.h
 *  \brief ������ʱĿ¼�����Ľӿ� Ix_TempFolder
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef X3_UTIL_ITEMPFOLDER_H_
#define X3_UTIL_ITEMPFOLDER_H_
#pragma once

#include <Ix_Object.h>

const XCLSID CLSID_TempFolder("6d215195-061e-4c03-827d-8c692c293617");

//! ��ʱĿ¼�����Ľӿ�
/*!
	\interface Ix_TempFolder
	\ingroup _GROUP_UTILITY_
	\see CLSID_TempFolder
*/
interface Ix_TempFolder
{
	//! ���ø�Ŀ¼��Ӱ����������´����Ķ���
	/*!
		\param path ��Ŀ¼��ȫ��
	*/
	virtual void SetRootPath(const std::wstring& path) = 0;

	//! ɾ����������ʱĿ¼
	/*! ��������ñ�����������ʱ��Ŀ¼���ڱ���������ʱ������˳�ʱҲ���Զ�ɾ��
		\return �Ƿ�ɾ���ɹ�
	*/
	virtual bool DeleteFolder() = 0;

	//! ������ʱĿ¼����ʼ��
	/*! ����ʱ��Ŀ¼���ڱ���������ʱ������˳�ʱ�Զ�ɾ��
		\param prefix ��Ŀ¼����ǰ׺�����硰pdf��
		\return ��ʱĿ¼��ȫ�������ش�����С��2ʱ��ʾʧ��
	*/
	virtual std::wstring CreateFolder(const std::wstring& prefix) = 0;

	//! ������ʱĿ¼��ȫ��
	virtual std::wstring GetPath() const = 0;

	//! �����µ���ʱ�ļ���
	/*!
		\param prefix �ļ���ǰ׺����Ϊ��
		\param ext �ļ���չ�������硰xml������_s.jpg��
		\return �µ��ļ�ȫ��
	*/
	virtual std::wstring CreateFileName(const std::wstring& prefix, 
		const std::wstring& ext) = 0;
};

#endif // X3_UTIL_ITEMPFOLDER_H_
