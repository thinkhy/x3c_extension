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

/*! \file XComCreator.h
 *  \brief ʵ�� xCreateObject �����Ա��ʹ�� Cx_Interface
 *  \note ���ļ�������Щ����Ҫʵ������࣬����Ҫʹ������ӿڵĹ��̣�����Ҫ����
 *        XModuleMacro.h �� XModuleImpl.h ���ļ���\n
 *        ��Щ����һ���ǵ�Ԫ���Գ��򡢷ǲ����ϵ�ĳ���COM�ؼ�����EXE���̡�\n
 *
 *    ʹ�÷�����һ�㽫���ļ�������StdAfx.cpp�У�ֻ�ڹ��̵�һ��CPP�а���������ͨ��ʵ�����е�
 *        xCreateObject �����������������\n
 *        (1) �����Ҫʹ�ö��������򲻶���USE_ONE_PLUGIN����ʹ�� PluginManager.h ������Щ�����\n
 *        (2) ���������һ�����������Բ�ʹ��PluginManager.h�����ǲ��ü򻯷�����
 *        �ȶ��� USE_ONE_PLUGIN ���ٰ������ļ������ⲿʹ�� LoadLibrary Ϊ g_hPluginDll ��ֵ��
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */

#ifndef USE_ONE_PLUGIN

#include "Ix_ObjectFactory.h"

HRESULT xCreateObject(const XCLSID& clsid, Ix_Object** ppv)
{
	if (NULL == ppv)
		return E_POINTER;
	*ppv = NULL;

	typedef Ix_ObjectFactory* (*FUNC_GET)();
	FUNC_GET pfn = (FUNC_GET)GetProcAddress(
		GetModuleHandleW(L"PluginManagerX3.dll"), "xGetRegisterBank");

	Ix_ObjectFactory* pFactory = pfn ? (*pfn)() : NULL;
	if (NULL == pFactory)
		return E_FAIL;	// ��Ҫʹ�� PluginManager.h ���ز��

	return pFactory->CreateObject(clsid, ppv, NULL);
}

#else // USE_ONE_PLUGIN

// ���� USE_ONE_PLUGIN ��������ļ������ⲿʹ�� LoadLibrary Ϊ g_hPluginDll ��ֵ��
//   Ȼ��xCreateObject�Ϳ�����������������ʹ�� Cx_Interface

HMODULE		g_hPluginDll = NULL;

HRESULT xCreateObject(const XCLSID& clsid, Ix_Object** ppv)
{
	if (NULL == ppv)
		return E_POINTER;
	*ppv = NULL;

	typedef HRESULT (*FUNC_CREATE)(const char*, Ix_Object**, HMODULE);
	FUNC_CREATE pfn = (FUNC_CREATE)GetProcAddress(
		g_hPluginDll, "_xInternalCreateObject");

	return pfn ? (*pfn)(clsid.str(), ppv, NULL) : E_FAIL;
}

#endif // USE_ONE_PLUGIN

HMODULE xGetModuleHandle()
{
	return NULL;
}
