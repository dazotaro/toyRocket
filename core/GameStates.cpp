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


bool DefaultGameState::load()
{
	return true;
}


bool DefaultGameState::initialize()
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


bool DefaultGameState::free()
{
	return true;
}


bool DefaultGameState::unload()
{
	return true;
}


} /* namespace JU */
