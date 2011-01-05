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

/*! \file Ix_FileTransaction.h
 *  \brief �����ļ�����ʵ�ò����Ľӿ� Ix_FileTransaction
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef X3_UTIL_IFILETRANSACTION_H_
#define X3_UTIL_IFILETRANSACTION_H_

#include <Ix_Object.h>

const XCLSID CLSID_FileTransaction("66087749-6a2d-40b7-86d9-687664f91e1b");

//! �ļ���������Ľӿ�
/*!
	\interface Ix_FileTransaction
	\ingroup _GROUP_UTILITY_
	\see CLSID_FileTransaction
*/
interface Ix_FileTransaction
{
	//! �ӹ���״̬�ع�����
	virtual void Rollback() = 0;

	//! �õ��������������
	virtual long GetLevel() const = 0;

	//! �����Ƿ����ڻع�����
	virtual bool IsRollbacking() const = 0;

	//! ɾ��һ��Ŀ¼���ļ�
	/*!
		\param filename Ŀ¼���ļ����ļ�ȫ��
		\param recycle true��ʾ�Ž�����վ��false��ʾֱ��ɾ��
		\return �Ƿ���ɾ����Ŀ¼���ļ�. �ļ�ȫ��Ϊ�ջ��ļ��������򷵻�true
	*/
	virtual bool DeletePathFile(LPCWSTR filename, bool recycle = false) = 0;
};

#endif // X3_UTIL_IFILETRANSACTION_H_
