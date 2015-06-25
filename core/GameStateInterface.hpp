/*
 * GameState.hpp
 *
 *  Created on: Jun 5, 2015
 *      Author: jusabiaga
 */

#ifndef GAMESTATEINTERFACE_HPP_
#define GAMESTATEINTERFACE_HPP_

#include <string>	// std::string

namespace JU
{

class GameStateInterface
{
    public:
		GameStateInterface(const std::string& name);
		virtual ~GameStateInterface();

		std::string getName() const;

		virtual bool load() = 0;
        virtual bool initialize() = 0;
        virtual bool update() = 0;
        virtual bool draw() = 0;
        virtual bool free() = 0;
        virtual bool unload() = 0;

    protected:
        std::string name_;
};

} /* namespace JU */

#endif /* GAMESTATEINTERFACE_HPP_ */
