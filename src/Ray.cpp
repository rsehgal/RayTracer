/*
 * Ray.cpp
 *
 *  Created on: 13-Mar-2019
 *      Author: rsehgal
 */

#include "Ray.h"

using namespace vecgeom;

namespace RayTracer {

Ray::Ray() {
	// TODO Auto-generated constructor stub

}

Ray::~Ray() {
	// TODO Auto-generated destructor stub
}

Vector3D<double> Ray::Color(){
	Vector3D<double> unit_dir = fRayDir.Unit();
	double t = 0.5*(unit_dir.y()+1.0);
	return (1.0-t)*Vector3D<double>(1.,1.,1.)+t*Vector3D<double>(0.5,0.7,1.);
}

} /* namespace RayTracer */
