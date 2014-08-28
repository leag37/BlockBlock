// Filename: BBTest.h
// Author: Gael Huber
#ifndef __BBTEST_H__
#define __BBTEST_H__

#include "BBPlatform.h"

#include <iostream>
#include <string>

namespace BlockBlock
{
	/** \addtogroup Tests
	*	@{
	*/

	/**
	 * Base class used for running unit tests.
	 */
	class Test
	{
	public:
		/**
		 * Default constructor
		 */
		Test();

		/**
		 * Destructor
		 */
		virtual ~Test();

		/**
		 * Setup the test
		 */
		virtual void Setup() = 0;

		/**
		 * Tear down the test
		 */
		virtual void Teardown() = 0;

		/**
		 * Run the test
		 */
		void Run();

		/**
		 * Get the total number of assertions in this test
		 * @return The total number of assertions
		 */
		uint GetTotalAssertions() const;

		/**
		 * Get the number of failed assertions in this test
		 * @return The number of failed assertions
		 */
		uint GetFailedAssertions() const;

	protected:

		/**
		 * Run the test
		 */
		virtual void RunImpl() = 0;

	protected:
		/**
		 * Total number of assertions made
		 */
		uint _totalAssertions;

		/**
		 * Number of failed assertions
		 */
		uint _failedAssertions;

		/**
		 * The string name of this test
		 */
		std::string _name;

	protected:
		/**
		 * Asserts whether two values are equal
		 * @param expected The expected value
		 * @param actual The actual value
		 */
		template <typename Type>
		void AssertEquals(Type expected, Type actual)
		{
		 	// Increment assertions
		 	++_totalAssertions;

		 	// Compare
	 		if((expected == actual) == false)
	 		{
	 			// Fail
	 			++_failedAssertions;

	 			std::cout << "AssertEquals failed; expected " << expected << ", got " << actual << std::endl;
	 		}
		}

		 /**
		 * Asserts whether two values are not equal
		 * @param expected The expected value
		 * @param actual The actual value
		 */
		template <typename Type>
		void AssertNotEquals(Type expected, Type actual)
		{
			++_totalAssertions;
			if((expected != actual) == false)
			{
				// Fail
 				++_failedAssertions;

 				std::cout << "AssertNotEquals failed; result should not be " << expected << ", got " << actual << std::endl;
			}
		}
	};

	/** @} */

}	// Namespace

#endif // __BBITEST_H__