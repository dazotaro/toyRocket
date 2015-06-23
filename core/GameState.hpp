/*
 * GameState.hpp
 *
 *  Created on: Jun 5, 2015
 *      Author: jusabiaga
 */

#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <string>	// std::string

namespace JU
{

// Forward Declarations
class GLScene;

class GameState
{
    public:
		GameState();
		virtual ~GameState();

		std::string getName() const;

		virtual bool load();
        virtual bool initialize();
        virtual bool update();
        virtual bool draw();
        virtual bool free();
        virtual bool unload();

        void registerGLScene(GLScene* scene);

    protected:
        std::string name_;
        GLScene* 	p_scene_;
};

} /* namespace JU */

#endif /* GAMESTATE_HPP_ */
