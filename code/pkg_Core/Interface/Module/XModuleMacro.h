/*! \file XModuleMacro.h
 *  \brief ���������ע��� XBEGIN_DEFINE_MODULE �Ⱥ�
 *  \note XModuleImpl.h �ͱ��ļ����Բ���Ҫͬʱ������һ��CPP�ļ��С�\n
 *        �����ϣ��ʹ�ñ��ļ��� XModuleImpl.h ���ļ�����ʹ�� XComCreator.h �ļ���
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.19
 */
#ifndef X3_PLUGINIMPL_MODULEMACRO_H_
#define X3_PLUGINIMPL_MODULEMACRO_H_

// XBEGIN_DEFINE_MODULE()
//     XDEFINE_CLASSMAP_ENTRY(clsid, cls)
//     XDEFINE_CLASSMAP_ENTRY_Singleton(clsid, cls)
//     XDEFINE_SPECIAL_INTERFACE_ENTRY_Singleton(clsid, iid, cls)
// XEND_DEFINE_MODULE()
// XEND_DEFINE_MODULE_WIN32DLL()
// XEND_DEFINE_MODULE_MFCEXTDLL()
// XEND_DEFINE_MODULE_MFCDLL()

#include "XClassItem.h"
#include "Cx_Object.h"
#include "Cx_SingletonObject.h"

//! ��ʼ�����ע��ĺ�
/*!
	\ingroup _GROUP_PLUGIN_CORE_
	\see XEND_DEFINE_MODULE
	\see XEND_DEFINE_MODULE_WIN32DLL, XEND_DEFINE_MODULE_MFCEXTDLL
*/
#define XBEGIN_DEFINE_MODULE()	\
	const _XCLASSMETA_ENTRY _XCLASSMETA_ENTRY::s_classes[] = {

//! ����ͨ��������ע��ĺ�
/*!
	\ingroup _GROUP_PLUGIN_CORE_
	\param clsid �����ID��������LPCSTR��CHAR����ĳ���
	\param cls �������
*/
#define XDEFINE_CLASSMAP_ENTRY(clsid, cls)		\
	_XCLASSMETA_ENTRY(1, "Cx_Object<" #cls ">", clsid, "",	\
		reinterpret_cast<PFNXObjectCreator>(&Cx_Object<cls>::CreateObject),	\
		reinterpret_cast<PFNXGetObjectCount>(&Cx_Object<cls>::GetObjectCount),	\
		reinterpret_cast<PFNXRefCountByOthers>(&Cx_Object<cls>::GetRefCountByOthers)), 

//! �Ե�ʵ����������ע��ĺ�
/*!
	\ingroup _GROUP_PLUGIN_CORE_
	\param clsid �����ID��������LPCSTR��CHAR����ĳ���
	\param cls �������
*/
#define XDEFINE_CLASSMAP_ENTRY_Singleton(clsid, cls)	\
	_XCLASSMETA_ENTRY(MIN_SINGLETON_TYPE,	\
		"Cx_SingletonObject<" #cls ">", clsid, "",	\
		reinterpret_cast<PFNXObjectCreator>(&Cx_SingletonObject<cls>::CreateObject),	\
		reinterpret_cast<PFNXGetObjectCount>(&Cx_SingletonObject<cls>::GetObjectCount),	\
		reinterpret_cast<PFNXRefCountByOthers>(&Cx_SingletonObject<cls>::GetRefCountByOthers)), 

//! ��֧���ض�ͨ�ýӿڵĵ�ʵ����������ע��ĺ�
/*!
	\ingroup _GROUP_PLUGIN_CORE_
	\param iid �ض�ͨ�ýӿڵĽӿ�ID���ƣ�������LPCSTR��CHAR����ĳ���
	\param cls �������
*/
#define XDEFINE_SPECIAL_INTERFACE_ENTRY_Singleton(iid, cls)		\
	_XCLASSMETA_ENTRY(MIN_SINGLETON_TYPE + 1,	\
		"Cx_SingletonObject<" #cls ">", XCLSID(), iid,	\
		reinterpret_cast<PFNXObjectCreator>(&Cx_SingletonObject<cls>::CreateObject),	\
		reinterpret_cast<PFNXGetObjectCount>(&Cx_SingletonObject<cls>::GetObjectCount),	\
		reinterpret_cast<PFNXRefCountByOthers>(&Cx_SingletonObject<cls>::GetRefCountByOthers)), 

//! ���������ע��ĺ�
/*!
	\ingroup _GROUP_PLUGIN_CORE_
	\see XEND_DEFINE_MODULE_WIN32DLL, XEND_DEFINE_MODULE_MFCEXTDLL
*/
#define	XEND_DEFINE_MODULE() \
		_XCLASSMETA_ENTRY()	\
	};

#pragma warning(disable:4710)	// inline function not expanded

//! ���������ע��ĺ꣬��ʵ��Win32DLL(USRDLL)Ĭ�ϵ���ں���
/*! Ҫʹ�ñ���Ļ�����Ҫͬʱ�������ļ��� XModuleImpl.h �ļ�
	\ingroup _GROUP_PLUGIN_CORE_
	\see XEND_DEFINE_MODULE_MFCEXTDLL, XEND_DEFINE_MODULE_MFCDLL
*/
#define	XEND_DEFINE_MODULE_WIN32DLL() \
		_XCLASSMETA_ENTRY()	\
	};	\
BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID)	\
{	\
	if (dwReason == DLL_PROCESS_ATTACH)	\
	{	\
		_xGetModuleInterface(NULL, (HMODULE)hModule);	\
	}	\
	else if (dwReason == DLL_PROCESS_DETACH)	\
	{	\
		xGetCurrentModule()->ClearModuleItems();	\
	}	\
	return TRUE;	\
}

//! ���������ע��ĺ꣬��ʵ��MFC��չDLLĬ�ϵ�DLL��ں���
/*! Ҫʹ�ñ���Ļ�����Ҫͬʱ�������ļ��� XModuleImpl.h �ļ�
	\ingroup _GROUP_PLUGIN_CORE_
	\see XEND_DEFINE_MODULE_WIN32DLL, XEND_DEFINE_MODULE_MFCDLL
*/
#define	XEND_DEFINE_MODULE_MFCEXTDLL() \
		_XCLASSMETA_ENTRY()	\
	};	\
static AFX_EXTENSION_MODULE MFCExtDLL = { NULL, NULL };	\
extern "C" int APIENTRY	\
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID)	\
{	\
	if (dwReason == DLL_PROCESS_ATTACH)	\
	{	\
		if (!AfxInitExtensionModule(MFCExtDLL, hInstance))	\
			return 0;	\
		new CDynLinkLibrary(MFCExtDLL);	\
		_xGetModuleInterface(NULL, MFCExtDLL.hModule);	\
	}	\
	else if (dwReason == DLL_PROCESS_DETACH)	\
	{	\
		xGetCurrentModule()->ClearModuleItems();		\
		AfxTermExtensionModule(MFCExtDLL);	\
	}	\
	return 1;	\
}

//! ���������ע��ĺ꣬��ʵ��MFC����DLLĬ�ϵ�DLL������� CPluginApp
/*! Ҫʹ�ñ���Ļ�����Ҫͬʱ�������ļ��� XModuleImpl.h �ļ�
	\note ��MFC����DLL���κε��������Ϳɹ��ⲿ���õĺ����У�������ʹ��MFC�����ǰ
		�ȵ��� AFX_MANAGE_STATE(AfxGetStaticModuleState());
	\ingroup _GROUP_PLUGIN_CORE_
	\see XEND_DEFINE_MODULE_WIN32DLL, XEND_DEFINE_MODULE_MFCEXTDLL
*/
#define	XEND_DEFINE_MODULE_MFCDLL() \
		_XCLASSMETA_ENTRY()	\
	};	\
class CPluginApp : public CWinApp	\
{	\
public:	\
	CPluginApp()	\
	{	\
	}	\
	virtual BOOL InitInstance()	\
	{	\
		CWinApp::InitInstance();	\
		_xGetModuleInterface(NULL, m_hInstance);	\
		return TRUE;	\
	}	\
	virtual int ExitInstance()	\
	{	\
		xGetCurrentModule()->ClearModuleItems();	\
		return CWinApp::ExitInstance();	\
	}	\
};

#endif // X3_PLUGINIMPL_MODULEMACRO_H_
