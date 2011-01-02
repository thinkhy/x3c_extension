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

#ifndef _X3_CORE_OBJECTFACTORY_H
#define _X3_CORE_OBJECTFACTORY_H

#include <XClassItem.h>
#include <Ix_Module.h>
#include <Ix_ObjectFactory.h>

class Cx_ObjectFactory
	: public Ix_ObjectFactory
{
public:
	Cx_ObjectFactory();
	virtual ~Cx_ObjectFactory();

public:
	virtual bool IsCreatorRegister(const XCLSID& clsid);
	virtual HRESULT CreateObject(const XCLSID& clsid, Ix_Object** ppv, HMODULE fromdll);
	virtual long CreateSpecialInterfaceObjects(const char* iid);
	virtual bool QuerySpecialInterfaceObject(long index, const char* iid, Ix_Object** ppv);
	virtual bool HasCreatorReplaced(const XCLSID& clsid);

protected:
	typedef std::vector<XCLSID>			VXCLSID;
	typedef std::map<XCLSID, _XCLASSMETA_ENTRY>	CLSMAP;
	//! ���ģ��Ǽ���
	struct MODULEINFO
	{
		HMODULE				hModule;	//!< ���DLL���
		Ix_Module*			pModule;	//!< ���ģ�����
		VXCLSID				clsids;		//!< ע�����๤����������ID
		bool				bOwner;		//!< �Ƿ��ɱ�������˸�DLL
		bool				bInit;		//!< �Ƿ����� InitializePlugins ����
	};
	std::vector<MODULEINFO>	m_vecModule;	//!< ���в��ģ��
	CLSMAP					m_mapEntry;		//!< ��ID���Ǽ����ӳ���

protected:
	int FindModule(HMODULE hModule);
	Ix_Module* GetModule(HMODULE hModule);
	long RegisterClassEntryTable(HMODULE hModule);
	void ReleaseModule(HMODULE hModule);

private:
	_XCLASSMETA_ENTRY* FindEntry(const XCLSID& clsid);
	bool RegisterClass(int moduleIndex, const _XCLASSMETA_ENTRY& cls);
};

#endif // _X3_CORE_OBJECTFACTORY_H
