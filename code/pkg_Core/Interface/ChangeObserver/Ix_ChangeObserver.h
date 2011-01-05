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

/*! \file Ix_ChangeObserver.h
 *  \brief ����ı�֪ͨ�۲��ߵĽӿ� Ix_ChangeObserver
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef X3_OBSERVER_ICHANGEOBSERVER_H_
#define X3_OBSERVER_ICHANGEOBSERVER_H_

class ChangeNotifyData;

//! �ı�֪ͨ�۲��ߵĽӿ�
/*!
	\interface Ix_ChangeObserver
	\ingroup _GROUP_CHANGE_OBSERVER_
*/
interface Ix_ChangeObserver
{
	//! �ı��֪ͨ
	/*!
		\param data ֪ͨ������һ��Ϊһ���ֲ������ĵ�ַ
	*/
	virtual void Update(ChangeNotifyData* data) = 0;
};

#endif // X3_OBSERVER_ICHANGEOBSERVER_H_
