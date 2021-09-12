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

int th=0;
int ph=0;
double dim=2;

#define LENGTH 8192
void Print(const char* format, ...)
{
   char buff[LENGTH];
   char* ch=buff;

   va_list args;
   va_start(args,format);
   vsnprintf(buff,LENGTH,format,args);
   va_end(args);

   while(*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

void Fatal(const char* format, ...)
{
   va_list args;
   va_start(args,format);
   vfprintf(stderr,format,args);
   va_end(args);
   exit(1);
}

void ErrCheck(const char* where)
{
   int err = glGetError();
   if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}

void display()
{
   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();

   glRotated(ph,1,0,0);
   glRotated(th,0,1,0);

   glColor3f(1,1,1);
   glBegin(GL_LINES);
   glVertex3d(0,0,0);
   glVertex3d(1,0,0);
   glVertex3d(0,0,0);
   glVertex3d(0,1,0);
   glVertex3d(0,0,0);
   glVertex3d(0,0,1);
   glEnd();

   glRasterPos3d(1,0,0);
   Print("X");
   glRasterPos3d(0,1,0);
   Print("Y");
   glRasterPos3d(0,0,1);
   Print("Z");

   glWindowPos2i(5,5);

   ErrCheck("Display");

   glFlush();
   glutSwapBuffers();
}

void key(unsigned char key, int x, int y)
{
   if (key == 27)
   {
      exit(0);
   }
   else if (key == '0')
   {
       th = ph = 0;
   }
   glutPostRedisplay();
}

void special(int key, int x, int y)
{
   if (key == GLUT_KEY_LEFT)
   {
      th -= 5;
   }
   else if (key == GLUT_KEY_RIGHT)
   {
      th += 5;
   }
   else if (key == GLUT_KEY_UP)
   {
      ph += 5;
   }
   else if (key == GLUT_KEY_DOWN)
   {
      ph += 5;
   }

   th %= 360;
   ph %= 360;

   glutPostRedisplay();
}

void reshape(int width,int height)
{
   glViewport(0,0, RES*width,RES*height);
   glMatrixMode(GL_PROJECTION);

   glLoadIdentity();
   double aspect = (height>0) ? (double)width/height : 1;

   glOrtho(-aspect*dim,+aspect*dim, -dim,+dim, -dim,+dim);
   
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

int main(int argc,char* argv[])
{
   glutInit(&argc, argv);

   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

   glutInitWindowSize(500, 500);

   glutCreateWindow("Jeff Colgan");

#ifdef USEGLEW
   if (glewInit() != GLEW_OK) Fatal("Error! Glew failed to initialize!");
#endif

   glutDisplayFunc(display);

   glutReshapeFunc(reshape);

   glutSpecialFunc(special);

   glutKeyboardFunc(key);

   glutMainLoop();
   return 0;
}