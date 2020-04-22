///////////////////////////////////////////////////
//
//	Manigandan Rajan
//	December, 2019
//
//	------------------------
//	Light.cpp
//	------------------------
//	
//	A minimal class for a light
//	
///////////////////////////////////////////////////

// Include statements
#include "light.h"
#include "vector3.h"

// Constructor
Light::Light(Cartesian3 position, double r, double g, double b, double intensity, int lightType)
{
	this->position = position;
	this->R = r;
	this->G = g;
	this->B = b;
	this->intensity = intensity;
	this->LightType = lightType;
}

// function to get position
Cartesian3 Light::getPosition()
{
	return  position;
}

// Function to calculate lighting
void Light::CalculateLighting(double albedo, double &red, double &green, double &blue)
{
		red = albedo * intensity * this->R;
		green = albedo * intensity * this->G;
		blue = albedo * intensity * this->B;
}
