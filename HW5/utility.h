/*
 *  Utility functions and include directives for CSCI-4229
 *  Homework 4.
 *  Created by Jeff Colgan. 
 */

#define GL_GLEXT_PROTOTYPES

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#ifdef USEGLEW
#include <GL/glew.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef RES
#define RES 1
#endif

// Convert math.h sin/cos to output in degrees rather than radians.
#define Cos(x) (cos((x)*3.1415927/180))
#define Sin(x) (sin((x)*3.1415927/180))

void Print(const char* format, ...);
void Fatal(const char* format, ...);
void ErrCheck(const char* where);
void MoveForward(double* x, double* z, int theta);
void MoveBackward(double* x, double* z, int theta);
void Turn(double* x, double* z, double dim, int theta);
void ResetPosition(double* Ex, double* Ey, double* Ez, double* Cx, double* Cy,
                   double* Cz, double* dim, int* theta, int* phi);