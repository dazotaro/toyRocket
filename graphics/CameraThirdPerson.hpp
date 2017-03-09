/*
 * CameraThirdPerson.hpp
 *
 *  Created on: May 10, 2013
 *      Author: jusabiaga
 */

#ifndef CAMERATHIRDPERSON_HPP_
#define CAMERATHIRDPERSON_HPP_

// Local includes
#include "CameraInterface.hpp"      // CameraInterface parent class
#include "CameraIntrinsic.hpp"      // CamneraIntrinsic object contained
#include "../core/Transform3D.hpp"     // Transform3D
#include "../core/Defs.hpp"         // JU::f32

// Global includes
#define _USE_MATH_DEFINES
#include <math.h>

namespace JU
{

/**
 * @brief   Third-person camera type
 *
 * \todo    Maybe it should not inherit from Transform3D but, instead, it should just contain a pointer to a Transform3D
 */
class CameraThirdPerson : public CameraInterface, public Transform3D
{
    public:
        CameraThirdPerson(const CameraIntrinsic &camera_intrinsic,
                          const Transform3D &target,
                          JU::f32 distance_to_target = 10.0f,
                          JU::f32 azimuth = 0.0f,
                          JU::f32 inclination = M_PI / 2.0f);


        virtual ~CameraThirdPerson();

        // CameraInterface
        void update(const Transform3D &object_3d);
        const glm::mat4& getPerspectiveMatrix(void) const;
        glm::mat4 getViewMatrix(void) const;
        void setAspectRatio(JU::f32 aspect_ratio);

        // Setters
        void update(const Transform3D &target, JU::f32 distance_delta, JU::f32 inclination_delta, JU::f32 azimuth_delta);
        void update(const Transform3D &target, JU::f32 distance_delta, JU::f32 angle, const glm::vec3& axis);

        // Algorithms
        void setFrameCartesian(const Transform3D &target);
        void setFrameSpherical(const Transform3D &target);

    private:
        CameraIntrinsic intrinsic_;     //!< Intrinsic parameters of the camera
        JU::f32 distance_to_target_;      //!< Distance to the target (i.e. radius of the sphere in spherical coordinates
        JU::f32 azimuth_;                 //!< Azimuth angle in spherical coordinates
        JU::f32 inclination_;             //!< Inclination angle in spherical coordinates
};

} // namespace JU

#endif /* CameraThirdPerson_HPP_ */
