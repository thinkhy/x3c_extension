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

#pragma once

#include "BaseTest.h"

class TestLogging : public BaseTest
{
	CPPUNIT_TEST_SUITE( TestLogging );
	CPPUNIT_TEST( testAllMacros );
	CPPUNIT_TEST( testAllMacrosWithID );
	CPPUNIT_TEST( testMultiTypes );
	CPPUNIT_TEST( testIdFormat );
	CPPUNIT_TEST( testGroup );
	CPPUNIT_TEST( testObserver );
	CPPUNIT_TEST_SUITE_END();

public:
	TestLogging();

	virtual void setUp();
	virtual void tearDown();

	void testAllMacros();
	void testAllMacrosWithID();
	void testMultiTypes();
	void testIdFormat();
	void testGroup();
	void testObserver();
};
