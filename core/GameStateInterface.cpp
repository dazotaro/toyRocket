/*
 * GameState.cpp
 *
 *  Created on: Jun 5, 2015
 *      Author: jusabiaga
 */

// Local includes
#include "GameStateInterface.hpp"

namespace JU
{

GameStateInterface::GameStateInterface(const std::string& name) : name_(name)
{
}


GameStateInterface::~GameStateInterface()
{
}


std::string GameStateInterface::getName() const
{
	return name_;
}


} /* namespace JU */
