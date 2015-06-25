/*
 * GameStateFactory.hpp
 *
 *  Created on: Jun 25, 2015
 *      Author: jusabiaga
 */

#ifndef GAMESTATEFACTORY_HPP_
#define GAMESTATEFACTORY_HPP_

#include <string>

namespace JU
{

// Forward Declarations
class GameStateInterface;

class GameStateFactory
{
	public:
		GameStateFactory();
		virtual ~GameStateFactory();

	public:
		virtual GameStateInterface* create(const std::string& state_name) const;
};

} /* namespace JU */

#endif /* GAMESTATEFACTORY_HPP_ */
