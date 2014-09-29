// Filename: BBVector.h
// Author: Gael Huber
#ifndef __BBVECTOR_H__
#define __BBVECTOR_H__

#include "BBPlatform.h"
#include "BBStdAllocator.h"

namespace BlockBlock
{
	/** \addtogroup Core
	 *	@{
	 */

	/**
	 * A contiguous container that holds a set of data. Vector are random-access.
	 */
	template <typename Type, typename Allocator = StdAllocator<Type> >
	class Vector
	{
	public:
		/**
		 * Iterator
		 */
		class Iterator;

		/**
		 * Constant iterator
		 */
		class ConstIterator;

		/**
		 * Reverse iterator
		 */
		class ReverseIterator;

		/**
		 * Constant reverse iterator
		 */
		class ConstReverseIterator;

	public:
		/**
		 * Default constructor
		 */
		Vector();

		/**
		 * Default constructor. 
		 * Constructs an empty container with no elements.
		 * @param allocator The allocator for this vector (if not specified, use default allocator)
		 */
		explicit Vector(const Allocator& allocator);

		/**
		 * Fill constructor.
		 * Constructs a container with n elements.
		 * @param n The number of elements to pre-allocate
		 * @param allocator The allocator for this vector (if not specified, use default allocator)
		 */
		explicit Vector(uint n, const Allocator& allocator = Allocator());

		/**
		 * Fill constructor
		 * Constructs a container with n elements, populated with the value provided
		 * @param n The number of elements to pre-allocate
		 * @param val The default value of the elements
		 * @param allocator The allocator for this vector (if not specified, use default allocator)
		 */
		explicit Vector(uint n, const Type& val, const Allocator& allocator = Allocator());

		/**
		 * Range constructor
		 * Constructs a container with as many elements as the range (first, last), which each element
		 * copied into the vector in order.
		 * @param first The first iterator value in the set
		 * @param last The last iterator value in the set
		 */
		template <class InputIterator>
		explicit Vector(InputIterator first, InputIterator last);

		/**
		 * Copy constructor.
		 * Copies an existing container to this container.
		 * @param other The container whose contents will be copied
		 */
		Vector(const Vector& other);

		/**
		 * Destructor
		 */
		~Vector();

		/**
		 * Assignment operator.
		 * Assign the contents of a vector to this iterator.
		 * @param other The vector to copy
		 */
		Vector& operator=(const Vector& other);

		/**
		 * Get an iterator to the start of the container
		 * @return An iterator to the first element in the container
		 */
		Iterator Begin();

		/**
		 * Get a constant iterator to the start of the container
		 * @return A constant iterator to the first element in the container
		 */
		ConstIterator Begin() const;

		/**
		 * Get an iterator to the end of the container
		 * @return An iterator to one block past the last element in the container
		 */
		Iterator End();

		/**
		 * Get a const iterator to the end of the container
		 * @return A const iterator to one block past the last element in the container
		 */
		ConstIterator End() const;

		/**
		 * Get a reverse iterator to the last element of the container
		 * @return A reverse iterator to the last element in the container
		 */
		ReverseIterator RBegin();

		/**
		 * Get a constant reverse iterator to the last element of the container
		 * @return A constant reverse iterator to the last element in the container
		 */
		ConstReverseIterator RBegin() const;

		/**
		 * Get a reverse iterator to the element that precedes the first element of the container
		 * @return A reverse iterator that precedes the frist element of the container by one
		 */
		ReverseIterator REnd();

		/**
		 * Get a const iterator to the end of the container
		 * @return A const iterator to one block past the last element in the container
		 */
		ConstReverseIterator REnd() const;

		/**
		 * Return the current size of the container
		 * @return The number of elements in the container
		 */
		uint Size() const;

		/**
		 * Return the maximum number of elements that can be stored in a vector
		 * @return The maximum number of elements that can be stored in a vector-type container
		 */
		uint MaxSize() const;

		/**
		 * Resize the vector so that it contains n elements. If n is smaller than the current \ref Size, the
		 * container is reduced to the first n elements and the remainder of the elements are disposed.
		 * If n is greater than the current \ref Size, the content is expanded by inserting the appropriate
		 * number of elements val at the end of the container until there are n elements. If val is 
		 * specified not specified, the default value for the value-type will be used. If n is greater
		 * than the current \ref Capacity, the container will be resized appropriately.
		 * @param n The number of elements this container should hold
		 * @param val The value used to value-initialize any elements past the existing size
		 */
		void Resize(uint n, Type val = Type());

		/**
		 * Return the current capacity in number of elements for this container.
		 * @return The current number of elements that this container can hold
		 */
		uint Capacity() const;

		/**
		 * Returns whether the \ref Vector is currently empty.
		 * @return Returns true if the \ref Size is 0
		 */
		bool Empty() const;

		/**
		 * Requests that the \ref Vector \ref Capacity be enough to contain at least n elements.
		 * If n is greater than the current \ref Capacity, the container will resize to fit n
		 * elements. Otherwise, if the \ref Capacity is already sufficiently large, no resizing
		 * will occur.
		 * @param size The number of elements required to fit
		 */
		void Reserve(uint size);
		
		/**
		 * Access operator. Returns the element at the specified index. This function does not check 
		 * against bounds.
		 * @param index The index to access
		 * @return Return the array element contained at the index specified
		 */
		Type& operator[](uint n);

		/**
		 * Access operator. Returns the element at the specified index. This function does not check 
		 * against bounds.
		 * @param index The index to access
		 * @return Return the array element contained at the index specified
		 */
		const Type& operator[](uint n) const;

		/**
		 * Access operator. Returns the element at the specified index. This function does check 
		 * against bounds.
		 * @param index The index to access
		 * @return Return the array element contained at the index specified
		 */
		Type& At(uint n);

		/**
		 * Access operator. Returns the element at the specified index. This function does check 
		 * against bounds.
		 * @param index The index to access
		 * @return Return the array element contained at the index specified
		 */
		const Type& At(uint n) const;

		/**
		 * Returns the first element in the container.
		 * @return This returns a reference to the first element in the container
		 */
		Type& Front();

		/**
		 * Returns the first element in the container.
		 * @return This returns a reference to the first element in the container
		 */
		const Type& Front() const;

		/**
		 * Returns the last element in the container.
		 * @return This returns a reference to the last element in the container
		 */
		Type& Last();

		/**
		 * Returns the last element in the container.
		 * @return This returns a reference to the last element in the container
		 */
		const Type& Last() const;

		/**
		 * Given a range of elements first to last, modify the contents of the \ref Vector
		 * such that it now contains the elements from first to last inclusive
		 * @param first The first element in the range
		 * @param last The last element in the range
		 */
		template <class InputIterator>
		void Assign(InputIterator first, InputIterator last);

		/**
		 * Given a number of elements n and a base value val, fill the array with n copies
		 * of val.
		 * @param n The number of elements to fill
		 * @param val The value to assign to each element
		 */
		void Assign(uint n, const Type& val);

		/**
		 * Add an element to end of the \ref Vector after the current last element
		 * @param val The value to add to the container
		 */
		void PushBack(const Type& val);

		/**
		 * Removes the last element in the container.
		 */
		void PopBack();

		/**
		 * Insert a single element into the container at a specified position.
		 * @param position The position at which to insert
		 * @param val The value to insert
		 * @return An iterator that points to the first of the newly inserted elements
		 */
		Iterator Insert(Iterator position, const Type& val);

		/**
		 * Insert a single element into the container n times at a specified position.
		 * @param position The position at which to insert
		 * @param n The number of times to insert the element
		 * @param val The value to insert
		 * @return An iterator that points to the first of the newly inserted elements
		 */
		Iterator Insert(Iterator position, uint n, const Type& val);

		/**
		 * Insert a range of elements into the container at a specified position.
		 * @param position The position at which to insert
		 * @param first The first element in the range to insert
		 * @param last The last element in the range to insert
		 * @return An iterator that points to the first of the newly inserted elements
		 */
		template <class InputIterator>
		Iterator Insert(Iterator position, InputIterator first, InputIterator last);

		/**
		 * Erases the element in the specified position
		 * @param position The position at which to erase
		 * @return The iterator pointing to the first element after the erased element
		 */
		Iterator Erase(Iterator position);

		/**
		 * Erases the range of elements in the specified position
		 * @param first The first element in the range to erase
		 * @param last The last element in the range to erase
		 * @return The iterator pointing to the first element after the erased range
		 */
		Iterator Erase(Iterator first, Iterator last);

		/**
		 * Swap the contents of this vector with another vector
		 * @param other The \ref Vector with which to swap contents
		 */
		void Swap(Vector& other);

		/**
		 * Clears the \ref Vector of its elements, destroying each element.
		 */
		void Clear();
		
	private:
		/**
		 * Allocator used for this vector
		 */
		Allocator _allocator;

		/**
		 * Number of elements currently in the array
		 */
		uint _elementCount;

		/**
		 * Maximum number of elements that can be stored in the container at the current size
		 */
		uint _elementCapacity;

		/**
		 * Pointer to the array
		 */
		Type* _array;
	};

	/** @} */

}	// Namespace

#endif // __BBVECTOR_H__