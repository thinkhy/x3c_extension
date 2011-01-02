#pragma once

#include "Cx_ObjectFactory.h"
#include "Ix_PluginLoader.h"

class Cx_PluginLoader
	: public Cx_ObjectFactory
	, public Ix_PluginLoader
{
public:
	Cx_PluginLoader();
	virtual ~Cx_PluginLoader();

	HMODULE GetMainModuleHandle();

	virtual long LoadPlugins(HMODULE instance, LPCWSTR path, 
		LPCWSTR ext = L".plugin.dll", bool recursive = true);
	virtual long LoadPlugins(LPCWSTR path, 
		LPCWSTR ext = L".plugin.dll", bool recursive = true);
	virtual long LoadPluginFiles(LPCWSTR path, 
		LPCWSTR files, HMODULE instance = NULL);
	virtual long InitializePlugins();
	virtual bool RegisterPlugin(HMODULE instance);
	virtual bool LoadPlugin(LPCWSTR filename);
    virtual bool UnloadPlugin(LPCWSTR name);
	virtual long UnloadPlugins();

private:
	bool issep(WCHAR c);
	bool ClearModuleItems(HMODULE hModule);

private:
	HMODULE	m_instance;
};
