#ifndef CUBE_H_
#define CUBE_H_

typedef struct _cube cube;

/* Creates a new cube struct where wSize is the size of
 * the window in "pixels", distZ is the distance between
 * the window and the world space, vDistZ is the distance
 * between the window and the virtual camera (essentially these set the perspective), 
 * fill is the character used to for the fill of the cube, and space is the character
 * used for space
 * wSize and distZ must be positive. vDistZ must be greater than 2.
 */
cube * newCube(int wSize, double distZ, double vDistZ, char fill, char space);

/* Frees the cube struct
 */
void deleteCube(cube * cubeA);

/* Increments the rotation of the cube by the amount specified in
 * degrees with yaw being the rotation in the x direction, pitch 
 * being the rotation in the y direction, and roll being the 
 * rotation of the camera
 */
void rotateBy(cube * cubeA, float roll, float pitch, float yaw);

/* Renders the cube
 */
void render(cube * cubeA);

#endif
