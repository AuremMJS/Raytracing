///////////////////////////////////////////////////
//
//	Manigandan Rajan
//	December, 2019
//
//	------------------------
//	Vector3.cpp
//	------------------------
//	
//	A minimal class for a Vector
//	
///////////////////////////////////////////////////

#include "vector3.h"
#include <math.h>

// Constructor
Vector3::Vector3(double x,double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

// Constructor
Vector3::Vector3(Cartesian3 x1, Cartesian3 x2)
{
	x = x2.x - x1.x;
	y = x2.y - x1.y;
	z = x2.z - x1.z;
}

// function to normalize the vector
void Vector3::Normalize()
{
    double magnitude = Magnitude();
    this->x/=magnitude;
    this->y/=magnitude;
    this->z/=magnitude;
}

// Function to calculate the magnitude
double Vector3::Magnitude()
{
    return sqrt(x*x + y*y + z*z);
}

// Function to cross product
Vector3 Vector3::cross(Vector3 &other)
{
    Vector3 returnVal(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    return returnVal;
}

// Operator * for dot product
float Vector3::operator*(Vector3 &other)
{
    return x*other.x+y*other.y+z*other.z;
}

// Negation operator
Vector3 Vector3::operator-()
{
	Vector3 res(-x, -y, -z);
	return res;
}

// Function to find the normal of the vector
Vector3 Vector3::normal()
{
	return Vector3(-y, x,z);
}

// Function to get the distance of a point to a vector
float Vector3::getDistance(Cartesian3 o, Cartesian3 p)
{
	Vector3 point(o.x - p.x, o.y - p.y, o.z - p.z);
	Vector3 n = normal();

	float d = (point*n) / n.Magnitude();
	return d;
}