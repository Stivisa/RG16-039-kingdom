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

//Teksture
extern unsigned int textures[17];
extern int currentTexture;
extern int currentTextureSelected;


//vojnici
extern int soldierObj;
extern soldier s;

//kocka
extern GLfloat cube_v[][3];