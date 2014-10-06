// Filename: BBTestVector.cpp
// Author: Gael Huber
#include "BBTestVector.h"
#include "BBVector.h"

#include <vector>

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
		TestConstructor();
		TestIterator();
		TestSize();
		TestAccessor();
		TestInsertion();
		TestRemove();
	}

	/** 
	 * Test constructing and destructing a vector
	 */
	void TestVector::TestConstructor()
	{
		// Plain Old Data
		//---------------
		
		// Default constructor
		Vector<int> v1;
		AssertEquals(0u, v1.Size());

		// Fill constructor
		Vector<int> v2(3u);
		AssertEquals(3u, v2.Size());
		AssertEquals(3u, v2.Capacity());
		for(uint i = 0; i < 3; ++i)
		{
			AssertEquals(0, v2[i]);
		}

		// Fill constructor with value
		Vector<int> v3(3u, 3);
		AssertEquals(3u, v3.Size());
		AssertEquals(3u, v3.Capacity());
		for(uint i = 0; i < 3; ++i)
		{
			AssertEquals(3, v3[i]);
		}
		 
		// Copy constructor
		Vector<int> v4(v3);
		AssertEquals(3u, v4.Size());
		AssertEquals(3u, v4.Capacity());
		for(uint i = 0; i < 3; ++i)
		{
			AssertEquals(3, v4[i]);
		}
		 
		// Assignment
		Vector<int> v5 = v4;
		AssertEquals(3u, v5.Size());
		AssertEquals(3u, v5.Capacity());
		for(uint i = 0; i < 3; ++i)
		{
			AssertEquals(3, v5[i]);
		}
		
		// Class
		//------
		
		// Default simple object
		SimpleClass c1 = SimpleClass();
		SimpleClass c2 = SimpleClass(1, 2);

		// Default constructor
		Vector<SimpleClass> v6;
		AssertEquals(0u, v6.Size());

		// Fill constructor
		Vector<SimpleClass> v7(3u);
		AssertEquals(3u, v7.Size());
		AssertEquals(3u, v7.Capacity());
		for(uint i = 0; i < 3; ++i)
		{
			AssertEquals(c1, v7[i]);
		}

		// Fill constructor with value
		Vector<SimpleClass> v8(3u, c2);
		AssertEquals(3u, v8.Size());
		AssertEquals(3u, v8.Capacity());
		for(uint i = 0; i < 3; ++i)
		{
			AssertEquals(c2, v8[i]);
		}
		 
		// Copy constructor
		Vector<SimpleClass> v9(v8);
		AssertEquals(3u, v9.Size());
		AssertEquals(3u, v9.Capacity());
		for(uint i = 0; i < 3; ++i)
		{
			AssertEquals(c2, v9[i]);
		}
		 
		// Assignment
		Vector<SimpleClass> v10 = v9;
		AssertEquals(3u, v10.Size());
		AssertEquals(3u, v10.Capacity());
		for(uint i = 0; i < 3; ++i)
		{
			AssertEquals(c2, v10[i]);
		}
	}

	/**
	 * Test iterators
	 */
	void TestVector::TestIterator()
	{
		
	}

	/**
	 * Test sizing, resizing, capacity, reserve, empty
	 */
	void TestVector::TestSize()
	{
		
	}

	/**
	 * Test accessors, front, last
	 */
	void TestVector::TestAccessor()
	{
		
	}

	/**
	 * Test insertion
	 */
	void TestVector::TestInsertion()
	{
		
	}

	/**
	 * Test removing
	 */
	void TestVector::TestRemove()
	{

	}

	/**
	 * Default constructor
	 */
	TestVector::SimpleClass::SimpleClass()
		:	_a(0),
			_b(0)
	{

	}

	/**
	 * Constructor
	 * @param a
	 * @param b
	 */
	TestVector::SimpleClass::SimpleClass(int a, int b)
		:	_a(a),
			_b(b)
	{

	}

	/**
	 * Destructor
	 */
	TestVector::SimpleClass::~SimpleClass()
	{

	}

	/**
	 * @return Returns a
	 */
	int TestVector::SimpleClass::A() const
	{
		return _a;
	}

	/**
	 * @return Returns b
	 */
	int TestVector::SimpleClass::B() const
	{
		return _b;
	}

	/**
	 * @param other The object against which to compre
	 * @return Returns true if the objects are equal in contents
	 */
	bool TestVector::SimpleClass::operator==(const SimpleClass& other)
	{
		return _a == other._a && _b == other._b;
	}

	/**
	 * Stream the contents of this class
	 * @param os The output stream
	 * @return Returns the streamed value
	 */
	std::ostream& operator<<(std::ostream& os, const TestVector::SimpleClass& val)
	{
		os << "{ _a: " << val.A() << ", _b: " << val.B() << "}";
		return os; 
	}

}	// Namespace