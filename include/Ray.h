/*
 * Ray.h
 *
 *  Created on: 13-Mar-2019
 *      Author: rsehgal
 */

#ifndef RAYTRACER_INCLUDE_RAY_H_
#define RAYTRACER_INCLUDE_RAY_H_

#include "base/Vector3D.h"
//using namespace vecgeom;

namespace RayTracer {

//class vecgeom::Vector3D;

class Ray {
	vecgeom::Vector3D<double> fRayOrigin;
	vecgeom::Vector3D<double> fRayDir;
public:
	Ray();
	Ray(vecgeom::Vector3D<double> rayOrigin, vecgeom::Vector3D<double> rayDir) : fRayOrigin(rayOrigin), fRayDir(rayDir){}
	vecgeom::Vector3D<double> GetRayOrigin() const {return fRayOrigin;}
	vecgeom::Vector3D<double> GetRayDir() const {return fRayDir;}
	vecgeom::Vector3D<double> PointAtDistance(double dist) {return fRayOrigin+dist*fRayDir;}
	vecgeom::Vector3D<double> Color();
	virtual ~Ray();
};

} /* namespace RayTracer */

#endif /* RAYTRACER_INCLUDE_RAY_H_ */
