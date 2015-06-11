/*
 * CoordinateHelper.h
 *
 *  Created on: Nov 6, 2013
 *      Author: aitatxo
 */

#ifndef COORDINATEHELPER_H_
#define COORDINATEHELPER_H_

namespace JU
{

namespace CoordinateHelper
{
	//void cartesian2spherical(float x, float y, float z, float &radius, float &inclination, float &azimuth);
	void spherical2cartesian(float radius, float inclination, float azimuth, float &x, float &y, float &z);
} // namespace CoordinateHelper
} // namespace JU
#endif /* COORDINATEHELPER_H_ */
