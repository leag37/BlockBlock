// Filename: BBTest.cpp
// Author: Gael Huber
#include "BBTest.h"

#include <iostream>

namespace BlockBlock
{
	/**
	 * Default constructor
	 */
	Test::Test()
	{

	}

	/**
	 * Destructor
	 */
	Test::~Test()
	{

	}

	/**
	 * Run the test
	 */
	void Test::Run()
	{
		// Start output
		std::cout << BOLDYELLOW << "Running " << _name << "..." << RESET << std::endl;

		// Setup
		Setup();

		// Run the implementation
		RunImpl();

		// Tear down
		Teardown();

		// Final output
		std::cout << BOLDYELLOW << "Completed " << _name << " with " << _totalAssertions << " assertions (" << RESET;
		std::cout << (_failedAssertions == 0 ? BOLDGREEN : BOLDRED) << _failedAssertions << " failed" << RESET;
		std::cout << BOLDYELLOW << ")" << RESET << std::endl << std::endl;
	}

	/**
	 * Get the total number of assertions in this test
	 * @return The total number of assertions
	 */
	uint Test::GetTotalAssertions() const
	{
		return _totalAssertions;
	}

	/**
	 * Get the number of failed assertions in this test
	 * @return The number of failed assertions
	 */
	uint Test::GetFailedAssertions() const
	{
		return _failedAssertions;
	}

}	// Namespace