// Filename: BBPlatform.h
// Author: Gael Huber
#ifndef __BBPLATFORM_H__
#define __BBPLATFORM_H__

namespace BlockBlock
{
    /** \addtogroup Core
     *	@{
     */

    /**
     * Typedef for an unsigned character
     */
    typedef unsigned char uchar;

    /**
     * Typedef for an unsigned short
     */    
    typedef unsigned short ushort;
    
    /**
     * Typedef for an unsigned integer
     */
    typedef unsigned int uint;
    
    /**
     * Typedef for an unsigned long
     */
    typedef unsigned long ulong;
    
    /**
     * Typedef for an unsigned long long (or unsigned 64-bit integer)
     */
    typedef unsigned long long uint64;
    
    /**
     * Typedef for a long long (or 64-bit integer)
     */
    typedef long long int64;

    /**
     * The game ID for this network
     */
    #define GAME_IDENTIFIER 0x6AE0E597

    /** @} */

}	// Namespace

#endif // __BBPLATFORM_H__
