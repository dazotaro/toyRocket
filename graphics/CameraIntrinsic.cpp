/*
 * Camera.cpp
 *
 *  Created on: May 8, 2013
 *      Author: jusabiaga
 */

#include "CameraIntrinsic.hpp"
#include <glm/gtc/matrix_transform.hpp>     // gluPerspective

namespace JU
{

/**
* @brief Non-Default Constructor
*
* @param fovy           Vertical field-of-view (in radians)
* @param aspect_ratio   Width divided by height
* @param zNear          Distance from the COP to the Near Plane
* @param zFar           Distance from the COP to the Far Plane
*/
CameraIntrinsic::CameraIntrinsic(f32 fovy, f32 aspect_ratio, f32 zNear, f32 zFar) :
    fovy_(fovy), aspect_ratio_(aspect_ratio), zNear_(zNear), zFar_(zFar)
{
    perspective_ = glm::perspective(fovy_, aspect_ratio_, zNear_, zFar_);
}


/**
* @brief Destructor
*/
CameraIntrinsic::~CameraIntrinsic()
{
    // TODO Auto-generated destructor stub
}


/**
* @brief Returns the Perspective Projection matrix
*
* @return 4x4 homogeneous matrix with the transformation
*/
const glm::mat4& CameraIntrinsic::getPerspectiveMatrix(void) const
{
    return perspective_;
}


/**
* @brief Updated the aspect ratio
*
* @param aspect_ratio_ The new aspect ratio (width / height)
*/
void CameraIntrinsic::setAspectRatio(f32 aspect_ratio)
{
    aspect_ratio_ = aspect_ratio;
    perspective_  = glm::perspective(fovy_, aspect_ratio_, zNear_, zFar_);
}


/**
* @brief Set vertical field-of-view
*
* @param fov Vertical field of view (in radians)
*/
void CameraIntrinsic::setVerticalFOY(f32 fov)
{
    fovy_ = fov;
    perspective_  = glm::perspective(fovy_, aspect_ratio_, zNear_, zFar_);
}

} // namespace JU
