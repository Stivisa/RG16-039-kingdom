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

//funkcije za crtanje
extern int axes;
extern int grid;
extern int vals;
extern int showAttackRadius;

//font
extern GLvoid *fontStyle;

//kordinate za mis
extern int mouseX, mouseY, mouseZ;

//Teksture
extern unsigned int textures[17];
extern int currentTexture;
extern int currentTextureSelected;
extern int backgrounds[6];

//vojnici
extern int soldierObj;
extern soldier s;
extern wave waves[DEF_LAST_WAVE];
extern soldier soldiers[DEF_MINION_PER_WAVE_SIZE];

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

//Pucnjevi i detekcija udara
extern int showCollisionDetection;
extern int lastShot;
extern shot shots[200];

//Animacija
extern int gameStarted;
extern int gamePaused;
extern int gameSpeed;
extern int moveLightB;
extern int lightPh;
extern int moveTowerTopsB;
extern int towerTh;

//Podaci o igri vazni za korisnika
extern char *info;
extern int lives;
extern int money;
extern int scrolls;
extern int score;
extern int waveNumber;
extern int lastWave;



//kule
extern tower default_towers[6];
extern tower tower_data[16];
extern point preview_points[DEF_CURRENT_OBJS_SIZE];
extern int preview;
extern int objectSelected;
extern int lastCurrentObject;
extern int renderMode;
extern int objectPicked;
extern int currentRed;
extern int currentGreen;
extern int currentBlue;
extern char *currentTowerName;
extern int currentTowerRange;
extern int currentTowerDamage;
extern int currentTowerFireRate;
extern int currentTowerCost;
extern char *currentTowerDescription;
extern tower towers[DEF_CURRENT_OBJS_SIZE];
extern tower preview_tower;
extern int towerTh;

//Senke
extern float N[];
extern float E[];
