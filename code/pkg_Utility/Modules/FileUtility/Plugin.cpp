#include "stdafx.h"
#include "Cx_TempFolder.h"

extern "C" __declspec(dllexport) void UninitializePlugin()
{
	Cx_TempFolder::DeleteFolders();
}
