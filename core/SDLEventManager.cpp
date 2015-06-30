/*
 * EventManager.cpp
 *
 *  Created on: Jun 4, 2015
 *      Author: jusabiaga
 */

// Local includes
#include "Defs.hpp"         // uint32

// Global includes
#include <cstdio>   // std::printf
#include "EventManager.hpp"

namespace JU
{
/**
* @brief Default Constructor
*
*/
EventManager::EventManager (): quit_(false)
{
}


/**
* @brief Default Destructor
*
*/
EventManager::~EventManager ()
{
}


/**
* @brief Initializer Function
*
* Initialize all components of input
*
* @return True if successful
*
*/
bool EventManager::initialize()
{
	keyboard_.reset();

	return true;
}


/**
* @brief Update event queue
*
* Go through all the events available since the last update
*
* @return True if successful
*
*/
bool EventManager::update()
{
	static uint32 frame_id = 0;
	frame_id++;
	//Event handler
	SDL_Event event;

	// Send event to AntTweakBar
	//static bool handled = TwEventSDL(&event, SDL_MAJOR_VERSION, SDL_MINOR_VERSION);

//        if (!handled)
//        {
		//Handle events on queue
		while (SDL_PollEvent( &event ) != 0)
		{
			switch(event.type)
			{
				case SDL_QUIT:
					quit_ = true;
					break;

				case SDL_KEYDOWN:
				case SDL_KEYUP:
					keyboard_.handleEvent(event.key);
					break;

				default:
					//std::printf ("Unhandled SDL2 event %i\n", event.type);
					break;
			}
		}
//        }

	return true;
}


bool EventManager::quitting() const
{
	return quit_;
}


} /* namespace JU */
