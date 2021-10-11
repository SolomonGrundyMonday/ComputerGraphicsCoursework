/*
 *  Definitions for helper functions to draw 3D objects.
 *  CSCI-4229 Homework 6: Textures and Lighting.
 *  Updated by Jeff Colgan, 10/10/2021. 
 */
#include "shapes.h"

// Constants for lighting and loaded textures.
const int shiny = 0;
const float emission = 0;
const float black[] = {0.0, 0.0, 0.0, 1.0};
const float white[] = {1.0, 1.0, 1.0, 1.0};
const float orange[] = {1.0, 0.5, 0.0, 1.0};
const float grey[] = {0.729, 0.690, 0.686, 1.0};
const float yellow[] = {1.0, 1.0, 0.0, 1.0};
const float red[] = {0.8, 0.0, 0.1, 0.0};
unsigned int axelTextures[4];
unsigned int bodyTexture;
unsigned int rocketTextures[3];

/*
 *  Load textures function.
 *  This function loads the various textures required for my complex
 *  3D objects. 
 *  Use of LoadTexBMP borrowed from ex14.c of the in-class examples. 
 */
void LoadTextures()
{
   // Load required textures for wheel axel objects.
   axelTextures[0] = LoadTexBMP("hubcap.bmp");
   axelTextures[1] = LoadTexBMP("tread.bmp");
   axelTextures[2] = LoadTexBMP("innertire.bmp");
   axelTextures[3] = LoadTexBMP("metal.bmp");

   // Load texture for placholder texture for rover body.
   bodyTexture = LoadTexBMP("roverbody.bmp");

   // Load textures for rocket objects.
   rocketTextures[0] = LoadTexBMP("rustymetal.bmp");
   rocketTextures[1] = LoadTexBMP("tailfinsteel.bmp");
   rocketTextures[2] = LoadTexBMP("fire.bmp");
}

/* 
 *  Draw triangles for computing vertex normals of a 3D object
 *  composed of triangles.
 *  The code for this function is borrowed from ex13.c of the 
 *  in-class examples.
 */ 
void DrawTriangle(vtx A, vtx B, vtx C)
{
   // Compute A - B.
   float dx0 = B.x - A.x;
   float dy0 = B.y - A.y;
   float dz0 = B.z - A.z;

   // Compute C - A.
   float dx1 = C.x - B.x;
   float dy1 = C.y - B.y;
   float dz1 = C.z - B.z;

   // Compute Normal.
   float Nx = dy0 * dz1 - dy1 * dz0;
   float Ny = dz0 * dx1 - dz1 * dx0;
   float Nz = dx0 * dy1 - dx1 * dy0;

   // Draw the triangle, specify texture coordinates.
   glNormal3f(Nx, Ny, Nz);
   glBegin(GL_TRIANGLES);
   glTexCoord2f(0.0, 0.0); glVertex3f(B.x, B.y, B.z);
   glTexCoord2f(1.0, 0.0); glVertex3f(A.x, A.y, A.z);
   glTexCoord2f(1.0, 1.0); glVertex3f(C.x, C.y, C.z);
   glEnd();
}

/*
 *  Function draws the line segments outlining the tail fin of Rocket objects.
 *  This allows the tail fins to be seen from the sides/back. 
 *  I made this into it's own function from previous assignments to reduce clutter
 *  in the Rocket function.
 */
void DrawTailFinOutline(float y, float z, float yOffset, float zOffset)
{
   float finTip = -0.1;
   float finEdge = -0.3;
   float fuselageBase = -0.50;

   // Draw lines outlining the tail fin and specify the texture coordinates.
   glBegin(GL_LINES);
   glTexCoord1f(0.0); glVertex3f(finTip, y, z);
   glTexCoord1f(1.0); glVertex3f(finEdge, y + yOffset, z + zOffset);
   glTexCoord1f(0.0); glVertex3f(fuselageBase, y, z);
   glTexCoord1f(1.0); glVertex3f(fuselageBase, y + yOffset, z + zOffset);
   glTexCoord1f(0.0); glVertex3f(finEdge, y + yOffset, z + zOffset);
   glTexCoord1f(1.0); glVertex3f(fuselageBase, y + yOffset, z + zOffset);
   glEnd();
}

// Order to compute normals for the top triangles of the tail fins.
const tri finTop[] =
{
   {1, 0, 2}, {4, 3, 5}, {7, 6, 8}, {10, 9, 11}
};

// Vertices for the top triangles of the tail fins.
const vtx finTopVert[] =
{
   {-0.1, 0.025, 0.025}, {-0.3, 0.025, 0.025}, {-0.3, 0.025 + 0.1, 0.025 + 0.1},
   {-0.1, -0.025, -0.025}, {-0.3, -0.025, -0.025}, {-0.3, -0.025 - 0.1, -0.025 - 0.1},
   {-0.1, -0.025, 0.025}, {-0.3, -0.025, 0.025}, {-0.3, -0.025 - 0.1, 0.025 + 0.1},
   {-0.1, 0.025, -0.025}, {-0.3, 0.025, -0.025}, {-0.3, 0.025 + 0.1, -0.025 - 0.1}
};

// Order to compute normals for the rectangle components of the tail fins.
const tri finBase[] =
{
   {0, 1, 2}, {3, 2, 1}, {6, 5, 4}, {5, 6, 7}, {10, 9, 8}, {9, 10, 11},
   {14, 13, 12}, {13, 14, 15}
};

// Vertices for the rectangle components of the tail fins.
const vtx finBaseVert[] =
{
   {-0.3, 0.025, 0.025}, {-0.3, 0.025 + 0.1, 0.025 + 0.1},
   {-0.50, 0.025, 0.025}, {-0.50, 0.025 + 0.1, 0.025 + 0.1},
   {-0.3, -0.025, -0.025}, {-0.3, -0.025 - 0.1, -0.025 - 0.1},
   {-0.50, -0.025, -0.025}, {-0.50, -0.025 - 0.1, -0.025 - 0.1},
   {-0.3, -0.025, 0.025}, {-0.3, -0.025 - 0.1, 0.025 + 0.1},
   {-0.50, -0.025, 0.025}, {-0.50, -0.025 - 0.1, 0.025 + 0.1},
   {-0.3, 0.025, -0.025}, {-0.3, 0.025 + 0.1, -0.025 - 0.1},
   {-0.50, 0.025, -0.025}, {-0.50, 0.025 + 0.1, -0.025 - 0.1}
};

/*
 *  Draw the wheel axel and attached wheels.  
 */
void WheelAxel(double x, double y, double z, double dx, double dy,
               double dz, double theta)
{
   // Apply color, emission, ambient, diffuse, specular and shininess lighing qualities.
   glColor4fv(grey);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, grey);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

   glPushMatrix();

   // Apply tranformations.
   glTranslated(x, y, z);
   glRotated(theta, 0, 0, 1);
   glScaled(dx, dy, dz);

   // Apply hubcap texture to outer wheel walls.
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D, axelTextures[0]);

   // Compute normals and draw the left outer wheel wall.
   glNormal3f(0.0, 0.0, -0.2);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5); glVertex3f(0.0, 0.0, 0.2);
   
   // Basic structure for applying hubcap texture borrowed from ex19.c in-class example.
   for (int i = 0; i <= 360; i += 30)
   {
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i)+0.5); glVertex3f(0.05 * Cos(i), 0.05 * Sin(i), 0.2);
   }
   glEnd();

   // Compute normal and draw the right outer wheel wall
   glNormal3f(0.0, 0.0, 0.45);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5); glVertex3f(0.0, 0.0, 0.45);

   // Basic structure for applying hubcap texture borrowed from ex19.c in-class example.
   for (int i = 0; i <= 360; i += 30)
   {
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5); glVertex3f(0.05 * Cos(i), 0.05 * Sin(i), 0.45);
   }
   glEnd();

   // Compute normals, apply tread texture and draw the right wheel tread.
   glBindTexture(GL_TEXTURE_2D, axelTextures[1]);
   glBegin(GL_QUAD_STRIP);

   for(int i = 0; i <= 12; i++)
   {
      // Make sure that exactly one copy of the tread texture is applied to each discrete
      // rectangle comprising the wheel tread.
      int theta = i * 30;
      glNormal3f(0.05 * Cos(theta), 0.05 * Sin(theta), 0.45);
      glTexCoord2f(0, i % 2); glVertex3f(0.05 * Cos(theta), 0.05 * Sin(theta), 0.45);
      glTexCoord2f(1, i % 2); glVertex3f(0.05 * Cos(theta), 0.05 * Sin(theta), 0.4);
   }
   glEnd();

   // Compute normals and draw the left wheel tread.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      // Make sure that exactly one copy of the tread texture is applied to each discrete
      // rectangle comprising the wheel tread.
      int theta = i * 30;
      glNormal3f(0.05 * Cos(theta), 0.05 * Sin(theta), -0.2);
      glTexCoord2f(0, i % 2); glVertex3f(0.05 * Cos(theta), 0.05 * Sin(theta), 0.25);
      glTexCoord2f(1, i % 2); glVertex3f(0.05 * Cos(theta), 0.05 * Sin(theta), 0.2);
   }
   glEnd();

   // Compute normal and apply inner tire texture to inner right wheel wall.
   glNormal3f(0.0, 0.0, -0.4);
   glBindTexture(GL_TEXTURE_2D, axelTextures[2]);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5); glVertex3f(0.0, 0.0, 0.4);

   // Basic structure for applying inner tire texture borrowed from ex19.c in-class example.
   for (int i = 0; i <= 360; i += 30)
   {
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5); glVertex3f(0.05 * Cos(i), 0.05 * Sin(i), 0.4);
   }
   glEnd();

   // Compute normal and apply innertire texture to inner left wheel wall.
   glNormal3f(0.0, 0.0, 0.25);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5); glVertex3f(0.0, 0.0, 0.25);

   // Basic structure for applying inner tire texture borrowed from ex19.c in-class example.
   for (int i = 0; i <= 360; i += 30)
   {
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5); glVertex3f(0.05 * Cos(i), 0.05 * Sin(i), 0.25);
   }
   glEnd();

   // Apply the axel texture to the wheel axel.
   glBindTexture(GL_TEXTURE_2D, axelTextures[3]);
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      // Ensure that exactly one copy of the axel texture is applied to each discrete component
      // rectangle.
      int theta = i * 30;
      glNormal3f(0.01 * Cos(theta), 0.01 * Cos(theta), 0.25);
      glTexCoord2f(0, i % 2); glVertex3f(0.01 * Cos(theta), 0.01 * Sin(theta), 0.25);
      glTexCoord2f(1, i % 2); glVertex3f(0.01 * Cos(theta), 0.01 * Sin(theta), 0.4);
   }
   glEnd();

   glDisable(GL_TEXTURE_2D);

   glPopMatrix();
}

/*
 *  Draw a Rover object.  For now, it is a simble cuboid
 *  with attached wheels and wheel axels.  I plan on
 *  further iteration to make a more complex object,
 *  perhaps for the final project. 
 */
void Rover(double x, double y, double z, double dx,
           double dy, double dz, double theta)
{
   glPushMatrix();

   // Apply transformations.
   glTranslated(x, y, z);
   glRotated(theta, 0, 1, 0);
   glScaled(dx, dy, dz);

   // Draw the body, and apply the body texture.
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, bodyTexture);
   Box(0.0, 0.0, 0.0, 1.25, 1.0, 1.0, 0);
   glDisable(GL_TEXTURE_2D);

   // Draw front and back wheel axels in grey.
   glColor3f(0.729, 0.690, 0.686);
   WheelAxel(-0.8, -1.1, -4.25, 5.0, 10.0, 13.0, 0);
   WheelAxel(0.8, -1.1, -4.25, 5.0, 10.0, 13.0, 0);
   glPopMatrix();
}

/*
 *  Draw a rocket object. 
 */
void Rocket(double x, double y, double z, double dx, double dy,
            double dz, double theta, double gamma, double omega)
{
   // Locals for computing vertices.
   double circumference = 0.05;
   double radius = circumference * 0.5;

   glEnable(GL_TEXTURE_2D);

   // Apply color, emission, ambient, diffuse, specular and shininess lighting qualities.
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

   glPushMatrix();

   // Apply transformations.
   glTranslated(x, y, z);
   glScaled(dx, dy, dz);
   glRotated(theta, 0, 0, 1);
   glRotated(gamma, 1, 0, 0);
   glRotated(omega, 0, 1, 0);

   // Set state machine to white color to avoid unwanted tinting of textures.
   glColor3f(1, 1, 1);
   
   // Apply rusty metal texture for the nose cone and fuselage of rocket.
   glBindTexture(GL_TEXTURE_2D, rocketTextures[0]);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

   // Compute normals, draw the nose cone and specify texture coordinates.
   glNormal3f(0.5, 0.0, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.5, 0.0, 0.0);

   for (int i = 0; i <= 360; i += 30)
   {
      glNormal3f(0.2, Cos(i), Sin(i));
      glTexCoord2f(0.5 * Cos(i) + 0.5, 0.5 * Sin(i) + 0.5); glVertex3f(0.2, 0.05 * Cos(i), 0.05 * Sin(i));
   }
   glEnd();

   // Compute normals, draw fuselage and apply texture coordinates.
   glBegin(GL_QUAD_STRIP);
   for (int i = 0; i <= 12; i++)
   {
      int theta = i * 30;
      glNormal3f(0.2, Cos(theta), Sin(theta)); 
      glTexCoord2f(0, i % 2); glVertex3f(0.2, 0.05 * Cos(theta), 0.05 * Sin(theta));
      glTexCoord2f(1, i % 2); glVertex3f(-0.5, 0.05 * Cos(theta), 0.05 * Sin(theta));
   }
   glEnd();

   // Apply fire texture to the thruster cone.
   glBindTexture(GL_TEXTURE_2D, rocketTextures[2]);
   glNormal3f(-0.7, 0.0, 0.0);

   // Draw thruster cone, compute normal and specify texture coordinates.
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.0, 0.0); glVertex3f(-0.7, 0.0, 0.0);

   for (int i = 0; i <= 12; i++)
   {
      float theta = i * 30;
      glNormal3f(-0.5, Cos(theta), Sin(theta));
      glTexCoord2f(1.0, i % 2); glVertex3f(-0.5, 0.05 * Cos(theta), 0.05 * Sin(theta));
   }
   glEnd();

   // Apply metal texture to tail fins.
   glBindTexture(GL_TEXTURE_2D, rocketTextures[1]);

   // Compute normals and draw tail fins.
   for (int i = 0; i < 4; i++)
   {
      glEnable(GL_CULL_FACE);
      glCullFace(GL_FRONT);
      DrawTriangle(finTopVert[finTop[i].A], finTopVert[finTop[i].B], finTopVert[finTop[i].C]);
      glDisable(GL_CULL_FACE);
      DrawTriangle(finTopVert[finTop[i].C], finTopVert[finTop[i].B], finTopVert[finTop[i].A]);
   }

   // Draw the bottom rectangles of the tail fins.
   for (int i = 0; i < 7; i += 2)
   {
      // This bit of code is slightly refined from last week's assignment, since my DrawQuad function
      // was essentially doing the same thing as DrawTriangles, I removed that function and just used DrawTriangles.
      glEnable(GL_CULL_FACE);
      glCullFace(GL_FRONT);
      DrawTriangle(finBaseVert[finBase[i].C], finBaseVert[finBase[i].B], finBaseVert[finBase[i].A]);
      DrawTriangle(finBaseVert[finBase[i+1].C], finBaseVert[finBase[i+1].B], finBaseVert[finBase[i+1].A]);

      glDisable(GL_CULL_FACE);
      DrawTriangle(finBaseVert[finBase[i].A], finBaseVert[finBase[i].B], finBaseVert[finBase[i].C]);
      DrawTriangle(finBaseVert[finBase[i+1].A], finBaseVert[finBase[i+1].B], finBaseVert[finBase[i+1].C]);
   }
   glDisable(GL_TEXTURE_2D);

   // Apply tail fin texture to the one-dimensional lines for the edges of the tail fins.
   glEnable(GL_TEXTURE_1D);

   // Draw lines so tail fins are visible from sides/front/back.
   DrawTailFinOutline(radius, radius, 0.1, 0.1);
   DrawTailFinOutline(-radius, -radius, -0.1, -0.1);
   DrawTailFinOutline(-radius, radius, -0.1, 0.1);  
   DrawTailFinOutline(radius, -radius, 0.1, -0.1); 

   glDisable(GL_TEXTURE_1D);

   glPopMatrix();
}

/*
 *  Draw a cuboid object for use as a floor (and walls when
 *  we introduce textures). 
 */
void Box(double x, double y, double z, double dx, double dy,
         double dz, double theta)
{
   float X = 1.0;
   float Z = 1.0;

   // Scaling parameters determine if/how many times to repeat textures across
   // Box object faces.
   if (dx > 1)
      X = dx;

   if (dz > 1)
      Z = dz;

   // Apply shininess, specular and emission qualities for a box object.
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

   glPushMatrix();

   // Apply transformations.
   glTranslated(x, y, z);
   glRotated(theta, 0, 1, 0);
   glScaled(dx, dy, dz);

   // Mirror repeat textures across large faces.
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);

   // Right face texture coordinates and corresponding vertices.
   glNormal3f(0.0, 0.0, 1.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 1.0, 1.0);
   glTexCoord2f(0.0, X); glVertex3f(1.0, 1.0, 1.0);
   glTexCoord2f(X, 0.0); glVertex3f(1.0, -1.0, 1.0);
   glTexCoord2f(X, X); glVertex3f(-1.0, -1.0, 1.0);
   glEnd();

   // Left face texture coordinates and corresponding vertices.
   glNormal3f(0.0, 0.0, -0.5);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(1.0, 1.0, -1.0);
   glTexCoord2f(0.0, X); glVertex3f(-1.0, 1.0, -1.0);
   glTexCoord2f(X, X); glVertex3f(-1.0, -1.0, -1.0);
   glTexCoord2f(X, 0.0); glVertex3f(1.0, -1.0, -1.0);
   glEnd();

   // Front face texture coordinates and corresponding vertices.
   glNormal3f(-0.5, 0.0, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 1.0, 1.0);
   glTexCoord2f(0.0, Z); glVertex3f(-1.0, -1.0, 1.0);
   glTexCoord2f(Z, Z); glVertex3f(-1.0, -1.0, -1.0);
   glTexCoord2f(Z, 0.0); glVertex3f(-1.0, 1.0, -1.0);
   glEnd();

   // Back face texture coordinates and corresponding vertices.
   glNormal3f(0.5, 0.0, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(1.0, 1.0, 1.0);
   glTexCoord2f(0.0, Z); glVertex3f(1.0, -1.0, 1.0);
   glTexCoord2f(Z, Z); glVertex3f(1.0, -1.0, -1.0);
   glTexCoord2f(Z, 0.0); glVertex3f(1.0, 1.0, -1.0);
   glEnd();

   // Top face texture coordinates and corresponding vertices.
   glNormal3f(0.0, 0.5, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(1.0, 1.0, 1.0);
   glTexCoord2f(0.0, X); glVertex3f(1.0, 1.0, -1.0);
   glTexCoord2f(Z, X); glVertex3f(-1.0, 1.0, -1.0);
   glTexCoord2f(Z, 0.0); glVertex3f(-1.0, 1.0, 1.0);
   glEnd();

   // Bottom face texture coordinates and corresponding vertices.
   glNormal3f(0.0, -0.5, 0.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 1.0);
   glTexCoord2f(0.0, X); glVertex3f(1.0, -1.0, -1.0);
   glTexCoord2f(Z, X); glVertex3f(-1.0, -1.0, -1.0);
   glTexCoord2f(Z, 0.0); glVertex3f(-1.0, -1.0, 1.0);
   glEnd();

   glPopMatrix();
}