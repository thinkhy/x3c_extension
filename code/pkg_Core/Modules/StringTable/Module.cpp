#include "stdafx.h"
#include <XModuleMacro.h>
#include <XModuleImpl.h>

#include "Cx_StringTable.h"

XBEGIN_DEFINE_MODULE()
	XDEFINE_CLASSMAP_ENTRY_Singleton(CLSID_StringTable, Cx_StringTable)
XEND_DEFINE_MODULE_WIN32DLL()
