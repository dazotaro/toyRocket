/*
 * IntersectionTests.hpp
 *
 *  Created on: Mar 12, 2017
 *      Author: jusabiaga
 */

#ifndef INTERSECTION_HPP_
#define INTERSECTION_HPP_

// Local includes
#include "Distance.hpp"     // sqDistPointBox
// Global includes
#include <glm/glm.hpp>      // vec3


namespace JU
{
    inline bool testSphereBox(const BoundingSphere& sphere, const BoundingBox& box)
    {
        glm::f32 sqDist = sqDistPointBox(sphere.center_, box);

        return sqDist <= sphere.radius_ * sphere.radius_;
    }

} // namespace JU

#endif /* INTERSECTION_HPP_ */
