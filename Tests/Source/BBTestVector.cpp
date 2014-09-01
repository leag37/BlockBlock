// Filename: BBTestVector.cpp
// Author: Gael Huber
#include "BBTestVector.h"
#include "BBVector.h"

namespace BlockBlock
{
	/**
	 * Default constructor
	 */
	TestVector::TestVector()
		:
		Test()
	{
		_name = "TestVector";
	}

	/**
	 * Destructor
	 */
	TestVector::~TestVector()
	{

	}

	/**
	 * Setup the test
	 */
	void TestVector::Setup()
	{

	}

	/**
	 * Tear down the test
	 */
	void TestVector::Teardown()
	{

	}

	/**
	 * Run the test
	 */
	void TestVector::RunImpl()
	{
		AssertEquals(true, true);
	}

}	// Namespace