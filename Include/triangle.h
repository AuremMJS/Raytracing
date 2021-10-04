///////////////////////////////////////////////////
//
//	Manigandan Rajan
//	December, 2019
//
//	------------------------
//	Triangle.h
//	------------------------
//	
//	A minimal class for a triangle
//	
///////////////////////////////////////////////////

#ifndef TRIANGLE_H
#define TRIANGLE_H

// Include statements
#include "Cartesian3.h"
#include "vector3.h"

// Triangle class
class Triangle
{
private:

	// Vertices of the triangle
	Cartesian3 A, B, C;

	Cartesian3 P0;

	double albedo;


public:
	Vector3 Normal, u, w;
	double ks, kd, h;
	int r, g, b;
	Triangle();
	Triangle(Cartesian3 A, Cartesian3 B, Cartesian3 C);
	bool isIntersects(Cartesian3 &l0, Vector3 &l, float &t);
	void CalculateBarycentricCoords(Cartesian3 &P, double &alpha, double &beta, double &gamma);
	void SetAlbedo(double value);
	double getAlbedo();
	Cartesian3 ConvertToPCS(Cartesian3 point);
	void operator =(Triangle other);
};

#endif // TRIANGLE_H
