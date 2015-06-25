/*
 * GameStates.hpp
 *
 *  Created on: Jun 25, 2015
 *      Author: jusabiaga
 */

#ifndef GAMESTATES_HPP_
#define GAMESTATES_HPP_

#include "GameStateInterface.hpp"		// JU::GameStateInterface

namespace JU
{

class DefaultGameState : public GameStateInterface
{
	public:
		DefaultGameState();
		virtual ~DefaultGameState();

	public:
		// GameStateInterface
		// ------------------
		bool load();
        bool initialize();
        bool update();
        bool draw();
        bool free();
        bool unload();
};

} /* namespace JU */

#endif /* GAMESTATES_HPP_ */
