/*
 *  CSCI-4229, Homework 6: Lighting and Textures
 *  Created by Jeff Colgan, 10/4/2021. 
 */
#include "utility.h"
#include "shapes.h"

int th = 45;               // View angle azimuth.
int ph = 45;               // View angle elevation.
int zh = 90;               // Light azimuth.
int mode = 0;              // Viewing mode.
int autoLight = 1;         // Automatic light orbit toggle.
int horizontalOrbit = 1;   // Horizontal/vertical orbit toggle.
int object = 0;            // Debug object toggle.
double dim = 5.0;          // Size of world.
double asp = 1.0;          // Aspect ratio.
double Ex = -3.0;          // Eye position x-value.
double Ey = 0.4;           // Eye position y-value.
double Ez = 3.0;           // Eye position z-value.
double Upx = 0.0;          // Up vector x-value.
double Upy = 1.0;          // Up vector y-value.
double Upz = 0.0;          // Up vector z-value.
double Cx = 3.3;           // Center vector x-value.
double Cy = 0.4;           // Center vector y-value.
double Cz = -3.3;          // Center vector z-value.
float distance = 3;        // Light distance.
float lightElev = 2.0;     // Light elevation (if horizontal orbit).
unsigned int textures[4];

/*
 *  Redraw the scene. 
 */
void display()
{
   char* objectString = "";

   // Erase window, depth buffer and enable z-buffering.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);

   glLoadIdentity();

   // Determine projection and set eye position based on the mode variable.
   if (mode == 0 || mode == 2)
   {
      glRotatef(ph, 1, 0, 0);
      glRotatef(th, 0, 1, 0);
   }
   else if (mode == 1)
   {
      Turn(&Cx, &Cz, dim, th);
      gluLookAt(Ex, Ey, Ez, Cx + Ex, Cy, Cz + Ez, Upx, Upy, Upz);
   }

   glShadeModel(GL_SMOOTH);

   float Ambient[] = { 0.1, 0.1, 0.1, 1.0 };
   float Diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
   float Specular[] = { 0.0, 0.0, 0.0, 1.0 };
   float Thruster[] = { 0.0, 0.0, 0.0, 1.0 };

   // Need to enable manual/automatic control of light source here.
   if (horizontalOrbit)
   {
      // Determine the position of the rocket object and light source based on zh.
      float Pos[] = {distance * Cos(zh), lightElev, distance * Sin(zh), 1.0};
      Thruster[0] = Pos[0] - (-0.5 * Sin(zh));
      Thruster[1] = Pos[1];
      Thruster[2] = Pos[2] + (-0.5 * Cos(zh));

      // Generate a rocket object that orbits the scene.
      Rocket(Pos[0], Pos[1], Pos[2], 1.0, 1.0, 1.0, 0, 0, -90 - zh);
   }
   else
   {
      // Determine the position of the rocket object and light source based on zh.
      float Pos[] = {0, distance * Cos(zh), distance * Sin(zh), 1.0};
      Thruster[0] = Pos[0];
      Thruster[1] = Pos[1] - (Sin(zh) * -0.5);
      Thruster[2] = Pos[2] + (Cos(zh) * -0.5);

      Rocket(Pos[0], Pos[1], Pos[2], 1.0, 1.0, 1.0, 0, 180 + zh, 90);
   }

   // This section of code (lines 84-100) are from ex13.c.
   // Enable normalization and lighting.
   glEnable(GL_NORMALIZE);
   glEnable(GL_LIGHTING);

   glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 0);
   glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

   // Create point light.
   glEnable(GL_COLOR_MATERIAL);
   glEnable(GL_LIGHT0);

   // Specify ambient, diffuse and specular qualities for point light and place 
   // at the orbiting rocket's thruster.
   glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
   glLightfv(GL_LIGHT0, GL_POSITION, Thruster);

   // If in debug mode and object selected = 0, draw a single Rocket at the 
   // middle of the light's orbit.
   if (mode == 2 && object == 0)
   {
      Rocket(0.0, lightElev, 0.0, 1.0, 1.0, 1.0, 90, 0, 0);
      objectString = "Rocket";
   }
   // If in debug mode and object selected = 1, draw a single Rover at the
   // middle of the light's orbit.
   else if (mode == 2 && object == 1)
   {
      glColor3f(1.0, 0.0, 0.0);
      Rover(0.0, lightElev, 0.0, 0.4, 0.15, 0.1, 90);
      objectString = "Rover";
   }
   // Otherwise, render the entire scene.
   else
   {
      // Generate objects to populate the scene.
      Rocket(0.75, 0.9, 0.75, 1.0, 1.0, 1.0, 90, 0, 0);
      //glColor3f(0.196, 0.514, 0.659);
      glEnable(GL_TEXTURE_2D);
      glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
      glBindTexture(GL_TEXTURE_2D, textures[1]);
      Box(0.0, -0.1, 0.0, 3.0, 0.1, 3.0, 0);
	  glDisable(GL_TEXTURE_2D);
      glColor3f(0.2, 1.0, 0.2);
      Rover(1.3, 0.225, 1.3, 0.4, 0.15, 0.1, 0);
      glColor3f(1.0, 0.0, 0.0);
      Rover(0.0, 0.225, 1.2, 0.4, 0.15, 0.1, 90);
      glColor3f(0.0, 0.0, 1.0);
      Rover(-0.5, 0.95, -0.1, 0.8, 0.6, 0.5, 0);
	  
   }

   glColor3f(1.0, 1.0, 1.0);

   // Raster text for user.
   glWindowPos2i(5, 5);
   switch(mode)
   {
      case 0:
         Print("Mode = Orthogonal Projection, slanted overhead.");
         break;
      case 1:
         Print("Mode = First person navigation.");
         break;
      case 2:
         Print("Debug Mode, Displayed Object : %s", objectString);
         break;
   }

   // Check for errors, flush and swap buffers.
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  Called when user presses a special key. 
 */
void special(int key, int x, int y)
{
   // If the user presses up arrow, move forward or adjust view angle elevation
   // for first person mode and orthogonal mode, respectively.
   if (key == GLUT_KEY_UP)
   {
      if(mode == 1)
         MoveForward(&Ex, &Ez, th);
      else
      {
         ph += 5;
         ph %= 360;
      }
   }
   // If the user presses down arrow, move backward or adjust view angle elevation
   // for first person mode and orthogonal mode, respectively.
   else if (key == GLUT_KEY_DOWN)
   {
      if (mode == 1)
         MoveBackward(&Ex, &Ez, th);
      else
      {
         ph -= 5;
         ph %= 360;
      }
   }
   // If the user presses right arrow increment th by 5 degrees.
   else if (key == GLUT_KEY_RIGHT)
   {
      th += 5;
      th %= 360;
   }
   // If the user presses left arrow, decrement th by 5 degrees.
   else if (key == GLUT_KEY_LEFT)
   {
      th -= 5;
      th %= 360;
   }

   // Call project for orthogonal projection if in orthogonal mode, perspective projection
   // with field of view of 45 degrees if first person mode.
   if (mode == 0 || mode == 2)
      Project(0, asp, dim);
   else
      Project(45, asp, dim);
   glutPostRedisplay();
}

/*
 *  Called when the user presses a key. 
 */
void key(unsigned char key, int x, int y)
{
   if (key == 27)
   {
      exit(0);
   }
   else if (key == 'm' || key == 'M')
   {
      // If user selects mode 0, give an overhead orthogonal projection
      // (adjustable).  Otherwise, first-person perspective projection.
      switch(mode)
      {
         case 0:
            mode = 1;
            th = 45;
            ph = 0;
            Project(45, asp, dim);
            break;
         case 1:
            mode = 2;
            th = 45;
            ph = 45;
            lightElev = 0.0;
            distance = 1.0;
            dim = 2.0;
            Project(0, asp, dim);
            break;
         case 2:
            mode = 0;
            th = 45;
            ph = 45;
            lightElev = 2.0;
            dim = 5.0;
            distance = 3.0;
            Project(0, asp, dim);
            break;
      }
   }
   // Reset eye position and center point position if user resets in mode 1.
   else if (key == 'r' || key == 'R')
   {
      if (mode == 1)
      {
         ResetPosition(&Ex, &Ey, &Ez, &Cx, &Cy, &Cz, &dim, &th, &ph);
         Project(45, asp, dim);
      }
   }
   // Toggle automatic light movement.
   else if (key == 'l' || key == 'L')
   {
      autoLight = (autoLight == 1) ? 0 : 1; 
   }
   // If automatic light movement is disabled, allow the user to increment light
   // position.
   else if (key == 'p' || key == 'P')
   {
      if (!autoLight)
      {
         zh += 10;
         zh %= 360;
      }
   }
   // Switch between vertical and horizontal orbit modes.
   else if (key == 'o' || key == 'O')
   {
      if (horizontalOrbit == 1)
         horizontalOrbit = 0;
      else
         horizontalOrbit = 1;
   }
   // Toggle the object viewed in debug mode (Rover or Rocket).
   else if (key == 's' || key == 'S')
   {
      if (mode == 2)
      {
         if (object == 0)
            object = 1;
         else
            object = 0;
      }
   }

   glutPostRedisplay();
}

/*
 *  Called when the window is resized.
 *  This code is mostly borrowed from the in-class examples,
 *  specifically ex13.c.
 */
void reshape(int width, int height)
{
   glViewport(0, 0, RES*width, RES*height);
   asp = (height > 0) ? (double)width/height : 1;
   if (mode == 0 || mode == 2)
      Project(0, asp, dim);
   else
      Project(45, asp, dim);
}

/*
 *  Called when there is nothing else to do. 
 *  This code is mostly borrowed from the in-class examples,
 *  this function specifically is from the ex13.c example.
 */
void idle()
{
   // If the automatic light orbit is enabled, change the zh parameter.
   if (autoLight)
   {
      double time = glutGet(GLUT_ELAPSED_TIME)/1000.0;
      zh = fmod(90*time, 360.0);
      glutPostRedisplay();
   }
}

/*
 *  Main entry point.
 *  This code is borrowed from the ex13.c in-class example.
 */
int main(int argc, char* argv[])
{
   // Initialize glut.
   glutInit(&argc, argv);

   // Create 500 x 500 window with true color rgb, z buffering and double buffer enabled.
   glutInitWindowSize(500, 500);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutCreateWindow("Jeff Colgan");

#ifdef USEGLEW
   if(glewInit() != GLEW_OK) Fatal("Error initializing GLEW\n");
#endif

   // Tell glut to use display, reshape, special, key and idle functions as the display function,
   // the reshape fucntion, the special function, the keyboard function and the idle function respectively.
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);

   // Load textures.
   textures[0] = LoadTexBMP("concrete.bmp");
   textures[1] = LoadTexBMP("Dirt.bmp");

   // Check for errors and pass control to glut.
   ErrCheck("init");
   glutMainLoop();

   return 0;
}