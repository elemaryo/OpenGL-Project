/* Athabasca University

   Comp390 - Introduction To Computer Graphics

   Final Project

   Program Description: Implement a vector construct with three dimensions and needed mathematical operations.

   Routine Description:
		vector3 - Constructors of a vector.
		normalize - Normalizes a vector3.
		add - Adds a vector3 dimensions to another vector3 object.
		subtract - Subtracts a vector3 dimensions from another vector3 object.
		scalar - Multiply vector3 dimenstions scalarly.
		dot - Calculates dot product of two vector3 objects.
		cross - Calculates cross product of two vector3 objects.
		reflect - Calculate reflection of a vector3 from a plane normal.
		distance - Calculate distance from one vector3 to another vector3 object.

   @author: Omar Elemary

   @ID:	3430222

   @date: April 16, 2021

*/

#include "vector3.h"

//-------------------------------------------------------

// normalize vector function

vector3 vector3::normalize() {

	// find the magnitude of the vector

	float length = sqrt((x * x) + (y * y) + (z * z));

	// if the magnitude is small

	if (length < 0.001)

		return vector3(0.0, 0.0, 0.0);

	else

		return vector3((x / length), (y / length), (z / length));

}



// add vectors functions

vector3 vector3::add(vector3 v) {

	// add all dimensions from each vector and return a vector3

	return vector3(x + v.x, y + v.y, z + v.z);

}



// subtract vectors functions

vector3 vector3::subtract(vector3 v) {

	// subtract all dimensions from each vector and return a vector3

	return vector3(x - v.x, y - v.y, z - v.z);

}



// scalar multiplication function

vector3 vector3::scalar(float f) {

	// multiply dimensions by float f and return the vector3

	return vector3(x * f, y * f, z * f);

}



// dot product vectors functions

float vector3::dot(vector3 v) {

	// multiply all dimensions from each vector and return a vector3

	return ((x * v.x) + (y * v.y) + (z * v.z));

}



// cross product vectors function

vector3 vector3::cross(vector3 v) {

	float x1 = (y * v.z) - (z * v.y);

	float y1 = (z * v.x) - (x * v.z);

	float z1 = (x * v.y) - (y * v.x);

	// return cross product

	return vector3(x1, y1, z1);

}



// reflection of vector function

vector3 vector3::reflect(vector3 norm) {

	// u = v - 2 * |Inc * Norm| * Norm

	vector3 n_inc = normalize();

	float   term1 = 2 * n_inc.dot(norm);

	vector3 term2 = norm.scalar(term1);

	// return normal vector

	return vector3(n_inc.subtract(term2));

}



// distance of vectors function

float vector3::distance(vector3 v) {

	// subtract dimensions

	float dx = v.x - x;

	float dy = v.y - y;

	float dz = v.z - z;

	// return magnitude

	return sqrt((dx * dx) + (dy * dy) + (dz * dz));

}