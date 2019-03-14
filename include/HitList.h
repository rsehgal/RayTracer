/*
 * HitList.h
 *
 *  Created on: 13-Mar-2019
 *      Author: rsehgal
 */

#ifndef RAYTRACER_INCLUDE_HITLIST_H_
#define RAYTRACER_INCLUDE_HITLIST_H_

#include "base/Vector3D.h"
#include "volumes/PlacedVolume.h"
#include <vector>


namespace RayTracer {

struct HitRecord{
	vecgeom::Vector3D<double> point;
	vecgeom::Vector3D<double> normal;
	double dist;

	HitRecord(vecgeom::Vector3D<double> pt, vecgeom::Vector3D<double> nr, double d):point(pt),normal(nr),dist(d){}
	void Clear(){
		/*point.clear();
		normal.clear();
		dist = 0.;*/
	}
};

class Ray;

//template<class shapeType>
class HitList {
	std::vector<const vecgeom::VPlacedVolume*> fVectOfPlacedVolume;
	std::vector<HitRecord> fVectOfHitRecord;
public:
	HitList(std::vector<const vecgeom::VPlacedVolume*> vectOfPlacedVolume):fVectOfPlacedVolume(vectOfPlacedVolume){}
	HitList(){}
	virtual ~HitList(){}
	bool FillHitRecordVector(Ray r){
		//fVectOfHitRecord.Clear();
		bool valid = false;
		//std::cout << "PlacedVolumeVector Size : " << fVectOfPlacedVolume.size() << std::endl;
		for (unsigned int i = 0; i < fVectOfPlacedVolume.size(); i++) {
			//std::cout << "Radius : " << dynamic_cast<shapeType*>(fVectOfPlacedVolume[i])->GetUnplacedVolume()->GetRadius() << std::endl;
			//std::cout << r.GetRayOrigin() << " : " << r.GetRayDir() << std::endl;

			//double dist = dynamic_cast<shapeType*>(fVectOfPlacedVolume[i])->DistanceToIn(r.GetRayOrigin(),r.GetRayDir());
			double dist = fVectOfPlacedVolume[i]->DistanceToIn(r.GetRayOrigin(),r.GetRayDir());

			//double dist = fVectOfPlacedVolume[i]->DistanceToIn(r.GetRayOrigin(),r.GetRayDir());
			//std::cout << "Dist : " <<  dist << std::endl;
			if (dist > 0. && dist < vecgeom::kInfLength) {
				//std::cout << "Dist : " <<  dist << std::endl;
				vecgeom::Vector3D<double> pt = r.PointAtDistance(dist);
				vecgeom::Vector3D<double> norm(0., 0., 0.);

				//Actual normal
				//valid |= fVectOfPlacedVolume[i]->Normal(pt, norm);
				norm = (pt-r.GetRayOrigin()).Unit();

				//if (valid)
				{
					//std::cout << pt << " : " << norm <<" : " << dist << std::endl;
					fVectOfHitRecord.push_back(HitRecord(pt, norm, dist));
				}
			}
		}
		return valid;
	}

	std::vector<HitRecord> GetHitRecordVector() const {return fVectOfHitRecord;}
};

} /* namespace RayTracer */

#endif /* RAYTRACER_INCLUDE_HITLIST_H_ */
