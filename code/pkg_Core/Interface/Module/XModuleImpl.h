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

/*! \file XModuleImpl.h
 *  \brief ʵ�ֲ��ģ��ĵ��������� xCreateObject ��ȫ�ֺ���
 *  \note �ڹ����е�һ��CPP�ļ��а������ļ�����ֻ����һ��CPP�ļ��а������ļ���\n
 *        �����ϣ��ʹ�ñ��ļ��� XModuleMacro.h ���ļ�����ʹ�� XComCreator.h �ļ���
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_PLUGINIMPL_MODULEIMPL_H_
#define X3_PLUGINIMPL_MODULEIMPL_H_

#include "XClassItem.h"
#include "XModuleItem.h"
#include "Cx_Module.h"
#include "Ix_ObjectFactory.h"

#define OUTAPI	extern "C" __declspec(dllexport)

OUTAPI Ix_Module*	_xGetModuleInterface(Ix_ObjectFactory*, HMODULE);
OUTAPI DWORD	_xGetClassEntryTable(DWORD*, DWORD*, _XCLASSMETA_ENTRY*, DWORD);
OUTAPI HRESULT	_xInternalCreateObject(const char*, Ix_Object**, HMODULE);
OUTAPI bool		xCanUnloadPlugin();

static Cx_Module	s_xModuleObject;	// ȫ��Ψһ�Ĳ��ģ�����

//! ���ģ��ĵ��������������������ʹ��
/*! \ingroup _GROUP_PLUGIN_CORE2_
	\param pFactory �������������ΪNULL�����
	\param hModule �����ģ���DLL�����ΪNULL�����
	\return �����ģ���Ψһģ�����
	\see _xInternalCreateObject, _xGetClassEntryTable, xPluginOnLoad, xPluginOnUnload
*/
OUTAPI Ix_Module* _xGetModuleInterface(Ix_ObjectFactory* pFactory, HMODULE hModule)
{
	if (pFactory || hModule)
	{
		s_xModuleObject.Initialize(pFactory, hModule);
	}
	return &s_xModuleObject;
}

static long GetClassCount(BYTE minType)
{
	int nClassCount = 0;
	const _XCLASSMETA_ENTRY* pCls = _XCLASSMETA_ENTRY::s_classes;

	for (; pCls->pfnObjectCreator; ++pCls)
	{
		if (pCls->type >= minType)
		{
			nClassCount++;
		}
	}

	return nClassCount;
}

//! ��ñ����ģ����������Ϣ��
/*! \ingroup _GROUP_PLUGIN_CORE2_
	\param[out] pBuildInfo ���VC++������Ϣ��ΪNULLʱ���Ըò���
	\param[in,out] pEntrySize �������� _XCLASSMETA_ENTRY �Ĵ�С��ΪNULLʱ���Ըò���
	\param[out] pTable ���������ַ������������Ϣ�ΪNULLʱ����ʵ��Ԫ�ظ���
	\param[in] nMaxCount ����pTable��Ԫ��������
	\return ʵ�ʸ��Ƶ�Ԫ�ظ�����pTableΪNULLʱΪʵ��Ԫ�ظ���
	\see _xGetModuleInterface, xPluginOnLoad, xPluginOnUnload
*/
OUTAPI DWORD _xGetClassEntryTable(DWORD* pBuildInfo, DWORD* pEntrySize, 
								  _XCLASSMETA_ENTRY* pTable, DWORD nMaxCount)
{
	if (pBuildInfo)
	{
		*pBuildInfo = _MSC_VER << 2;
#ifdef _DEBUG
		*pBuildInfo |= 1;
#endif
	}

	DWORD nEntrySize = sizeof(_XCLASSMETA_ENTRY);

	if (pEntrySize)
	{
		nEntrySize = min(nEntrySize, *pEntrySize);
		nEntrySize = nEntrySize ? nEntrySize : sizeof(_XCLASSMETA_ENTRY);
		*pEntrySize = nEntrySize;
	}

	DWORD nClassCount = GetClassCount(0);

	if (NULL == pTable)
	{
		return nClassCount;
	}

	nClassCount = min(nClassCount, nMaxCount);
	for (DWORD i = 0; i < nClassCount; i++)
	{
		memcpy((LPBYTE)pTable + i * nEntrySize, 
			_XCLASSMETA_ENTRY::s_classes + i, nEntrySize);
	}

	return nClassCount;
}

//! ���ڱ������ڴ�������ĵ�������
/*! \ingroup _GROUP_PLUGIN_CORE2_
	\param clsid �����UID��������Ч
	\param ppv ��䴴���Ķ��󣬱���Ϊ��Ч��ַ
	\param fromdll ����������ģ���DLL���
	\return S_OK ��ʾ�ɹ�������ʧ��
	\see _xGetModuleInterface, xCreateObject, _xGetModuleInterface
*/
OUTAPI HRESULT _xInternalCreateObject(const char* clsid, Ix_Object** ppv, HMODULE fromdll)
{
	if (NULL == ppv)
		return E_POINTER;
	*ppv = NULL;

	XCLSID clsid2(clsid);
	const _XCLASSMETA_ENTRY* pCls = _XCLASSMETA_ENTRY::s_classes;

	for (; pCls->pfnObjectCreator; ++pCls)
	{
		if (clsid2 == pCls->clsid)
		{
			*ppv = (*pCls->pfnObjectCreator)(fromdll);
			return S_OK;
		}
	}

	return E_NOINTERFACE;
}

//! ��������ʹ�õĶ��󴴽�����
/*! \ingroup _GROUP_PLUGIN_CORE2_
	����ָ���� Cx_Interface �� Cx_Ptr ����ñ�������
	�����ϣ��ʹ��XModuleImpl.h���ļ�����ʹ�� XComCreator.h �ļ���

	\param clsid �����UID��������Ч
	\param ppv ��䴴���Ķ��󣬱���Ϊ��Ч��ַ
	\return S_OK ��ʾ�ɹ�������ʧ��
	\see _xInternalCreateObject, Ix_ObjectFactory, xIsCreatorRegister
*/
HRESULT xCreateObject(const XCLSID& clsid, Ix_Object** ppv)
{
	if (NULL == ppv)
		return E_POINTER;
	*ppv = NULL;

	HRESULT hr;
	bool bRetry = true;
	Ix_ObjectFactory* pFactory = s_xModuleObject.GetObjectFactory();

	if (pFactory && pFactory->HasCreatorReplaced(clsid))
	{
		hr = pFactory->CreateObject(clsid, ppv, xGetModuleHandle());
		if (S_OK == hr)
		{
			return hr;
		}
		bRetry = false;
	}

	hr = _xInternalCreateObject(clsid.str(), ppv, xGetModuleHandle());

	if (FAILED(hr) && pFactory && bRetry)
	{
		hr = pFactory->CreateObject(clsid, ppv, xGetModuleHandle());
	}

	return hr;
}

//! ���ص�ǰ���ģ���DLL��������ڼ�¼����ģ���Ƿ�ʹ�����ڲ��������
HMODULE xGetModuleHandle()
{
	return s_xModuleObject.GetModuleInstance();
}

Ix_Module* xGetCurrentModule()
{
	return &s_xModuleObject;
}

bool xIsCreatorRegister(const XCLSID& clsid)
{
	Ix_ObjectFactory* pFactory = s_xModuleObject.GetObjectFactory();
	return pFactory && pFactory->IsCreatorRegister(clsid);
}

Cx_Module::Cx_Module() : m_pFactory(NULL), m_hModule(NULL), m_hResource(NULL)
{
}

Cx_Module::~Cx_Module()
{
}

void Cx_Module::ClearModuleItems()
{
	CModuleItem::ClearModuleItems();
}

void Cx_Module::Initialize(Ix_ObjectFactory* pFactory, HMODULE hModule)
{
	m_pFactory = pFactory;

	if (hModule && !m_hModule)
	{
		m_hModule = hModule;
		m_hResource = m_hModule;
	}

	CModuleItem::InitModuleItems(GetClassCount(MIN_SINGLETON_TYPE));
}

HMODULE Cx_Module::SetModuleResourceHandle(HMODULE hResource)
{
	HMODULE hOld = m_hResource;
	m_hResource = (NULL == hResource) ? m_hModule : hResource;
	return hOld;
}

long Cx_Module::GetUnfreeObjectCount()
{
	long n, nTotal = 0;
	const _XCLASSMETA_ENTRY* pCls = _XCLASSMETA_ENTRY::s_classes;

	for (; pCls->pfnObjectCreator; ++pCls)
	{
		PFNXGetObjectCount pfn = pCls->pfnGetObjectCount;
		if (pfn && (n = (*pfn)()) > 0)
		{
			nTotal += n;

			OutputDebugStringA("> Unfree: ");
			OutputDebugStringA(pCls->className);
#ifdef TRACE1
			TRACE1(", %d", n);
#endif
			OutputDebugStringA("!\n");
		}
	}

	return nTotal;
}

/*! \ingroup _GROUP_PLUGIN_CORE2_
 *  \brief ���ر�ģ���Ƿ���԰�ȫж�أ���û������ģ������ʹ�����ڲ��������
 */
OUTAPI bool xCanUnloadPlugin()
{
	const _XCLASSMETA_ENTRY* pCls = _XCLASSMETA_ENTRY::s_classes;

	for (; pCls->pfnObjectCreator; ++pCls)
	{
		PFNXRefCountByOthers pfn = pCls->pfnRefCountByOthers;
		long n = 0;

		if (pfn && (n = (*pfn)()) > 0)
		{
			return false;
		}
	}

	return true;
}

#endif // X3_PLUGINIMPL_MODULEIMPL_H_
