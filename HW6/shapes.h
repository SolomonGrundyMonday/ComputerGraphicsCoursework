/*
 *  Function declarations and struct definitions for
 *  3D object drawing for CSCI-4229 Homework 6: Textures and Lighting.
 *  Created by Jeff Colgan.  
 */
#include "CSCIx229.h"

// Define structs for (x, y, z) coordinates of vertices and triangles
// consisting of three vertices.  Code borrowed from ex13.c.
#ifndef TRIANGLE_STRUCTS
#define TRIANGLE_STRUCTS

typedef struct {float x, y, z;} vtx;
typedef struct {int A, B, C;} tri;

#endif

// Function declaration for LoadTextures function.
void LoadTextures();

// Function declaration for DrawTriangle function.
void DrawTriangle(vtx A, vtx B, vtx C);

// Function declaration for DrawQuad function.
void DrawQuad(vtx A, vtx B, vtx C);

// Function declaration for WheelAxel function.
void WheelAxel(double x, double y, double z, double dx, double dy, 
               double dz, double theta);

// Function declaration for Rover function.
void Rover(double x, double y, double z, double dx, double dy,
           double dz, double theta);

// Function declaration for Rocket function.
void Rocket(double x, double y, double z, double dx, double dy,
            double dz, double theta, double gamma, double omega);

// Function declaration for Box function.
void Box(double x, double y, double z, double dx, double dy,
         double dz, double theta);