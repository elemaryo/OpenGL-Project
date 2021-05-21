/* Athabasca University

   Comp390 - Introduction To Computer Graphics

   Final Project

   Program Description: Implements a reflective sphere object

   Routine Description:
		sphere - Constructors for a reflective sphere object
		intersect - calculates the intersection point of a given ray with the sphere, returns the distance from the ray origin to intersection point.
		normal - calculate the normal at the intersection point

   @author: Omar Elemary

   @ID:	3430222

   @date: April 16, 2021

*/

#ifndef _SPHERE_H
#define _SPHERE_H

#include <cmath>

#include "vector3.h"

//-------------------------------------------------------

class sphere {
public:

	// constructors

	// default constructor

	sphere() {} 

	sphere(float xc, float yc, float zc, float r, float refl_coef, vector3 Color):
		color(Color), x(xc), y(yc), z(zc), radius(r), reflect_coef(refl_coef) {}


	// methods

	float intersect(vector3 &o, vector3 &dir, vector3 &ip);

	vector3 normal(const vector3 &p);



	// data element - color

	vector3 color;



	// data elements - coordinates of center and radius

	float x, y, z, radius;



	// data element - reflection coefficient

	float reflect_coef;
};

#endif // _SPHERE_H

