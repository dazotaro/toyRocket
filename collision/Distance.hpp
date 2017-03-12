/*
 * Distance.hpp
 *
 *  Created on: Mar 12, 2017
 *      Author: jusabiaga
 */

#ifndef DISTANCE_HPP_
#define DISTANCE_HPP_

// Local includes
#include "BoundingVolumes.hpp"     // BoundingBox
// Global includes
#include <glm/glm.hpp>      // vec3


namespace JU
{
    inline glm::f32 sqDistPointBox(const glm::vec3& point, const BoundingBox& box)
    {
        glm::f32 sqDist = 0.0f;

        for (glm::uint8 i = 0; i < 3; i++)
        {
            // For each of the axis add the square distance to the closest side of the box (or zero, if inside)
            glm::f32 v = point[i];

            if (v < box.pmin_[i])
                sqDist += (box.pmin_[i] - v) * (box.pmin_[i] - v);
            if (v > box.pmax_[i])
                sqDist += (v - box.pmax_[i]) * (v - box.pmax_[i]);
        }

        return sqDist;
    }

} // namespace JU

#endif /* DISTANCE_HPP_ */
