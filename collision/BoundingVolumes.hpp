/*
 * BoundingVolumes.hpp
 *
 *  Created on: Mar 12, 2017
 *      Author: jusabiaga
 */

#ifndef BOUNDINGVOLUMES_HPP_
#define BOUNDINGVOLUMES_HPP_

#include <glm/glm.hpp>      // vec3, f32

namespace JU
{
    /**
     * @brief Bounding Box class
     *
     */
    class BoundingBox
    {
        public:
            BoundingBox() : pmin_(glm::vec3(0.0f)), pmax_(glm::vec3(0.0f)) {}
            BoundingBox(const glm::vec3& pmin, const glm::vec3& pmax) : pmin_(pmin), pmax_(pmax) {}

        public:
            glm::vec3 pmin_;    //!< Minimum extreme point
            glm::vec3 pmax_;    //!< Maximum extreme point
    };


    /**
     * @brief Bounding Sphere class
     *
     */
    class BoundingSphere
    {
        public:
            BoundingSphere(const glm::vec3& center, glm::f32 radius) : center_(center), radius_(radius) {}

        public:
            glm::vec3 center_;  //!< Center of the sphere
            glm::f32  radius_;  //!< Radius
    };


}   // end namespace JU



#endif /* BOUNDINGVOLUMES_HPP_ */
