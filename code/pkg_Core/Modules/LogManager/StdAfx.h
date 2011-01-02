#pragma once

#if _MSC_VER >= 1600 // VC2010
#include <SDKDDKVer.h>		// Defines the highest available Windows platform.
#endif

#define WIN32_LEAN_AND_MEAN	// Exclude rarely-used stuff from Windows headers
#include <windows.h>		// Windows master include file
#include <shlwapi.h>		// Windows light-weight utility APIs

#include <vecfunc.h>		// STL master include file and functions
#include <Log/DebugR.h>		// ASSERT, VERIFY and ASSERT_MESSAGE
#include <XComPtr.h>		// Cx_Interface & Cx_Ptr
