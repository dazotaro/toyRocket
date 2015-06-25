/*
 * Registry.cpp
 *
 *  Created on: Jun 25, 2015
 *      Author: jusabiaga
 */

#include "Registry.hpp"
#include "GameStateFactory.hpp"

#include <cstdio>			// std::printf

namespace JU
{


Registry::Registry() : p_obj_factory_(nullptr)
{
}


Registry::~Registry()
{
	std::printf("Calling ~Registry\n");
}


void Registry::setObjectFactory(GameStateFactory* p_obj_factory)
{
	p_obj_factory_ = p_obj_factory;
}


GameStateFactory* Registry::getObjectFactory() const
{
	return p_obj_factory_;
}


void Registry::releaseObjects() const
{
	std::printf("Registry::releaseObjects\n");

	delete p_obj_factory_;
}


} /* namespace JU */
