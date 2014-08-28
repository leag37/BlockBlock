// Filename: BBTestVector.h
// Author: Gael Huber
#ifndef __BBTESTVECTOR_H__
#define __BBTESTVECTOR_H__

#include "BBPlatform.h"
#include "BBTest.h"

namespace BlockBlock
{
	/** \addtogroup Tests
	 *	@{
	 */

	/**
	 * Unit tests for Vector container.
	 */
	class TestVector : public Test
	{
	public:
		/**
		 * Default constructor
		 */
		TestVector();

		/**
		 * Destructor
		 */
		~TestVector();

		/**
		 * Setup the test
		 */
		void Setup();

		/**
		 * Tear down the test
		 */
		void Teardown();

	protected:
		/**
		 * Run the test
		 */
		void RunImpl();

	private:
	};

	 /** @} */

}	// Namespace

#endif // __BBTESTVECTOR_H__