/*
*  CSCI-4229: Computer Graphics, Homework 2 Lorenz Attractor Program
*  Created by Jeff Colgan, 09/11/2021.
* 
*  Program to trace the path of the lorenz attractor algorithm provided in
*  the assignment statement.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/glut.h>
#endif

#ifndef RES
#define RES 1
#endif

// Globals.
int th = 0;         // View angle azimuth.
int ph = 0;         // View angle elevation.
int mode = 1;       // Lorenz parameter currently displayed/modifyable.
double dim = 2;     // Orthogonal box dimension.
double s = 10;      // Lorenz Parameter: Sigma Value, default = 10.
double b = 2.6666;  // Lorenz Parameter: Geometric Factor, default = 8/3.
double r = 28;      // Lorennz Parameter: Rayleigh Number, default = 28.

// Max string length for Print function.
#define LENGTH 8192

/*
 *  Function to output raster text.
 */
void Print(const char* format, ...)
{
   char buff[LENGTH];
   char* ch=buff;

   // Converts function parameters into a character string.
   va_list args;
   va_start(args,format);
   vsnprintf(buff,LENGTH,format,args);
   va_end(args);

   // Output characters at the current raster position.
   while(*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

/*
 *  Function prints an error message to stderr and terminates application with exit status 1.
 */
void Fatal(const char* format, ...)
{
   va_list args;
   va_start(args,format);
   vfprintf(stderr,format,args);
   va_end(args);
   exit(1);
}

/*
 *  Function to check for gl errors. If errors are reported by glGetError, print to stderr.
 */
void ErrCheck(const char* where)
{
   int err = glGetError();
   if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}

/*
 *  Display the Lorenz attractor scene. 
 */
void display()
{
   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();

   glRotated(ph, 1, 0, 0);
   glRotated(th, 0, 1, 0);

   // Initial values for x, y, z, dt.
   double x = 1;
   double y = 1;
   double z = 1;
   double dt = 0.001;

   // Set color to red, and connect the vertices generated by lorenz attractor algorithm.
   glColor3f(1, 0, 0);
   glBegin(GL_LINE_STRIP);
   glVertex3d(x*0.02, y*0.02, z*0.02);

   // Lorenz attractor code from provided c file, modified to draw vertices at the generated
   // coordinate points and connect them with line strips.
   for (int i = 0; i < 50000; i++)
   {
      double dx = s * (y - x);
      double dy = x * (r - z) - y;
      double dz = x * y - b * z;

      x += dt * dx;
      y += dt * dy;
      z += dt * dz;

      glVertex3d(x*0.02, y*0.02, z*0.02);
   }
   glEnd();

   // Draw the x, y, z axes in white
   glColor3f(1, 1, 1);
   glBegin(GL_LINES);
   glVertex3d(0, 0, 0);
   glVertex3d(1, 0, 0);
   glVertex3d(0, 0, 0);
   glVertex3d(0, 1, 0);
   glVertex3d(0, 0, 0);
   glVertex3d(0, 0, 1);
   glEnd();

   // Label x, y, z axes.
   glRasterPos3d(1, 0, 0);
   Print("X");
   glRasterPos3d(0, 1, 0);
   Print("Y");
   glRasterPos3d(0, 0, 1);
   Print("Z");

   // Set raster position.
   glWindowPos2i(5, 5);

   // Print current sigma value if mode==1.
   if (mode == 1)
   {
      Print("Sigma Value=%8.4lf", s);
   }
   // Print current Geometric factor if mode==2.
   else if (mode == 2)
   {
      Print("Geometric Factor=%8.4lf", b);
   }
   // Print current Rayleigh Number if mode==3.
   else if (mode == 3)
   {
      Print("Rayleigh Number=%8.4lf", r);
   }

   // Check for errors, flush and swap buffers.
   ErrCheck("Display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this function when a key is pressed.
 */
void key(unsigned char key, int x, int y)
{
   // Exit application if "escape" key pressed.
   if (key == 27)
   {
      exit(0);
   }

   // Reset rotations if 0 key pressed.
   else if (key == '0')
   {
       th = ph = 0;
   }

   // If user presses the 's' key, change to mode 1.
   else if (key == 's')
   {
      mode = 1;
   }

   // If user presses the 'b' key, change to mode 2.
   else if (key == 'b')
   {
      mode = 2;
   }

   // If user presses the 'r' key, change to mode 3.
   else if (key == 'r')
   {
      mode = 3;
   }

   // Increase the specified lorenz value if '+' key is pressed.
   else if(key == '+')
   {
      switch(mode)
      {
         case 1:
            s = (s >= 200) ? 0 : s + 1;
            break;
         case 2:
            b = (b >= 99.9902) ? -24.9973 : b + .3333;
            break;
         case 3:
            r = (r >= 89) ? 0 : r + 1;
            break;
      }
   }

   // Decrease the specified lorenz value if '-' key is pressed.
   else if(key == '-')
   {
      switch(mode)
      {
         case 1:
            s = (s <= -250) ? 90 : s - 1;
            break;
         case 2:
            b = (b <= -24.9973) ? 99.9902 : b - 0.3333;
            break;
         case 3:
            r = (r <= 0) ? 89 : r - 1;
            break;
      }
   }

   // If user presses 'd' key, reset all lorenz equation parameters to their default values.
   else if (key == 'd')
   {
      s = 10;
      b = 2.6666;
      r = 28;
   }

   // Redraw window.
   glutPostRedisplay();
}

/*
 *  GLUT calls this function when the user presses an arrow key.
 */
void special(int key, int x, int y)
{
   // Rotate theta by -5 if left arrow key pressed.
   if (key == GLUT_KEY_LEFT)
   {
      th -= 5;
   }
   // Rotate theta by +5 if right arrow key pressed.
   else if (key == GLUT_KEY_RIGHT)
   {
      th += 5;
   }
   // Rotate phi by +5 if up arrow key pressed.
   else if (key == GLUT_KEY_UP)
   {
      ph += 5;
   }
   // Rotate phi by -5 if down arrow key pressed.
   else if (key == GLUT_KEY_DOWN)
   {
      ph -= 5;
   }

   // Keep theta and phi within range [0,360].
   th %= 360;
   ph %= 360;

   // Redraw window.
   glutPostRedisplay();
}

/*
 *  Function called when window is resized. 
 */
void reshape(int width,int height)
{
   // Set the current viewport to new window size.
   glViewport(0,0, RES*width,RES*height);
   // Tell OpenGL to manupulate the projection matrix.
   glMatrixMode(GL_PROJECTION);

   // Undo previous transformations.
   glLoadIdentity();

   // Adjust orthogonal projection box for window's aspect ratio.
   double aspect = (height>0) ? (double)width/height : 1;
   glOrtho(-aspect*dim,+aspect*dim, -dim,+dim, -dim,+dim);
   
   // Manipulate the model view matrix and undo previous transforms.
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

/*
 *  Main entry point.  Start up GLUT and tell it what to do.
 */
int main(int argc,char* argv[])
{
   // Initialize GLUT, process command line parameters.
   glutInit(&argc, argv);

   // Initialize display mode with double-buffered, true color window.
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

   // Request and create 500 x 500 pixel window.
   glutInitWindowSize(500, 500);
   glutCreateWindow("Jeff Colgan");

#ifdef USEGLEW
   // Initialize GLEW (if applicable).
   if (glewInit() != GLEW_OK) Fatal("Error! Glew failed to initialize!");
#endif

   // Instruct GLUT to call display when the scene should be drawn.
   glutDisplayFunc(display);

   // Instruct GLUT to call reshape when the window is resized.
   glutReshapeFunc(reshape);

   // Instruct GLUT to call special when an arrow key is pressed.
   glutSpecialFunc(special);

   // Instruct GLUT to call key when a key is pressed.
   glutKeyboardFunc(key);

   // Enter GLUT main loop for user interaction.
   glutMainLoop();
   return 0;
}