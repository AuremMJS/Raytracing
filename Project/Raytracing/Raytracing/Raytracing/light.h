///////////////////////////////////////////////////
//
//	Manigandan Rajan
//	December, 2019
//
//	------------------------
//	Light.h
//	------------------------
//	
//	A minimal class for a light
//	
///////////////////////////////////////////////////

#ifndef LIGHT_H
#define LIGHT_H
#include "Cartesian3.h"

// Light class
class Light
{
protected:
	// position of the light
    Cartesian3 position;
  
public:

	// Color of  the light
	double R, G, B;

	// Light type - Directional or point light
    int LightType;

	// Intensity of the light
	double intensity;

	// Constructor
    Light(Cartesian3 position,double r,double g,double b,double intensity,int lightType);
	
	// Functions
    Cartesian3 getPosition();
    virtual void CalculateLighting(double albedo, double &red, double &g, double &b);
};

#endif // LIGHT_H
