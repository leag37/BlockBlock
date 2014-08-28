// Filename: BBTestSuite.cpp
// Author: Gael Huber
#include "BBTestSuite.h"

#include "BBTestVector.h"

namespace BlockBlock
{
	/**
	 * Default constructor
	 */
	TestSuite::TestSuite()
	{

	}

	/**
	 * Destructor
	 */
	TestSuite::~TestSuite()
	{

	}

	/**
	 * Initialize the test suite
	 * @return Returns true if successfully initialized
	 */
	bool TestSuite::Initialize()
	{
		_tests.push_back(new TestVector());

		return true;
	}

	/**
	 * Shut down the suite
	 */
	void TestSuite::Shutdown()
	{
		// Delete all the tests
		while(_tests.size() > 0)
		{
			Test* test = _tests[_tests.size() - 1];
			_tests.pop_back();
			delete test;
		}
	}

	/**
	 * Run the test suite
	 */
	void TestSuite::Run()
	{
		uint numAssertions = 0;
		uint numFailedAssertions = 0;

		// Run tests
		for(uint i = 0; i < _tests.size(); ++i)
		{
			// Fetch and run the test
			Test* test = _tests[i];
			test->Run();

			// Tabulate total assertion successes/failures
			numAssertions += test->GetTotalAssertions();
			numFailedAssertions += test->GetFailedAssertions();
		}

		printf("Executed %lu tests with %u assertions (%u failed)\n", _tests.size(), numAssertions, numFailedAssertions);
	}

}	// Namespace