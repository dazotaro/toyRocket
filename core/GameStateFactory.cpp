/*
 * GameStateFactory.cpp
 *
 *  Created on: Jun 25, 2015
 *      Author: jusabiaga
 */

#include "GameStateFactory.hpp"
#include "GameStates.hpp"			// JU::DefaultGameState

namespace JU
{

GameStateFactory::GameStateFactory()
{
	// TODO Auto-generated constructor stub

}

GameStateFactory::~GameStateFactory()
{
	// TODO Auto-generated destructor stub
}


GameStateInterface* GameStateFactory::create(const std::string& state_name) const
{
	if (state_name == "DefaultGameState")
		return new DefaultGameState();

	return nullptr;
}


} /* namespace JU */
