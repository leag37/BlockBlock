// Filename: BBTimer.h
// Author: Gael Huber
#ifndef __BBTIMER_H__
#define __BBTIMER_H__

#include "BBPlatform.h"

#include <sys/time.h>
#include <iostream>

namespace BlockBlock
{
	/** \addtogroup
	*	@{
	*/

	#define MICROSECONDS_PER_SECOND 1000000

	/**
	* A timer keeps track of the passage of time, both cumulative time since last reset and the delta
	* since the last poll interval
	*/
	class Timer
	{
	public:
		/**
		* Default constructor
		*/
		Timer();

		/**
		* Copy constructor
		* @param
		*	const Timer& The timer to copy
		*/
		Timer(const Timer&);

		/**
		* Destructor
		*/
		~Timer();

		/**
		* Assignment operator
		* @param
		*	const Timer& The timer to copy
		* @return
		*	Timer& The resultant timer
		*/
		Timer& operator=(const Timer&);

		/**
		* Start the clock
		* @return
		*	bool Returns true if the clock was started successfully
		*/
		bool Start();

		/**
		* Stop the clock
		*/
		void Stop();

		/**
		* Reset the clock
		*/
		void Reset();

		/**
		* Zero the clock
		*/
		void Zero();

		/**
		* Update the timer for this polling interval
		*/
		void Update();

		/**
		* Get the delta for this timer in milliseconds
		* @return
		*	long The delta for the timer
		*/
		long GetDeltaTimeMs() const;

		/**
		* Get the current elapsed time since starting the clock
		* @return
		*	long The elapsed time in milliseconds
		*/
		long GetElapsedTimeMs() const;

	private:
		/**
		* The time when the timer was started
		*/
		timeval _start;

		/**
		* The time time when the timer was stopped
		*/
		timeval _stop;

		/**
		* The time at the previous update call
		*/
		timeval _previous;

		/**
		* The time from the most recent update call
		*/
		timeval _current;
	};

	/** @} */

}	// Namespace

#endif // __BBTIMER_H__