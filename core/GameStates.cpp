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


bool DefaultGameState::update()
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
