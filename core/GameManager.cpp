/*
 * GameManager.cpp
 *
 *  Created on: Jun 4, 2015
 *      Author: jusabiaga
 */

// Local includes
#include "GameManager.hpp"

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

	if (!input_manager_.initialize())
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
	while(running_)
	{
		input_manager_.update();
		if (input_manager_.quitting())
		{
			running_ = false;
			break;
		}
		state_manager_.update();
		state_manager_.draw();
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
