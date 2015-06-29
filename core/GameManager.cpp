/*
 * GameManager.cpp
 *
 *  Created on: Jun 4, 2015
 *      Author: jusabiaga
 */

// Local includes
#include "GameManager.hpp"
#include "Timer.hpp"		// JU::Timer
// Global includes
#include <cstdio>       // std::printf

namespace JU
{

GameManager::GameManager () : running_(true)
{
	// TODO Auto-generated constructor stub

}


GameManager::~GameManager ()
{
	// TODO Auto-generated destructor stub
}


bool GameManager::initialize()
{
	if (!window_.initialize(800, 600))
	{
		std::printf("Window failed to initialize!!!\n");
		return false;
	}

	if (!event_manager_.initialize())
	{
		std::printf("Input Manager failed to initialize!!!\n");
		return false;
	}

	if (!state_manager_.initialize())
	{
		std::printf("Input Manager failed to initialize!!!\n");
		return false;
	}

	running_= true;

	return true;
}


void GameManager::loop()
{
	// FPS Calculation
	uint32 counted_frames = 0;
	Timer timer;
	timer.start();

	while(running_)
	{
		uint32 time = timer.getTicks();
		if (time > 1000)
		{
			//Calculate and correct fps
			float avgFPS = counted_frames  * 1000.0f / time;
			if( avgFPS > 2000000 )
			{
				avgFPS = 0;
			}

			std::printf("FPS = %f\n", avgFPS);
			timer.start();
			counted_frames = 0;
		}
		else
			counted_frames++;

		event_manager_.update();
		if (event_manager_.quitting())
		{
			running_ = false;
			break;
		}
		state_manager_.update();
		state_manager_.draw();
		window_.render();
	}
	state_manager_.exit();
}


void GameManager::exit()
{

}


GameStateManager& GameManager::getStateManager()
{
	return state_manager_;
}

} /* namespace JU */
