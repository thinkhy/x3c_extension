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

/*! \file Ix_ObjectFactory.h
 *  \brief ���崴������Ľӿ� Ix_ObjectFactory
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_CORE_IOBJECTFACTORY_H_
#define X3_CORE_IOBJECTFACTORY_H_

#include "Ix_Object.h"

/*! \ingroup _GROUP_PLUGIN_CORE_
 *  \interface Ix_ObjectFactory
 *  \brief ��������ӿڶ���Ľӿ�
 *  \see   Ix_Object, Ix_Module
 */
interface Ix_ObjectFactory
{
	//! ����ָ����������Ƿ��Ѽ���
	virtual bool IsCreatorRegister(const XCLSID& clsid) = 0;

	//! ����һ�������ID��Ӧ�Ķ���ʵ��
	virtual HRESULT CreateObject(const XCLSID& clsid, Ix_Object** ppv, HMODULE fromdll) = 0;

	//! �����в��ģ���д����ض��ӿڵĵ�ʵ������
	/*!
		\param iid ָ���Ľӿ�ID
		\return ֧�ָýӿڵĲ���ĸ����������Ƿ��Ѵ���
	*/
	virtual long CreateSpecialInterfaceObjects(const char* iid) = 0;

	//! �õ�ָ����ŵĲ��ģ���е�ָ���ӿڵĵ�ʵ������
	/*!
		\param[in] index ָ���Ĳ����ţ�����ʵ�ʼ���˳���йأ�С�ڲ������
		\param[in] iid ָ���Ľӿ�ID
		\param[in,out] ppv ��������ĵ�ַ�����ش����Ķ���ΪNULL��ȥ����
		\return ָ���Ĳ�����Խ��ʱ����false�����򷵻�true������ֵ��ppv�޹�
	*/
	virtual bool QuerySpecialInterfaceObject(long index, const char* iid, Ix_Object** ppv) = 0;

	//! �����Ƿ����๤���������滻
	virtual bool HasCreatorReplaced(const XCLSID& clsid) = 0;
};

#endif // X3_CORE_IOBJECTFACTORY_H_
