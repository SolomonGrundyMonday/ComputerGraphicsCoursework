#include "shapes.h"

// Constants for lighting.
const int shiny = 0;
const float emission = 0;
const float black[] = {0.0, 0.0, 0.0, 1.0};
const float white[] = {1.0, 1.0, 1.0, 1.0};
const float orange[] = {1.0, 0.5, 0.0, 1.0};
const double noseHeight =  0.20;
const double circ = 0.05;
const double base = -0.50;
const double finTip = -0.1;
const double finEdge = -0.3;
const double radius = 0.025;
const double fuselageBase = -0.50;

/* 
 *  Draw triangles for computing vertex normals of a 3D object
 *  composed of triangles.
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
 */
void DrawQuad(vtx A, vtx B, vtx C)
{
   
   float dx0 = A.x - B.x;
   float dy0 = A.y - B.y;
   float dz0 = A.z - B.z;

   float dx1 = C.x - A.x;
   float dy1 = C.y - A.y;
   float dz1 = C.z - A.z;

   float Nx = dy0 * dz1 - dy1 * dz0;
   float Ny = dz0 * dx1 - dz1 * dx0;
   float Nz = dx0 * dy1 - dx1 * dy0;

   glNormal3f(Nx, Ny, Nz);
   glVertex3f(A.x, A.y, A.z);
   glVertex3f(B.x, B.y, B.z);
   glVertex3f(C.x, C.y, C.z);
}

/*
 *  Draw the wheel axel and attached wheels.  
 */
void WheelAxel(double x, double y, double z, double dx, double dy,
               double dz, double theta)
{
   // Locals for vertices.
   double circumference = 0.05;
   double axel = circumference * 0.2;
   double lInnerWall = 0.2;
   double lOuterWall = 0.25;
   double rInnerWall = 0.45;
   double rOuterWall = 0.4;

   glPushMatrix();

   // Apply tranformations.
   glTranslated(x, y, z);
   glRotated(theta, 0, 0, 1);
   glScaled(dx, dy, dz);

   // Draw the left wheel tread.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 360; i += 30)
   {
      glVertex3f(circumference * Cos(i), circumference * Sin(i), lInnerWall);
      glVertex3f(circumference * Cos(i), circumference * Sin(i), lOuterWall);
   }
   glEnd();

   // Draw the inside of the left wheel wall.
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0, 0, 0.2);
   for (int i = 0; i <= 360; i += 30)
      glVertex3f(circumference * Cos(i), circumference * Sin(i), lInnerWall);
   glEnd();

   // Draw the outside of the left wheel wall.
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0, 0, 0.25);
   for (int i = 0; i <= 360; i += 30)
      glVertex3f(circumference * Cos(i), circumference * Sin(i), lOuterWall);
   glEnd();

   // Draw the right wheel tread.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 360; i += 30)
   {
      glVertex3f(circumference * Cos(i), circumference * Sin(i), rOuterWall);
      glVertex3f(circumference * Cos(i), circumference * Sin(i), rInnerWall);
   }
   glEnd();

   // Draw the right inside wheel wall.
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0, 0, 0.4);
   for (int i = 0; i <= 360; i += 30)
      glVertex3f(circumference * Cos(i), circumference * Sin(i), rOuterWall);
   glEnd();

   // Draw the right outside wheel wall.
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0, 0, 0.45);
   for (int i = 0; i <= 360; i += 30)
      glVertex3f(circumference * Cos(i), circumference * Sin(i), rInnerWall);
   glEnd();

   // Draw the axel between the wheels.
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 360; i += 30)
   {
      glVertex3f(axel * Cos(i), axel * Sin(i), lInnerWall);
      glVertex3f(axel * Cos(i), axel * Sin(i), rInnerWall);
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

   glBegin(GL_QUADS);

   // Front face.
   glVertex3f(-1, -1, 1);
   glVertex3f(1, -1, 1);
   glVertex3f(1, 1, 1);
   glVertex3f(-1, 1, 1);

   // Back face.
   glVertex3f(1, -1, -1);
   glVertex3f(-1, -1, -1);
   glVertex3f(-1, 1, -1);
   glVertex3f(1, 1, -1);

   // Middle side face.
   glVertex3f(-1, -1, -1);
   glVertex3f(-1, -1, 1);
   glVertex3f(-1, 1, 1);
   glVertex3f(-1, 1, -1);

   // Middle side face.
   glVertex3f(1, -1, 1);
   glVertex3f(1, -1, -1);
   glVertex3f(1, 1, -1);
   glVertex3f(1, 1, 1);

   // Top face.
   glVertex3f(-1, 1, 1);
   glVertex3f(1, 1, 1);
   glVertex3f(1, 1, -1);
   glVertex3f(-1, 1, -1);

   // Bottom face.
   glVertex3f(-1, -1, -1);
   glVertex3f(1, -1, -1);
   glVertex3f(1, -1, 1);
   glVertex3f(-1, -1, 1);
   glEnd();

   // Draw front and back wheel axels in grey.
   glColor3f(0.729, 0.690, 0.686);
   WheelAxel(-0.8, -1.1, -4.25, 5.0, 10.0, 13.0, 0);
   WheelAxel(0.8, -1.1, -4.25, 5.0, 10.0, 13.0, 0);
   glPopMatrix();
}

// Specify the triangles that compose a cone object.
const tri nose[] =
{
   {1, 0, 2}, {2, 0, 3}, {3, 0, 4}, {4, 0, 5}, {5, 0, 6},
   {6, 0, 7}, {7, 0, 8}, {8, 0, 9}, {9, 0, 10}, {10, 0, 11},
   {11, 0, 12}, {12, 0, 1}
};

// Specify the vertices for drawing the nose cone of the Rocket.
const vtx noseCone[] = 
{
   {0.50, 0.0, 0.0}, {noseHeight, circ, 0.0},
   {noseHeight, circ * Cos(30), circ * Sin(30)}, {noseHeight, circ * Cos(60), circ * Sin(60)}, 
   {noseHeight, 0.0, circ}, {noseHeight, circ * Cos(120), circ * Sin(120)}, 
   {noseHeight, circ * Cos(150), circ * Sin(150)}, {noseHeight, -circ, 0.0}, 
   {noseHeight, circ * Cos(210), circ * Sin(210)}, {noseHeight, circ * Cos(240), circ * Sin(240)}, 
   {noseHeight, 0.0, -circ}, {noseHeight, circ * Cos(300), circ * Sin(300)}, 
   {noseHeight, circ * Cos(330), circ * Sin(330)}
};

// Compute vertex normals in this order for the fuselage.
const tri fuselage[] = 
{
   {2, 1, 0}, {1, 2, 3}, {4, 3, 2}, {3, 4, 5},
   {6, 5, 4}, {5, 6, 7}, {8, 7, 6}, {7, 8, 9},
   {10, 9, 8}, {9, 10, 11}, {12, 11, 10}, {11, 12, 13},
   {14, 13, 12}, {13, 14, 15}, {16, 15, 14}, {15, 16, 17},
   {18, 17, 16}, {17, 18, 19}, {20, 19, 18}, {19, 20, 21},
   {22, 21, 20}, {21, 22, 23}, {0, 23, 22}, {23, 0, 1}
};

// Vertices for the fuselage.
const vtx fuselageVert[] = 
{
   {noseHeight, circ, 0.0}, {base, circ, 0.0}, {noseHeight, circ * Cos(30), circ * Sin(30)},
   {base, circ * Cos(30), circ * Sin(30)}, {noseHeight, circ * Cos(60), circ * Sin(60)},
   {base, circ * Cos(60), circ * Sin(60)}, {noseHeight, 0.0, circ}, {base, 0.0, circ},
   {noseHeight, circ * Cos(120), circ * Sin(120)}, {base, circ * Cos(120), circ * Sin(120)},
   {noseHeight, circ * Cos(150), circ * Sin(150)}, {base, circ * Cos(150), circ * Sin(150)},
   {noseHeight, -circ, 0.0}, {base, -circ, 0.0}, {noseHeight, circ * Cos(210), circ * Sin(210)},
   {base, circ * Cos(210), circ * Sin(210)}, {noseHeight, circ * Cos(240), circ * Sin(240)},
   {base, circ * Cos(240), circ * Sin(240)}, {noseHeight, 0.0, -circ}, {base, 0.0, -circ},
   {noseHeight, circ * Cos(300), circ * Sin(300)}, {base, circ * Cos(300), circ * Sin(300)},
   {noseHeight, circ * Cos(330), circ * Sin(330)}, {base, circ * Cos(330), circ * Sin(330)}
};

const tri finTop[] =
{
   {1, 0, 2}, {4, 3, 5}, {7, 6, 8}, {10, 9, 11}
};

const vtx finTopVert[] =
{
   {finTip, radius, radius}, {finEdge, radius, radius}, {finEdge, radius + 0.1, radius + 0.1},
   {finTip, -radius, -radius}, {finEdge, -radius, -radius}, {finEdge, -radius - 0.1, -radius - 0.1},
   {finTip, -radius, radius}, {finEdge, -radius, radius}, {finEdge, -radius - 0.1, radius + 0.1},
   {finTip, radius, -radius}, {finEdge, radius, -radius}, {finEdge, radius + 0.1, -radius - 0.1}
};

const tri finBase[] =
{
   {2, 1, 0}, {1, 2, 3}, {6, 5, 4}, {5, 6, 7}, {10, 9, 8}, {9, 10, 11},
   {14, 13, 12}, {13, 14, 15}
};

const vtx finBaseVert[] =
{
   {fuselageBase, radius, radius}, {fuselageBase, radius + 0.1, radius + 0.1},
   {finEdge, radius, radius}, {finEdge, radius + 0.1, radius + 0.1},
   {fuselageBase, -radius, -radius}, {fuselageBase, -radius - 0.1, -radius - 0.1},
   {finEdge, -radius, -radius}, {finEdge, -radius - 0.1, -radius - 0.1},
   {fuselageBase, -radius, radius}, {fuselageBase, -radius - 0.1, radius + 0.1},
   {finEdge, -radius, radius}, {finEdge, -radius - 0.1, radius + 0.1},
   {fuselageBase, radius, -radius}, {fuselageBase, radius + 0.1, -radius - 0.1},
   {finEdge, radius, -radius}, {finEdge, radius + 0.1, -radius - 0.1}
};

/*
 *  Draw a rocket object. 
 */
void Rocket(double x, double y, double z, double dx, double dy,
            double dz, double theta)
{
   // Locals for computing vertices.
   double circumference = 0.05;
   double radius = circumference * 0.5;
   double fuselageBase = -0.50;
   double finTip = -0.1;
   double finEdge = -0.3;

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

   // Compute vertex normals and draw the nose cone.
   for (int i = 0; i < 12; i++)
   {
      DrawTriangle(noseCone[nose[i].A], noseCone[nose[i].B], noseCone[nose[i].C]);
   }

   // Draw the fuselage.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i < 24; i++)
   {
      DrawQuad(fuselageVert[fuselage[i].A], fuselageVert[fuselage[i].B], fuselageVert[fuselage[i].C]);
   }
   glEnd();

   glColor3f(1.0, 0.0, 0.1);

   for (int i = 0; i < 4; i ++)
   {
      DrawTriangle(finTopVert[finTop[i].A], finTopVert[finTop[i].B], finTopVert[finTop[i].C]);
   }

   for (int i = 0; i < 8; i++)
   {
      if (i % 2 == 0)
         glBegin(GL_QUAD_STRIP);
      DrawQuad(finBaseVert[finBase[i].A], finBaseVert[finBase[i].B], finBaseVert[finBase[i].C]);
      if (i % 2 == 1)
         glEnd();
   }

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

   // Thruster jet.
   glBegin(GL_TRIANGLE_FAN);
   glColor3f(1.0, 1.0, 0.0);
   glVertex3f(-0.7, 0.0, 0.0);
   for (int i = 0; i <= 360; i += 30)
      glVertex3f(fuselageBase, circumference * Cos(i), circumference * Sin(i));
   glEnd();

   glPopMatrix();
}

/*
 *  Draw a cuboid object for use as a floor (and walls when
 *  we introduce textures). 
 */
void Box(double x, double y, double z, double dx, double dy,
         double dz, double theta)
{
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);

   glPushMatrix();

   // Apply transformations.
   glTranslated(x, y, z);
   glRotated(theta, 0, 1, 0);
   glScaled(dx, dy, dz);
   glColor3f(0.196, 0.514, 0.659);

   glBegin(GL_QUADS);

   // Front face.
   glVertex3f(-1, -1, 1);
   glVertex3f(1, -1, 1);
   glVertex3f(1, 1, 1);
   glVertex3f(-1, 1, 1);

   // Back face.
   glVertex3f(1, -1, -1);
   glVertex3f(-1, -1, -1);
   glVertex3f(-1, 1, -1);
   glVertex3f(1, 1, -1);

   // Right face.
   glVertex3f(1, -1, 1);
   glVertex3f(-1, -1, 1);
   glVertex3f(-1, 1, 1);
   glVertex3f(-1, 1, -1);

   // Left face.
   glVertex3f(-1, -1, -1);
   glVertex3f(-1, -1, 1);
   glVertex3f(-1, 1, 1);
   glVertex3f(-1, 1, -1);

   // Top face.
   glVertex3f(-1, 1, 1);
   glVertex3f(1, 1, 1);
   glVertex3f(1, 1, -1);
   glVertex3f(-1, 1, -1);

   // Bottom face.
   glVertex3f(-1, -1, -1);
   glVertex3f(1, -1, -1);
   glVertex3f(1, -1, 1);
   glVertex3f(-1, -1, 1);

   glEnd();
   glPopMatrix();
}

/*
 *  Placeholder for light source.
 */
void Ball(double x, double y, double z, double r)
{
   glPushMatrix();

   glTranslated(x, y, z);
   glScaled(r, r, r);

   float yellow[] = {1.0, 1.0, 0.0, 1.0};
   float Emission[] = {0.0, 0.0, 0.01 * emission, 1.0};

   glColor3f(1, 1, 1);
   glMaterialf(GL_FRONT, GL_SHININESS, shiny);
   glMaterialfv(GL_FRONT, GL_SPECULAR, yellow);
   glMaterialfv(GL_FRONT, GL_EMISSION, Emission);

   for (int i = -90; i < 90; i += 10)
   {
      glBegin(GL_QUAD_STRIP);
      for (int j = 0; j <= 360; j += 20)
      {
         Vertex(j, i);
         Vertex(j, i + 10);
      }
      glEnd();
   }
   glPopMatrix();
}

/*
 *  Compute a vertex in polar coordinates.  
 */
void Vertex(double theta, double phi)
{
   // Compute polar x, y, z.
   double x = Sin(theta) * Cos(phi);
   double y = Cos(theta) * Cos(phi);
   double z = Sin(phi);

   // Compute normal, draw vertex.
   glNormal3d(x, y, z);
   glVertex3d(x, y, z);
}