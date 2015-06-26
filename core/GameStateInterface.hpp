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

		virtual bool enter() 				  = 0;
        virtual bool synchronize() 			  = 0;
        virtual bool commonEnterSynchronize() = 0;
        virtual bool update() 				  = 0;
        virtual bool draw() 				  = 0;
        virtual bool exit() 				  = 0;
        virtual bool suspend() 				  = 0;
        virtual bool commonExitSuspend() 	  = 0;

    protected:
        std::string name_;
};

} /* namespace JU */

#endif /* GAMESTATEINTERFACE_HPP_ */
