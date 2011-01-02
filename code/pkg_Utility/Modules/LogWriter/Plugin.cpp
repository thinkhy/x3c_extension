#include "stdafx.h"
#include "LogObserver.h"

static CLogObserver* s_pObserver = NULL;

extern "C" __declspec(dllexport) bool InitializePlugin()
{
	ASSERT(!s_pObserver);
	s_pObserver = new CLogObserver;

	return true;
}

extern "C" __declspec(dllexport) void UninitializePlugin()
{
	SafeDelete(s_pObserver);
}
