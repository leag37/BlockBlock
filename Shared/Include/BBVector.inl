// Filename: BBVector.inl
// Author: Gael Huber

/**
 * Default constructor
 */
template <typename Type, typename Allocator>
Vector<Type, Allocator>::Vector()
	:	_elementCount(0),
		_elementCapacity(1),
		_array(0)
{
	// Create start capacity
	_array = _allocator.Allocate(_elementCapacity);
}

/**
 * Default constructor. 
 * Constructs an empty container with no elements.
 * @param allocator The allocator for this vector (if not specified, use default allocator)
 */
template <typename Type, typename Allocator>
Vector<Type, Allocator>::Vector(const Allocator& allocator)
	:	_allocator(allocator),
		Vector()
{
}

/**
 * Fill constructor.
 * Constructs a container with n elements.
 * @param n The number of elements to pre-allocate
 * @param allocator The allocator for this vector (if not specified, use default allocator)
 */
template <typename Type, typename Allocator>
Vector<Type, Allocator>::Vector(uint n, const Allocator& allocator)
	:	_allocator(allocator),
		_elementCount(n),
		_elementCapacity(n),
		_array(0)
{
	// Create a default type
	Type defaultType = Type();
	_array = _allocator.Allocate(_elementCapacity);
	for(uint i = 0; i < _elementCount; ++i)
	{
		_array[i] = defaultType;
	}
}

/**
 * Fill constructor
 * Constructs a container with n elements, populated with the value provided
 * @param n The number of elements to pre-allocate
 * @param val The default value of the elements
 * @param allocator The allocator for this vector (if not specified, use default allocator)
 */
template <typename Type, typename Allocator>
Vector<Type, Allocator>::Vector(uint n, const Type& val, const Allocator& allocator)
	:	_allocator(allocator),
		_elementCount(n),
		_elementCapacity(n),
		_array(0)
{
	_array = _allocator.Allocate(_elementCapacity);
	for(uint i = 0; i < n; ++i)
	{
		_array[i] = val;
	}
}

/**
 * Range constructor
 * Constructs a container with as many elements as the range (first, last), which each element
 * copied into the vector in order.
 * @param first The first iterator value in the set
 * @param last The last iterator value in the set
 */
//template <typename Type, typename Allocator>
//template <class InputIterator>
//Vector<Type, Allocator>::Vector(InputIterator first, InputIterator last);

/**
 * Copy constructor.
 * Copies an existing container to this container.
 * @param other The container whose contents will be copied
 */
template <typename Type, typename Allocator>
Vector<Type, Allocator>::Vector(const Vector& other)
	:	_allocator(other._allocator),
		_elementCount(other._elementCount),
		_elementCapacity(other._elementCapacity),
		_array(0)
{
	_array = _allocator.Allocate(_elementCapacity);
	for(uint i = 0; i < _elementCount; ++i)
	{
		_array[i] = other._array[i];
	}
}

/**
 * Destructor
 */
template <typename Type, typename Allocator>
Vector<Type, Allocator>::~Vector()
{
	// If the array exists, deallocate it
	if(_array)
	{
		_allocator.Deallocate(_array);
	}
}

/**
 * Assignment operator.
 * Assign the contents of a vector to this iterator.
 * @param other The vector to copy
 */
template <typename Type, typename Allocator>
Vector<Type, Allocator>& Vector<Type, Allocator>::operator=(const Vector& other)
{
	// Self assignment guard
	if(this == &other)
	{
		return *this;
	}

	// If the array exists, erase it first
	if(_array)
	{
		_allocator.Deallocate(_array);
	}

	// Copy all the elements
	_allocator = other._allocator;
	_elementCount = other._elementCount;
	_elementCapacity = other._elementCapacity;
	_array = _allocator.Allocate(_elementCount);
	for(uint i = 0; i < _elementCount; ++i)
	{
		_array[i] = other._array[i];
	}
	
	return *this;
}

/**
 * Get an iterator to the start of the container
 * @return An iterator to the first element in the container
 */
//Iterator Begin();

/**
 * Get a constant iterator to the start of the container
 * @return A constant iterator to the first element in the container
 */
//ConstIterator Begin() const;

/**
 * Get an iterator to the end of the container
 * @return An iterator to one block past the last element in the container
 */
//Iterator End();

/**
 * Get a const iterator to the end of the container
 * @return A const iterator to one block past the last element in the container
 */
//ConstIterator End() const;

/**
 * Get a reverse iterator to the last element of the container
 * @return A reverse iterator to the last element in the container
 */
//ReverseIterator RBegin();

/**
 * Get a constant reverse iterator to the last element of the container
 * @return A constant reverse iterator to the last element in the container
 */
//ConstReverseIterator RBegin() const;

/**
 * Get a reverse iterator to the element that precedes the first element of the container
 * @return A reverse iterator that precedes the frist element of the container by one
 */
//ReverseIterator REnd();

/**
 * Get a const iterator to the end of the container
 * @return A const iterator to one block past the last element in the container
 */
//ConstReverseIterator REnd() const;

/**
 * Return the current size of the container
 * @return The number of elements in the container
 */
template <typename Type, typename Allocator>
uint Vector<Type, Allocator>::Size() const
{
	return _elementCount;
}

/**
 * Return the maximum number of elements that can be stored in a vector
 * @return The maximum number of elements that can be stored in a vector-type container
 */
template <typename Type, typename Allocator>
uint Vector<Type, Allocator>::MaxSize() const
{
	return 0u - 1u;
}

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
//template <typename Type, typename Allocator>
//void Vector<Type, Allocator>::Resize(uint n, Type val = Type());

/**
 * Return the current capacity in number of elements for this container.
 * @return The current number of elements that this container can hold
 */
template <typename Type, typename Allocator>
uint Vector<Type, Allocator>::Capacity() const
{
	return _elementCapacity;
}

/**
 * Returns whether the \ref Vector is currently empty.
 * @return Returns true if the \ref Size is 0
 */
template <typename Type, typename Allocator>
bool Vector<Type, Allocator>::Empty() const
{
	return _elementCount == 0;
}

/**
 * Requests that the \ref Vector \ref Capacity be enough to contain at least n elements.
 * If n is greater than the current \ref Capacity, the container will resize to fit n
 * elements. Otherwise, if the \ref Capacity is already sufficiently large, no resizing
 * will occur.
 * @param size The number of elements required to fit
 */
//template <typename Type, typename Allocator>
//void Vector<Type, Allocator>::Reserve(uint size);

/**
 * Access operator. Returns the element at the specified index. This function does not check 
 * against bounds.
 * @param index The index to access
 * @return Return the array element contained at the index specified
 */
template <typename Type, typename Allocator>
Type& Vector<Type, Allocator>::operator[](uint n)
{
	return _array[n];
}

/**
 * Access operator. Returns the element at the specified index. This function does not check 
 * against bounds.
 * @param index The index to access
 * @return Return the array element contained at the index specified
 */
template <typename Type, typename Allocator>
const Type& Vector<Type, Allocator>::operator[](uint n) const
{
	return _array[n];
}

/**
 * Access operator. Returns the element at the specified index. This function does check 
 * against bounds.
 * @param index The index to access
 * @return Return the array element contained at the index specified
 */
template <typename Type, typename Allocator>
Type& Vector<Type, Allocator>::At(uint n)
{
	// TODO: Throw out of range exception
	if(n >= _elementCount)
	{
		//throw OutOfRangeException(n, _elementCount);
	}

	return _array[n];
}

/**
 * Access operator. Returns the element at the specified index. This function does check 
 * against bounds.
 * @param index The index to access
 * @return Return the array element contained at the index specified
 */
template <typename Type, typename Allocator>
const Type& Vector<Type, Allocator>::At(uint n) const
{
	// TODO: Throw out of range exception
	if(n >= _elementCount)
	{
		//throw OutOfRangeException(n, _elementCount);
	}

	return _array[n];
}

/**
 * Returns the first element in the container.
 * @return This returns a reference to the first element in the container
 */
template <typename Type, typename Allocator>
Type& Vector<Type, Allocator>::Front()
{
	return _array[0];
}

/**
 * Returns the first element in the container.
 * @return This returns a reference to the first element in the container
 */
template <typename Type, typename Allocator>
const Type& Vector<Type, Allocator>::Front() const
{
	return _array[0];
}

/**
 * Returns the last element in the container.
 * @return This returns a reference to the last element in the container
 */
template <typename Type, typename Allocator>
Type& Vector<Type, Allocator>::Last()
{
	return _array[_elementCount - 1];
}

/**
 * Returns the last element in the container.
 * @return This returns a reference to the last element in the container
 */
template <typename Type, typename Allocator>
const Type& Vector<Type, Allocator>::Last() const
{
	return _array[_elementCount - 1];
}

/**
 * Given a range of elements first to last, modify the contents of the \ref Vector
 * such that it now contains the elements from first to last inclusive
 * @param first The first element in the range
 * @param last The last element in the range
 */
//template <typename Type, typename Allocator>
//template <class InputIterator>
//void Vector<Type, Allocator>::Assign(InputIterator first, InputIterator last);

/**
 * Given a number of elements n and a base value val, fill the array with n copies
 * of val.
 * @param n The number of elements to fill
 * @param val The value to assign to each element
 */
//template <typename Type, typename Allocator>
//void Vector<Type, Allocator>::Assign(uint n, const Type& val);

/**
 * Add an element to end of the \ref Vector after the current last element
 * @param val The value to add to the container
 */
template <typename Type, typename Allocator>
void Vector<Type, Allocator>::PushBack(const Type& val)
{
	// If the current size is equal to the capacity, grow the array
	if(_elementCount == _elementCapacity)
	{
		// Double the capacity
		_elementCapacity *= 2;

		// Allocate a new array and copy the elements
		Type* tArray = _allocator.Allocate(_elementCapacity);
		for(uint i = 0; i < _elementCount; ++i)
		{
			tArray[i] = _array[i];
		}

		// Free the old array
		_allocator.Deallocate(_array);

		// Assign new array
		_array = tArray;
	}

	// Push back a new element
	_array[_elementCount++] = val;
}

/**
 * Removes the last element in the container.
 */
template <typename Type, typename Allocator>
void Vector<Type, Allocator>::PopBack()
{
	// Assign default term to back and decrease count
	_array[_elementCount--] = Type();
}

/**
 * Insert a single element into the container at a specified position.
 * @param position The position at which to insert
 * @param val The value to insert
 * @return An iterator that points to the first of the newly inserted elements
 */
//template <typename Type, typename Allocator>
//Iterator Vector<Type, Allocator>::Insert(Iterator position, const Type& val);

/**
 * Insert a single element into the container n times at a specified position.
 * @param position The position at which to insert
 * @param n The number of times to insert the element
 * @param val The value to insert
 * @return An iterator that points to the first of the newly inserted elements
 */
//template <typename Type, typename Allocator>
//Iterator Vector<Type, Allocator>::Insert(Iterator position, uint n, const Type& val);

/**
 * Insert a range of elements into the container at a specified position.
 * @param position The position at which to insert
 * @param first The first element in the range to insert
 * @param last The last element in the range to insert
 * @return An iterator that points to the first of the newly inserted elements
 */
//template <typename Type, typename Allocator>
//template <class InputIterator>
//Iterator Vector<Type, Allocator>::Insert(Iterator position, InputIterator first, InputIterator last);

/**
 * Erases the element in the specified position
 * @param position The position at which to erase
 * @return The iterator pointing to the first element after the erased element
 */
//template <typename Type, typename Allocator>
//Iterator Vector<Type, Allocator>::Erase(Iterator position);

/**
 * Erases the range of elements in the specified position
 * @param first The first element in the range to erase
 * @param last The last element in the range to erase
 * @return The iterator pointing to the first element after the erased range
 */
//template <typename Type, typename Allocator>
//Iterator Vector<Type, Allocator>::Erase(Iterator first, Iterator last);

/**
 * Swap the contents of this vector with another vector
 * @param other The \ref Vector with which to swap contents
 */
//template <typename Type, typename Allocator>
//void Vector<Type, Allocator>::Swap(Vector& other);

/**
 * Clears the \ref Vector of its elements, destroying each element.
 */
//template <typename Type, typename Allocator>
//void Vector<Type, Allocator>::Clear();
