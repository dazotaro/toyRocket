/*
 * Registry.hpp
 *
 *  Created on: Jun 25, 2015
 *      Author: jusabiaga
 */

#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_


namespace JU
{

// Forward Declaration
class GameStateFactory;


class Registry
{
	public:
		static Registry& getInstance();

		Registry();

	protected:
		Registry(const Registry& rhs) {}
		Registry& operator=(const Registry& rhs);

		virtual ~Registry();

	public:
		void setObjectFactory(GameStateFactory* p_obj_factory);
		GameStateFactory* getObjectFactory() const;
		void releaseObjects() const;

	private:
		GameStateFactory* p_obj_factory_;

};

} /* namespace JU */

#endif /* REGISTRY_HPP_ */
