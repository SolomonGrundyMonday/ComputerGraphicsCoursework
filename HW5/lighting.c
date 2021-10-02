#include "utility.h"
#include "shapes.h"

int th = 45;
int ph = 45;
int mode = 0;
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

void display()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);

   glLoadIdentity();

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

   Rocket(0.75, 0.9, 0.75, 1.0, 1.0, 1.0, 0);
   Box(0.0, -0.1, 0.0, 3.0, 0.1, 3.0, 0);

   glColor3f(0.2, 1.0, 0.2);
   Rover(1.3, 0.225, 1.3, 0.4, 0.15, 0.1, 0);

   glColor3f(1.0, 0.0, 0.0);
   Rover(0.0, 0.225, 1.2, 0.4, 0.15, 0.1, 90);

   glColor3f(0.0, 0.0, 1.0);
   Rover(-0.5, 0.95, -0.1, 0.8, 0.6, 0.5, 0);

   Rocket(0.4, 0.5, 0.4, 0.4, 0.4, 0.4, 90);

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

   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

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

   glutPostRedisplay();
}

void reshape(int width, int height)
{
   glViewport(0, 0, RES*width, RES*height);
   asp = (height > 0) ? (double)width/height : 1;
   Projection();
}

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

   glutMainLoop();

   return 0;
}