/*
 * UsingRay.cpp
 *
 *  Created on: 13-Mar-2019
 *      Author: rsehgal
 */

#include "Ray.h"
#include <iostream>
using namespace vecgeom;
using namespace RayTracer;

int main(){
	int nx = 200;
	int ny = 100;
	std::cout << "P3\n" << nx << " " << ny <<"\n255\n";
	Vector3D<double> lower_left_corner(-2.,-1.,-1.);
	Vector3D<double> horizontal(4.,0.,0.);
	Vector3D<double> vertical(0.,2.,0.);
	Vector3D<double> origin(0.,0.,0.);

	for(int j = ny-1; j >=0 ; j--){
			for(int i = 0 ; i < nx ; i++){
				float u = float(i)/float(nx);
				float v = float(j)/float(ny);
				Ray r(origin,lower_left_corner+u*horizontal+v*vertical);
				Vector3D<double> col = r.Color();
				Vector3D<int> icol(255.99*col);
				std::cout << icol.x() << " " << icol.y() << " " << icol.z() << "\n";
			}
	}
}


