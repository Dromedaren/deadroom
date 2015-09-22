/*
 * timer.h
 *
 *  Created on: 25 nov 2013
 *      Author: bleh
 */

#ifndef TIMER_H_
#define TIMER_H_
#include <SDL/SDL.h>
class Timer
{
public:
	//Initializes variables
	Timer();

	//clock actions
	void Start();
	void Stop();
	void Pause();
	void Unpause();

	//gets timers time
	int get_ticks();

	//Checks the status of the timer

	bool is_started();
	bool is_paused();

	int startTicks{0};

private:

	int pausedTicks{0};

	bool paused{false};
	bool started{false};
};
#endif /* TIMER_H_ */
