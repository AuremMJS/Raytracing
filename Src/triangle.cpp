///////////////////////////////////////////////////
//
//	Manigandan Rajan
//	December, 2019
//
//	------------------------
//	Triangle.cpp
//	------------------------
//	
//	A minimal class for a triangle
//	
///////////////////////////////////////////////////

#include "triangle.h"
#include "vector3.h"

// Default Constructor
Triangle::Triangle() 
	:Normal(0, 0, 0), u(0, 0, 0), w(0, 0, 0)
{

}

// Constructor
Triangle::Triangle(Cartesian3 A,Cartesian3 B, Cartesian3 C)
    :Normal(0,0,0), A(A),B(B),C(C), P0(A), u(0,0,0), w(0, 0, 0)
{
    u= Vector3(A.x - B.x,A.y - B.y,A.z - B.z);
    Vector3 v( A.x - C.x ,A.y - C.y ,A.z - C.z);

    Normal = u.cross(v);
    w = Normal.cross(u);

	Normal.Normalize();
}

// Function to check whether the ray intersects the triangle
bool Triangle::isIntersects(Cartesian3 &l0, Vector3 &l, float &t)
{
	// Convert dir to Plane Coordinates
	
    double denom =  Normal * l;
    if(denom>1e-16)
    {
        Vector3 p0l0( P0.x - l0.x,P0.y - l0.y,P0.z - l0.z);
        t = (p0l0 * Normal) / denom;
		if (t >= 0)
		{
			double alpha = 0;
			double beta = 0;
			double gamma = 0;
			double ix = l0.x + l.x * t;
			double iy = l0.y + l.y * t;
			double iz = l0.z + l.z * t;
			Cartesian3 p(ix, iy, iz);
			CalculateBarycentricCoords(p, alpha, beta, gamma);

			return (alpha >= 0 && beta >= 0 && gamma >= 0);
		}
    }
    return false;
}

// Function to calculate barycentric coordinates
void Triangle::CalculateBarycentricCoords(Cartesian3 &P,double &alpha, double &beta, double &gamma)
{
	Cartesian3 a = ConvertToPCS(A);
	Cartesian3 b = ConvertToPCS(B);
	Cartesian3 c = ConvertToPCS(C);

	Vector3 ab(a, b);
	Vector3 bc(b, c);
	Vector3 ca(c, a);

	Cartesian3 p = ConvertToPCS(P);

	float a_BC = bc.getDistance(a, b);
	float b_CA = ca.getDistance(b, c);
	float c_AB = ab.getDistance(c, a);

    float p_BC = bc.getDistance(p,b);
    float p_CA = ca.getDistance(p,c);
    float p_AB = ab.getDistance(p,a);
    alpha = p_BC / a_BC ;
    beta =  p_CA / b_CA;
    gamma = p_AB / c_AB ;
}

// Function to set the albedo of the triangle
void Triangle::SetAlbedo(double value)
{
    albedo = value;
}

// Function to get the albedo of the triangle
double Triangle::getAlbedo()
{
    return  albedo;
}

// Function to convert a point to plane coordinate system
Cartesian3 Triangle::ConvertToPCS(Cartesian3 point)
{
	Vector3 s(point.x - P0.x, point.y - P0.y, point.z - P0.z);
	double x = s * u;
	double y = s * w;
	double z = s * Normal;
	return Cartesian3(x, y, z);
}

// Equality operator
void Triangle::operator =(Triangle other)
{
	A = other.A;
	B = other.B;
	C = other.C;

	P0 = other.P0;

	albedo = other.albedo;
	Normal = other.Normal;
	u = other.u;
	w = other.w;

	ks = other.ks;
	kd = other.kd;
	h = other.h;

	r = other.r;
	g = other.g;
	b = other.b;
}