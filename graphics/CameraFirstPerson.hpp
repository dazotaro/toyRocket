/*
 * CameraFirstPerson.hpp
 *
 *  Created on: May 10, 2013
 *      Author: jusabiaga
 */

#ifndef CAMERAFIRSTPERSON_HPP_
#define CAMERAFIRSTPERSON_HPP_

#include "CameraIntrinsic.hpp"      // CameraIntrinsic object contained
#include "../core/Transform3D.hpp"     // Transform3D


namespace JU
{

/**
 * @brief   First-person camera type
 *
 * @detail  It implements the CameraInterface interface
 */
class CameraFirstPerson : public Transform3D
{
    public:
        CameraFirstPerson(const CameraIntrinsic &camera_intrinsic, const Transform3D &first_person);
        virtual ~CameraFirstPerson();

        // CameraInterface
        void update(const Transform3D &first_person);
        glm::mat4 getViewMatrix(void) const;

    public:
        CameraIntrinsic intrinsic_;     //!< Intrinsic parameters of this camera
};

} // namespace JU

#endif /* CameraFirstPerson_HPP_ */
