#include <iostream>
#include "base/Vector3D.h"
using namespace vecgeom;
//using namespace std;

void SimpleImage();
int main(int argc, char **argv) {
	//cout << "Hello world";
	SimpleImage();
	return 0;
}

void SimpleImage(){
	int nx = 200;
	int ny = 100;
	std::cout << "P3\n" << nx << " " << ny <<"\n255\n";
	for(int j = ny-1; j >=0 ; j--){
		for(int i = 0 ; i < nx ; i++){
			/*float r = float(i)/float(nx);
			float g = float(j)/float(ny);
			float b = 0.2;*/
			Vector3D<double> col(float(i)/float(nx),float(j)/float(ny),0.2);
			/*int ir = int(255.99*r);
			int ig = int(255.99*g);
			int ib = int(255.99*b);*/
			Vector3D<int> icol(255.99*col);
			//std::cout << ir << " " << ig << " " << ib << "\n";
			std::cout << icol.x() << " " << icol.y() << " " << icol.z() << "\n";
		}
	}
}
