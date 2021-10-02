#include "shapes.h"

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

void Rocket(double x, double y, double z, double dx, double dy,
            double dz, double theta)
{
   double circumference = 0.05;
   double radius = circumference * 0.5;

   double noseTip = 0.50;
   double noseHeight = 0.20;
   double fuselageBase = -0.50;
   double finTip = -0.1;
   double finEdge = -0.3;

   glPushMatrix();

   glTranslated(x, y, z);
   glRotated(theta, 0, 0, 1);
   glScaled(dx, dy, dz);

   glColor3f(1.0, 0.5, 0.0);

   // Draw the nose cone.
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(noseTip, 0.0, 0.0);
   for (int i = 0; i <= 360; i += 30)
      glVertex3f(noseHeight, circumference * Cos(i), circumference * Sin(i));
   glEnd();

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