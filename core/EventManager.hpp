/*
 * EventManager.hpp
 *
 *  Created on: Jun 4, 2015
 *      Author: jusabiaga
 */

#ifndef EVENTMANAGER_HPP_
#define EVENTMANAGER_HPP_

#include "Keyboard.hpp" // Keyboard

namespace JU
{
    class EventManager
    {
        public:
            EventManager ();
            virtual ~EventManager ();

        public:
            bool initialize();
            bool update();
            bool quitting() const;

        public:
            Keyboard keyboard_;
            bool 	 quit_;
    };

} /* namespace JU */

#endif /* EVENTMANAGER_HPP_ */
