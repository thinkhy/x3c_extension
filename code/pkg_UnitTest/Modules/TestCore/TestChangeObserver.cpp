#include "stdafx.h"
#include "TestChangeObserver.h"
#include <../../pkg_Example/Interface/Ix_ChangeObserverTest.h>

CPPUNIT_TEST_SUITE_REGISTRATION( TestChangeObserver );

TestChangeObserver::TestChangeObserver()
{
}

void TestChangeObserver::setUp()
{
	VERIFY(2 == LoadPlugins(
		L"ChangeManager.plugin.dll, ChangeObserverExample.plugin.dll", false));
}

void TestChangeObserver::tearDown()
{
	UnloadPlugins();
}

void TestChangeObserver::testResponsibilityChain()
{
	Cx_Interface<Ix_ChangeObserverTest> pIFTest(CLSID_ChangeObserverTest);
	ASSERT(pIFTest.IsNotNull());
	VERIFY(pIFTest->TestResponsibilityChain());
}

void TestChangeObserver::testResponsibilityChain2()
{
	Cx_Interface<Ix_ChangeObserverTest> pIFTest(CLSID_ChangeObserverTest);
	ASSERT(pIFTest.IsNotNull());
	VERIFY(pIFTest->TestResponsibilityChain2(1, 'x'));
	VERIFY(pIFTest->TestResponsibilityChain2(0, '-'));
	VERIFY(!pIFTest->TestResponsibilityChain2(0, 'x'));
}

void TestChangeObserver::testEventObserver()
{
	Cx_Interface<Ix_ChangeObserverTest> pIFTest(CLSID_ChangeObserverTest);
	ASSERT(pIFTest.IsNotNull());
	VERIFY(pIFTest->TestEventObserver());
}

void TestChangeObserver::testSelectionObserver()
{
	Cx_Interface<Ix_ChangeObserverTest> pIFTest(CLSID_ChangeObserverTest);
	ASSERT(pIFTest.IsNotNull());
	VERIFY(pIFTest->TestSelectionObserver());
}
