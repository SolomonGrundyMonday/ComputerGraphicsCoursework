/*
 *  Homework 4, CSCI-4229 Computer Graphics.
 *  Created by:  Jeff Colgan September 29, 2021. 
 */
#include "utility.h"

int th = 45;           // View angle azimuth.
int ph = 45;           // View angle elevation.
int mode = 0;         // Determines the projection mode/eyepoint.
double dim = 3.0;     // Dimensions of viewport.
double asp = 1.0;     // Aspect ratio for use in gluPerspective.
double Ex = -3.0;      // Eye point x-value.
double Ey = 0.4;      // Eye point y-value.
double Ez = 3.0;      // Eye point z-value.
double Upx = 0.0;     // Up vector x-value.
double Upy = 1.0;     // Up vector y-value.
double Upz = 0.0;     // Up vector z-value.
double Cx = 3.3;      // C-vector x coordinate.
double Cy = 0.4;      // C-vector y coordinate.
double Cz = -3.3;     // C-vector z coordinate.

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

   // Local variables for readability.
   double lInnerWall = 0.2;
   double lOuterWall = 0.25;
   double rInnerWall = 0.45;
   double rOuterWall = 0.4;

   glPushMatrix();

   // Apply the translation, rotation and scaling.
   glTranslated(x, y, z);
   glRotated(theta, 0, 0, 1);
   glScaled(dx, dy, dz);

   // Draw the left wheel tread.
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 360; i += 30)
   {
      glVertex3d(circumference * Cos(i), circumference * Sin(i), lInnerWall);
      glVertex3d(circumference * Cos(i), circumference * Sin(i), lOuterWall);
   }
   glEnd();

   // Draw the inside of the left wheel wall.
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0, 0, 0.2);
   for (int i = 0; i <= 360; i += 30)
      glVertex3f(circumference * Cos(i), circumference * Sin(i), lInnerWall);
   glEnd();

   // Draw the outside of the wheel wall
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0, 0, 0.25);
   for (int i = 0; i <= 360; i += 30)
      glVertex3f(circumference * Cos(i), circumference * Sin(i), lOuterWall);
   glEnd();

   // Draw the right wheel tread.
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 360; i += 30)
   {
      glVertex3f(circumference * Cos(i), circumference * Sin(i), rOuterWall);
      glVertex3f(circumference * Cos(i), circumference * Sin(i), rInnerWall);
   }
   glEnd();

   // Draw the inside wheel wall.
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0, 0, 0.4);
   for (int i = 0; i <= 360; i += 30)
      glVertex3f(circumference * Cos(i), circumference * Sin(i), rOuterWall);
   glEnd();

   // Draw the outside wheel wall.
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0, 0, 0.45);
   for (int i = 0; i <= 360; i += 30)
      glVertex3f(circumference * Cos(i), circumference * Sin(i), rInnerWall);
   glEnd();

   // Draw the axel between the wheels.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 360; i += 30)
   {
      glVertex3f(axel * Cos(i), axel * Sin(i), lInnerWall);
      glVertex3f(axel * Cos(i), axel * Sin(i), rInnerWall);
   }
   glEnd();

   glPopMatrix();
}

/*
 *  This function draws a rover object, implemented as a cube placed above two
 *  wheel axels (see above function).  Hopefully I can further iterate on this
 *  object when we get to texturing, as well as introduce more complex/realistic
 *  geometry. 
 */
static void Rover(double x, double y, double z, double dx,
                  double dy, double dz, double theta)
{
   glPushMatrix();

   // Apply translation, rotation and scaling from the input parameters.
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

   // Middle face.
   glVertex3f(-1, -1, -1);
   glVertex3f(-1, -1, 1);
   glVertex3f(-1, 1, 1);
   glVertex3f(-1, 1, -1);

   // Middle face. 
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

   // Wheel axels near the front and near the back.
   glColor3f(0.729, 0.690, 0.686);
   WheelAxel(-0.8, -1.1, -4.25, 5.0, 10.0, 13.0, 0);
   WheelAxel(0.8, -1.1, -4.25, 5.0, 10.0, 13.0, 0);
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

   // Local variables for readability.
   double noseTip = 0.50;
   double noseHeight = 0.20;
   double fuselageBase = -0.50;
   double finTip = -0.1;
   double finEdge = -0.3;

   glPushMatrix();

   // Apply translation, rotation and scaling to object based on input parameters.
   glTranslated(x, y, z);
   glRotated(theta, 0, 0, 1);
   glScaled(dx, dy, dz);

   // Set the fuselage color.
   glColor3f(1.0, 0.5, 0.0);

   // Nose cone for the Rocket object
   glBegin(GL_TRIANGLE_FAN);
   glVertex3d(noseTip, 0.0, 0.0);
   for (int i = 0; i <= 360; i += 30)
      glVertex3f(noseHeight, circumference * Cos(i), circumference * Sin(i));
   glEnd();

   // Fuselage of the Rocket object (implemented as a cyllender).
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 360; i += 30)
   {
      glVertex3f(noseHeight, circumference * Cos(i), circumference * Sin(i));
      glVertex3f(fuselageBase, circumference * Cos(i), circumference * Sin(i));
   }
   glEnd();

   // Set the tail fin color.
   glColor3f(1.0, 0.0, 0.1);

   // Tail fin one: positive y,z (rocket coordinate system).
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

   // Lines so the fins are visible from above/below.
   glBegin(GL_LINES);
   glVertex3f(finTip, radius, radius);
   glVertex3f(finEdge, radius + 0.1, radius + 0.1);
   glVertex3f(fuselageBase, radius, radius);
   glVertex3f(fuselageBase, radius + 0.1, radius + 0.1);
   glVertex3f(finEdge, radius + 0.1, radius + 0.1);
   glVertex3f(fuselageBase, radius + 0.1, radius + 0.1);
   glEnd();

   // Tail fin two: negative y,z (rocket coordinate system).
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

   // Lines so the fins are visible from above/below.
   glBegin(GL_LINES);
   glVertex3f(finTip, -radius, -radius);
   glVertex3f(finEdge, -radius - 0.1, -radius - 0.1);
   glVertex3f(fuselageBase, -radius, -radius);
   glVertex3f(fuselageBase, -radius - 0.1, -radius - 0.1);
   glVertex3f(finEdge, -radius - 0.1, -radius - 0.1);
   glVertex3f(fuselageBase, -radius - 0.1, -radius - 0.1);
   glEnd();

   // Tail fin three: negative y, positive z (rocket coordinate system).
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

   // Lines so the fins are visible from sides/above/below.
   glBegin(GL_LINES);
   glVertex3f(finTip, -radius, radius);
   glVertex3f(finEdge, -radius - 0.1, radius + 0.1);
   glVertex3f(fuselageBase, -radius, radius);
   glVertex3f(fuselageBase, -radius - 0.1, radius + 0.1);
   glVertex3f(finEdge, -radius - 0.1, radius + 0.1);
   glVertex3f(fuselageBase, -radius - 0.1, radius + 0.1);
   glEnd();

   // Tail fin four: positive y, negative z (rocket coordinate system).
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

   // Lines so the fins are visible from sides/above/below.
   glBegin(GL_LINES);
   glVertex3f(finTip, radius, -radius);
   glVertex3f(finEdge, radius + 0.1, -radius - 0.1);
   glVertex3f(fuselageBase, radius, -radius);
   glVertex3f(fuselageBase, radius + 0.1, -radius - 0.1);
   glVertex3f(finEdge, radius + 0.1, -radius - 0.1);
   glVertex3f(fuselageBase, radius + 0.1, -radius - 0.1);
   glEnd();
   
   // Thrusters here we just have a yellow cone emitted from the back of
   // the fuselage, hopefully I can further iterate on this in the lighting
   // or texturing units to make more realistic fire effects.
   glBegin(GL_TRIANGLE_FAN);
   glColor3f(1.0, 1.0, 0.0);
   glVertex3f(-0.7, 0.0, 0.0);
   for(int i = 0; i <= 360; i += 30)
   {
      glVertex3f(fuselageBase, circumference * Cos(i), circumference * Sin(i));
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

   // Apply scale, translation, and rotation from input parameters.
   glTranslated(x, y, z);
   glRotated(theta, 0, 1, 0);
   glScaled(dx, dy, dz);
   glColor3f(0.196, 0.514, 0.659);

   // Launch Platform.
   glBegin(GL_QUADS);

   // Front face
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
   glVertex3f(1, -1, -1);
   glVertex3f(1, 1, -1);
   glVertex3f(1, 1, 1);

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
 *  This function sets the Projection matrix based on the fov.  For now, a
 *  fov value of zero sets it to orthogonal, and any other value will set
 *  to perspective.  I plan to iterate on this in the future.
 */
void Projection()
{
   // Switch to manipulating projection matrix and undo previous transforms.
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   // I chose 45 degrees for the field of view.
   if (mode == 1 || mode == 2)
   {
      gluPerspective(45, asp, dim / 16, 16 * dim);
   }
   // Otherwise do orthogonal.
   else
   {
      glOrtho(-asp * dim, asp * dim, -dim, dim, -dim, dim);
   }

   // Switch back to model matrix and undo previous transforms.
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
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

   // Allow user to control view angle in orthogonal projection
   if (mode == 0)
   {
      glRotatef(ph, 1, 0, 0);
      glRotatef(th, 0, 1, 0);
   }
   // For perspective projection - slanted overhead
   else if (mode == 1)
   {
      gluLookAt(-5.0, 6.0, 5.0, 0.0, 0.0, 0.0, 0, 1, 0);
   }
   else
   {
      Turn(&Cx, &Cz, dim, th);
      gluLookAt(Ex, Ey, Ez, Cx + Ex, Cy, Cz + Ey, Upx, Upy, Upz);
   }

   // Generate a Rocket object
   Rocket(0.75, 0.9, 0.75, 1.0, 1.0, 1.0, 0);

   // Generate a cube to represent the floor of my scene.
   Box(0.0, -0.1, 0.0, 3.0, 0.1, 3.0, 0);

   // Generate a Rover object.
   glColor3f(0.2, 1.0, 0.2);
   Rover(1.3, 0.225, 1.3, 0.4, 0.15, 0.1, 0);

   // Generate a Rover object copy.
   glColor3f(1.0, 0.0, 0.0);
   Rover(0.0, 0.225, 1.2, 0.4, 0.15, 0.1, 90);

   // Generate a Rover object copy.
   glColor3f(0.0, 0.0, 1.0);
   Rover(-0.5, 0.95, -0.1, 0.8, 0.6, 0.5, 0);

   // Generate a Rocket object copy.
   Rocket(0.4, 0.5, 0.4, 0.4, 0.4, 0.4, 90);

   // Bottom left corner.
   glWindowPos2i(5, 5);

   // Print user-friendly message about mode at the bottom of the window.
   switch(mode)
   {
      case 0:
         Print("Mode = Orthogonal Projection, slanted overhead.");
         break;
      case 1:
         Print("Mode = Perspective Projection, slanted overhead.");
         break;
      case 2:
         Print("Cx, Cz = %.1lf, %.1lf; Theta = %d, Ex, Ez = %.1lf, %.1lf", Cx, Cz, th, Ex, Ez);
         break;
   }

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
   if(mode == 2)
   {
      // Move first person camera forward.
      if(key == GLUT_KEY_UP)
      {
         MoveForward(&Ex, &Ez, th);
      }
      // Move first person camera backward.
      else if (key == GLUT_KEY_DOWN)
      {
         MoveBackward(&Ex, &Ez, th);
      }
      // Increase horizontal camera angle by 5 deg.
      else if (key == GLUT_KEY_RIGHT)
      {
         th += 5;
         th %= 360;
      }
      // Decrease horizontal camera angle by 5 deg.
      else if (key == GLUT_KEY_LEFT)
      {
         th -= 5;
         th %= 360;
      }
   }

   Projection();

   // Redisplay the scene.
   glutPostRedisplay();
}

/*
 *  This function is called by GLUT when the user presses a key.
 */
void key(unsigned char key, int x, int y)
{
   // Escape key causes application to exit with status of zero.
   if (key == 27)
   {
      exit(0);
   }
   // M key toggles between orthogonal, perspective and first person modes.
   else if (key == 'm' || key == 'M')
   {
      switch(mode)
      {
         case 0:
            mode = 1;
            th = 45;
            Projection();
            break;
         case 1:
            mode = 2;
            ph = 0;
            Projection();
            break;
         case 2:
            mode = 0;
            Projection();
            th = 45;
            ph = 45;
            break;
      }
   }
   // R key resets the first person camera to the starting position and orientation.
   else if (key == 'r' || key == 'R')
   {
      if (mode == 2)
      {
         ResetPosition(&Ex, &Ey, &Ez, &Cx, &Cy, &Cz, &dim, &th, &ph);
         Projection();
      }
   }

   // Tell GLUT to redraw the scene.
   glutPostRedisplay();
}

/*
 *  GLUT calls this function when the window is resized.
 */
void reshape(int width, int height)
{
   // Specify entire window as viewport.
   glViewport(0, 0, RES*width, RES*height);

   // Compute new aspect ratio.
   asp = (height > 0) ? (double)width/height : 1;

   Projection();
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