/*
 * RayTracingWithPointsFromWorld.cpp
 *
 *  Created on: 14-Mar-2019
 *      Author: rsehgal
 */

#include "base/SOA3D.h"
#include "base/Stopwatch.h"
#include "base/Transformation3D.h"
#include "volumes/PlacedBox.h"
#include "volumes/utilities/VolumeUtilities.h"
#include "volumes/Orb.h"
#include <iostream>
#include "Ray.h"
#include "management/GeoManager.h"
#include "volumes/LogicalVolume.h"
#include <fstream>
#include "HitList.h"

using namespace vecgeom;
using namespace RayTracer;

int main(){
	std::ofstream outfile("fromWorld.ppm");
	int nx = 2000;
		int ny = 1000;
		int fPointCount = nx*ny;
		outfile << "P3\n" << nx << " " << ny << "\n255\n";
//	int fPointCount = 102400;
	double fToInBias = 0.8;
	UnplacedBox worldUnplaced = UnplacedBox(10., 10., 10.);
	LogicalVolume world("world", &worldUnplaced);

	double r = 0.5;
	UnplacedOrb orbUnplaced = UnplacedOrb(r);
	LogicalVolume orb("p4r4", &orbUnplaced);

	Transformation3D placement(0, 0, 0);
	world.PlaceDaughter("orb", &orb, &placement);

	Transformation3D wplacement(0, 0, 0);
	VPlacedVolume *fWorld = world.Place(&wplacement);

	SOA3D<Precision> *fPointPool     = new SOA3D<Precision>(fPointCount);
	SOA3D<Precision> *fDirectionPool = new SOA3D<Precision>(fPointCount);
	volumeUtilities::FillUncontainedPoints(*fWorld, *fPointPool);
	volumeUtilities::FillBiasedDirections(*fWorld, *fPointPool, fToInBias, *fDirectionPool);

	//std::vector<const VPlacedVolume*>vectOfPlacedVolume;
	std::vector<const VPlacedVolume*>vectOfPlacedVolume;
	//creating std::vector of PlacedVolume
	for (Vector<Daughter>::const_iterator j = (*fWorld).GetDaughters().cbegin(),
			jEnd = (*fWorld).GetDaughters().cend(); j != jEnd; ++j) {
		//VPlacedVolume *vol = const_cast<VPlacedVolume*>(*j);
		vectOfPlacedVolume.push_back(*j);
	}

	std::cout << "VectorOfPlaceVolume Size : " << vectOfPlacedVolume.size() << std::endl;



	Vector3D<double> origin(0.,0.,0.);
	//for(int i = 0 ; i < fPointCount ; i++){

	Vector3D<double> lower_left_corner(-2., -1., -1.);
		Vector3D<double> horizontal(4., 0., 0.);
		Vector3D<double> vertical(0., 2., 0.);
	//	Vector3D<double> origin(0.0, 0., 0.);

	for (int j = ny - 1; j >= 0; j--) {
			for (int i = 0; i < nx; i++) {
				//countTotal++;
				float u = float(i) / float(nx);
				float v = float(j) / float(ny);
				Vector3D<double> dir = lower_left_corner + u * horizontal + v * vertical;

		//Vector3D<double> pt(fPointPool->x(i),fPointPool->y(i),fPointPool->z(i));
		//Vector3D<double> dir(fDirectionPool->x(i),fDirectionPool->y(i),fDirectionPool->z(i));
		//Vector3D<double> dir = (pt-origin).Unit();
		//std::cout << pt <<" : "<< dir << std::endl;

		HitList hitL(vectOfPlacedVolume);
		Vector3D<double> col;
		dir.Normalize();
		Ray r(origin, dir);
		bool valid = hitL.FillHitRecordVector(r);
//		if(valid)
		{
			std::vector<HitRecord> hitRecordVector = hitL.GetHitRecordVector();

			if(hitRecordVector.size()==1)
			{
				col = 0.5*Vector3D<double>(hitRecordVector[0].normal+1);
			}
#if(1)
			else if(hitRecordVector.size() > 1)
			{
				/*//Get the color for smallest distance
				double minDist = hitRecordVector[0].dist;
				Vector3D<double> chosenNormal= hitRecordVector[i].normal;
				for(unsigned int i = 1 ; i < hitRecordVector.size() ; i++){
					if(hitRecordVector[i].dist < minDist){
						minDist = hitRecordVector[i].dist;
						chosenNormal = hitRecordVector[i].normal;
					}
				}
				col = 0.5*Vector3D<double>(chosenNormal+1);
				Vector3D<int> icol(255.99 * col);
				std::cout << icol.x() << " " << icol.y() << " " << icol.z() << "\n";*/

				for (unsigned int i = 1; i < hitRecordVector.size(); i++) {
					col = 0.5 * Vector3D<double>(hitRecordVector[i].normal + 1);
					Vector3D<int> icol(255.99 * col);
					std::cout << icol.x() << " " << icol.y() << " " << icol.z() << "\n";

				}


				continue;
			}
#endif
		}
		Vector3D<int> icol(255.99 * col);
		//std::cout << icol.x() << " " << icol.y() << " " << icol.z() << "\n";
		outfile << icol.x() << " " << icol.y() << " " << icol.z() << "\n";

			}}

	outfile.close();
}




