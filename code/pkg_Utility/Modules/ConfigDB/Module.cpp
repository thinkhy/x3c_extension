#include "stdafx.h"
#include <XModuleMacro.h>
#include <XModuleImpl.h>

#include "ClsID_Internal.h"
#include "Cx_ConfigFactory.h"
#include "Cx_CfgDatabase.h"

XBEGIN_DEFINE_MODULE()
	XDEFINE_CLASSMAP_ENTRY_Singleton(CLSID_ConfigDBFactory, Cx_ConfigFactory)
	XDEFINE_CLASSMAP_ENTRY(CLSID_CfgDatabase, Cx_CfgDatabase)
XEND_DEFINE_MODULE_MFCEXTDLL()
