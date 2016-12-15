//standarne biblioteke
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>

//glut biblioteka
#include <GL/glut.h>

//definicije pocetnih vrednosti
#include "defines.h"

//strukture podataka
#include "structs.h"

//protpipi funkcija
#include "prototypes.h"



//Globalne promenljive

//genericke za inicijalizaciju prozora
extern int debug;
extern char *windowName;
extern int windowHeight;
extern int windowWidth;
extern GLuint window, screen, sidebar;

//za projekciju
extern double asp;
extern double dim;
extern int th;
extern int ph;
extern int fov;
extern double ecX;
extern double ecY;
extern double ecZ;

//za crtanje terena
extern int axes;
extern int grid;
extern int vals;

//Teksture
extern unsigned int textures[17];
extern int currentTexture;
extern int currentTextureSelected;
extern int backgrounds[6];

//vojnici
extern int soldierObj;
extern soldier s;

//kocka i putevi
extern GLfloat cube_v[][3];
extern pathCube pathCubes[];
extern pathCube fullPath[];

//svetlost
extern int light;
extern int distance;
extern int ambient;
extern int diffuse;
extern int emission;
extern int specular;
extern int shininess;
extern float shinyvec[1];
extern float lightY;
extern float white[];
extern int lightPh;

extern int renderMode;