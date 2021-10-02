/*
 *  Utility function definitions for CSCI-4229 Homework
 *  4.
 *  Created by Jeff Colgan. 
 */

#include "utility.h"

/*
 *  Function to print raster text.
 */
#define LEN 8192
void Print(const char* format, ...)
{
   char buf[LEN];
   char* ch = buf;

   va_list args;
   va_start(args, format);
   vsnprintf(buf, LEN, format, args);
   va_end(args);

   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *ch++);
}

/*
 *  Print error message to stderr and exit with status 1.
 */
void Fatal(const char* format, ...)
{
   va_list args;
   va_start(args, format);
   vfprintf(stderr, format, args);
   va_end(args);
   exit(1);
}

/*
 *  Check for errors in OpenGL.
 */
void ErrCheck(const char* where)
{
   int err = glGetError();
   if (err) fprintf(stderr, "ERROR: %s [%s]\n", gluErrorString(err), where);
}

/*
 *  This utility function "moves" the camera forward/backward 
 *  by modifying the x, z values of the Eye vector (for use in
 *  glLookAt).
 */
void MoveForward(double* x, double* z, int theta)
{  
   // Compute the new Ex, Ez values.
   *x += (Sin(theta) * 0.1);
   *z += (-Cos(theta) * 0.1);

   // Keep x-values in the boundaries established by the floor.
   if (*x < -3.0)
   {
      *x = -3.0;
   }
   else if (*x > 3.0)
   {
      *x = 3.0;
   }
   
   // Keep z-values in the boundaries established by the floor.
   if (*z < -3.0)
   {
      *z = -3.0;
   }
   else if (*z > 3.0)
   {
      *z = 3.0;
   }
}

/*
 *  This utility function "moves" the camera backward by
 *  modifying the x, z values of the Eye vector (for use in
 *  glLookAt). 
 */
void MoveBackward(double* x, double* z, int theta)
{
   // Compute the new Ex, Ez values.
   *x -= (Sin(theta) * 0.1);
   *z -= (-Cos(theta) * 0.1);

   // Keep x-values in the boundaries established by the floor.
   if (*x < -3.0)
   {
      *x = -3.0;
   }
   else if (*x > 3.0)
   {
      *x = 3.0;
   }

   // Keep z-values in the boundaries established by the floor.
   if (*z < -3.0)
   {
      *z = -3.0;
   }
   else if (*z > 3.0)
   {
      *z = 3.0;
   }
}

/*
 *  This utility function "turns" the camera by modifying
 *  the x, z values of the C-vector (for use in glLookAt). 
 */
void Turn(double* x, double* z, double dim, int theta)
{
   // Compute the new Cx, Cz values.
   *x = 2 * dim * Sin(theta);
   *z = -2 * dim * Cos(theta);
}

/*
 *  This utility function resets the eye position vector, theta, phi, and
 *  C-vector (for first-person perspective navigation).
 */
void ResetPosition(double* Ex, double* Ey, double* Ez, double *Cx, double* Cy, 
                   double* Cz, double* dim, int*theta, int* phi)
{
   // Reset the eye vector values to the start coordinates.
   *Ex = -3.0;
   *Ey = 0.4;
   *Ez = 3.0;
   
   // Reset dim, th, ph to the start values.
   *dim = 3.0;
   *theta = 45;
   *phi = 45;
 
   // Reset C-vector to start coordinates.
   *Cx = 3.3;
   *Cy = 0.4;
   *Cz = -3.3;
}