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
 *  This function sets the Projection matrix based on the fov.  For now, a
 *  fov value of zero sets it to orthogonal, and any other value will set
 *  to perspective.  I plan to iterate on this in the future.
 */
void Projection(double fov, double asp, double dim)
{
   // Switch to manipulating projection matrix and undo previous transforms.
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   // If the fov is anything other than zero, perspective projection
   if (fov != 0)
   {
      gluPerspective(fov, asp, dim / 16, 16 * dim);
   }
   // Otherwise do orthogonal.
   else
   {
      glOrtho(-asp * dim, asp * dim, -dim, dim, -dim, dim);
   }

   // Switch back to model matrix and undo previous transforms.
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void MoveForward(double* x, double* y, double* z, double dim, int theta, int phi)
{   
   *x = -2 * dim * Sin(theta) * Cos(phi);
   *z = 2 * dim * Cos(theta) * Cos(phi);
}

void MoveBackward(double* x, double* y, double* z, double dim, int theta, int phi)
{
   *x = -2 * dim * Sin(theta) * Cos(phi);
   *z = 2 * dim * Cos(theta) * Cos(phi);
}

void TurnLeft(double* x, double* y, double* z, double dim, int* theta, int phi)
{
   *theta -= 5;
   *theta %= 360;
   *x = -2 * dim * Sin(*theta) * Cos(phi);
   *z = 2 * dim * Cos(*theta) * Cos(phi);
}

void TurnRight(double* x, double* y, double* z, double dim, int* theta, int phi)
{
   *theta += 5;
   *theta %= 360;
   *x = -2 * dim * Sin(*theta) * Cos(phi);
   *z = 2 * dim * Cos(*theta) * Cos(phi);
}