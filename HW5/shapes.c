#include "shapes.h"

const int shiny = 0;
const float emission = 0;
const float black[] = {0.0, 0.0, 0.0, 1.0};
const float white[] = {1.0, 1.0, 1.0, 1.0};
const float orange[] = {1.0, 0.5, 0.0, 1.0};

void DrawTriangle(vtx A, vtx B, vtx C)
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
   glBegin(GL_TRIANGLES);
   glVertex3f(A.x, A.y, A.z);
   glVertex3f(B.x, B.y, B.z);
   glVertex3f(C.x, C.y, C.z);
   glEnd();
}

void WheelAxel(double x, double y, double z, double dx, double dy,
               double dz, double theta)
{
   double circumference = 0.05;
   double axel = circumference * 0.2;

   double lInnerWall = 0.2;
   double lOuterWall = 0.25;
   double rInnerWall = 0.45;
   double rOuterWall = 0.4;

   glPushMatrix();

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

void Rover(double x, double y, double z, double dx,
           double dy, double dz, double theta)
{
   glPushMatrix();

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

   glColor3f(0.729, 0.690, 0.686);
   WheelAxel(-0.8, -1.1, -4.25, 5.0, 10.0, 13.0, 0);
   WheelAxel(0.8, -1.1, -4.25, 5.0, 10.0, 13.0, 0);
   glPopMatrix();
}

const tri idx[] =
{
   {0, 1, 2}, {0, 2, 3}, {0, 3, 4}, {0, 4, 5}, {0, 5, 6},
   {0, 6, 7}, {0, 7, 8}, {0, 8, 9}, {0, 9, 10}, {0, 10, 11},
   {0, 11, 12}, {0, 12, 1}
};

const vtx xyz[] = 
{
   {0.50, 0.0, 0.0}, {0.20, 0.05, 0.0},
   {0.20, 0.05 * Cos(30), 0.05 * Sin(30)}, {0.20, 0.05 * Cos(60), 0.05 * Sin(60)}, 
   {0.20, 0.0, 0.05}, {0.20, 0.05 * Cos(120), 0.05 * Sin(120)}, 
   {0.20, 0.05 * Cos(150), 0.05 * Sin(150)}, {0.20, -0.05, 0.0}, 
   {0.20, 0.05 * Cos(210), 0.05 * Sin(210)}, {0.20, 0.05 * Cos(240), 0.05 * Sin(240)}, 
   {0.20, 0.0, -0.05}, {0.20, 0.05 * Cos(300), 0.05 * Sin(300)}, 
   {0.20, 0.05 * Cos(330), 0.05 * Sin(330)}
};

void Rocket(double x, double y, double z, double dx, double dy,
            double dz, double theta)
{
   double circumference = 0.05;
   double radius = circumference * 0.5;

   //double noseTip = 0.50;
   double noseHeight = 0.20;
   double fuselageBase = -0.50;
   double finTip = -0.1;
   double finEdge = -0.3;

   glColor4fv(orange);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, orange);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

   glPushMatrix();

   glTranslated(x, y, z);
   glScaled(dx, dy, dz);
   glRotated(theta, 0, 0, 1);

   /* Draw the nose cone.
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(noseTip, 0.0, 0.0);
   for (int i = 0; i <= 360; i += 30)
      glVertex3f(noseHeight, circumference * Cos(i), circumference * Sin(i));
   glEnd();*/

   for (int i = 0; i < 12; i++)
   {
      //glBegin(GL_TRIANGLE_FAN);
      DrawTriangle(xyz[idx[i].A], xyz[idx[i].B], xyz[idx[i].C]);
      //glEnd();
   }

   // Draw the fuselage.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 360; i += 30)
   {
      glVertex3f(noseHeight, circumference * Cos(i), circumference * Sin(i));
      glVertex3f(fuselageBase, circumference * Cos(i), circumference * Sin(i));
   }
   glEnd();

   glColor3f(1.0, 0.0, 0.1);

   // Tail fin one.
   glBegin(GL_TRIANGLES);
   glVertex3f(finTip, radius, radius);
   glVertex3f(finEdge, radius, radius);
   glVertex3f(finEdge, radius + 0.1, radius + 0.1);
   glEnd();

   glBegin(GL_QUAD_STRIP);
   glVertex3f(fuselageBase, radius, radius);
   glVertex3f(fuselageBase, radius + 0.1, radius + 0.1);
   glVertex3f(finEdge, radius, radius);
   glVertex3f(finEdge, radius + 0.1, radius + 0.1);
   glEnd();

   glBegin(GL_LINES);
   glVertex3f(finTip, radius, radius);
   glVertex3f(finEdge, radius + 0.1, radius + 0.1);
   glVertex3f(fuselageBase, radius, radius);
   glVertex3f(fuselageBase, radius + 0.1, radius + 0.1);
   glVertex3f(finEdge, radius + 0.1, radius + 0.1);
   glVertex3f(fuselageBase, radius + 0.1, radius + 0.1);
   glEnd();

   // Tail fin two.
   glBegin(GL_TRIANGLES);
   glVertex3f(finTip, -radius, -radius);
   glVertex3f(finEdge, -radius, -radius);
   glVertex3f(finEdge, -radius - 0.1, -radius - 0.1);
   glEnd();

   glBegin(GL_QUAD_STRIP);
   glVertex3f(fuselageBase, -radius, -radius);
   glVertex3f(fuselageBase, -radius - 0.1, -radius - 0.1);
   glVertex3f(finEdge, -radius, -radius);
   glVertex3f(finEdge, -radius - 0.1, -radius - 0.1);
   glEnd();

   glBegin(GL_LINES);
   glVertex3f(finTip, -radius, -radius);
   glVertex3f(finEdge, -radius - 0.1, -radius - 0.1);
   glVertex3f(fuselageBase, -radius, -radius);
   glVertex3f(fuselageBase, -radius - 0.1, -radius - 0.1);
   glVertex3f(finEdge, -radius - 0.1, -radius - 0.1);
   glVertex3f(fuselageBase, -radius - 0.1, -radius - 0.1);
   glEnd();

   // Tail fin three.
   glBegin(GL_TRIANGLES);
   glVertex3f(finTip, -radius, radius);
   glVertex3f(finEdge, -radius, radius);
   glVertex3f(finEdge, -radius - 0.1, radius + 0.1);
   glEnd();

   glBegin(GL_QUAD_STRIP);
   glVertex3f(fuselageBase, -radius, radius);
   glVertex3f(fuselageBase, -radius - 0.1, radius + 0.1);
   glVertex3f(finEdge, -radius, radius);
   glVertex3f(finEdge, -radius - 0.1, radius + 0.1);
   glEnd();

   glBegin(GL_LINES);
   glVertex3f(fuselageBase, -radius, radius);
   glVertex3f(finEdge, -radius - 0.1, radius + 0.1);
   glVertex3f(fuselageBase, -radius, radius);
   glVertex3f(fuselageBase, -radius - 0.1, radius + 0.1);
   glVertex3f(finEdge, -radius - 0.1, radius + 0.1);
   glVertex3f(fuselageBase, -radius - 0.1, radius + 0.1);
   glEnd();

   // Tail fin four.
   glBegin(GL_TRIANGLES);
   glVertex3f(finTip, radius, -radius);
   glVertex3f(finEdge, radius, -radius);
   glVertex3f(finEdge, radius + 0.1, -radius - 0.1);
   glEnd();

   glBegin(GL_QUAD_STRIP);
   glVertex3f(fuselageBase, radius, -radius);
   glVertex3f(fuselageBase, radius + 0.1, -radius - 0.1);
   glVertex3f(finEdge, radius, -radius);
   glVertex3f(finEdge, radius + 0.1, -radius - 0.1);
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

void Box(double x, double y, double z, double dx, double dy,
         double dz, double theta)
{
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);

   glPushMatrix();

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
         Vertex(j, i + 20);
      }
      glEnd();
   }
   glPopMatrix();
}

void Vertex(double theta, double phi)
{
   double x = Sin(theta) * Cos(phi);
   double y = Cos(theta) * Cos(phi);
   double z = Sin(phi);

   glNormal3d(x, y, z);
   glVertex3d(x, y, z);
}