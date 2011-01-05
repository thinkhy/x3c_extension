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

/*! \file Ix_ChangeManager.h
 *  \brief ����ı�֪ͨ�������Ľӿ� Ix_ChangeManager
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef X3_OBSERVER_ICHANGEMANAGER_H_
#define X3_OBSERVER_ICHANGEMANAGER_H_

#include "Ix_ChangeObserver.h"

const XCLSID CLSID_ChangeManager("34c6e7c0-fe4a-45a1-b227-3da06e08499f");

//! �ı�֪ͨ�������Ľӿ�
/*!
	\interface Ix_ChangeManager
	\ingroup _GROUP_CHANGE_OBSERVER_
	\see CLSID_ChangeManager
*/
interface Ix_ChangeManager
{
	//! ע��۲���
	/*!
		\param type ֪ͨ������, �ɾ���ϵͳ����
		\param observer Ҫ��ӵĹ۲���
	*/
	virtual void RegisterObserver(const char* type, Ix_ChangeObserver* observer) = 0;

	//! ע���۲���
	/*!
		\param type ֪ͨ������, �ɾ���ϵͳ����
		\param observer Ҫȥ���Ĺ۲���
	*/
	virtual void UnRegisterObserver(const char* type, Ix_ChangeObserver* observer) = 0;

	//! ��һ��۲��߹㲥�ı�֪ͨ
	/*!
		\param type ֪ͨ������, �ɾ���ϵͳ����
		\param data ֪ͨ������һ��Ϊһ���ֲ������ĵ�ַ
	*/
	virtual void ChangeNotify(const char* type, ChangeNotifyData* data) = 0;
};

#endif // X3_OBSERVER_ICHANGEMANAGER_H_
