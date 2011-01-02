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

/*! \file Ix_Module.h
 *  \brief ������ģ��ӿ� Ix_Module
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_PLUGINIMPL_IMODULE_H_
#define X3_PLUGINIMPL_IMODULE_H_

#include "Ix_Object.h"

interface Ix_ObjectFactory;

/*! \ingroup _GROUP_PLUGIN_CORE_
 *  \interface Ix_Module
 *  \brief ���ģ��ӿ�
 *  \note  ÿ�����ģ��DLL�а���һ��Ix_Module����, ���� xGetCurrentModule() �õ��ö���
 *  \see xGetCurrentModule, xIsCreatorRegister, Ix_ObjectFactory
 */
interface Ix_Module
{
	//! ��ж��ģ��ǰ�ͷ����е�ʵ������
	virtual void ClearModuleItems() = 0;

	//! ����δ�ͷŵĶ������
	virtual long GetUnfreeObjectCount() = 0;

	//! ���ز������������
	virtual Ix_ObjectFactory* GetObjectFactory() const = 0;

	//! ���ر�ģ��DLL���
	virtual HMODULE GetModuleInstance() const = 0;

	//! ���ر�ģ����Դ���
	virtual HMODULE GetModuleResourceHandle() const = 0;

	//! ���ñ�ģ�����Դ���������Ҫ֧�ֱ��ػ���Դʱ����
	virtual HMODULE SetModuleResourceHandle(HMODULE hResource) = 0;
};

//! ���ص�ǰ�����ڵ�ģ�����
/*!
	\ingroup _GROUP_PLUGIN_CORE_
	\return ��ǰ���ģ����Ψһ��ģ�����
*/
Ix_Module* xGetCurrentModule();

//! ����ָ���������ID�Ƿ��Ѿ�ע���๤������
/*!
	\ingroup _GROUP_PLUGIN_CORE_
	\param clsid �����ID
	\return ��������Ƿ��Ѿ�ע��(���Ƿ��Ѽ�������)
*/
bool xIsCreatorRegister(const XCLSID& clsid);

#endif // X3_PLUGINIMPL_IMODULE_H_
