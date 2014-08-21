// Filename: BBTimer.cpp
// Author: Gael Huber
#include "BBTimer.h"

namespace BlockBlock
{
	/**
	* Default constructor
	*/
	Timer::Timer()
	{

	}

	/**
	* Copy constructor
	* @param other The timer to copy
	*/
	Timer::Timer(const Timer& other)
		:	_start(other._start),
			_stop(other._stop),
			_previous(other._previous),
			_current(other._current)
	{

	}

	/**
	* Destructor
	*/
	Timer::~Timer()
	{

	}

	/**
	* Assignment operator
	* @param other The timer to copy
	* @return The resultant timer
	*/
	Timer& Timer::operator=(const Timer& other)
	{
		_start = other._start;
		_stop = other._stop;
		_previous = other._previous;
		_current = other._current;
		return *this;
	}

	/**
	* Start the clock
	* @return Returns true if the clock was started successfully
	*/
	bool Timer::Start()
	{
		// Set the start time
		if(gettimeofday(&_start, NULL) == -1)
		{
			return false;
		}

		// Update current, previous, and stop
		// Stop must be set in order to ensure that pause-unpause type bevavious is correctly registered
		_current = _previous = _stop = _start;
		return true;
	}

	/**
	* Stop the clock
	*/
	void Timer::Stop()
	{
		// Poll for the stop time
		gettimeofday(&_stop, NULL);

		// Update the previous and current as during a regular time step
		_previous = _current;
		_current = _stop;
	}

	/**
	* Reset the clock such that the start time matches the current time
	*/
	void Timer::Reset()
	{
		_start = _current;
	}

	/**
	* Zero the clock
	*/
	void Timer::Zero()
	{
		_start.tv_sec = 0;
		_start.tv_usec = 0;

		_current = _previous = _stop = _start;
	}

	/**
	* Update the timer for this polling interval
	*/
	void Timer::Update()
	{
		// Set the previous time to the existing current time
		_previous = _current;

		// Update the current time
		if(gettimeofday(&_current, NULL) == -1)
		{
			printf("ERROR");
		}
	}

	/**
	* Get the delta for this timer in milliseconds
	* @return The delta for the timer
	*/
	long Timer::GetDeltaTimeMs() const
	{
		// Calculate the difference between seconds and milliseconds, 
		// then convert both to milliseconds and add the two
		long seconds = _current.tv_sec - _previous.tv_sec;
		long milliseconds = static_cast<long>(_current.tv_usec - _previous.tv_usec);
		return (seconds * MICROSECONDS_PER_SECOND) + milliseconds;
	}

	/**
	* Get the current elapsed time since starting the clock
	* @return The elapsed time in milliseconds
	*/
	long Timer::GetElapsedTimeMs() const
	{
		// Calculate the total time between _start and _current
		long seconds = _current.tv_sec - _start.tv_sec;
		long milliseconds = static_cast<long>(_current.tv_usec - _start.tv_usec);
		return (seconds * MICROSECONDS_PER_SECOND) + milliseconds;
	}

}	// Namespace
