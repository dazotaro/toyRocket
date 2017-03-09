/*
 * CameraInterface.hpp
 *
 *  Created on: May 11, 2013
 *      Author: jusabiaga
 */

#ifndef CAMERAINTERFACE_HPP_
#define CAMERAINTERFACE_HPP_

#include <glm/glm.hpp>          // glm::mat4

namespace JU
{

// Forward Declarations
class Transform3D;

/**
 * @brief Pure Virtual Class to offer a common interface for all camera objects (e.g. fist-person, third-person)
 */
class CameraInterface
{
    public:
        virtual void update(const Transform3D &object_3d) = 0;
        virtual const glm::mat4& getPerspectiveMatrix(void) const = 0;
        virtual glm::mat4 getViewMatrix(void) const = 0;
        virtual void setAspectRatio(float aspect_ratio) = 0;

        virtual ~CameraInterface() {}
};

} // namespace JU

#endif /* CAMERAINTERFACE_HPP_ */
