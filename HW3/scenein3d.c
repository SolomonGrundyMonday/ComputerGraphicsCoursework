/*
 *  Homework 3, CSCI-4229 Computer Graphics.
 *  Created by:  Jeff Colgan September 21, 2021. 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#ifdef USEGLEW
#include <GL/glew.h>
#endif

#define GL_EXIT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef RES
#define RES 1
#endif

int th = 0;           // View angle azimuth.
int ph = 0;           // View angle elevation.

// Convert math.h sin/cos to output in degrees rather than radians.
#define Cos(x) (cos((x)*3.1415927/180))
#define Sin(x) (sin((x)*3.1415927/180))

/*
 *  Function to print raster text.
 */
#define LEN 8192
void Print(const char* format, ...)
{
   char buf[LEN];
   char* ch=buf;

   va_list args;
   va_start(args, format);
   vsnprintf(buf, LEN, format, args);
   va_end(args);

   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *ch++);
}

/*
 *  Check for errors in OpenGL.
 */
void ErrCheck(const char* where)
{
   int err = glGetError();
   if (err) fprintf(stderr, "ERROR: %s [%s]\n", gluErrorString(err), where);
}

/*
 *  Print error message to stderr and exit with status 1.
 */
void Fatal(const char* format, ...)
{
   va_list args;
   va_start(args, format);
   vfprintf(stderr, format, args);
   va_end(args);
   exit(1);
}

static void Floor(double x, double y, double z)
{
   glPushMatrix();

   glTranslated(x, y, z);
   glRotated(90, 1, 0, 0);

   glColor3f(0.647, 0.165, 0.165);
   glBegin(GL_QUADS);
   glVertex3f(-1, -1, 0);
   glVertex3f(-1, 1, 0);
   glVertex3f(1, 1, 0);
   glVertex3f(1, -1, 0);
   glEnd();

   glPopMatrix();
}

static void Rocket(double x, double y, double z, double circumference)
{
   // Compute radius from specified circumference.
   double radius = circumference * 0.5;
   glPushMatrix();

   glTranslated(x, y, z);
   //glMultMatrix(matrix);
   glRotated(90, 0, 0, 1);

   glColor3f(1.0, 0.5, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glVertex3d(0.50, 0.0, 0.0);

   // Nose cone
   for (int i = 0; i <= 360; i += 30)
      glVertex3d(0.20, circumference * Cos(i), circumference * Sin(i));
   glEnd();

   // Fuselage
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 360; i += 30)
   {
      glVertex3d(0.20, circumference * Cos(i), circumference * Sin(i));
      glVertex3d(-0.50, circumference * Cos(i), circumference * Sin(i));
   }
   glEnd();

   // Tail fins.
   glColor3f(1.0, 0.0, 0.1);
   glBegin(GL_TRIANGLES);
   glVertex3d(-0.1, radius, radius);
   glVertex3d(-0.3, radius, radius);
   glVertex3d(-0.3, radius + 0.1, radius + 0.1);
   glEnd();

   glBegin(GL_TRIANGLES);
   glVertex3d(-0.1, -radius, -radius);
   glVertex3d(-0.3, -radius, -radius);
   glVertex3d(-0.3, -radius - 0.1, -radius - 0.1);
   glEnd();

   glBegin(GL_TRIANGLES);
   glVertex3d(-0.1, -radius, radius);
   glVertex3d(-0.3, -radius, radius);
   glVertex3d(-0.3, -radius - 0.1, radius + 0.1);
   glEnd();

   glBegin(GL_TRIANGLES);
   glVertex3d(-0.1, radius, -radius);
   glVertex3d(-0.3, radius, -radius);
   glVertex3d(-0.3, radius + 0.1, -radius - 0.1);
   glEnd();

   glBegin(GL_QUAD_STRIP);
   glVertex3d(-0.5, radius, radius);
   glVertex3d(-0.5, radius + 0.1, radius + 0.1);
   glVertex3d(-0.3, radius, radius);
   glVertex3d(-0.3, radius + 0.1, radius + 0.1);
   glEnd();

   glBegin(GL_QUAD_STRIP);
   glVertex3d(-0.5, -radius, -radius);
   glVertex3d(-0.5, -radius - 0.1, -radius - 0.1);
   glVertex3d(-0.3, -radius, -radius);
   glVertex3d(-0.3, -radius - 0.1, -radius - 0.1);
   glEnd();

   glBegin(GL_QUAD_STRIP);
   glVertex3d(-0.5, -radius, radius);
   glVertex3d(-0.5, -radius - 0.1, radius + 0.1);
   glVertex3d(-0.3, -radius, radius);
   glVertex3d(-0.3, -radius - 0.1, radius + 0.1);
   glEnd();

   glBegin(GL_QUAD_STRIP);
   glVertex3d(-0.5, radius, -radius);
   glVertex3d(-0.5, radius + 0.1, -radius - 0.1);
   glVertex3d(-0.3, radius, -radius);
   glVertex3d(-0.3, radius + 0.1, -radius - 0.1);
   glEnd();
   
   // Thrusters.
   glBegin(GL_TRIANGLE_FAN);
   glColor3f(1.0, 1.0, 0.0);
   glVertex3d(-0.7, 0.0, 0.0);
   for(int i = 0; i <= 360; i += 30)
   {
      glVertex3d(-0.5, radius * Cos(i), radius * Sin(i));
   }
   glEnd();
   
   glPopMatrix();
}

static void LaunchPad(double x, double y, double z, double dx, double dy, double dz, double theta)
{
   glPushMatrix();

   glTranslated(x, y, z);
   glRotated(theta, 0, 1, 0);
   glScaled(dx, dy, dz);
   glColor3f(1.0, 0.0, 1.0);

   // Launch Platform.
   glBegin(GL_QUADS);
   // Front
   glVertex3f(-1, -1, 1);
   glVertex3f(1, -1, 1);
   glVertex3f(1, 1, 1);
   glVertex3f(-1, 1, 1);
   // Back
   glVertex3f(1, -1, -1);
   glVertex3f(-1, -1, -1);
   glVertex3f(-1, 1, -1);
   glVertex3f(1, 1, -1);
   // Right
   glVertex3f(1, -1, 1);
   glVertex3f(1, -1, -1);
   glVertex3f(1, 1, -1);
   glVertex3f(1, 1, 1);
   // Left
   glVertex3f(-1, -1, -1);
   glVertex3f(-1, -1, 1);
   glVertex3f(-1, 1, 1);
   glVertex3f(-1, 1, -1);
   // Top
   glVertex3f(-1, 1, 1);
   glVertex3f(1, 1, 1);
   glVertex3f(1, 1, -1);
   glVertex3f(-1, 1, -1);
   // Base
   glVertex3f(-1, -1, -1);
   glVertex3f(1, -1, -1);
   glVertex3f(1, -1, 1);
   glVertex3f(-1, -1, 1);
   glEnd();

   // Elevator.

   //
   glPopMatrix();
}

void display()
{
   // Do stuff here.

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);

   glLoadIdentity();
   glRotatef(ph, 1, 0, 0);
   glRotatef(th, 0, 1, 0);

   //Floor(1.0, 0.0, 1.0);
   Rocket(0.75, 0.75, 0.75, 0.05);
   LaunchPad(1.0, 0.05, 1.0, 1.0, 0.1, 1.0, 0);

   glColor3f(1, 1, 1);
   glBegin(GL_LINES);
   glVertex3d(0.0, 0.0, 0.0);
   glVertex3d(1.5, 0.0, 0.0);
   glVertex3d(0.0, 0.0, 0.0);
   glVertex3d(0.0, 1.5, 0.0);
   glVertex3d(0.0, 0.0, 0.0);
   glVertex3d(0.0, 0.0, 1.5);
   glEnd();

   glRasterPos3d(1.5, 0.0, 0.0);
   Print("X");
   glRasterPos3d(0.0, 1.5, 0.0);
   Print("Y");
   glRasterPos3d(0.0, 0.0, 1.5);
   Print("Z");

   glWindowPos2i(5, 5);
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this function when an arrow key is pressed by user.
 */
void special(int key, int x, int y)
{
   if(key == GLUT_KEY_UP)
   {
      ph += 5;
   }
   else if (key == GLUT_KEY_DOWN)
   {
      ph -= 5;
   }
   else if (key == GLUT_KEY_RIGHT)
   {
      th += 5;
   }
   else if (key == GLUT_KEY_LEFT)
   {
      th -= 5;
   }

   th %= 360;
   ph %= 360;
   glutPostRedisplay();
}

void key(unsigned char key, int x, int y)
{
   if (key == 27)
   {
      exit(0);
   }
   // Do stuff here.
}

/*
 *  GLUT calls this function when the window is resized.
 */
void reshape(int width, int height)
{
   glViewport(0, 0, RES*width, RES*height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   const double dim = 2.5;
   double asp = (height > 0) ? (double)width/height : 1;
   glOrtho(-asp*dim, +asp*dim, -dim, +dim, -dim, +dim);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void idle()
{
   // Do stuff here.
}

/*
 *  Main entry point.
 */
int main(int argc, char* argv[])
{
   glutInit(&argc, argv);
   glutInitWindowSize(500, 500);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

   glutCreateWindow("Jeff Colgan");

#ifdef USEGLEW
   if (glewInit() != GLEW_OK) Fatal("Error initializing GLEW\n");
#endif

   glutIdleFunc(idle);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);

   glutMainLoop();
   
   return 0;
}