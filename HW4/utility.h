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
void Projection(double fov, double asp, double dim);
void ErrCheck(const char* where);
void MoveForward(double* x, double* y, double* z, double dim, int theta, int phi);
void MoveBackward(double* x, double* y, double* z, double dim, int theta, int phi);
void TurnLeft(double* x, double* y, double* z, double dim, int* theta, int phi);
void TurnRight(double* x, double* y, double* z, double dim, int* theta, int phi);