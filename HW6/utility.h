/*
 *  Utility function declarations. 
 *  CSCI-4229 Homework 6 : Textures and Lighting.
 *  Created by Jeff Colgan, 10/10/2021. 
 */

#include "CSCIx229.h"

// Function declaration for MoveForward function.
void MoveForward(double* x, double* z, int theta);

// Function declaration for MoveBackward function.
void MoveBackward(double* x, double* z, int theta);

// Function declaration for Turn function.
void Turn(double* x, double* z, double dim, int theta);

// Function declaration for ResetPosition function.
void ResetPosition(double* Ex, double* Ey, double* Ez, double* Cx, double* Cy,
                   double* Cz, double* dim, int* theta, int* phi);