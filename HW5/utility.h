/*
 *  Utility functions and include directives for CSCI-4229
 *  Homework 4.
 *  Created by Jeff Colgan. 
 */

#include "CSCIx229.h"

void MoveForward(double* x, double* z, int theta);
void MoveBackward(double* x, double* z, int theta);
void Turn(double* x, double* z, double dim, int theta);
void ResetPosition(double* Ex, double* Ey, double* Ez, double* Cx, double* Cy,
                   double* Cz, double* dim, int* theta, int* phi);
//void Vertex(double theta, double phi);