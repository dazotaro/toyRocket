/*
 * GameStates.cpp
 *
 *  Created on: Jun 25, 2015
 *      Author: jusabiaga
 */

#include "GameStates.hpp"

namespace JU
{

DefaultGameState::DefaultGameState() : GameStateInterface("DefaultGameState")
{
}


DefaultGameState::~DefaultGameState()
{
}


bool DefaultGameState::enter()
{
	return true;
}


bool DefaultGameState::synchronize()
{
	return true;
}


bool DefaultGameState::commonEnterSynchronize()
{
	return true;
}


/**
* @brief Update routine
*
* @param time Time elapsed since the last call (in milliseconds)
*/
bool DefaultGameState::update(JU::uint32 time)
{
	return true;
}


bool DefaultGameState::draw()
{
	return true;
}


bool DefaultGameState::exit()
{
	return true;
}


bool DefaultGameState::suspend()
{
	return true;
}


bool DefaultGameState::commonExitSuspend()
{
	return true;
}


} /* namespace JU */
