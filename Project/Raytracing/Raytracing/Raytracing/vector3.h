///////////////////////////////////////////////////
//
//	Manigandan Rajan
//	December, 2019
//
//	------------------------
//	Vector3.h
//	------------------------
//	
//	A minimal class for a vector
//	
///////////////////////////////////////////////////

#ifndef VECTOR3_H
#define VECTOR3_H

// Include statement
#include "Cartesian3.h"

// class for vector
class Vector3
{
public:
	double x, y, z;
	Vector3(double x, double y, double z);
	Vector3(Cartesian3 x1, Cartesian3 x2);
	void Normalize();
	double Magnitude();
	Vector3 cross(Vector3 &other);
	float operator*(Vector3 &other);
	Vector3 operator-();
	Vector3 normal();
	float getDistance(Cartesian3 o, Cartesian3 p);
};

#endif // VECTOR3_H
