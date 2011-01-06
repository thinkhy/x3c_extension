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

/*! \file XClassItem.h
 *  \brief ���������ע�������Ԫ�ؽṹ���ڲ��ļ�
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_PLUGINIMPL_CLASSITEM_H_
#define X3_PLUGINIMPL_CLASSITEM_H_

#include "Ix_Object.h"

//! �����Ķ��󴴽�����
typedef Ix_Object* (STDMETHODCALLTYPE *PFNXObjectCreator)(HMODULE);

//! ����������ʹ�õĶ����������
typedef long (STDMETHODCALLTYPE *PFNXGetObjectCount)();

//! ������������ģ��ʹ�ü�������
typedef long (STDMETHODCALLTYPE *PFNXRefCountByOthers)();

#define MIN_SINGLETON_TYPE	10

#pragma pack(push, 8)

/*! \ingroup _GROUP_PLUGIN_CORE2_
 *  \brief �����Ķ��󴴽���Ϣ��
 *  \see   _xGetClassEntryTable, XBEGIN_DEFINE_MODULE
 */
struct _XCLASSMETA_ENTRY
{
	BYTE				type;				//!< ������, �� MIN_SINGLETON_TYPE, XModuleMacro.h
	LPCSTR				className;			//!< ʵ���������
	XCLSID				clsid;				//!< �����ID
	const char*			iidSpecial;			//!< �ض��ĵ�ʵ���ӿ�
	PFNXObjectCreator	pfnObjectCreator;	//!< ���󴴽������ĵ�ַ
	PFNXGetObjectCount	pfnGetObjectCount;	//!< δ�ͷŵĶ������
	PFNXRefCountByOthers	pfnRefCountByOthers;	//!< ������ģ��ʹ�ü���

	//! �� XDEFINE_CLASSMAP_ENTRY �Ⱥ�ʹ�õĹ��캯��
	_XCLASSMETA_ENTRY(BYTE      _type, 
		LPCSTR                  _className, 
		const XCLSID&           _clsid, 
		const char*             _iidSpecial, 
		PFNXObjectCreator       _pfnObjectCreator, 
		PFNXGetObjectCount      _pfnGetObjectCount = NULL, 
		PFNXRefCountByOthers    _pfnRefCountByOthers = NULL)

		: type(_type), className(_className)
		, clsid(_clsid), iidSpecial(_iidSpecial)
		, pfnObjectCreator(_pfnObjectCreator)
		, pfnGetObjectCount(_pfnGetObjectCount)
		, pfnRefCountByOthers(_pfnRefCountByOthers)
	{
	}

	//! Ĭ�Ϲ��캯������ XEND_DEFINE_MODULE ʹ��
	_XCLASSMETA_ENTRY()
		: type(0), className(""), clsid(""), iidSpecial("")
		, pfnObjectCreator(NULL), pfnGetObjectCount(NULL)
		, pfnRefCountByOthers(NULL)
	{
	}

	//! �������Ϣ������飬�� XBEGIN_DEFINE_MODULE ���Ԫ��
	static const _XCLASSMETA_ENTRY s_classes[];
};

#pragma pack(pop)
#endif // X3_PLUGINIMPL_CLASSITEM_H_
