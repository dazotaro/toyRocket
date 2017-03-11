/*
 * GameManager.cpp
 *
 *  Created on: Jun 4, 2015
 *      Author: jusabiaga
 */

// Local includes
#include "GameManager.hpp"
#include "Timer.hpp"			// JU::Timer
#include "Singleton.hpp"		// JU::Singleton
#include "SDLEventManager.hpp"	// JU::SDLEventManager
#include "SystemLog.hpp"		// JU::SystemLog
// Global includes
#include <cstdio>       // std::printf

namespace JU
{

GameManager::GameManager () : SDL_event_manager_(nullptr), running_(true)
{
	// TODO Auto-generated constructor stub

}


GameManager::~GameManager ()
{
	// TODO Auto-generated destructor stub
}


bool GameManager::initialize()
{
	// WINDOW
	// ------
	if (!window_.initialize(1280, 720))
	{
		std::printf("Window failed to initialize!!!\n");
		return false;
	}

	// SDL EVENT MANAGER
	// -----------------
	SDL_event_manager_ = JU::Singleton<JU::SDLEventManager>::getInstance();
	if (!SDL_event_manager_->initialize())
	{
		std::printf("Input Manager failed to initialize!!!\n");
		return false;
	}
	// Register window resize event
	SDL_event_manager_->attachEventHandler(SDL_WINDOWEVENT, "MainWindowResize", &window_);

	// KEYBOARD
	// --------
	Keyboard* pkeyboard = JU::Singleton<Keyboard>::getInstance();
	pkeyboard->reset();
	// Register window resize event
	SDL_event_manager_->attachEventHandler(SDL_KEYDOWN, "Keydown", pkeyboard);
	SDL_event_manager_->attachEventHandler(SDL_KEYUP, 	"Keyup",   pkeyboard);

	// GAME STATE MANAGER
	// ------------------
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
	Timer timer;
	timer.start();

	while(running_)
	{
		uint32 time = timer.getTicks();
		timer.start();

		SDL_event_manager_->update();
		if (SDL_event_manager_->quitting() || Singleton<Keyboard>::getInstance()->isKeyDown(SDL_SCANCODE_ESCAPE))
		{
			running_ = false;
			break;
		}
		state_manager_.update(time);
		state_manager_.draw();
		window_.render();

		// For debugging purposes
		SystemLog::printAllLogs();
		SystemLog::clarAllLogs();
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
