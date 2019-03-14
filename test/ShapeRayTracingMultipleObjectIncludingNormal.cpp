/*
 * ShapeWithRayTracer.cpp
 *
 *  Created on: 13-Mar-2019
 *      Author: rsehgal
 */

#include "volumes/Orb.h"
#include "volumes/Tube.h"
#include <iostream>
#include "Ray.h"
#include "management/GeoManager.h"
#include "volumes/LogicalVolume.h"
#include <fstream>
#include "HitList.h"
#include "volumes/GenericPolycone.h"

using namespace vecgeom;
using namespace RayTracer;

int main(){
	std::ofstream ppmfile("mult.ppm");
	/*std::vector<vecgeom::VPlacedVolume*> vectOfPlacedVolume;
	double r = 0.5;
	UnplacedOrb orbUnplaced = UnplacedOrb(r);
	LogicalVolume orb("p4r4", &orbUnplaced);
	Transformation3D placement = Transformation3D(0.5,0.,-1.);
	Transformation3D placement2 = Transformation3D(-0.5,0.,-1.);
	VPlacedVolume *orbPlaced = orb.Place(&placement);
	vectOfPlacedVolume.push_back(orbPlaced);
	VPlacedVolume *orbPlaced2 = orb.Place(&placement2);
	vectOfPlacedVolume.push_back(orbPlaced2);
	//std::cout <<"Rad from TEst : " << dynamic_cast<PlacedOrb*>(orbPlaced)->GetRadius() << std::endl;*/


	UnplacedBox worldUnplaced = UnplacedBox(50., 50., 50.);
		LogicalVolume world("world", &worldUnplaced);

		double r = 6;
		UnplacedOrb orbUnplaced = UnplacedOrb(r);
		LogicalVolume orb("p4r4", &orbUnplaced);

		//UnplacedOrb tubeUnplaced = UnplacedTube(0.,0.6,0.6,0.,2*M_PI);
		auto tubeUnplaced         = GeoManager::MakeInstance<UnplacedTube>(r-3,r,r,0.,2*M_PI);
		const int numRZ1    = 10;
		  double polycone_r[] = {1, 5, 3, 4, 9, 9, 3, 3, 2, 1};
		  double polycone_z[] = {0, 1, 2, 3, 0, 5, 4, 3, 2, 1};
		  double sphi = M_PI/3.;
		  double dphi = 2*M_PI/3.;
		  auto genericPolyconeUnplaced =
		      GeoManager::MakeInstance<UnplacedGenericPolycone>(sphi, dphi, numRZ1, polycone_r, polycone_z);

		LogicalVolume tube("tube", tubeUnplaced);

		Transformation3D placement(0.5, 0, -1.);
		Transformation3D placement2(0., 0, -1.);
		//world.PlaceDaughter("orb", &orb, &placement);
		world.PlaceDaughter("tube", &tube, &placement2);

		//Transformation3D wplacement(0, 0, 0);
		//VPlacedVolume *fWorld = world.Place(&wplacement);
		VPlacedVolume *fWorld = world.Place();

		Vector3D<double> aMin,aMax;
		fWorld->Extent(aMin,aMax);

	std::vector<const VPlacedVolume*> vectOfPlacedVolume;
	for (Vector<Daughter>::const_iterator j = (*fWorld).GetDaughters().cbegin(),
			jEnd = (*fWorld).GetDaughters().cend(); j != jEnd; ++j) {
		vectOfPlacedVolume.push_back(*j);
	}

	int nx = 6000;
	int ny = 3000;
	//std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	ppmfile << "P3\n" << nx << " " << ny << "\n255\n";
	//Vector3D<double> lower_left_corner(-2., -1., -1.);
	Vector3D<double> lower_left_corner = aMin;
	lower_left_corner.z() = aMax.z();
	//Vector3D<double> horizontal(4., 0., 0.);
	Vector3D<double> horizontal(2*worldUnplaced.x(), 0., 0.);
	//Vector3D<double> vertical(0., 2., 0.);
	Vector3D<double> vertical(0., 2*worldUnplaced.y(), 0.);
	Vector3D<double> origin(0.0, 40., 100.);

	int countTotal = 0;
	int countHits = 0;
	std::ofstream hitfile("hitCount.txt");

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			countTotal++;
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			Vector3D<double> dir = lower_left_corner + u * horizontal + v * vertical;
			dir -= origin;
			dir.Normalize();
			Vector3D<double> col;
			Ray r(origin, dir);
			//HitList<PlacedOrb> hitL(vectOfPlacedVolume);
			HitList hitL(vectOfPlacedVolume);
			bool valid = hitL.FillHitRecordVector(r);
	//		if(valid)
			{
				std::vector<HitRecord> hitRecordVector = hitL.GetHitRecordVector();

				if(hitRecordVector.size()==1)
				{
					col = 0.5*Vector3D<double>(hitRecordVector[0].normal+1);
					//col = Vector3D<double>(1.,0.,0.);
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
						//col = 0.5 * Vector3D<double>(hitRecordVector[i].normal + 1);
						col = Vector3D<double>(1.,0.,0.);
						Vector3D<int> icol(255.99 * col);
						//std::cout << icol.x() << " " << icol.y() << " " << icol.z() << "\n";
						ppmfile << icol.x() << " " << icol.y() << " " << icol.z() << "\n";

					}


					continue;
				}
#endif
			}
#if(0)
			else{
				//col = r.Color();
			}
#endif
			//Vector3D<double> col = r.Color();
			Vector3D<int> icol(255.99 * col);
			//std::cout << icol.x() << " " << icol.y() << " " << icol.z() << "\n";
			ppmfile << icol.x() << " " << icol.y() << " " << icol.z() << "\n";
		}
	}

	hitfile << "Total Number of Rays : " << countTotal << std::endl;
	hitfile << "Total Number of Hits : " << countHits << std::endl;
	hitfile.close();
	ppmfile.close();

}




