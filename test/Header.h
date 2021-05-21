/* Athabasca University

   Comp390 - Introduction To Computer Graphics

   Final Project

   Program Description:

   Routine Description:
		initialize - Sets the background color of the display window, enables depth testing, set the light parameters
						for two light sources and creates sphere, mirror and cube shapes used for scene.
		floorcolor - Returns floor color depending on the tile.
		localColor - Calculates the local color of an intersected object using ambient and diffuse intensity contributions.
		raytrace - Recursive function that returns the color values. The algorithm casts the ray from the viewer to the scene and recursively calls itself to calculate the color depending on the object in the scene the ray intersects with or reflects from.
					If the ray hits a non-reflective object, or the ray does not hit anything, or the ray has been reflected max_calls times, the method will terminate.
		render -  Render the scene using the raytrace function. A series of rectangles occupying one pixel of the screen are placed on the xy plane (z = 0)
					and the color of each square is calculated through raytrace.
		display - Sets the display viewing properties and calls render function.
		reshape - Sets the viewing properties that occur during a window resize.
		main - Initializes the GLUT library, creates and positions the display window and calls routines to display content during the program main loop.

   @author: Omar Elemary

   @ID:	3430222

   @date: April 16, 2021

*/

#ifndef _PROJECTHEADERS_H
#define _PROJECTHEADERS_H

#include <windows.h>

#include <stdio.h>

#include <stdlib.h>

#include <math.h>

#include "gl/glut.h"

#include <vector>

#include "plane.h"

#include "sphere.h"

using namespace std;

//-------------------------------------------------------

// defining the light struct

struct light {

	vector3 position;

	float ambient_coef, diffuse_coef;

};



// initialize light positions

vector3 light_position0 (20.0f, 50.0f, 100.0);

vector3 light_position1 (-50.0f, 120.0f, 75.0f);



// lighting elements

float l0_ambient_coef = 0.1f;

float l0_diffuse_coef = 0.9f;

float l1_diffuse_coef = 0.7f;



//-------------------------------------------------------

// viewer (camera) position

vector3 viewer (30.0f, 70.0f, 160.0f);

vector3 center (0.0f, 10.0f, 0.0f);

vector3 up (0.0f, 1.0f, 0.0f);



// near plane vectors

// center of near plane

vector3 vo;

// width of near plane

vector3 vu;

// height of near plane

vector3 vv;



// near plane boundaries

// bottom value of near plane
float vbottom = -0.6f;

// top value of near plane

float vtop = 0.6f;

// right value of near plane

float vright = 0.9f;

// left value of near plane

float vleft = -0.9f;

// distance to the near plane

float vnear = 1.5f;

// maximum allowed distance

float max_dist = 500.0f;



// height and width of the image and glut window

int imageheight = 500;

int imagewidth = imageheight * (vright - vleft) / (vtop - vbottom);



// ray trace maximum calls

int max_calls = 4;



// initialize colors

vector3 backgroundColor(0.0f, 0.0f, 0.0f);

vector3 BROWN(0.3f, 0.3f, 0.1f);

vector3 GREEN(0.0f, 1.0f, 0.2f);

vector3 BLUE(0.1f, 0.1f, 0.9f);

vector3 ORANGE(1.0f, 0.3f, 0.0f);

vector3 PURPLE(0.5f, 0.0f, 0.6f);

vector3 RED(0.75, 0.1, 0.1);

vector3 LIGHTGRAY(0.75, 0.75, 0.75);



// cube vertices

vector3 cubev[8] = {

	vector3(-0.5f, -0.5f, -0.5f),

	vector3(0.5f, -0.5f, -0.5f),

	vector3(-0.5f, -0.5f, 0.5f),

	vector3(0.5f, -0.5f, 0.5f),

	vector3(-0.5f, 0.5f, -0.5f),

	vector3(0.5f, 0.5f, -0.5f),

	vector3(-0.5f, 0.5f, 0.5f),

	vector3(0.5f, 0.5f, 0.5f)
};

// length of the cube

float cubeLength = 35.0f;

// cube coefficient of reflection

float cubeRC = 0.65f;

// center of cube

vector3 cubeCenter(30.0f, 25.0f, -10.0f);



// floor plane

vector3 floorLimit1(-75.0f, 0.0f, 75.0f);

vector3 floorLimit2(75.0f, 0.0f, 75.0f);

vector3 floorLimit3(-75.0f, 0.0f, -75.0f);

plane floorDef (floorLimit1, floorLimit2, floorLimit3, 0.4f, RED);



// mirror plane

vector3 mirrorLimit1(-75.0f, 10.0f, -50.0f);

vector3 mirrorLimit2(-5.0f, 10.0f, -75.0f);

vector3 mirrorLimit3(-75.0f, 60.0f, -50.0f);

plane mirror (mirrorLimit1, mirrorLimit2, mirrorLimit3, 0.8f, BROWN);



// cube planes for each face scaled to cube size

// bottom face

plane cube1(cubev[0].scalar(cubeLength).add(cubeCenter), cubev[1].scalar(cubeLength).add(cubeCenter), cubev[2].scalar(cubeLength).add(cubeCenter), cubeRC, PURPLE);

// top face

plane cube2(cubev[4].scalar(cubeLength).add(cubeCenter), cubev[6].scalar(cubeLength).add(cubeCenter), cubev[5].scalar(cubeLength).add(cubeCenter), cubeRC, PURPLE);

// left face

plane cube3(cubev[0].scalar(cubeLength).add(cubeCenter), cubev[2].scalar(cubeLength).add(cubeCenter), cubev[4].scalar(cubeLength).add(cubeCenter), cubeRC, PURPLE);

// right face

plane cube4(cubev[3].scalar(cubeLength).add(cubeCenter), cubev[1].scalar(cubeLength).add(cubeCenter), cubev[7].scalar(cubeLength).add(cubeCenter), cubeRC, PURPLE);

// back face

plane cube5(cubev[1].scalar(cubeLength).add(cubeCenter), cubev[0].scalar(cubeLength).add(cubeCenter), cubev[5].scalar(cubeLength).add(cubeCenter), cubeRC, PURPLE);

// front face

plane cube6(cubev[2].scalar(cubeLength).add(cubeCenter), cubev[3].scalar(cubeLength).add(cubeCenter), cubev[6].scalar(cubeLength).add(cubeCenter), cubeRC, PURPLE);


// vectors for lights and objects

vector <light> lights;

vector <plane> planes;

vector <sphere> spheres;

//-------------------------------------------------------

void initialize();

vector3 floorcolor(vector3& p);

vector3 localColor(vector3 point, vector3 baseColor, vector3 normal);

vector3 raytrace(vector3 incident, vector3 direction, int calls);

void render();

void display();

void reshape(int w, int h);

#endif // !_PROJECTHEADERS_H

