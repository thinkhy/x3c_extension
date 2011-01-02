#include "stdafx.h"
#include <cppunit/ui/mfc/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

class CUnitTestsApp : public CWinApp
{
public:
	CUnitTestsApp()
	{
	}

	virtual BOOL InitInstance()
	{
		AfxOleInit();
		SetRegistryKey(_T("Founder\\UnitTests"));

		CppUnit::MfcUi::TestRunner runner;
		runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );
		runner.run();

		return FALSE;
	}
};

CUnitTestsApp theApp;
