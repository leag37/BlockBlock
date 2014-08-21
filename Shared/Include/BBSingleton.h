// Filename: BBSingleton.h
// Author: Gael Huber
#ifndef __BBSINGLETON_H__
#define __BBSINGLETON_H__

#include "BBPlatform.h"

namespace BlockBlock
{
    /** \addtogroup Core
     *	@{
     */

    /**
     * Defines a singleton implementation for a class
     */
    template <typename Type>
        class Singleton
        {
            public:
                /**
                 * Default constructor
                 */
                Singleton();

                /**
                 * Destructor
                 */
                virtual ~Singleton();

            private:
                /**
                 * Copy constructor
                 * @param other The singleton instance to copy
                 */
                Singleton(const Singleton& other);

                /**
                 * Assignment operator
                 * @param other The singleton instance to assign
                 * @return The resultant singleton
                 */
                Singleton& operator=(const Singleton& other);

            protected:
                /**
                 * Singleton instance
                 */
                static Type* _instance;
        };

#include "BBSingleton.inl"

    /** @} */

}	// Namespace

#endif // __BBSINGLETON_H__
