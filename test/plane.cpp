/* Athabasca University

   Comp390 - Introduction To Computer Graphics

   Final Project

   Program Description: Implements a place construct and defines methods essential to the 
							calculation of the line-plane intersection

   Routine Description:
		plane - Constructor for a plane construct
		intersect - Calculates the intersection point of a given ray with the plane, returns the distance from the ray origin to intersection point.
		normal - Return the normal of the plane

   @author: Omar Elemary

   @ID:	3430222

   @date: April 16, 2021

*/

#include "plane.h"

using namespace std;



// parameter used to prevent selecting the objects with distance zero from the ray origin

#define epsilon 0.0001



// An intersect point with distance equal to max_dist will be not used

extern float max_dist;

//-------------------------------------------------------

plane::plane(vector3 p1, vector3 p2, vector3 p3, float refl_coef, vector3 Color) :
	reflect_coef(refl_coef), color(Color) {
	
	// p is p1, d1 is p2 - p1 and d2 is p3 - p1

	px = p1.x;
	py = p1.y;
	pz = p1.z;
	d1x = p2.x - px;
	d2x = p3.x - px;
	d1y = p2.y - py;
	d2y = p3.y - py;
	d1z = p2.z - pz;
	d2z = p3.z - pz;



	// normal coordinates, cross product of d1 and d2, a is nx, b is ny and c is nz

	a = d1y * d2z - d1z * d2y;
	b = d1z * d2x - d1x * d2z;
	c = d1x * d2y - d1y * d2x;




	// norm of normal vector

	float t = a * a + b * b + c * c;



	// normalizing

	if (t > epsilon * epsilon) {
		t = 1 / sqrt(t);
		a *= t; b *= t; c *= t;
		type = 1;
	}



	// if t is zero, the 3 points are collinear, the plane can not be rendered (wrong parameters)

	else
		type = -1;
}



// Calculates the intersection point (ip) of a given ray with the plane, returns the distance from the ray origin (o) to intersection point.

float plane::intersect(vector3& o, vector3& dir, vector3& ip) {

	// t is the distance from o to ip

	float t;

	// from https://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection

	if (type == 1) {
		
		float det = dir.x * (d1y * d2z - d1z * d2y) + dir.y * (d1z * d2x - d1x * d2z) + dir.z * (d1x * d2y - d1y * d2x);
		
		// parallel ray

		if (fabs(det) < epsilon) {
			
			return max_dist;
		}

		float tx = o.x - px;

		float ty = o.y - py;

		float tz = o.z - pz;
		
		det = 1.0f / det;
		
		float u = (tx * (d2y * dir.z - d2z * dir.y) + ty * (d2z * dir.x - d2x * dir.z) + tz * (d2x * dir.y - d2y * dir.x)) * det;
		
		

		// no intersection

		if (u <= 0 || u >= 1.0f) {
			
			return max_dist;
		}

		float v = (tx * (dir.y * d1z - dir.z * d1y) + ty * (dir.z * d1x - dir.x * d1z) + tz * (dir.x * d1y - dir.y * d1x)) * det;
		


		// no intersection

		if (v <= 0 || v >= 1.0f) {
			
			return max_dist;

		}
		


		// distance calculation based on parallelogram

		t = -(tx * (d1y * d2z - d1z * d2y) + ty * (d1z * d2x - d1x * d2z) + tz * (d1x * d2y - d1y * d2x)) * det;
	}

	// resolve only t for infinity plane

	else if (type == 0) {
		
		float constant = (a * o.x) + (b * o.y) + (c * o.z);

		float tcoef = (a * dir.x) + (b * dir.y) + (c * dir.z);

		t = (-d - constant) / tcoef;
	}



	// type -1 means that the plane data are wrong, and the plane will be not rendered

	else
		return max_dist; 



	// no intersection, plane too close to o or in opposed direction

	if (t < epsilon) {
		return max_dist;
	}


	// resolve

	ip.x = o.x + (dir.x * t);

	ip.y = o.y + (dir.y * t);

	ip.z = o.z + (dir.z * t);



	// returns the distance from the ray origin (o) to intersection point (ip)

	return t; 
}



// return the plane normal vector

vector3 plane::normal() {

	return vector3(a, b, c);
}







