/*
 *  Definitions for helper functions to draw 3D objects
 *  for CSCI-4229 Homework 5: Lighting.
 *  Created by Jeff Colgan. 
 */
#include "shapes.h"

// Constants for lighting and computing vertices and normals.
const int shiny = 0;
const float emission = 0;
const float black[] = {0.0, 0.0, 0.0, 1.0};
const float white[] = {1.0, 1.0, 1.0, 1.0};
const float orange[] = {1.0, 0.5, 0.0, 1.0};
const float grey[] = {0.729, 0.690, 0.686, 1.0};
const float yellow[] = {1.0, 1.0, 0.0, 1.0};
const float red[] = {1.0, 0.0, 0.1, 1.0};


/* 
 *  Draw triangles for computing vertex normals of a 3D object
 *  composed of triangles.
 *  The code for this function is borrowed from ex13.c of the 
 *  in-class examples.
 */ 
void DrawTriangle(vtx A, vtx B, vtx C)
{
   // Compute A - B.
   float dx0 = A.x - B.x;
   float dy0 = A.y - B.y;
   float dz0 = A.z - B.z;

   // Compute C - A.
   float dx1 = C.x - A.x;
   float dy1 = C.y - A.y;
   float dz1 = C.z - A.z;

   // Compute Normal.
   float Nx = dy0 * dz1 - dy1 * dz0;
   float Ny = dz0 * dx1 - dz1 * dx0;
   float Nz = dx0 * dy1 - dx1 * dy0;

   // Draw the triangle.
   glNormal3f(Nx, Ny, Nz);
   glBegin(GL_TRIANGLES);
   glVertex3f(A.x, A.y, A.z);
   glVertex3f(B.x, B.y, B.z);
   glVertex3f(C.x, C.y, C.z);
   glEnd();
}

/*
 *  Compute vertex normals for QUAD_STRIPS. 
 *  This function is heavily based off of the draw triangle function
 *  above, and is largely borrowed from ex13.c of the in-class examples.
 */
void DrawQuad(vtx A, vtx B, vtx C)
{
   // Compute A - B.
   float dx0 = A.x - B.x;
   float dy0 = A.y - B.y;
   float dz0 = A.z - B.z;

   // Compute C - A.
   float dx1 = C.x - A.x;
   float dy1 = C.y - A.y;
   float dz1 = C.z - A.z;

   // Normalize.
   float Nx = dy0 * dz1 - dy1 * dz0;
   float Ny = dz0 * dx1 - dz1 * dx0;
   float Nz = dx0 * dy1 - dx1 * dy0;

   // Draw three vertices.
   glNormal3f(Nx, Ny, Nz);
   glVertex3f(A.x, A.y, A.z);
   glVertex3f(B.x, B.y, B.z);
   glVertex3f(C.x, C.y, C.z);
}

// Specify the order of vertices to compute normals for a cone object.
const tri cone[] =
{
   {1, 0, 2}, {2, 0, 3}, {3, 0, 4}, {4, 0, 5}, {5, 0, 6},
   {6, 0, 7}, {7, 0, 8}, {8, 0, 9}, {9, 0, 10}, {10, 0, 11},
   {11, 0, 12}, {12, 0, 1}
};

// Specify order of vertices to compute normals for a cyllender.
const tri cyllender[] =
{
   {2, 1, 0}, {1, 2, 3}, {4, 3, 2}, {3, 4, 5},
   {6, 5, 4}, {5, 6, 7}, {8, 7, 6}, {7, 8, 9},
   {10, 9, 8}, {9, 10, 11}, {12, 11, 10}, {11, 12, 13},
   {14, 13, 12}, {13, 14, 15}, {16, 15, 14}, {15, 16, 17},
   {18, 17, 16}, {17, 18, 19}, {20, 19, 18}, {19, 20, 21},
   {22, 21, 20}, {21, 22, 23}, {0, 23, 22}, {23, 0, 1}
};

// List of vertices for the inner wall of the left wheel.
const vtx lInnerVert[] =
{
   {0.0, 0.0, 0.25}, {0.05, 0.0, 0.25}, {0.05 * Cos(30), 0.05 * Sin(30), 0.25},
   {0.05 * Cos(60), 0.05 * Sin(60), 0.25}, {0.0, 0.05, 0.25},
   {0.05 * Cos(120), 0.05 * Sin(120), 0.25}, {0.05 * Cos(150), 0.05 * Sin(150), 0.25},
   {-0.05, 0.0, 0.25}, {0.05 * Cos(210), 0.05 * Sin(210), 0.25},
   {0.05 * Cos(240), 0.05 * Sin(240), 0.25}, {0.0, -0.05, 0.25},
   {0.05 * Cos(300), 0.05 * Sin(300), 0.25}, {0.05 * Cos(330), 0.05 * Sin(330), 0.25}
};

// List of vertices for the outer wall of the left wheel.
const vtx lOuterVert[] = 
{
   {0.0, 0.0, 0.2}, {0.05, 0.0, 0.2}, {0.05 * Cos(30), 0.05 * Sin(30), 0.2},
   {0.05 * Cos(60), 0.05 * Sin(60), 0.2}, {0.0, 0.05, 0.2},
   {0.05 * Cos(120), 0.05 * Sin(120), 0.2}, {0.05 * Cos(150), 0.05 * Sin(150), 0.2},
   {-0.05, 0.0, 0.2}, {0.05 * Cos(210), 0.05 * Sin(210), 0.2},
   {0.05 * Cos(240), 0.05 * Sin(240), 0.2}, {0.0, -0.05, 0.2},
   {0.05 * Cos(300), 0.05 * Sin(300), 0.2}, {0.05 * Cos(330), 0.05 * Sin(330), 0.2}
};

// List of vertices for the inner wall of the right wheel.
const vtx rInnerVert[] = 
{
   {0.0, 0.0, 0.4}, {0.05, 0.0, 0.4}, {0.05 * Cos(30), 0.05 * Sin(30), 0.4},
   {0.05 * Cos(60), 0.05 * Sin(60), 0.4}, {0.0, 0.05, 0.4},
   {0.05 * Cos(120), 0.05 * Sin(120), 0.4}, {0.05 * Cos(150), 0.05 * Sin(150), 0.4},
   {-0.05, 0.0, 0.4}, {0.05 * Cos(210), 0.05 * Sin(210), 0.4},
   {0.05 * Cos(240), 0.05 * Sin(240), 0.4}, {0.0, -0.05, 0.4},
   {0.05 * Cos(300), 0.05 * Sin(300), 0.4}, {0.05 * Cos(330), 0.05 * Sin(330), 0.4}
};

// List of vertices for the outer wall of the right wheel.
const vtx rOuterVert[] = 
{
   {0.0, 0.0, 0.45}, {0.05, 0.0, 0.45}, {0.05 * Cos(30), 0.05 * Sin(30), 0.45},
   {0.05 * Cos(60), 0.05 * Sin(60), 0.45}, {0.0, 0.05, 0.45},
   {0.05 * Cos(120), 0.05 * Sin(120), 0.45}, {0.05 * Cos(150), 0.05 * Sin(150), 0.45},
   {-0.05, 0.0, 0.45}, {0.05 * Cos(210), 0.05 * Sin(210), 0.45},
   {0.05 * Cos(240), 0.05 * Sin(240), 0.45}, {0.0, -0.05, 0.45},
   {0.05 * Cos(300), 0.05 * Sin(300), 0.45}, {0.05 * Cos(330), 0.05 * Sin(330), 0.45}
};

// List of vertices for the tread of the left wheel.
const vtx leftTread[] =
{
   {0.05, 0.0, 0.2}, {0.05, 0.0, 0.25}, {0.05 * Cos(30), 0.05 * Sin(30), 0.2},
   {0.05 * Cos(30), 0.05 * Sin(30), 0.25}, {0.05 * Cos(60), 0.05 * Sin(60), 0.2},
   {0.05 * Cos(60), 0.05 * Sin(60), 0.25}, {0.0, 0.05, 0.2}, {0.0, 0.05, 0.25},
   {0.05 * Cos(120), 0.05 * Sin(120), 0.2}, {0.05 * Cos(120), 0.05 * Sin(120), 0.25},
   {0.05 * Cos(150), 0.05 * Sin(150), 0.2}, {0.05 * Cos(150), 0.05 * Sin(150), 0.25},
   {-0.05, 0.0, 0.2}, {-0.05, 0.0, 0.25}, {0.05 * Cos(210), 0.05 * Sin(210), 0.2},
   {0.05 * Cos(210), 0.05 * Sin(210), 0.25}, {0.05 * Cos(240), 0.05 * Sin(240), 0.2},
   {0.05 * Cos(240), 0.05 * Sin(240), 0.25}, {0.0, -0.05, 0.2}, {0.0, -0.05, 0.25},
   {0.05 * Cos(300), 0.05 * Sin(300), 0.2}, {0.05 * Cos(300), 0.05 * Sin(300), 0.25},
   {0.05 * Cos(330), 0.05 * Sin(330), 0.2}, {0.05 * Cos(330), 0.05 * Sin(330), 0.25}
};

// List of vertices for the tread of the right wheel.
const vtx rightTread[] =
{
   {0.05, 0.0, 0.45}, {0.05, 0.0, 0.4}, {0.05 * Cos(30), 0.05 * Sin(30), 0.45},
   {0.05 * Cos(30), 0.05 * Sin(30), 0.4}, {0.05 * Cos(60), 0.05 * Sin(60), 0.45},
   {0.05 * Cos(60), 0.05 * Sin(60), 0.4}, {0.0, 0.05, 0.45}, {0.0, 0.05, 0.4},
   {0.05 * Cos(120), 0.05 * Sin(120), 0.45}, {0.05 * Cos(120), 0.05 * Sin(120), 0.4},
   {0.05 * Cos(150), 0.05 * Sin(150), 0.45}, {0.05 * Cos(150), 0.05 * Sin(150), 0.4},
   {-0.05, 0.0, 0.45}, {-0.05, 0.0, 0.4}, {0.05 * Cos(210), 0.05 * Sin(210), 0.45},
   {0.05 * Cos(210), 0.05 * Sin(210), 0.4}, {0.05 * Cos(240), 0.05 * Sin(240), 0.45},
   {0.05 * Cos(240), 0.05 * Sin(240), 0.4}, {0.0, -0.05, 0.45}, {0.0, -0.05, 0.4},
   {0.05 * Cos(300), 0.05 * Sin(300), 0.45}, {0.05 * Cos(300), 0.05 * Sin(300), 0.4},
   {0.05 * Cos(330), 0.05 * Sin(330), 0.45}, {0.05 * Cos(330), 0.05 * Sin(330), 0.4}
};

// List of vertices for the tread of the left wheel.
const vtx axelBar[] =
{
   {0.01, 0.0, 0.25}, {0.01, 0.0, 0.4}, {0.01 * Cos(30), 0.01 * Sin(30), 0.25},
   {0.01 * Cos(30), 0.01 * Sin(30), 0.4}, {0.01 * Cos(60), 0.01 * Sin(60), 0.25},
   {0.01 * Cos(60), 0.01 * Sin(60), 0.4}, {0.0, 0.01, 0.25}, {0.0, 0.01, 0.4},
   {0.01 * Cos(120), 0.01 * Sin(120), 0.25}, {0.01 * Cos(120), 0.01 * Sin(120), 0.4},
   {0.01 * Cos(150), 0.01 * Sin(150), 0.25}, {0.01 * Cos(150), 0.01 * Sin(150), 0.4},
   {-0.01, 0.0, 0.25}, {-0.01, 0.0, 0.4}, {0.01 * Cos(210), 0.01 * Sin(210), 0.25},
   {0.01 * Cos(210), 0.01 * Sin(210), 0.4}, {0.01 * Cos(240), 0.01 * Sin(240), 0.25},
   {0.01 * Cos(240), 0.01 * Sin(240), 0.4}, {0.0, -0.01, 0.25}, {0.0, -0.01, 0.4},
   {0.01 * Cos(300), 0.01 * Sin(300), 0.25}, {0.01 * Cos(300), 0.01 * Sin(300), 0.4},
   {0.01 * Cos(330), 0.01 * Sin(330), 0.25}, {0.01 * Cos(330), 0.01 * Sin(330), 0.4}
};

// Specify the vertices for drawing the nose cone of the Rocket.
const vtx noseCone[] =
{
   {0.50, 0.0, 0.0}, {0.20, 0.05, 0.0},
   {0.20, 0.05 * Cos(30), 0.05 * Sin(30)}, {0.20, 0.05 * Cos(60), 0.05 * Sin(60)},
   {0.20, 0.0, 0.05}, {0.20, 0.05 * Cos(120), 0.05 * Sin(120)},
   {0.20, 0.05 * Cos(150), 0.05 * Sin(150)}, {0.20, -0.05, 0.0},
   {0.20, 0.05 * Cos(210), 0.05 * Sin(210)}, {0.20, 0.05 * Cos(240), 0.05 * Sin(240)},
   {0.20, 0.0, -0.05}, {0.20, 0.05 * Cos(300), 0.05 * Sin(300)},
   {0.20, 0.05 * Cos(330), 0.05 * Sin(330)}
};

// Vertices for the fuselage.
const vtx fuselageVert[] =
{
   {0.20, 0.05, 0.0}, {-0.50, 0.05, 0.0}, {0.20, 0.05 * Cos(30), 0.05 * Sin(30)},
   {-0.50, 0.05 * Cos(30), 0.05 * Sin(30)}, {0.20, 0.05 * Cos(60), 0.05 * Sin(60)},
   {-0.50, 0.05 * Cos(60), 0.05 * Sin(60)}, {0.20, 0.0, 0.05}, {-0.50, 0.0, 0.05},
   {0.20, 0.05 * Cos(120), 0.05 * Sin(120)}, {-0.50, 0.05 * Cos(120), 0.05 * Sin(120)},
   {0.20, 0.05 * Cos(150), 0.05 * Sin(150)}, {-0.50, 0.05 * Cos(150), 0.05 * Sin(150)},
   {0.20, -0.05, 0.0}, {-0.50, -0.05, 0.0}, {0.20, 0.05 * Cos(210), 0.05 * Sin(210)},
   {-0.50, 0.05 * Cos(210), 0.05 * Sin(210)}, {0.20, 0.05 * Cos(240), 0.05 * Sin(240)},
   {-0.50, 0.05 * Cos(240), 0.05 * Sin(240)}, {0.20, 0.0, -0.05}, {-0.50, 0.0, -0.05},
   {0.20, 0.05 * Cos(300), 0.05 * Sin(300)}, {-0.50, 0.05 * Cos(300), 0.05 * Sin(300)},
   {0.20, 0.05 * Cos(330), 0.05 * Sin(330)}, {-0.50, 0.05 * Cos(330), 0.05 * Sin(330)}
};

// Order to compute normals for the top triangles of the tail fins.
const tri finTop[] =
{
   {1, 0, 2}, {4, 3, 5}, {7, 6, 8}, {10, 9, 11}
};

// Vertices for the top triangles of the tail fins.
const vtx finTopVert[] =
{
   {-0.1, 0.025, 0.025}, {-0.3, 0.025, 0.025}, {-0.3, 0.025 + 0.1, 0.025 + 0.1},
   {-0.1, -0.025, -0.025}, {-0.3, -0.025, -0.025}, {-0.3, -0.025 - 0.1, -0.025 - 0.1},
   {-0.1, -0.025, 0.025}, {-0.3, -0.025, 0.025}, {-0.3, -0.025 - 0.1, 0.025 + 0.1},
   {-0.1, 0.025, -0.025}, {-0.3, 0.025, -0.025}, {-0.3, 0.025 + 0.1, -0.025 - 0.1}
};

// Order to compute normals for the rectangle components of the tail fins.
const tri finBase[] =
{
   {0, 1, 2}, {3, 2, 1}, {6, 5, 4}, {5, 6, 7}, {10, 9, 8}, {9, 10, 11},
   {14, 13, 12}, {13, 14, 15}
};

// Vertices for the rectangle components of the tail fins.
const vtx finBaseVert[] =
{
   {-0.50, 0.025, 0.025}, {-0.50, 0.025 + 0.1, 0.025 + 0.1},
   {-0.3, 0.025, 0.025}, {-0.3, 0.025 + 0.1, 0.025 + 0.1},
   {-0.50, -0.025, -0.025}, {-0.50, -0.025 - 0.1, -0.025 - 0.1},
   {-0.3, -0.025, -0.025}, {-0.3, -0.025 - 0.1, -0.025 - 0.1},
   {-0.50, -0.025, 0.025}, {-0.50, -0.025 - 0.1, 0.025 + 0.1},
   {-0.3, -0.025, 0.025}, {-0.3, -0.025 - 0.1, 0.025 + 0.1},
   {-0.50, 0.025, -0.025}, {-0.50, 0.025 + 0.1, -0.025 - 0.1},
   {-0.3, 0.025, -0.025}, {-0.3, 0.025 + 0.1, -0.025 - 0.1}
};

// Specify the vertices for drawing the nose cone of the Rocket.
const vtx thrusterCone[] =
{
   {-0.7, 0.0, 0.0}, {-0.50, 0.05, 0.0},
   {-0.50, 0.05 * Cos(30), 0.05 * Sin(30)}, {-0.50, 0.05 * Cos(60), 0.05 * Sin(60)},
   {-0.50, 0.0, 0.05}, {-0.50, 0.05 * Cos(120), 0.05 * Sin(120)},
   {-0.50, 0.05 * Cos(150), 0.05 * Sin(150)}, {-0.50, -0.05, 0.0},
   {-0.50, 0.05 * Cos(210), 0.05 * Sin(210)}, {-0.50, 0.05 * Cos(240), 0.05 * Sin(240)},
   {-0.50, 0.0, -0.05}, {-0.50, 0.05 * Cos(300), 0.05 * Sin(300)},
   {-0.50, 0.05 * Cos(330), 0.05 * Sin(330)}
};

// Order of vertices to compute normals for cuboid.
const tri cuboid[] =
{
   {2, 1, 0}, {6, 1, 2}, {7, 4, 5}, {3, 5, 7},
   {1, 6, 7}, {6, 5, 1}, {4, 2, 3}, {0, 3, 4},
   {3, 0, 1}, {1, 5, 3}, {4, 7, 2}, {6, 2, 4}
};

// Vertices for cuboid object.
const vtx cuboidVert[] =
{
   {1, 1, 1}, {-1, 1, 1}, {1, -1, 1}, {1, 1, -1},
   {1, -1, -1}, {-1, 1, -1}, {-1, -1, 1}, {-1, -1, -1}
};

/*
 *  Draw the wheel axel and attached wheels.  
 */
void WheelAxel(double x, double y, double z, double dx, double dy,
               double dz, double theta)
{

   // Apply color, emission, ambient, diffuse, specular and shininess lighing qualities.
   glColor4fv(grey);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, grey);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

   glPushMatrix();

   // Apply tranformations.
   glTranslated(x, y, z);
   glRotated(theta, 0, 0, 1);
   glScaled(dx, dy, dz);

   // Compute normals and draw the inner and outer wheel walls.
   for (int i = 0; i < 12; i++)
      DrawTriangle(lInnerVert[cone[i].A], lInnerVert[cone[i].B], lInnerVert[cone[i].C]);

   for (int i = 0; i < 12; i++)
      DrawTriangle(lOuterVert[cone[i].C], lOuterVert[cone[i].B], lOuterVert[cone[i].A]);

   for (int i = 0; i < 12; i++)
      DrawTriangle(rInnerVert[cone[i].C], rInnerVert[cone[i].B], rInnerVert[cone[i].A]);

   for (int  i = 0; i < 12; i++)
      DrawTriangle(rOuterVert[cone[i].A], rOuterVert[cone[i].B], rOuterVert[cone[i].C]);

   // Draw the left wheel tread.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i < 24; i++)
   {
      DrawQuad(leftTread[cyllender[i].C], leftTread[cyllender[i].B], leftTread[cyllender[i].A]);
   }
   glEnd();

   // Draw the right wheel tread.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i < 24; i++)
   {
      DrawQuad(rightTread[cyllender[i].A], rightTread[cyllender[i].B], rightTread[cyllender[i].C]);
   }
   glEnd();

   // Draw the axel between the wheels.
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i < 24; i++)
   {
      DrawQuad(axelBar[cyllender[i].C], axelBar[cyllender[i].B], axelBar[cyllender[i].A]);
   }
   glEnd();

   glPopMatrix();
}

/*
 *  Draw a Rover object.  For now, it is a simble cuboid
 *  with attached wheels and wheel axels.  I plan on
 *  further iteration to make a more complex object,
 *  perhaps for the final project. 
 */
void Rover(double x, double y, double z, double dx,
           double dy, double dz, double theta)
{
   glPushMatrix();

   // Apply transformations.
   glTranslated(x, y, z);
   glRotated(theta, 0, 1, 0);
   glScaled(dx, dy, dz);

   Box(0.0, 0.0, 0.0, 1.25, 1.0, 1.0, 0);

   // Draw front and back wheel axels in grey.
   glColor3f(0.729, 0.690, 0.686);
   WheelAxel(-0.8, -1.1, -4.25, 5.0, 10.0, 13.0, 0);
   WheelAxel(0.8, -1.1, -4.25, 5.0, 10.0, 13.0, 0);
   glPopMatrix();
}

/*
 *  Draw a rocket object. 
 */
void Rocket(double x, double y, double z, double dx, double dy,
            double dz, double theta, double gamma, double omega)
{
   // Locals for computing vertices.
   double circumference = 0.05;
   double radius = circumference * 0.5;
   double fuselageBase = -0.50;
   double finTip = -0.1;
   double finEdge = -0.3;

   // Apply color, emission, ambient, diffuse, specular and shininess lighting qualities.
   glColor4fv(orange);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, orange);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

   glPushMatrix();

   // Apply transformations.
   glTranslated(x, y, z);
   glScaled(dx, dy, dz);
   glRotated(theta, 0, 0, 1);
   glRotated(gamma, 1, 0, 0);
   glRotated(omega, 0, 1, 0);

   // Compute vertex normals and draw the nose cone.
   for (int i = 0; i < 12; i++)
      DrawTriangle(noseCone[cone[i].A], noseCone[cone[i].B], noseCone[cone[i].C]);

   // Draw the fuselage.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i < 24; i++)
      DrawQuad(fuselageVert[cyllender[i].A], fuselageVert[cyllender[i].B], fuselageVert[cyllender[i].C]);
   glEnd();

   glColor4fv(red);

   // Draw the tops of the tail fins.
   for (int i = 0; i < 4; i++)
   {
      // This bit of code is from my research into culling faces (khronos documentation, see README).
      glEnable(GL_CULL_FACE);
      glCullFace(GL_FRONT);
      DrawTriangle(finTopVert[finTop[i].A], finTopVert[finTop[i].B], finTopVert[finTop[i].C]);
      glDisable(GL_CULL_FACE);
      DrawTriangle(finTopVert[finTop[i].C], finTopVert[finTop[i].B], finTopVert[finTop[i].A]);
   }

   // Draw the bottom rectangles of the tail fins.
   for (int i = 0; i < 7; i += 2)
   {
      // This bit of code is from my research into culling faces (khronos documentation, see README).
      glEnable(GL_CULL_FACE);
      glCullFace(GL_FRONT);
      DrawTriangle(finBaseVert[finBase[i].A], finBaseVert[finBase[i].B], finBaseVert[finBase[i].C]);
      DrawTriangle(finBaseVert[finBase[i+1].A], finBaseVert[finBase[i+1].B], finBaseVert[finBase[i+1].C]);

      glDisable(GL_CULL_FACE);
      DrawTriangle(finBaseVert[finBase[i].C], finBaseVert[finBase[i].B], finBaseVert[finBase[i].A]);
      DrawTriangle(finBaseVert[finBase[i+1].C], finBaseVert[finBase[i+1].B], finBaseVert[finBase[i+1].A]);
   }
   

   // Draw lines so tail fins are visible from sides/front/back.
   glBegin(GL_LINES);
   glVertex3f(finTip, radius, radius);
   glVertex3f(finEdge, radius + 0.1, radius + 0.1);
   glVertex3f(fuselageBase, radius, radius);
   glVertex3f(fuselageBase, radius + 0.1, radius + 0.1);
   glVertex3f(finEdge, radius + 0.1, radius + 0.1);
   glVertex3f(fuselageBase, radius + 0.1, radius + 0.1);
   glEnd();

   glBegin(GL_LINES);
   glVertex3f(finTip, -radius, -radius);
   glVertex3f(finEdge, -radius - 0.1, -radius - 0.1);
   glVertex3f(fuselageBase, -radius, -radius);
   glVertex3f(fuselageBase, -radius - 0.1, -radius - 0.1);
   glVertex3f(finEdge, -radius - 0.1, -radius - 0.1);
   glVertex3f(fuselageBase, -radius - 0.1, -radius - 0.1);
   glEnd();

   glBegin(GL_LINES);
   glVertex3f(finTip, -radius, radius);
   glVertex3f(finEdge, -radius - 0.1, radius + 0.1);
   glVertex3f(fuselageBase, -radius, radius);
   glVertex3f(fuselageBase, -radius - 0.1, radius + 0.1);
   glVertex3f(finEdge, -radius - 0.1, radius + 0.1);
   glVertex3f(fuselageBase, -radius - 0.1, radius + 0.1);
   glEnd();

   glBegin(GL_LINES);
   glVertex3f(finTip, radius, -radius);
   glVertex3f(finEdge, radius + 0.1, -radius - 0.1);
   glVertex3f(fuselageBase, radius, -radius);
   glVertex3f(fuselageBase, radius + 0.1, -radius - 0.1);
   glVertex3f(finEdge, radius + 0.1, -radius - 0.1);
   glVertex3f(fuselageBase, radius + 0.1, -radius - 0.1);
   glEnd();

   // Set material settings approprate for the tail thruster flame jet.
   glColor4fv(yellow);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, yellow);
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, yellow);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, yellow);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

   // Thruster jet.
   for (int i = 0; i < 12; i++)
      DrawTriangle(thrusterCone[cone[i].A], thrusterCone[cone[i].B], thrusterCone[cone[i].C]);
      
   glPopMatrix();
}

/*
 *  Draw a cuboid object for use as a floor (and walls when
 *  we introduce textures). 
 */
void Box(double x, double y, double z, double dx, double dy,
         double dz, double theta)
{
   // Apply shininess, specular and emission qualities for a box object.
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

   glPushMatrix();

   // Apply transformations.
   glTranslated(x, y, z);
   glRotated(theta, 0, 1, 0);
   glScaled(dx, dy, dz);

   // Draw the faces of the box.
   for (int i = 0; i < 12; i++)
   {
      if (i % 2 == 0)
         glBegin(GL_QUAD_STRIP);

      DrawQuad(cuboidVert[cuboid[i].A], cuboidVert[cuboid[i].B], cuboidVert[cuboid[i].C]);

      if (i % 2 == 1)
         glEnd();
   }

   glPopMatrix();
}