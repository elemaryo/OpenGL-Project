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

#include "sphere.h"

//-------------------------------------------------------


// parameter used to prevent selecting the objects with distance zero from the ray origin

#define epsilon 0.0001



// An intersect point with distance equal to max_dist will be not used

extern float max_dist;


//-------------------------------------------------------

// calculate the intersect point (ip) of a ray (with origin o and direction dir) and the sphere

float sphere::intersect(vector3& o, vector3& dir, vector3& ip) {

	// DP = Pc - Po

	float DPx = x - o.x;
	float DPy = y - o.y;
	float DPz = z - o.z;

	// u dot DP

	float uDP = dir.x * DPx + dir.y * DPy + dir.z * DPz;

	// (u . DP)^2 - |DP|^2 + r^2

	float s = uDP * uDP - DPx * DPx - DPy * DPy - DPz * DPz + radius * radius;



	// no intersection (sqrt(s) is imaginary)

	if (s < 0.0) {
		return max_dist;
	}

	s = uDP - sqrtf(s); // eq. 21-9



	// no intersection (the ray origin is on the sphere surface)

	if (s < epsilon) {
		return max_dist;
	}



	// Po + s u

	ip.x = o.x + s * dir.x;

	ip.y = o.y + s * dir.y;

	ip.z = o.z + s * dir.z;



	// returns the distance from the ray origin (o) to intersection point (ip)

	return s; 
}



// p have to be the intersect point.
// The normal is the unit vector from the sphere center to the intersect point

vector3 sphere::normal(const vector3 &p) {

	float t = 1/radius;

	return vector3((p.x - x)*t, (p.y - y)*t, (p.z - z)*t);
}

