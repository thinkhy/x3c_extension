#include "stdafx.h"
#include <XModuleMacro.h>
#include <XModuleImpl.h>

#include "Cx_TextUtil.h"
#include "Cx_GuidGenerator.h"
#include "Cx_ClipboardUtil.h"

XBEGIN_DEFINE_MODULE()
	XDEFINE_CLASSMAP_ENTRY_Singleton(CLSID_TextUtil, Cx_TextUtil)
	XDEFINE_CLASSMAP_ENTRY_Singleton(CLSID_GuidGenerator, Cx_GuidGenerator)
	XDEFINE_CLASSMAP_ENTRY_Singleton(CLSID_ClipboardUtil, Cx_ClipboardUtil)
XEND_DEFINE_MODULE_WIN32DLL()
