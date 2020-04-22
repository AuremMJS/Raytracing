///////////////////////////////////////////////////
//
//	Manigandan Rajan
//	December, 2019
//
//	------------------------
//	Raytracing.cpp
//	------------------------
//	
//	Main class for raytracing
//	
///////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Cartesian3.h"
#include "triangle.h"
#include "vector3.h"
#include "light.h"

// Function to render a black triangle using raytracing
void RenderBlackTriangle()
{
	// Set width and height
	int width = 128;
	int height = 128;

	// Generate output file
	std::ofstream oFile("BlackTriangle.ppm");
	oFile << "P3" << std::endl;
	oFile << "# Creator " << std::endl;
	oFile << width << " " << height << std::endl;
	oFile << "255" << std::endl;

	// Coordinates of Triangle
	Cartesian3 A(-0.04688, -0.84375, 1.0);
	Cartesian3 B(0.5625, 0.5625, 1.0);
	Cartesian3 C(-0.60938, 0.40625, 1.0);

	// Triangle
	Triangle T(A, B, C);

	// Eye position
	Cartesian3 l0(0, 0, 0);

	// Loop through every pixel in the image plane
	for (int j = height - 1; j >= 0; j--)
	{
		for (int i = 0; i < width; i++)
		{
			double x = (2 * (i + 0.5) / (double)width - 1);
			double y = (2 * (j + 0.5) / (double)height - 1);
			Vector3 dir(x, y, 1);
			dir.Normalize();
			float t = 0;

			// Check whether ray  intersects the triangle
			if (T.isIntersects(l0, dir, t))
			{
				// Set color as black if the point exists within the triangle
				oFile << "0 0 0" << std::endl;
			}
			else
			{
				// Set color as light yellow if the point exists within the triangle
				oFile << "255 255 192" << std::endl;
			}
		}
	}
}

// Function to render a triangle in colors based on barycentric coordinates
void RenderRainbowTriangle()
{
	// Set width and height of the image
	int width = 128;
	int height = 128;

	// Generate output file
	std::ofstream oFile("RainbowTriangle.ppm");
	oFile << "P3" << std::endl;
	oFile << "# Creator " << std::endl;
	oFile << width << " " << height << std::endl;
	oFile << "255" << std::endl;

	// Coordinates of the triangle
	Cartesian3 A(-0.04688, -0.84375, 1.0);
	Cartesian3 B(0.5625, 0.5625, 1.0);
	Cartesian3 C(-0.60938, 0.40625, 1.0);

	// Initialising the Triangle
	Triangle T(A, B, C);

	// Eye position
	Cartesian3 l0(0, 0, 0);

	// Loop through every pixel in the image plane
	for (int j = height - 1; j >= 0; j--)
	{
		for (int i = 0; i < width; i++)
		{
			double x = (2 * (i + 0.5) / (double)width - 1);
			double y = (2 * (j + 0.5) / (double)height - 1);

			Vector3 dir(x, y, 1);
			dir.Normalize();
			float t = 0;

			// Check whether the ray intersects the triangle
			if (T.isIntersects(l0, dir, t))
			{
				// Find the intersection point
				double ix = l0.x + dir.x * t;
				double iy = l0.y + dir.y * t;
				double iz = l0.z + dir.z * t;
				Cartesian3 p(ix, iy, iz);

				// Calculate the barycentric coordinates
				double alpha;
				double beta;
				double gamma;
				T.CalculateBarycentricCoords(p, alpha, beta, gamma);
				if ((alpha >= 0.0) && (beta >= 0.0) && (gamma >= 0.0))
				{
					// Set the color based on barycentric coordinates
					int r = 255 * alpha;
					int g = 255 * beta;
					int b = 255 * gamma;
					oFile << r << std::endl << g << std::endl << b << std::endl;
				}
				else
				{
					// Set the color to light yellow outside the triangle
					oFile << "255 255 192" << std::endl;
				}
			}
			else
			{
				// Set the color to light yellow outside the triangle
				oFile << "255 255 192" << std::endl;
			}
		}
	}
}

// Function to render a triangle based on Blinn Phong shading
void BlinnPhong(double ks, double kd, const char* filename)
{
	// Initialize lights vector
	std::vector<Light> lights;

	// Set width and height of the image
	int width = 128;
	int height = 128;

	// Generate the output file
	std::ofstream oFile(filename);
	oFile << "P3" << std::endl;
	oFile << "# Creator " << std::endl;
	oFile << width << " " << height << std::endl;
	oFile << "255" << std::endl;

	// Coordinates of the triangle
	Cartesian3 A(-0.04688, -0.84375, 1.0);
	Cartesian3 B(0.5625, 0.5625, 1.0);
	Cartesian3 C(-0.60938, 0.40625, 1.0);

	// Initialize the triangle
	Triangle T(A, B, C);
	T.SetAlbedo(0.9);
	T.ks = ks;
	T.h = 2000;
	T.kd = kd;
	T.r = 255;
	T.g = 0;
	T.b = 0;

	// Set Eye position
	Cartesian3 l0(0, 0, 0);

	// Directional light for ambient light
	Light al(l0, 0.7, 0.7, 0.7, 0.5, 0);

	// Light position of a point light
	Cartesian3 LightPos(-0.75, 0.4375, 0.0);

	// Initialize the point light
	Light pl(LightPos, 1.0, 0.0, 0.0, 0.9, 1);

	// Add the lights to the vector
	lights.push_back(al);
	lights.push_back(pl);

	// Loop through every pixel in the image plane
	for (int j = height - 1; j >= 0; j--)
	{
		for (int i = 0; i < width; i++)
		{
			double x = (2 * (i + 0.5) / (double)width - 1);
			double y = (2 * (j + 0.5) / (double)height - 1);
			Vector3 dir(x, y, 1);
			dir.Normalize();
			float t = 0;

			// Check whether the ray intersects the triangle
			if (T.isIntersects(l0, dir, t))
			{
				// Find the intersection point
				double ix = l0.x + dir.x * t;
				double iy = l0.y + dir.y * t;
				double iz = l0.z + dir.z * t;
				Cartesian3 p(ix, iy, iz);

				// Set the triangle color
				int r = 0;
				int g = 125;
				int b = 0;
				double totalR = 0, totalG = 0, totalB = 0;

				// Loop through the lights
				for (auto &light : lights)
				{
					double rToAdd, gToAdd, bToAdd;
					if (light.LightType == 0)
					{
						// Add ambient light illumination
						light.CalculateLighting(T.getAlbedo(), rToAdd, gToAdd, bToAdd);
					}
					if (light.LightType == 1)
					{
						// Add point light illumination
						Vector3 LightDir(p.x - light.getPosition().x,
							p.y - light.getPosition().y,
							p.z - light.getPosition().z);

						// Calculate the diffuse value
						double diffuse = (T.Normal * LightDir) / (T.Normal.Magnitude() * LightDir.Magnitude());
						if (diffuse < 0)
							diffuse = 0;

						// Calculate the specular value
						Vector3 dir2(i, j, 1);
						double h = 2;

						Vector3 b((dir2.x + LightDir.x) / 2, (dir2.y + LightDir.y) / 2, (dir2.z + LightDir.z) / 2);
						Vector3 n = T.u.cross(T.w);
						double dotP = LightDir * T.Normal;
						b = Vector3(LightDir.x - 2 * dotP * T.Normal.x, LightDir.y - 2 * dotP * T.Normal.y, LightDir.z - 2 * dotP * T.Normal.z);
						b = Vector3(b.x, b.y, -b.z);
						double specular = pow(std::max(0.0, (T.Normal * b) / (T.Normal.Magnitude() * b.Magnitude())), h);

						// Calculate the total illumination
						rToAdd = (diffuse * T.kd * light.intensity + specular * T.ks * light.intensity);
						gToAdd = (diffuse * T.kd * light.intensity + specular * T.ks * light.intensity);
						bToAdd = (diffuse * T.kd * light.intensity + specular * T.ks * light.intensity);
					}
					totalR += rToAdd;
					totalG += gToAdd;
					totalB += bToAdd;
				}
				r *= totalR;
				g *= totalG;
				b *= totalB;
				r = std::min(255, r);
				g = std::min(255, g);
				b = std::min(255, b);

				r = std::max(0, r);
				g = std::max(0, g);
				b = std::max(0, b);

				// Set the calculate color to the output image
				oFile << r << std::endl << g << std::endl << b << std::endl;
			}
			else
			{
				// Set light yellow when the point is outside the triangle
				oFile << "255 255 192" << std::endl;
			}
		}
	}
}

// Function to trace rays to every triangle
bool trace(std::vector<Triangle> triangles, Cartesian3 &l0, Vector3 &dir, float &t, int& isectIndex, int currentTriangleIndex = -1)
{
	// Set depth as infinity
	double depth = INT_MAX;
	int index = -1;
	for (int i = 0; i < triangles.size(); i++)
	{
		// Skip if the current triangle is same as the triangle to check
		if (currentTriangleIndex != -1 && i == currentTriangleIndex)
			continue;
		float t2 = 0;
		Triangle T = triangles.at(i);

		// Check whether the ray intersects the triangle
		if (T.isIntersects(l0, dir, t2))
		{
			if (depth >= t2)
			{
				// Set depth to current triangle depth
				depth = t2;
				index = i;
			}
		}
	}
	t = depth;
	isectIndex = index;
	return isectIndex != -1;
}

// Function to render an image with Shadows
void Shadow()
{
	// Vector of lights
	std::vector<Light> lights;

	// Vector of triangles
	std::vector<Triangle> triangles;

	// Set height and width
	int width = 128;
	int height = 128;

	// Generate output file
	std::ofstream oFile("Shadow.ppm");
	oFile << "P3" << std::endl;
	oFile << "# Creator " << std::endl;
	oFile << width << " " << height << std::endl;
	oFile << "255" << std::endl;

	// Initialize the walls
	Cartesian3 A(-1, -1, 1);
	Cartesian3 B(1, -1, 1);
	Cartesian3 C(-1, -1, 2);

	Triangle T1(A, B, C);
	T1.SetAlbedo(0.9);
	T1.ks = 0.0;
	T1.h = 10;
	T1.kd = 1.0;
	T1.r = 0;
	T1.g = 192;
	T1.b = 0;

	triangles.push_back(T1);

	Cartesian3 A2(1, -1, 2);
	Cartesian3 B2(-1, -1, 2);
	Cartesian3 C2(1, -1, 1);

	Triangle T2(A2, B2, C2);
	T2.SetAlbedo(0.9);
	T2.ks = 0.0;
	T2.h = 10;
	T2.kd = 1.0;
	T2.r = 0;
	T2.g = 192;
	T2.b = 0;

	triangles.push_back(T2);

	Cartesian3 A3(-1, 1, 1);
	Cartesian3 B3(1, 1, 1);
	Cartesian3 C3(-1, 1, 2);

	Triangle T3(A3, C3, B3);
	T3.SetAlbedo(0.9);
	T3.ks = 0.0;
	T3.h = 10;
	T3.kd = 1.0;
	T3.r = 0;
	T3.g = 192;
	T3.b = 0;

	triangles.push_back(T3);

	Cartesian3 A4(1, 1, 1);
	Cartesian3 B4(1, 1, 2);
	Cartesian3 C4(-1, 1, 2);

	Triangle T4(A4, C4, B4);
	T4.SetAlbedo(0.9);
	T4.ks = 0.0;
	T4.h = 10;
	T4.kd = 1.0;
	T4.r = 0;
	T4.g = 192;
	T4.b = 0;

	triangles.push_back(T4);

	Cartesian3 A5(-1, 1, 1);
	Cartesian3 B5(-1, -1, 1);
	Cartesian3 C5(-1, 1, 2);

	Triangle T5(A5, B5, C5);
	T5.SetAlbedo(0.9);
	T5.ks = 0.0;
	T5.h = 10;
	T5.kd = 1.0;
	T5.r = 255;
	T5.g = 192;
	T5.b = 0;
	triangles.push_back(T5);

	Cartesian3 A6(-1, 1, 2);
	Cartesian3 B6(-1, -1, 1);
	Cartesian3 C6(-1, -1, 2);

	Triangle T6(A6, B6, C6);
	T6.SetAlbedo(0.9);
	T6.ks = 0.0;
	T6.h = 10;
	T6.kd = 1.0;
	T6.r = 255;
	T6.g = 192;
	T6.b = 0;

	triangles.push_back(T6);


	Cartesian3 A7(1, 1, 1);
	Cartesian3 B7(1, -1, 1);
	Cartesian3 C7(1, 1, 2);

	Triangle T7(A7, C7, B7);
	T7.SetAlbedo(0.9);
	T7.ks = 0.0;
	T7.h = 10;
	T7.kd = 1.0;
	T7.r = 255;
	T7.g = 192;
	T7.b = 0;
	triangles.push_back(T7);

	Cartesian3 A8(1, 1, 2);
	Cartesian3 B8(1, -1, 1);
	Cartesian3 C8(1, -1, 2);

	Triangle T8(A8, C8, B8);
	T8.SetAlbedo(0.9);
	T8.ks = 0.0;
	T8.h = 10;
	T8.kd = 1.0;
	T8.r = 255;
	T8.g = 192;
	T8.b = 0;
	triangles.push_back(T8);


	Cartesian3 A9(-1, 1, 2);
	Cartesian3 B9(-1, -1, 2);
	Cartesian3 C9(1, 1, 2);

	Triangle T9(A9, B9, C9);
	T9.SetAlbedo(0.9);
	T9.ks = 0.0;
	T9.h = 10;
	T9.kd = 1.0;
	T9.r = 0;
	T9.g = 0;
	T9.b = 255;

	triangles.push_back(T9);

	Cartesian3 A10(1, 1, 2);
	Cartesian3 B10(-1, -1, 2);
	Cartesian3 C10(1, -1, 2);

	Triangle T10(A10, B10, C10);
	T10.SetAlbedo(0.9);
	T10.ks = 0.0;
	T10.h = 10;
	T10.kd = 1.0;
	T10.r = 0;
	T10.g = 0;
	T10.b = 255;

	triangles.push_back(T10);

	// Initialize the triangle
	Cartesian3 A11(-0.04688, -0.84375, 1.0);
	Cartesian3 B11(0.5625, 0.5625, 1.0);
	Cartesian3 C11(-0.60938, 0.40625, 1.0);

	Triangle T11(A11, B11, C11);
	T11.SetAlbedo(0.9);
	T11.ks = 1.0;
	T11.h = 20;
	T11.kd = 0.5;
	T11.r = 255;
	T11.g = 0;
	T11.b = 0;

	triangles.push_back(T11);

	// Set eye position
	Cartesian3 l0(0, 0, 0);

	// Initialize the ambient light
	Light al(l0, 0.7, 0.7, 0.7, 0.8, 0);

	// Set light position of point light
	Cartesian3 LightPos(-0.75, 0.4375, 0.0);

	// Initialize the point light
	Light pl(LightPos, 1.0, 1.0, 1.0, 0.5, 1);

	// Add the lights to the lights vector
	lights.push_back(al);
	lights.push_back(pl);

	// Loop through every pixel in the image plane
	for (int j = height - 1; j >= 0; j--)
	{
		for (int i = 0; i < width; i++)
		{
			double x = (2 * (i + 0.5) / (double)width - 1);
			double y = (2 * (j + 0.5) / (double)height - 1);
			Vector3 dir(x, y, 1);

			float t = 0;

			int r = 255;
			int g = 255;
			int b = 192;

			int isectIndex = -1;

			// Trace through the triangles and find the intersection
			if (trace(triangles, l0, dir, t, isectIndex) && isectIndex != -1)
			{
				Triangle hitTriangle = triangles.at(isectIndex);

				// Find the intersection point
				double ix = l0.x + dir.x * t;
				double iy = l0.y + dir.y * t;
				double iz = l0.z + dir.z * t;
				Cartesian3 p(ix, iy, iz);
				double totalR = 0, totalG = 0, totalB = 0;

				// Loop through every lights
				for (auto &light : lights)
				{
					double rToAdd = 0, gToAdd = 0, bToAdd = 0;
					if (light.LightType == 0)
					{
						// Add ambient light
						light.CalculateLighting(hitTriangle.getAlbedo(), rToAdd, gToAdd, bToAdd);
					}
					else
					{
						Vector3 lightdir(p.x - light.getPosition().x,
							p.y - light.getPosition().y,
							p.z - light.getPosition().z);
						lightdir.Normalize();

						Vector3 lightdir2 = -lightdir;
						Cartesian3 lightPosition = light.getPosition();
						float t2 = 0;
						int isectIndex2 = -1;

						// Trace shadow rays and check for visibility
						if (!(trace(triangles, lightPosition, lightdir, t2, isectIndex2, isectIndex) && t2 < t))
						{
							double ix = l0.x + dir.x * t;
							double iy = l0.y + dir.y * t;
							double iz = l0.z + dir.z * t;
							Cartesian3 p(ix, iy, iz);

							// Calculate diffuse value
							double diffuse = (hitTriangle.Normal * lightdir) / (hitTriangle.Normal.Magnitude() * lightdir.Magnitude());
							if (diffuse < 0)
								diffuse = 0;

							// Calculate specular value
							double h = hitTriangle.h;
							Vector3 b((dir.x + lightdir.x) / 2, (dir.y + lightdir.y) / 2, (dir.z + lightdir.z) / 2);
							b.Normalize();
							double specular = pow(std::max(0.0, (hitTriangle.Normal * b) / (hitTriangle.Normal.Magnitude() * b.Magnitude())), h);

							// Calculate the illummination to add
							rToAdd = (diffuse * hitTriangle.kd * light.intensity + specular * hitTriangle.ks * light.intensity) * light.R;
							gToAdd = (diffuse * hitTriangle.kd * light.intensity + specular * hitTriangle.ks * light.intensity) * light.G;
							bToAdd = (diffuse * hitTriangle.kd * light.intensity + specular * hitTriangle.ks * light.intensity) * light.B;
						}
					}
					totalR += rToAdd;
					totalG += gToAdd;
					totalB += bToAdd;
				}

				r = hitTriangle.r * totalR;
				g = hitTriangle.g * totalG;
				b = hitTriangle.b * totalB;
				r = std::min(255, r);
				g = std::min(255, g);
				b = std::min(255, b);

				r = std::max(0, r);
				g = std::max(0, g);
				b = std::max(0, b);

			}
			// Write the total color value to output file
			oFile << r << " " << g << " " << b << std::endl;
		}
	}
}

int main()
{
	// Prompt user for choice
	std::cout << "Enter choice\n1. Render Black Triangle\n2. Render Rainbow Triangle\n3. Render Blinn Phong - Ambient Only\n4. Render Blinn Phong - Specular\n5. Render Blinn Phong - Diffuse\n6. Render Blinn Phong - Diffuse and Specular\n7. Render image with shadows";
	int choice = 0;
	std::cin >> choice;

	// Render image based on the choice
	switch (choice)
	{
	case 1:
		RenderBlackTriangle();
		break;
	case 2:
		RenderRainbowTriangle();
		break;
	case 3:
		BlinnPhong(0, 0, "AmbientLight.ppm");
		break;
	case 4:
		BlinnPhong(0, 0.5, "DiffuseLight.ppm");
		break;
	case 5:
		BlinnPhong(0.5, 0, "SpecularLight.ppm");
		break;
	case 6:
		BlinnPhong(1.0, 0.5, "AmbientAndSpecularLight.ppm");
		break;
	case 7:
		Shadow();
		break;
	}
}

