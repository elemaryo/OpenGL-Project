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

#ifndef _VECTOR3_H
#define _VECTOR3_H

#include <math.h>

//-------------------------------------------------------

class vector3 {

public:

	// constructors

	vector3() {}

	vector3(float x1, float y1, float z1) : x(x1), y(y1), z(z1) {}



	// methods - vector

	vector3 normalize();

	vector3 add(vector3 v);

	vector3 subtract(vector3 v);

	vector3 scalar(float f);

	float dot(vector3 v);

	vector3 cross(vector3 v);

	vector3 reflect(vector3 norm);



	// method - geometry

	float distance(vector3 v);



	// data elements

	float x;

	float y;

	float z;

};

#endif // _VECTOR3_H

