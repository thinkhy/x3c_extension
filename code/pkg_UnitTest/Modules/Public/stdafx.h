#pragma once

#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers

#if _MSC_VER >= 1600		// VC2010
#include <SDKDDKVer.h>		// Defines the highest available Windows platform.
#endif

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <shlwapi.h>		// Windows light-weight utility APIs

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#undef ASSERT
#undef VERIFY
#define ASSERT CPPUNIT_ASSERT
#define VERIFY CPPUNIT_ASSERT

#include <XComPtr.h>
