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
	private:
		// Inner class for testing storage
		class SimpleClass;

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
		/** 
		 * Test constructing and destructing a vector
		 */
		void TestConstructor();

		/**
		 * Test iterators
		 */
		void TestIterator();

		/**
		 * Test sizing, resizing, capacity, reserve, empty
		 */
		void TestSize();

		/**
		 * Test accessors, front, last
		 */
		void TestAccessor();

		/**
		 * Test insertion
		 */
		void TestInsertion();

		/**
		 * Test removing
		 */
		void TestRemove();

		/**
		 * Stream the contents of this class
		 * @param os The output stream
		 * @return Returns the streamed value
		 */
		friend std::ostream& operator<<(std::ostream& os, const SimpleClass& val);
	};

	/**
	 * Simple class used for testing storage of structures
	 */
	class TestVector::SimpleClass
	{
	public:
		/**
		 * Default constructor
		 */
		SimpleClass();

		/**
		 * Constructor
		 * @param a
		 * @param b
		 */
		SimpleClass(int a, int b);

		/**
		 * Destructor
		 */
		~SimpleClass();

		/**
		 * @return Returns a
		 */
		int A() const;

		/**
		 * @return Returns b
		 */
		int B() const;

		/**
		 * @param other The object against which to compre
		 * @return Returns true if the objects are equal in contents
		 */
		bool operator==(const SimpleClass& other);

	private:
		int _a;
		int _b;
	};

	 /** @} */

}	// Namespace

#endif // __BBTESTVECTOR_H__