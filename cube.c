#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "cube.h"

int const sizeX = 12; //World space size in x, y, and z (12 by 12 by 12)
int const sizeY = 12;
int const sizeZ = 12;
double const scale = 0.22; //Amount by which ray move forward in each iteration of ray trace
double const PI = 3.14159265358; //Used to convert between degrees and radians

//Hardcoded definition of the cube world space
int worldSpace[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  //1st layer
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //2nd
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,

    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //3rd
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //4th
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //5th
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //6th
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //7th
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,

    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //8th
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,

    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //9th
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,

    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //10th
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,

    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //11th
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,

    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, //12th
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

struct _cube{
  int wSizeX; //Window size in "pixels" in x and y
  int wSizeY;
  double distZ; //Distance between window and world space
  int vDistZ; //Distance between window and virtual camera

  char fill;
  char space;
  
  float theta; //Yaw
  float phi; //Pitch
  float omega; //Roll
};

/* Looks up a point in the world space and returns that value, either 1 or 0
 */
int getE(double x, double y, double z, int * worldSpace){
  return worldSpace[(int)x + (sizeX * (int)y) + ((sizeX * sizeY) * (int)z)];
}

/* Traces a ray through the world space
 */
int traceRay(double wX, double wY, double wZ,
	     double vX, double vY, double vZ,
	     double max, int * worldSpace){
  double norm = sqrt(pow(vX-wX,2) + pow(vY-wX,2) + pow(vZ-wZ,2));
  double slopeX = (wX-vX) / norm;
  double slopeY = (wY-vY) / norm;
  double slopeZ = (wZ-vZ) / norm;
  double x = vX;
  double y = vY;
  double z = vZ;
  while(1){
    x += slopeX*scale;
    y += slopeY*scale;
    z += slopeZ*scale;
    if(pow(vX-x,2) + pow(vY-y,2) + pow(vZ-z,2) > max) return 0; //Ray is beyond world space, return 0
    if(x < sizeX && y < sizeY && z < sizeZ && x > 0 && y > 0 && z > 0){ //Ray is inside world space
      int rv;
      if((rv = getE(x, y, z, worldSpace))) return rv;
    }
  }
}

/* Creates a new cube struct where wSize is the size of
 * the window in "pixels", distZ is the distance between
 * the window and the world space, vDistZ is the distance
 * between the window and the virtual camera (essentially these set the perspective), 
 * fill is the character used to for the fill of the cube, and space is the character
 * used for space
 * wSize and distZ must be positive. vDistZ must be greater than 2.
 */
cube * newCube(int wSize, double distZ, double vDistZ, char fill, char space){
  if(wSize < 1 || distZ < 0 || vDistZ < 2) return NULL;
  cube * a = malloc(sizeof(cube));
  a->wSizeX = wSize;
  a->wSizeY = wSize;
  a->distZ = distZ;
  a->vDistZ = vDistZ;
  a->fill = fill;
  a->space = space;
  a->theta = 0.0f;
  a->phi = 0.0f;
  a->omega = 0.0f;
  return a;
}

/* Frees the cube struct
 */
void deleteCube(cube * cubeA){
  free(cubeA);
}

/* Increments the rotation of the cube by the amount specified in
 * degrees with yaw being the rotation in the x direction, pitch 
 * being the rotation in the y direction, and roll being the 
 * rotation of the camera
 */
void rotateBy(cube * cubeA, float roll, float pitch, float yaw){
  cubeA->theta += (PI/180.0)*yaw;
  cubeA->phi += (PI/180.0)*pitch;
  cubeA->omega += (PI/180.0)*roll;
}

/* Renders the cube
 */
void render(cube * cubeA){
  int window[cubeA->wSizeX * cubeA->wSizeY];
  for(int y = 0; y < cubeA->wSizeX; y++){
    for(int x = 0; x < cubeA->wSizeY; x++){ //Iterate through each "pixel" in the window
      
      //Calculates the position of the virtual camera and the center of each "pixel" in the window
      int i = x + (y * cubeA->wSizeX);
      double wX = ((x + 0.5)/cubeA->wSizeX)*sizeX;
      double wY = ((y + 0.5)/cubeA->wSizeY)*sizeY;
      double wZ = sizeZ + cubeA->distZ;
      double vX, vY, vZ;
      double r = cubeA->distZ + (0.5*sizeZ);
      double vR = r + cubeA->vDistZ;
      double xDispt = (wX-(0.5*sizeX));
      double yDispt = (wY-(0.5*sizeY));
      double xDisp = (xDispt*cos(cubeA->omega)) - (yDispt*sin(cubeA->omega));
      double yDisp = (xDispt*sin(cubeA->omega)) + (yDispt*cos(cubeA->omega));
      
      wX = (0.5*sizeX) + (r*sin(cubeA->theta)) + (xDisp*cos(cubeA->theta));
      wZ = (0.5*sizeZ) + (r*cos(cubeA->theta)) - (xDisp*sin(cubeA->theta));
      r = wZ - (0.5*sizeZ);
      wY = (0.5*sizeY) + (r*sin(cubeA->phi)) + (yDisp*cos(cubeA->phi));
      wZ = (0.5*sizeZ) + (r*cos(cubeA->phi)) - (yDisp*sin(cubeA->phi));
      
      vX = (0.5*sizeX) + (vR*sin(cubeA->theta));
      vZ = (0.5*sizeZ) + (vR*cos(cubeA->theta));
      vR = vZ - (0.5*sizeZ);
      vY = (0.5*sizeY) + (vR*sin(cubeA->phi));
      vZ = (0.5*sizeZ) + (vR*cos(cubeA->phi));

      //Largest distance that ray can travel and still be in world space, used to determine if the ray has passed the world space
      double max = (pow(sizeX,2) + pow(sizeY,2) + pow(sizeZ,2) +
		    pow(cubeA->distZ+cubeA->vDistZ+sizeZ,2));
      
      //Send calculated values to trace ray
      window[i] = traceRay(wX, wY, wZ, vX, vY, vZ, max, worldSpace);
      if(window[i] == 0) printf("%c%c",cubeA->space,cubeA->space);
      if(window[i] == 1) printf("%c%c",cubeA->fill,cubeA->fill);
    }
    printf("\n");
    }
  printf("\n");
}
