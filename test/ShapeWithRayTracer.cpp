/*
 * ShapeWithRayTracer.cpp
 *
 *  Created on: 13-Mar-2019
 *      Author: rsehgal
 */

#include "volumes/Orb.h"
#include <iostream>
#include "Ray.h"
#include "management/GeoManager.h"
#include "volumes/LogicalVolume.h"
#include <fstream>

using namespace vecgeom;
using namespace RayTracer;

int main(){
	double r = 0.5;
	UnplacedOrb orbUnplaced = UnplacedOrb(r);
	LogicalVolume orb("p4r4", &orbUnplaced);
	Transformation3D placement = Transformation3D(0.,0.,-1.);
	VPlacedVolume *orbPlaced = orb.Place(&placement);

	int nx = 500;
	int ny = 250;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	Vector3D<double> lower_left_corner(-2., -1., -1.);
	Vector3D<double> horizontal(4., 0., 0.);
	Vector3D<double> vertical(0., 2., 0.);
	Vector3D<double> origin(0.0, 0., 0.);

	int countTotal = 0;
	int countHits = 0;
	std::ofstream hitfile("hitCount.txt");

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			countTotal++;
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			Vector3D<double> dir = lower_left_corner + u * horizontal + v * vertical;
			dir.Normalize();
			double dist = orbPlaced->DistanceToIn(origin,dir);
			//std::cout << "Distance : " << dist << std::endl;
			Vector3D<double> col;
			if(dist < kInfLength){
				hitfile << countTotal << " : " << dist << std::endl;
				countHits++;
				col.Set(1.,0.,0.);
			}
			else{
				Ray r(origin, dir);
				col = r.Color();
			}
			//Vector3D<double> col = r.Color();
			Vector3D<int> icol(255.99 * col);
			std::cout << icol.x() << " " << icol.y() << " " << icol.z() << "\n";
		}
	}

	hitfile << "Total Number of Rays : " << countTotal << std::endl;
	hitfile << "Total Number of Hits : " << countHits << std::endl;
	hitfile.close();

}




