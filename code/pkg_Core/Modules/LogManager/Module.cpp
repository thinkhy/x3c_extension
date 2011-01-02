#include "stdafx.h"
#include <XModuleMacro.h>
#include <XModuleImpl.h>

#include "Cx_LogManager.h"

XBEGIN_DEFINE_MODULE()
	XDEFINE_CLASSMAP_ENTRY_Singleton(CLSID_LogManager, Cx_LogManager)
XEND_DEFINE_MODULE_WIN32DLL()
