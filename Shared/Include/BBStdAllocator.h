// Filename: BBStdAllocator.h
// Author: Gael Huber
#ifndef __BBSTDALLOCATOR_H__
#define __BBSTDALLOCATOR_H__

#include "BBPlatform.h"

#include <stdlib.h>

namespace BlockBlock
{
	/** \addtogroup Core
	 *	@{
	 */

	/**
	 * A standard memory StdAllocator. This uses a very dumb allocation pattern and does nothing against fragmentation.
	 */
	template <typename Type>
	class StdAllocator
	{
	public:
		/**
		 * A pointer to this type
		 */
		typedef Type* Pointer;

		/**
		 * A constant pointer to this type
		 */
		typedef const Type* ConstPointer;

		/**
		 * A reference to this type
		 */
		typedef Type& Reference;

		/**
		 * A constant reference to this type
		 */
		typedef const Type& ConstReference;

		/**
		 * This type as a value
		 */
		typedef Type Value;

		/**
		 * Default constructor
		 */
		StdAllocator()
		{

		}

		/**
		 * Copy constructor
		 * @param other The StdAllocator to copy
		 */
		StdAllocator(const StdAllocator& other)
		{

		}

		/**
		 * Destructor
		 */
		~StdAllocator()
		{

		}

		/**
		 * Allocate a block of memory for this type
		 * @param numElements The number of elements of the specified type to allocate
		 * @return A pointer to the allocated memory block
		 */
		Pointer Allocate(uint numElements)
		{
			return static_cast<Pointer>(malloc(numElements * sizeof(Type)));
		}

		/**
		 * Free a block of memory
		 * @param pointer The pointer to the address of the memory block to free
		 */
		void Deallocate(Pointer pointer)
		{
			free(static_cast<void*>(pointer));
		}

		/**
		 * Reallocate this block of memory with a larger size
		 * @param pointer A pointer to the current block of memory
		 * @param numElements The new number of elements for this allocation
		 */
		Pointer Reallocate(Pointer pointer, uint numElements)
		{
			return static_cast<Pointer>(realloc(pointer, numElements * sizeof(Type)));
		}

		/**
		 * The maximum number of elements that can be allocated in a single call to this function
		 * @return The max number of elements to allocate in a single call
		 */
		uint MaxSize() const
		{
			return uint(-1) / sizeof(Type);
		}

		/**
		 * The address of a memory block
		 * @param reference The reference to the object
		 * @return A pointer to the address of the object
		 */
		Pointer Address(Reference& reference) const
		{
			return &reference;
		}

		/**
		 * The address of a memory block
		 * @param reference The reference to the object
		 * @return A pointer to the address of the object
		 */
		ConstPointer Address(ConstReference& reference) const
		{
			return &reference;
		}
	};

	/** @} */

}	// Namespace


#endif // __BBSTDALLOCATOR_H__