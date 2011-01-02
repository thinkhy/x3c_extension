/*! \file PluginManager.h
 *  \brief ������������DLL�ķ�װ��
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.28
 */
#ifndef X3_MANAGER_PLUGINMANAGER_H_
#define X3_MANAGER_PLUGINMANAGER_H_

#include "Ix_ObjectFactory.h"
#include "Ix_PluginLoader.h"

#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

/*! \ingroup _GROUP_PLUGIN_CORE_
 *  \brief ���������DLL�ķ�װ��
 *  \see   Ix_ObjectFactory, Ix_PluginLoader
 */
class CPluginManager
{
public:
	CPluginManager() : m_dll(NULL)
	{
		lstrcpyW(m_filename, L"PluginManagerX3.dll");
	}

	~CPluginManager()
	{
		Unload();
	}

	//! ж�ز��������DLL
	void Unload(bool all = false)
	{
		if (all || m_dll)
		{
			Ix_PluginLoader* pLoader = GetPluginLoader();
			if (pLoader != NULL)
			{
				pLoader->UnloadPlugins();
			}
		}
		if (m_dll != NULL)
		{
			FreeLibrary(m_dll);
			m_dll = NULL;
		}
	}

	//! ���ز��������
	bool LoadPluginManager(LPCWSTR subdir, HMODULE instance = NULL)
	{
		GetModuleFileNameW(instance, m_filename, MAX_PATH);
		PathRemoveFileSpecW(m_filename);
		PathAppendW(m_filename, subdir);
		PathAppendW(m_filename, L"PluginManagerX3.dll");

		if (GetModuleHandleW(m_filename) || m_dll)
		{
			return true;
		}

		m_dll = LoadLibraryW(m_filename);
		return m_dll != NULL;
	}

	//! ���غ��Ĳ���Ͳ��������
	bool LoadCorePlugins(LPCWSTR subdir, HMODULE instance = NULL)
	{
		if (!LoadPluginManager(subdir, instance))
		{
			return false;
		}

		Ix_PluginLoader* pLoader = GetPluginLoader();
		if (pLoader)
		{
			long n = pLoader->LoadPluginFiles(subdir, 
				L"LogManager.plugin.dll, "
				L"LogWriter.plugin.dll, "
				L"ConfigXml.plugin.dll, "
				L"StringTable.plugin.dll, "
				L"ChangeManager.plugin.dll, "
				L"FileUtility.plugin.dll, "
				L"PluginManagerEx.plugin.dll", instance);

			if (pLoader->InitializePlugins() > 0 && n > 0)
			{
				return true;
			}
		}

		return false;
	}

	//! ���ض��󴴽������ӿڶ���
	Ix_ObjectFactory* GetObjectFactory()
	{
		typedef Ix_ObjectFactory* (*FUNC_GETREGISTERBANK)();
		FUNC_GETREGISTERBANK pfn = (FUNC_GETREGISTERBANK)GetProcAddress(
			GetModuleHandleW(m_filename), "xGetRegisterBank");

		return pfn ? (*pfn)() : NULL;
	}

	//! ���ز�����صĽӿڶ���
	Ix_PluginLoader* GetPluginLoader()
	{
		return dynamic_cast<Ix_PluginLoader*>(GetObjectFactory());
	}

private:
	HMODULE		m_dll;
	WCHAR		m_filename[MAX_PATH];
};

#endif // X3_MANAGER_PLUGINMANAGER_H_
