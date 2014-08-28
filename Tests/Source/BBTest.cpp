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
		std::cout << "Running " << _name << "..." << std::endl;

		// Setup
		Setup();

		// Run the implementation
		RunImpl();

		// Tear down
		Teardown();

		// Final output
		std::cout << "Completed " << _name << " with " << _totalAssertions << " assertions (" << _failedAssertions << " failed)" << std::endl << std::endl;
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