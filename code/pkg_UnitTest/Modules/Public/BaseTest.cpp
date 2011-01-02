#include "stdafx.h"
#include "BaseTest.h"
#include <PluginManager.h>

static CPluginManager s_loader;
static WCHAR s_datapath[MAX_PATH] = { 0 };
static WCHAR s_temppath[MAX_PATH] = { 0 };

BaseTest::BaseTest()
{
	MakeRootPath(s_datapath, L"TestData");
	MakeRootPath(s_temppath, L"Temp");
}

long BaseTest::LoadPlugins(LPCWSTR plugins, bool loadCore)
{
	// Initialize COM
	VERIFY(SUCCEEDED(CoInitialize(NULL)));

	// Load plugins
	VERIFY(s_loader.LoadPluginManager(PLUGINS_DIR));

	if (loadCore)
	{
		VERIFY(s_loader.LoadCorePlugins(PLUGINS_DIR));
	}

	long count = 1;

	if (plugins && *plugins)
	{
		Ix_PluginLoader* pPluginLoader = s_loader.GetPluginLoader();
		ASSERT(pPluginLoader != NULL);

		count = pPluginLoader->LoadPluginFiles(PLUGINS_DIR, plugins);
		pPluginLoader->InitializePlugins();
	}

	return count;
}

void BaseTest::UnloadPlugins()
{
	s_loader.Unload();		// Unload plugins
	CoUninitialize();		// Free COM resource
}

Ix_PluginLoader* BaseTest::GetPluginLoader()
{
	return s_loader.GetPluginLoader();
}

void BaseTest::MakeRootPath(LPWSTR path, LPCWSTR name)
{
	WCHAR filename[MAX_PATH];

	if (0 == path[0])
	{
		GetModuleFileNameW(NULL, filename, MAX_PATH);
		PathRemoveFileSpecW(filename);
		PathAppendW(filename, L"UnitTests.ini");

		lstrcpynW(path, filename, MAX_PATH);
		PathRemoveFileSpecW(path);		// bin\vc80\debug\tests
		PathRemoveFileSpecW(path);		// bin\vc80\debug
		PathRemoveFileSpecW(path);		// bin\vc80
		PathRemoveFileSpecW(path);		// bin
		PathAppendW(path, name);		// bin\name

		GetPrivateProfileStringW(L"Path", name, path, 
			path, MAX_PATH, filename);
		PathAddBackslashW(path);

		SetFileAttributesW(filename, FILE_ATTRIBUTE_NORMAL);
		WritePrivateProfileStringW(L"Path", name, path, filename);
	}
}

std::wstring BaseTest::MakeDataPath(LPCWSTR folder, LPCWSTR file)
{
	WCHAR filename[MAX_PATH];

	if (folder && *folder)
	{
		lstrcpynW(filename, s_datapath, MAX_PATH);
		PathAppendW(filename, folder);
	}
	else
	{
		lstrcpynW(filename, s_temppath, MAX_PATH);
		::CreateDirectoryW(s_temppath, NULL);
	}

	if (file && *file)
	{
		PathAppendW(filename, file);
	}
	else
	{
		PathAddBackslashW(filename);
	}

	return filename;
}
