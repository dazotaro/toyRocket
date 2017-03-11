/*
 * Camera.hpp
 *
 *  Created on: May 8, 2013
 *      Author: jusabiaga
 */

#ifndef CAMERAINTRINSIC_HPP_
#define CAMERAINTRINSIC_HPP_

// Global includes
#include <glm/glm.hpp>      // glm::mat4
// Local includes
#include "../core/Defs.hpp" // built-in data types typedefs

namespace JU
{

/**
 * @brief      Camera intrinsic parameters
 *
 * @details
 *
 */
class CameraIntrinsic
{
    public:
        CameraIntrinsic(f32 fovy, f32 aspect_ratio, f32 zNear, f32 zFar);
        virtual ~CameraIntrinsic();

        // Getters
        const glm::mat4& getPerspectiveMatrix(void) const;

        // Setters
        void setAspectRatio(f32 aspect_ratio);
        void setVerticalFOY(f32 fov);

    private:
        f32 fovy_;            //!< Field of View in the Y axis (in radians)
        f32 aspect_ratio_;    //!< Aspect ratio
        f32 zNear_;           //!< Near plane
        f32 zFar_;            //!< Far plane
        glm::mat4 perspective_; //!< Perspective matrix
};

} // namespace JU

#endif /* CAMERAINTRINSIC_HPP_ */
