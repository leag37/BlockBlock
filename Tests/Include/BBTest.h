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
	 * Text output colors
	 */
	#define RESET   "\033[0m"
	#define BLACK   "\033[30m"      /* Black */
	#define RED     "\033[31m"      /* Red */
	#define GREEN   "\033[32m"      /* Green */
	#define YELLOW  "\033[33m"      /* Yellow */
	#define BLUE    "\033[34m"      /* Blue */
	#define MAGENTA "\033[35m"      /* Magenta */
	#define CYAN    "\033[36m"      /* Cyan */
	#define WHITE   "\033[37m"      /* White */
	#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
	#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
	#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
	#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
	#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
	#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
	#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
	#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

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
		 * Macro for proper logging on AssertEquals
		 */
		#define AssertEquals(expected, actual) _AssertEquals(expected, actual, __FILE__, __PRETTY_FUNCTION__, __LINE__)

		/**
		 * Macro for proper logging on AssertNotEquals
		 */
		#define AssertNotEquals(expected, actual) _AssertNotEquals(expected, __FILE__, __PRETTY_FUNCTION__, __LINE__)

		/**
		 * Asserts whether two values are equal
		 * @param expected The expected value
		 * @param actual The actual value
		 * @param fileName The filename containing the calling function
		 * @param funcName The function name of the calling function
		 * @param lineNumber The line number for the invocation of the assertion
		 *	in the file containing the calling function
		 */
		template <typename Type>
		void _AssertEquals(Type expected, Type actual, 
			const char* fileName, const char* funcName, int lineNumber)
		{
			// Increment assertions
		 	++_totalAssertions;

		 	// Compare
	 		if((expected == actual) == false)
	 		{
	 			// Fail
	 			++_failedAssertions;
	 			LogFailure(expected, actual, "AssertEquals", fileName, funcName, lineNumber);	
	 		}
		}

		 /**
		 * Asserts whether two values are not equal
		 * @param expected The expected value
		 * @param actual The actual value
		 * @param fileName The filename containing the calling function
		 * @param funcName The function name of the calling function
		 * @param lineNumber The line number for the invocation of the assertion
		 *	in the file containing the calling function
		 */
		template <typename Type>
		void _AssertNotEquals(Type expected, Type actual,
			const char* fileName, const char* funcName, int lineNumber)
		{
			++_totalAssertions;
			if((expected != actual) == false)
			{
				// Fail
 				++_failedAssertions;
 				LogFailure(expected, actual, "AssertNotEquals", fileName, funcName, lineNumber);
			}
		}

		/**
		 * Output failure text to log
		 * @param expected The expected value
		 * @param actual The actual value
		 * @param fileName The filename containing the calling function
		 * @param funcName The function name of the calling function
		 * @param lineNumber The line number for the invocation of the assertion
		 *	in the file containing the calling function
		 */
		template <typename Type>
		void LogFailure(Type expected, Type actual, 
			const char* assertion, const char* fileName, const char* funcName, int lineNumber)
		{
			std::cout << RED << assertion << " failed; " << RESET << "expected " << expected << ", got " << actual << std::endl;
 			std::cout << "Failure in " << funcName << " line " << lineNumber << " (" << fileName << ")" << std::endl;
		}
	};

	/** @} */

}	// Namespace

#endif // __BBITEST_H__