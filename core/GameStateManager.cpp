/*
 * GameStateManager.cpp
 *
 *  Created on: Jun 2, 2015
 *      Author: jusabiaga
 */

#include "GameStateManager.hpp"
#include "GameStateInterface.hpp"	// GameStateInterface
#include "SystemLog.hpp"			// SystemLog::logMessage

namespace JU
{

GameStateManager::GameStateManager () : status_(IDLE)
{
// TODO Auto-generated constructor stub

}


GameStateManager::~GameStateManager ()
{

}


bool GameStateManager::initialize()
{
	status_ = IDLE;

    return true;
}


void GameStateManager::exit()
{
	status_ = SUSPENDED;

	for (StateMapIter iter = state_map_.begin(); iter != state_map_.end(); ++iter)
	{
		iter->second->commonExitSuspend();
		iter->second->exit();
		delete iter->second;
	}
}


/**
* @brief Update routine
*
* @param time   Time elapsed since the last call in milliseconds
*/
void GameStateManager::update(JU::uint32 time)
{
	if (status_ == IDLE)
	{
		curr_state_->second->enter();
		curr_state_->second->commonEnterSynchronize();

		status_ = RUNNING;
	}
	if (RUNNING)
	{
		curr_state_->second->update(time);
	}
}

bool GameStateManager::draw()
{
	curr_state_->second->draw();

	return true;
}


void GameStateManager::addState(const char* name, GameStateInterface* game_state)
{
	if (state_map_.find(name) != state_map_.end())
	{
		SystemLog::logMessage("GameStateManager", "addState(), state already exits");
		exit();
	}
	state_map_[name] = game_state;
}


bool GameStateManager::changeState(const char* name)
{
	StateMapIter state_iter = state_map_.find(name);

	if (state_iter == state_map_.end())
	{
		SystemLog::logMessage("GameStateManager", "changeState(), state does not exits");

		return false;
	}

	curr_state_ = state_iter;

	return true;
}


// Given a property tree, it imports its contents into the object
bool GameStateManager::importFromPropertyTree(const boost::property_tree::ptree& pt)
{
	/*
    std::string current_state = pt.get<std::string>("current_state");

    boost::property_tree::ptree children = pt.get_child("states");
    for (boost::property_tree::ptree::const_iterator node_iter = children.begin(); node_iter != children.end(); ++node_iter)
    {
        GameState state;
        state.importFromPropertyTree(node_iter->second);
        // Does this message already exist?
        if (state_map_.find(state.getName()) != state_map_.end())
        {
        	char message[100];
        	sprintf(message, "State %s already exits", state.getName());
        	SystemLog::logMessage("GameStateManager", message);

        	return false;
        }
        state_map_.insert(state.getName(), state);
    }
    */

	return true;
}


// It exports the contents of the object to a property tree
bool GameStateManager::exportToPropertyTree(boost::property_tree::ptree& pt) const
{

	return true;
}


} /* namespace JU */
