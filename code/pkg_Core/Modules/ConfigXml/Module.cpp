#include "stdafx.h"
#include <XModuleMacro.h>
#include <XModuleImpl.h>

#include "Cx_ConfigXml.h"
#include "Cx_XmlSection.h"
#include "XmlUtil/XmlUtil.cpp"

XBEGIN_DEFINE_MODULE()
	XDEFINE_CLASSMAP_ENTRY(CLSID_ConfigXmlFile, Cx_ConfigXml)
	XDEFINE_CLASSMAP_ENTRY(XCLSID(), Cx_XmlSection)
XEND_DEFINE_MODULE_WIN32DLL()
