#include "utility.h"
#include "shapes.h"

int th = 45;
int ph = 45;
int zh = 90;
int mode = 0;
int local = 0;
double dim = 3.0;
double asp = 1.0;
double Ex = -3.0;
double Ey = 0.4;
double Ez = 3.0;
double Upx = 0.0;
double Upy = 1.0;
double Upz = 0.0;
double Cx = 3.3;
double Cy = 0.4;
double Cz = -3.3;
float distance = 3;
float lightElev = 1;
int autoLight = 1;

/*
 *  MARKED FOR REMOVAL, USE LIBRARY FUNCTION INSTEAD!!!
 */
void Projection()
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   if (mode == 1 || mode == 2)
   {
      gluPerspective(45, asp, dim / 16, 16 * dim);
   }
   else
   {
      glOrtho(-asp * dim, asp * dim, -dim, dim, -dim, dim);
   }

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

/*
 *  Redraw the scene. 
 */
void display()
{

   // Erase window, depth buffer and enable z-buffering.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);

   glLoadIdentity();

   // Determine projection and set eye position based on the mode variable.
   if (mode == 0)
   {
      glRotatef(ph, 1, 0, 0);
      glRotatef(th, 0, 1, 0);
   }
   else if (mode == 1)
   {
      gluLookAt(-5.0, 6.0, 5.0, 0.0, 0.0, 0.0, 0, 1, 0);
   }
   else
   {
      Turn(&Cx, &Cz, dim, th);
      gluLookAt(Ex, Ey, Ez, Cx + Ex, Cy, Cz + Ez, Upx, Upy, Upz);
   }

   glShadeModel(GL_SMOOTH);

   // Need to enable manual/automatic control of light source here.
   if (1)
   {
      float Ambient[] = {0.1, 0.1, 0.1, 1.0};
      float Diffuse[] = {0.5, 0.5, 0.5, 1.0};
      float Specular[] = {0.0, 0.0, 0.0, 1.0};
      float Pos[] = {distance * Cos(zh), 1.5, distance * Sin(zh), 1.0};

      glColor3f(1, 1, 1);

      if (autoLight)
      {
         Ball(Pos[0], Pos[1], Pos[2], 0.1);
      }
      else
      {
         Ball(0, 2.0, 0, 0.1);
      }

      glEnable(GL_NORMALIZE);
      glEnable(GL_LIGHTING);

      glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 0);
      glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

      glEnable(GL_COLOR_MATERIAL);
      glEnable(GL_LIGHT0);

      glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
      glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
      glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
      glLightfv(GL_LIGHT0, GL_POSITION, Pos);
   }

   // Generate objects to populate the scene.
   Rocket(0.75, 0.9, 0.75, 1.0, 1.0, 1.0, 90);
   Box(0.0, -0.1, 0.0, 3.0, 0.1, 3.0, 0);
   glColor3f(0.2, 1.0, 0.2);
   //Rover(1.3, 0.225, 1.3, 0.4, 0.15, 0.1, 0);
   glColor3f(1.0, 0.0, 0.0);
   //Rover(0.0, 0.225, 1.2, 0.4, 0.15, 0.1, 90);
   glColor3f(0.0, 0.0, 1.0);
   Rover(-0.5, 0.95, -0.1, 0.8, 0.6, 0.5, 0);
   //Rocket(0.4, 0.5, 0.4, 0.4, 0.4, 0.4, 90);

   // Raster text for user.
   glWindowPos2i(5, 5);
   switch(mode)
   {
      case 0:
         Print("Mode = Orthogonal Projection, slanted overhead.");
         break;
      case 1:
         Print("Mode = Perspective Projection, slanted overhead.");
         break;
      case 2:
         Print("Mode = First person navigation.");
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
   if (mode == 2)
   {
      if (key == GLUT_KEY_UP)
      {
         MoveForward(&Ex, &Ez, th);
      }
      else if (key == GLUT_KEY_DOWN)
      {
         MoveBackward(&Ex, &Ez, th);
      }
      else if (key == GLUT_KEY_RIGHT)
      {
         th += 5;
         th %= 360;
      }
      else if (key == GLUT_KEY_LEFT)
      {
         th -= 5;
         th %= 360;
      }
   }

   Projection();
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
            th = 45;
            ph = 45;
            Projection();
            break;
      }
   }
   else if (key == 'r' || key == 'R')
   {
      if (mode == 2)
      {
         ResetPosition(&Ex, &Ey, &Ez, &Cx, &Cy, &Cz, &dim, &th, &ph);
         Projection();
      }
   }
   else if (key == 'l' || key == 'L')
   {
      autoLight = (autoLight == 1) ? 0 : 1; 
   }

   glutPostRedisplay();
}

/*
 *  Called when the window is resized.
 */
void reshape(int width, int height)
{
   glViewport(0, 0, RES*width, RES*height);
   asp = (height > 0) ? (double)width/height : 1;
   Projection();
}

/*
 *  Called when there is nothing else to do. 
 */
void idle()
{
   if (autoLight)
   {
      double time = glutGet(GLUT_ELAPSED_TIME)/1000.0;
      zh = fmod(90*time, 360.0);
      glutPostRedisplay();
   }
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
   if(glewInit() != GLEW_OK) Fatal("Error initializing GLEW\n");
#endif

   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);

   ErrCheck("init");
   glutMainLoop();

   return 0;
}