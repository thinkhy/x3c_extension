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

/*! \file Ix_TempFolder.h
 *  \brief ������ʱĿ¼�����Ľӿ� Ix_TempFolder
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef X3_UTIL_ITEMPFOLDER_H_
#define X3_UTIL_ITEMPFOLDER_H_

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
