/*
 * GameStateManager.hpp
 *
 *  Created on: Jun 2, 2015
 *      Author: jusabiaga
 */

#ifndef GAMESTATEMANAGER_HPP_
#define GAMESTATEMANAGER_HPP_

// Local Includes
#include "PropertyTreeInterface.hpp"	// PropertyTreeInterface
// Global Includes
#include <string>						// std::string
#include <map>  						// std::map

namespace JU
{

// Forward Declarations
class GameStateInterface;

class GameStateManager : public PropertyTreeInterface
{
		enum Status
		{
			IDLE,
			RUNNING,
			SUSPENDED
		};

    public:
        GameStateManager ();
        virtual ~GameStateManager ();

        // Interface Functions
        virtual bool initialize();
        virtual void exit();
        virtual void update();
		virtual bool draw();
		void addState(const char* name, GameStateInterface* game_state);
		bool changeState(const char* name);

    public:
		// PropertyTreeInterface
		// ----------------------
        // It returns the [XML,JSON] tag of object
        virtual const char* getTag() const { return "GameStateManager"; }
        // Given a property tree, it imports its contents into the object
        virtual bool importFromPropertyTree(const boost::property_tree::ptree& pt);
        // It exports the contents of the object to a property tree
        virtual bool exportToPropertyTree(boost::property_tree::ptree& pt) const;


    private:
		// Type Definitions
		typedef std::map<std::string, GameStateInterface*> StateMap;
		typedef StateMap::iterator StateMapIter;
		// Member Variables
		StateMap 			state_map_;
		StateMapIter		curr_state_;
		Status				status_;
};

} /* namespace JU */

#endif /* GAMESTATEMANAGER_HPP_ */
