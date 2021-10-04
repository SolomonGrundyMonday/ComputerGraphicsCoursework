#include "CSCIx229.h"

#ifndef TRIANGLE_STRUCTS
#define TRIANGLE_STRUCTS

typedef struct {float x, y, z;} vtx;
typedef struct {int A, B, C;} tri;

#endif

void DrawTriangle(vtx A, vtx B, vtx C);
void WheelAxel(double x, double y, double z, double dx, double dy, 
                      double dz, double theta);
void Rover(double x, double y, double z, double dx, double dy,
                  double dz, double theta);
void Rocket(double x, double y, double z, double dx, double dy,
                   double dz, double theta);
void Box(double x, double y, double z, double dx, double dy,
                double dz, double theta);
void Ball(double x, double y, double z, double r);
void Vertex(double theta, double phi);