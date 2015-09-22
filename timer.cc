/*
 * timer.cc
 *
 *  Created on: 25 nov 2013
 *      Author: bleh
 */
#include "timer.h"

Timer::Timer()
{
	//initialize
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}

void Timer::Start()
{
	//start
	started = true;

	//Unpause
	paused = true;

	//Get the current clock
	startTicks = SDL_GetTicks();
}

void Timer::Stop()
{
	//stop timer
	started = false;

	//unpause timer
	paused = false;
}

void Timer::Unpause()
{
	//If the timer is paused
	if ( paused == true )
	{
		//Unpause the timer
		paused = false;

		//reset the starting ticks
		startTicks = SDL_GetTicks() - pausedTicks;

		//Reset the paused ticks
		pausedTicks = 0;
	}
}

int Timer::get_ticks()
{
	//If the timer is running
	if ( started == true )
	{
		//If the timer is paused
		if ( paused == true )
		{
			//Return the number of ticks when the timer was paused
			return pausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			return SDL_GetTicks() - startTicks;
		}
	}
	//If the timer isnt running
	return 0;
}

bool Timer::is_started()
{
	return started;
}

bool Timer::is_paused()
{
	return paused;
}
