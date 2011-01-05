// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// https://sourceforge.net/projects/x3c/
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
