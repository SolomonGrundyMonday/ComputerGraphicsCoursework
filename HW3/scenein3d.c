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
int mode = 0;

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

/*
 *  Function draws a wheel axel, with two parallel cyllenders connected in the
 *  middle by a long, narrow cyllender.
 */
static void WheelAxel(double x, double y, double z, double dx, double dy,
                  double dz, double theta)
{
   // Variables for circumference, axel circumference.
   double circumference = 0.05;
   double axel = circumference * 0.2;
   glPushMatrix();

   // Apply the translation, rotation and scaling to the object based on the input
   // parameters.
   glTranslated(x, y, z);
   glRotated(theta, 0, 0, 1);
   glScaled(dx, dy, dz);

   // Draw the left wheel tread.
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 360; i += 30)
   {
      glVertex3d(circumference * Cos(i), circumference * Sin(i), 0.2);
      glVertex3d(circumference * Cos(i), circumference * Sin(i), 0.25);
   }
   glEnd();

   // Draw the inside of the left wheel wall.
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0, 0, 0.2);
   for (int i = 0; i <= 360; i += 30)
      glVertex3f(circumference * Cos(i), circumference * Sin(i), 0.2);
   glEnd();

   // Draw the outside of the wheel wall
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0, 0, 0.25);
   for (int i = 0; i <= 360; i += 30)
      glVertex3f(circumference * Cos(i), circumference * Sin(i), 0.25);
   glEnd();

   // Draw the right wheel tread.
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 360; i += 30)
   {
      glVertex3f(circumference * Cos(i), circumference * Sin(i), 0.4);
      glVertex3f(circumference * Cos(i), circumference * Sin(i), 0.45);
   }
   glEnd();

   // Draw the inside wheel wall.
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0, 0, 0.4);
   for (int i = 0; i <= 360; i += 30)
      glVertex3f(circumference * Cos(i), circumference * Sin(i), 0.4);
   glEnd();

   // Draw the outside wheel wall.
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0, 0, 0.45);
   for (int i = 0; i <= 360; i += 30)
      glVertex3f(circumference * Cos(i), circumference * Sin(i), 0.45);
   glEnd();

   // Draw the axel between the wheels.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 360; i += 30)
   {
      glVertex3f(axel * Cos(i), axel * Sin(i), 0.2);
      glVertex3f(axel * Cos(i), axel * Sin(i), 0.45);
   }
   glEnd();

   glPopMatrix();
}

/*
 *  This function draws a rover object, implemented as a cube placed above two
 *  wheel axels (see above function).  Hopefully I can further iterate on this
 *  object when we get to texturing.
 */
static void Rover(double x, double y, double z, double dx,
                  double dy, double dz, double theta)
{
   //double length = 0.8;
   
   glPushMatrix();

   glTranslated(x, y, z);
   glRotated(theta, 0, 0, 1);
   glScaled(dx, dy, dz);
   glColor3f(0.0, 1.0, 0.0);

   glBegin(GL_QUADS);
   // Front.
   glVertex3f(-1, -1, 1);
   glVertex3f(1, -1, 1);
   glVertex3f(1, 1, 1);
   glVertex3f(-1, 1, 1);

   // Back.
   glVertex3f(1, -1, -1);
   glVertex3f(-1, -1, -1);
   glVertex3f(-1, 1, -1);
   glVertex3f(1, 1, -1);

   // Left Middle.
   glVertex3f(-1, -1, -1);
   glVertex3f(-1, -1, 1);
   glVertex3f(-1, 1, 1);
   glVertex3f(-1, 1, -1);

   // Right Middle.
   glVertex3f(1, -1, 1);
   glVertex3f(1, -1, -1);
   glVertex3f(1, 1, -1);
   glVertex3f(1, 1, 1);

   // Top
   glVertex3f(-1, 1, 1);
   glVertex3f(1, 1, 1);
   glVertex3f(1, 1, -1);
   glVertex3f(-1, 1, -1);
  
   // Bottom
   glVertex3f(-1, -1, -1);
   glVertex3f(1, -1, -1);
   glVertex3f(1, -1, 1);
   glVertex3f(-1, -1, 1);
   glEnd();

   /*glBegin(GL_TRIANGLES);
   // Front Left.
   glVertex3f(-1, -1, -1);
   glVertex3f(-1, -1, -1);
   glVertex3f(-1, 1, -1);
   
   // Front Right.
   glVertex3f(-1, -1, -1);
   glVertex3f(-1, -1, 1);
   glVertex3f(-1, 1, 1);
   glEnd();*/

   WheelAxel(-0.8, -1.1, -3.5, 5.0, 10.0, 11.0, 0);
   WheelAxel(0.8, -1.1, -3.5, 5.0, 10.0, 11.0, 0);
   glPopMatrix();
}

/*
 *  This function draws a rocket object, complete with nose cone, tail fins and 
 *  fire/propulsion.  (Hoping to animate and apply lighting to the fire for 
 *  later assignments). 
 */
static void Rocket(double x, double y, double z, 
                   double dx, double dy, double dz, double theta)
{
   // Compute radius from specified circumference.
   double circumference = 0.05;
   double radius = circumference * 0.5;
   glPushMatrix();

   // Apply translation, rotation and scaling to object based on input parameters.
   glTranslated(x, y, z);
   glRotated(theta, 0, 0, 1);
   glScaled(dx, dy, dz);

   // Set the color.
   glColor3f(1.0, 0.5, 0.0);

   // Nose cone for the Rocket object
   glBegin(GL_TRIANGLE_FAN);
   glVertex3d(0.50, 0.0, 0.0);
   for (int i = 0; i <= 360; i += 30)
      glVertex3f(0.20, circumference * Cos(i), circumference * Sin(i));
   glEnd();

   // Fuselage of the Rocket object (implemented as a cyllender).
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 360; i += 30)
   {
      glVertex3f(0.20, circumference * Cos(i), circumference * Sin(i));
      glVertex3f(-0.50, circumference * Cos(i), circumference * Sin(i));
   }
   glEnd();

   // Tail fin one, positive y,z (rocket coordinate system).
   glColor3f(1.0, 0.0, 0.1);
   glBegin(GL_TRIANGLES);
   glVertex3f(-0.1, radius, radius);
   glVertex3f(-0.3, radius, radius);
   glVertex3f(-0.3, radius + 0.1, radius + 0.1);
   glEnd();

   glBegin(GL_QUAD_STRIP);
   glVertex3f(-0.5, radius, radius);
   glVertex3f(-0.5, radius + 0.1, radius + 0.1);
   glVertex3f(-0.3, radius, radius);
   glVertex3f(-0.3, radius + 0.1, radius + 0.1);
   glEnd();

   // Tail fin two, negative y,z (rocket coordinate system).
   glBegin(GL_TRIANGLES);
   glVertex3f(-0.1, -radius, -radius);
   glVertex3f(-0.3, -radius, -radius);
   glVertex3f(-0.3, -radius - 0.1, -radius - 0.1);
   glEnd();

   glBegin(GL_QUAD_STRIP);
   glVertex3f(-0.5, -radius, -radius);
   glVertex3f(-0.5, -radius - 0.1, -radius - 0.1);
   glVertex3f(-0.3, -radius, -radius);
   glVertex3f(-0.3, -radius - 0.1, -radius - 0.1);
   glEnd();

   // Tail fin three, negative y, positive z (rocket coordinate system).
   glBegin(GL_TRIANGLES);
   glVertex3f(-0.1, -radius, radius);
   glVertex3f(-0.3, -radius, radius);
   glVertex3f(-0.3, -radius - 0.1, radius + 0.1);
   glEnd();

   glBegin(GL_QUAD_STRIP);
   glVertex3f(-0.5, -radius, radius);
   glVertex3f(-0.5, -radius - 0.1, radius + 0.1);
   glVertex3f(-0.3, -radius, radius);
   glVertex3f(-0.3, -radius - 0.1, radius + 0.1);
   glEnd();

   // Tail fin four positive y, negative z (rocket coordinate system).
   glBegin(GL_TRIANGLES);
   glVertex3f(-0.1, radius, -radius);
   glVertex3f(-0.3, radius, -radius);
   glVertex3f(-0.3, radius + 0.1, -radius - 0.1);
   glEnd();

   glBegin(GL_QUAD_STRIP);
   glVertex3f(-0.5, radius, -radius);
   glVertex3f(-0.5, radius + 0.1, -radius - 0.1);
   glVertex3f(-0.3, radius, -radius);
   glVertex3f(-0.3, radius + 0.1, -radius - 0.1);
   glEnd();
   
   // Thrusters here we just have a yellow cone emitted from the back of
   // the fuselage, hopefully I can further iterate on this in the lighting
   // or texturing units to make more realistic fire effects.
   glBegin(GL_TRIANGLE_FAN);
   glColor3f(1.0, 1.0, 0.0);
   glVertex3f(-0.7, 0.0, 0.0);
   for(int i = 0; i <= 360; i += 30)
   {
      glVertex3f(-0.5, circumference * Cos(i), circumference * Sin(i));
   }
   glEnd();
   
   glPopMatrix();
}

/*
 *  This function draws a simmple cube object which can serve as the floor for my scene. 
 */
static void Box(double x, double y, double z, double dx, double dy, double dz, double theta)
{
   glPushMatrix();

   glTranslated(x, y, z);
   glRotated(theta, 0, 1, 0);
   glScaled(dx, dy, dz);
   glColor3f(0.196, 0.514, 0.659);

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

   glPopMatrix();
}

/*
 *  This function is called by GLUT to draw the scene.
 */
void display()
{
   // Erase window and depth buffer, enable z-buffering in OpenGL.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);

   // Undo previous transforms and set the view angles.
   glLoadIdentity();
   glRotatef(ph, 1, 0, 0);
   glRotatef(th, 0, 1, 0);

   // Generate a Rocket object with 0.75,0.9,0.75 x,y,x translation
   // zero rotation, 1,1,1 x,y,z scaling
   Rocket(0.75, 0.9, 0.75, 1.0, 1.0, 1.0, 0);

   // Generate a cube to represent the floor of my scene.
   Box(0.0, -0.1, 0.0, 2.0, 0.1, 2.0, 0);

   // Generate a Rover object with 1.3-0.25-1.3 x-y-z translation, zero
   // rotation, 0.4, 0.15, 0.1 x-y-z scaling.
   Rover(1.3, 0.25, 1.3, 0.4, 0.15, 0.1, 0);

   // Generate copy of a Rover object with -0.5,0.95,-0.1 (x,y,z) translation,
   // zero rotation, 0.4,0.4,0.4 x,y,x scaling.
   Rover(-0.5, 0.95, -0.1, 0.8, 0.6, 0.5, 0);
   Rocket(0.4, 0.5, 0.4, 0.4, 0.4, 0.4, 90);

   // Only display axes if user toggles "debug" mode.
   if (mode == 0)
   {
      // Draw axes in white.
      glColor3f(1, 1, 1);
      glBegin(GL_LINES);
      glVertex3d(0.0, 0.0, 0.0);
      glVertex3d(1.5, 0.0, 0.0);
      glVertex3d(0.0, 0.0, 0.0);
      glVertex3d(0.0, 1.5, 0.0);
      glVertex3d(0.0, 0.0, 0.0);
      glVertex3d(0.0, 0.0, 1.5);
      glEnd();

      // Label X, Y, Z axes.
      glRasterPos3d(1.5, 0.0, 0.0);
      Print("X");
      glRasterPos3d(0.0, 1.5, 0.0);
      Print("Y");
      glRasterPos3d(0.0, 0.0, 1.5);
      Print("Z");
   }

   // Bottom left corner.
   glWindowPos2i(5, 5);

   // Check for gl errors, flush and swap buffer.
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this function when an arrow key is pressed by user.
 */
void special(int key, int x, int y)
{
   // Increase elevation by 5 deg.
   if(key == GLUT_KEY_UP)
   {
      ph += 5;
   }
   // Decrease elevation by 5 deg.
   else if (key == GLUT_KEY_DOWN)
   {
      ph -= 5;
   }
   // Increase azimuth by 5 deg.
   else if (key == GLUT_KEY_RIGHT)
   {
      th += 5;
   }
   // Decrease azimuth by 5 deg.
   else if (key == GLUT_KEY_LEFT)
   {
      th -= 5;
   }

   // Limit azimuth/elevation to [-360, 360].
   th %= 360;
   ph %= 360;

   // Redisplay the scene.
   glutPostRedisplay();
}

void key(unsigned char key, int x, int y)
{
   // Escape key causes application to exit with status of zero.
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
   // Specify entire window as viewport.
   glViewport(0, 0, RES*width, RES*height);

   // Tell GLUT to manipulate projection matrix.
   glMatrixMode(GL_PROJECTION);

   // Undo previous transform.
   glLoadIdentity();

   // Use orthogonal projection.
   const double dim = 2.5;
   double asp = (height > 0) ? (double)width/height : 1;
   glOrtho(-asp*dim, +asp*dim, -dim, +dim, -dim, +dim);

   // Switch to manipulating model matrix and undo previous transform.
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
   // Initialize GLUT, and process command-line args.
   glutInit(&argc, argv);

   // Create double buffered 500x500 window with true color and z-buffering enabled. 
   glutInitWindowSize(500, 500);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

   // Create window with my name as title.
   glutCreateWindow("Jeff Colgan");

#ifdef USEGLEW
   // Initialize GLEW if present.
   if (glewInit() != GLEW_OK) Fatal("Error initializing GLEW\n");
#endif

   // Tell GLUT to call "idle" when there is nothing to do POSSIBLE DEPRECATION.
   glutIdleFunc(idle);

   // Tell GLUT to call "display" when the scene needs to be drawn.
   glutDisplayFunc(display);

   // Tell GLUT to call "reshape" when the user resizes the window.
   glutReshapeFunc(reshape);

   // Tell GLUT to call "special" when user presses an arrow key.
   glutSpecialFunc(special);

   // Tell GLUT to call "key" when user presses a key.
   glutKeyboardFunc(key);

   // Pass control to GLUT.
   glutMainLoop();
   
   return 0;
}