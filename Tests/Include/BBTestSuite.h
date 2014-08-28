// Filename: BBTestSuite.h
// Author: Gael Huber
#ifndef __BBTESTSUITE_H__
#define __BBTESTSUITE_H__

#include "BBPlatform.h"
#include "BBTest.h"

#include <vector>
//#include "BBVector.h"

namespace BlockBlock
{
	/**	\addtogroup Tests
	 *	@{
	 */

	/**
	 * Driver for a test suite
	 */
	class TestSuite
	{
	public:
		/**
		 * Default constructor
		 */
		TestSuite();

		/**
		 * Destructor
		 */
		~TestSuite();

		/**
		 * Initialize the test suite
		 * @return Returns true if successfully initialized
		 */
		bool Initialize();

		/**
		 * Shut down the suite
		 */
		void Shutdown();

		/**
		 * Run the test suite
		 */
		void Run();

	private:
		/**
		 * Vector of tests to run
		 */
		 std::vector<Test*> _tests;
		//Vector<ITest*> _tests;
	};

	/** @} */

}	// Namespace

#endif // __BBTESTSUITE_H__