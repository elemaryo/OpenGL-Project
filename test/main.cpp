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

#include "Header.h"

using namespace std;

//-------------------------------------------------------

// initialize all scene settings

void initialize() {

	// set background color

	glClearColor(0.0, 0.0, 0.0, 0.0);

	// enable depth buffer method

	glEnable(GL_DEPTH_TEST);



	// enable lighting

	light lg;



	// first light source

	lg.position = light_position0;

	lg.ambient_coef = l0_ambient_coef;

	lg.diffuse_coef = l0_diffuse_coef;



	// second light source

	lights.push_back(lg);

	lg.position = light_position1;

	lg.diffuse_coef = l1_diffuse_coef;

	lights.push_back(lg);


	// create shapes
	
	// create spheres

	// construct blue sphere

	spheres.push_back(sphere(-30.0f, 25.0f, 30.0f, 20.0f, 0.6f, BLUE));

	// construct green sphere
	
	spheres.push_back(sphere(15.0f, 20.0f, 60.0f, 12.5f, 0.6f, GREEN));



	// create mirror

	planes.push_back(mirror);



	// create cube

	// bottom face

	planes.push_back(cube1);

	// top face

	planes.push_back(cube2);

	// left face

	planes.push_back(cube3);

	// right face
	planes.push_back(cube4);

	// back face

	planes.push_back(cube5);

	// front face

	planes.push_back(cube6);



	// calculation of other global variables

	// u is the unitary vector from the viewer to image center direction, used to calculate vv, vu and vo

	vector3 u = center.subtract(viewer).normalize();

	// unitary vector down to up direction of the near plane

	vv = up.subtract(u.scalar(u.dot(up))).normalize();

	// unitary vector left to right direction of the near plane

	vu = u.cross(vv);

	// center of the near plane

	vo = viewer.add(u.scalar(vnear));
}



// function that calculate floor color

vector3 floorcolor(vector3& p) {

	// the lower x and z floor coordinate is -75, i and j are not negatives
	
	int i = p.x + 75;
	
	int j = p.z + 75;



	// The width of floor is 150, each 25 units the tile color changes
	
	// if i/25 + j/25 is odd

	if ((i / 25 + j / 25) & 1) { 
		
		return RED;
	
	}

	else {
	
		return LIGHTGRAY;
	
	}
}



// calculate local color

vector3 localColor(vector3 point, vector3 baseColor, vector3 normal) {
	
	// The intersect is calculated but is not used in this function 

	vector3 intersect;

	// current light intensity
	
	float intensity = 0.0f;

	// loop for all light sources to calculate intensity

	for (int i = 0; i < lights.size(); i++) {

		// add ambient contribution

		intensity += lights[i].ambient_coef; 

		// ldir is the direction from the surface point to the light position

		vector3 ldir = lights[i].position.subtract(point).normalize();

		float dist = floorDef.intersect(point, ldir, intersect);
		
		if (dist < max_dist) {

			// the light beam is interrupted by the floor

			dist = 0.0f;

		} else

			dist = max_dist;
		

		// if the light is not interrupted, search intersections with other planes

		if (dist != 0.0f) {

			for (int j = 0; j < planes.size(); j++) {
				
				if (dist > planes[j].intersect(point, ldir, intersect)) {
					
					// the light beam is interrupted by a plane

					dist = 0.0f; 

					break;
				}

			}
			

			// if the light is not interrupted, try with spheres

			if (dist != 0.0f) {
				
				// search intersections with spheres

				for (int j = 0; j < spheres.size(); j++) {

					if (dist > spheres[j].intersect(point, ldir, intersect)) {
						
						// the light beam is interrupted by a sphere

						dist = 0.0f; 
						
						break;
					}
				}

				// if the light is not interrupted

				if (dist != 0.0f) {

					float dotProd = ldir.dot(normal);

					if (dotProd > 0.0f)
						
						// add diffuse contribution to intensity

						intensity += lights[i].diffuse_coef * dotProd; 
				}
			}
		}
	}



	// local color is intensity * base color

	float r = intensity * baseColor.x;

	float g = intensity * baseColor.y;

	float b = intensity * baseColor.z;



	return vector3(r, g, b);
}



// recursive ray tracing function

vector3 raytrace(vector3 incident, vector3 direction, int calls) {

	// base case of max recursion level reached

	if (calls == max_calls) {
		
		return backgroundColor;
	}

	// search for nearest object that intersect the ray

	// intersect points

	vector3 intersect, aux;
	int index = -1; // shape index (plane or sphere)

	// object intersection with floor

	float sphere_dist, plane_dist = floorDef.intersect(incident, direction, intersect);

	// searches for the nearest intersecting plane

	for (int j = 0; j < planes.size(); j++) { 
		
		float dist = planes[j].intersect(incident, direction, aux);
		
		// if this plane is the nearest
		
		if (dist < plane_dist) {
			index = j;
			plane_dist = dist;
			intersect = aux;
		}
	}

	// searches for spheres distances lower than the nearest plane distance

	sphere_dist = plane_dist; 

	// loop through all spheres

	for (int j = 0; j < spheres.size(); j++) { 
		
		float dist = spheres[j].intersect(incident, direction, aux);
		
		// if the intersection point of the sphere is the nearest

		if (dist < sphere_dist) {
			index = j;
			sphere_dist = dist;
			intersect = aux;
		}
	}

	// if the ray is intersected
	
	if (sphere_dist < max_dist) { 

		vector3 normal, mixedColor;

		// coefficient of reflection

		float rc;
		


		// The object that intersect the ray is identified to extract some properties

		// the intersected object is a sphere

		if (sphere_dist < plane_dist) { 
			
			normal = spheres[index].normal(intersect);
			
			mixedColor = localColor(intersect, spheres[index].color, normal);
			
			rc = spheres[index].reflect_coef;
		} 


		
		// the intersected object is the floor plane

		else if (index < 0) {
			
			normal = floorDef.normal();
			
			mixedColor = localColor(intersect, floorcolor(intersect), normal);
			
			rc = floorDef.reflect_coef;
		} 



		// the intersected object is another plane

		else {
			
			normal = planes[index].normal();
			
			mixedColor = localColor(intersect, planes[index].color, normal);
			
			rc = planes[index].reflect_coef;
		}


		// if the intersected shape reflect the ray

		if (rc > 0.0f) { 

			// calculate reflection ray direction

			vector3 reflectDir = intersect.subtract(incident).reflect(normal); 

			// recursively ray trace reflected ray if it intersects with reflective surface

			vector3 reflectColor = raytrace(intersect, reflectDir, calls + 1); 
			
			return reflectColor.scalar(rc).add(mixedColor.scalar(1.0f - rc));
		}

		return mixedColor;
	}

	// outside of the reflection base case, use background color only if ray hits nothing

	return backgroundColor;
}



// render

void render() {

	float h_2 = imageheight*0.5f, w_2 = imagewidth*0.5f;

	float aspect = (float)imagewidth/imageheight;

	// distance vector to right neighbor pixel

	vector3 u = vu.scalar((vtop - vbottom)*aspect/imagewidth); 

	// distance vector to upper neighbor pixel

	vector3 v = vv.scalar((vtop - vbottom)/imageheight); 

	// lower left corner of the near plane

	vector3 o = vector3(vo.x - w_2*u.x - h_2*v.x, vo.y - w_2*u.y - h_2*v.y, vo.z - w_2*u.z - h_2*v.z);

	// render scene

	for (int j = 0; j < imageheight; j++)

		for (int i = 0; i < imagewidth; i++) {

			// p is a point in the near plane, used as origin of ray in raytrace function

			vector3 p = vector3(o.x + i*u.x + j*v.x, o.y + i*u.y + j*v.y, o.z + i*u.z + j*v.z);

			// calculate reflection color through ray tracing

			vector3 mixedColor = raytrace(p, p.subtract(viewer).normalize(), 0);

			// use the small rectangles method based on colors from raytracing

			glColor3f(mixedColor.x, mixedColor.y, mixedColor.z);

			glBegin(GL_POLYGON);

				glVertex3i(i, j, 0);

				glVertex3i(i + 1, j, 0);

				glVertex3i(i + 1, j + 1, 0);

				glVertex3i(i, j + 1, 0);

			glEnd();
		}
}



// display registry

void display(void) {

	// clear the color and depth buffers 

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// load identity matrix

	glLoadIdentity();



	// call render function

	render();



	// swap the backbuffer with the front buffer

	glutSwapBuffers();
}



// reshape registry

void reshape(int w, int h) {

	// recreate the viewport 

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// set projection mode as matrix

	glMatrixMode(GL_PROJECTION);

	// load identity matrix to reset for projection

	glLoadIdentity();


	// the coordinates in the glut window are equal to pixel coordinates with lower left origin

	glOrtho(0, w, 0, h, -1, 1);
	
	// reassign image width

	imagewidth = w;
	
	// reassign image width

	imageheight = h;



	// set modelview mode as matrix

	glMatrixMode(GL_MODELVIEW);
}



// main program

int main(int argc, char** argv)
{
	// initialize glut

	glutInit(&argc, argv);

	// initialize the display mode with double buffering, RGB colors and depth

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// set the width and height of the window

	glutInitWindowSize(imagewidth, imageheight);

	// set the initial window position

	glutInitWindowPosition(100, 100);



	// set the window handle and title bar of the window

	int windowHandle = glutCreateWindow("Athabasca University - Comp 390 Final Project");

	// set the window handle

	glutSetWindow(windowHandle);



	// set the display callback function

	glutDisplayFunc(display);

	// set the reshape callback function

	glutReshapeFunc(reshape);



	// call the initialize function

	initialize();



	// call OpenGL's main loop

	glutMainLoop();

}

