/*
 * GameManager.hpp
 *
 *  Created on: Jun 4, 2015
 *      Author: jusabiaga
 */

#ifndef GAMEMANAGER_HPP_
#define GAMEMANAGER_HPP_

#include "GameStateManager.hpp" // GameStateManager
#include "../graphics/Window.hpp"           // Window
#include "EventManager.hpp"		// EventManager


namespace JU
{

class GameManager
{
    public:
        GameManager ();
        virtual ~GameManager ();

        virtual bool initialize();
        virtual void loop();
        virtual void exit();

        GameStateManager& getStateManager();

    private:
        GameStateManager state_manager_;
        Window           window_;
        EventManager     event_manager_;

        bool			 running_;
};

} /* namespace JU */

#endif /* GAMEMANAGER_HPP_ */
