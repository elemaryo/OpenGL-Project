/* Athabasca University

   Comp390 - Introduction To Computer Graphics

   Final Project

   Program Description: Implements a place construct and defines methods essential to the
							calculation of the line-plane intersection

   Routine Description:
		plane - Constructor for a plane construct
		intersect - Calculates the intersection point of a given ray with the plane, 
						returns the distance from the ray origin to intersection point.
		normal - Return the normal of the plane

   @author: Omar Elemary

   @ID:	3430222

   @date: April 16, 2021

*/

#ifndef _PLANE_H
#define _PLANE_H

#include <iostream>

#include <math.h>

#include "vector3.h"

//-------------------------------------------------------


class plane {

public:

	// constructors

	// default constructor

	plane();

	// a1*x + b1*y + c1*z + d1 = 0

	plane(float a1, float b1, float c1, float d1, float refl_coef, vector3 Color) : a(a1), b(b1), c(c1), d(d1) {};

	/*    p3____
	      /    /
	     /____/
	   p1     p2  */

	plane(vector3 p1, vector3 p2, vector3 p3, float refl_coef, vector3 Color);



	// methods

	float intersect(vector3& o, vector3& dir, vector3& ip);



	// calculate and return plane normal

	vector3 normal();



	// data elements - formula

	float a;

	float b;

	float c;

	float d;



	// data elements - coordinates of corners, d1 = p2 - p1, d2 = p3 - p1

	float px, py, pz,

		d1x, d1y, d1z,
		
		d2x, d2y, d2z;



	// data element - reflection coefficient

	float reflect_coef;



	// data element - color

	vector3 color;


	
	// type: 0 infinity plane, 1 parallelogram, -1 error
	
	int type;
};

#endif // _PLANE_H

