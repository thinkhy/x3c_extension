#pragma once

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
	//! 插件模块登记项
	struct MODULEINFO
	{
		HMODULE				hModule;	//!< 插件DLL句柄
		Ix_Module*			pModule;	//!< 插件模块对象
		VXCLSID				clsids;		//!< 注册了类工厂的所有类ID
		bool				bOwner;		//!< 是否由本类加载了该DLL
		bool				bInit;		//!< 是否已由 InitializePlugins 调用
	};
	std::vector<MODULEINFO>	m_vecModule;	//!< 所有插件模块
	CLSMAP					m_mapEntry;		//!< 类ID到登记项的映射表

protected:
	int FindModule(HMODULE hModule);
	Ix_Module* GetModule(HMODULE hModule);
	long RegisterClassEntryTable(HMODULE hModule);
	void ReleaseModule(HMODULE hModule);

private:
	_XCLASSMETA_ENTRY* FindEntry(const XCLSID& clsid);
	bool RegisterClass(int moduleIndex, const _XCLASSMETA_ENTRY& cls);
};
