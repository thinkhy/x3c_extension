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
