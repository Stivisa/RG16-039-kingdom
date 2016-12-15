#include "kingdom_main.h"

// Opste globalne promenljive
char *windowName = "Kindoms Tower Defense";	//Naziv prozora
int windowHeight = DEF_WINDOW_HEIGHT;	//pocetna visina prozora
int windowWidth = DEF_WINDOW_WIDTH;	//pocetna sirina prozora
GLuint window, screen, sidebar;


//Projekcija
double asp = DEF_ASP;		//aspect ration
double dim = DEF_DIM;		//dimenzije kutije
int th = DEF_TH;		//azimuth of view angle
int ph = DEF_PH;		//elevation of view angle
int fov = DEF_FOV;		//field of view for perspective
double ecX = DEF_ECX;		//eye center positon x
double ecY = DEF_ECY;		//eye center positon y
double ecZ = DEF_ECZ;		//eye center postion z

//sta zelimo da crtamo
int axes = DEF_AXES;		// ukljuci/iskljuci axes
int grid = DEF_GRID;		// ukljuci/iskljuci grid
int vals=DEF_VALS;

//teksture
unsigned int textures[17];	//sadrzi nase teksture
int currentTexture = TEX_DEFAULT;	//ako nije postavljeno nista
int currentTextureSelected = TEX_DEFAULT;	//ako nista nije selektovano
int backgrounds[6];

//vojnici
int soldierObj = DEF_SOLDIER_OBJ;
soldier s;

//kocke
GLfloat cube_v[][3]={
  {-1.0,-1.0,-1.0},{+1.0,-1.0,-1.0},{+1.0,+1.0,-1.0},
  {-1.0,+1.0,-1.0},{-1.0,-1.0,+1.0},{+1.0,-1.0,+1.0},
  {+1.0,+1.0,+1.0},{-1.0,+1.0,+1.0}
};

//Svetlost
int light=DEF_LIGHT;          //Ukljuciti svetlost
int distance=DEF_DISTANCE;    //Daljina svetlosti
int ambient=DEF_AMBIENT;      //ambient intensity in %
int diffuse=DEF_DIFFUSE;      // diffuse intensity %
int emission=DEF_EMISSION;    // emission intensity % 
int specular=DEF_SPECULAR;    // specular intensity % 
int shininess=DEF_SHININESS;  //odsjaj
float shinyvec[1]={1};        //vrednost odsjaja
float lightY=DEF_L_Y;         //elevation of light
int lightPh=DEF_L_PH;
float white[]={1,1,1,1};

//definiseme da li nesto renderujemo
int renderMode=DEF_RENDER; 

//definisemo putanju puta koji treba da se iscrta i na kome idu vojnici
pathCube pathCubes[] = {
  {{25,-3,-1},  TEX_STREET1,90, DEF_NORTH},
  {{21,-3,-1},  TEX_STREET1,90, DEF_NORTH}, {{17,-3,-1},  TEX_STREET1,90, DEF_NORTH},
  {{13,-3,-1},  TEX_STREET6,270,DEF_EAST},  {{13,-3,-5},  TEX_STREET2,0,  DEF_EAST},
  {{13,-3,-9},  TEX_STREET2,0,  DEF_EAST},  {{13,-3,-13}, TEX_STREET2,0,  DEF_EAST},
  {{13,-3,-17}, TEX_STREET4,90, DEF_NORTH}, {{9,-3,-17},  TEX_STREET1,90, DEF_NORTH},
  {{5,-3,-17},  TEX_STREET3,180,DEF_WEST},  {{5,-3,-13},  TEX_STREET2,180,DEF_WEST},
  {{5,-3,-9},   TEX_STREET2,180,DEF_WEST},  {{5,-3,-5},   TEX_STREET2,180,DEF_WEST},
  {{5,-3,-1},   TEX_STREET2,180,DEF_WEST},  {{5,-3,3},    TEX_STREET2,180,DEF_WEST},
  {{5,-3,7},    TEX_STREET6,270,DEF_SOUTH}, {{9,-3,7},    TEX_STREET1,270,DEF_SOUTH},
  {{13,-3,7},   TEX_STREET1,270,DEF_SOUTH}, {{17,-3,7},   TEX_STREET4,90, DEF_WEST},
  {{17,-3,11},  TEX_STREET2,0,  DEF_WEST},  {{17,-3,15},  TEX_STREET5,0,  DEF_NORTH},
  {{13,-3,15},  TEX_STREET1,90, DEF_NORTH}, {{9,-3,15},   TEX_STREET1,90, DEF_NORTH},
  {{5,-3,15},   TEX_STREET1,90, DEF_NORTH}, {{1,-3,15},   TEX_STREET1,90, DEF_NORTH},
  {{-3,-3,15},  TEX_STREET6,270,DEF_EAST},  {{-3,-3,11},  TEX_STREET2,0,  DEF_EAST},
  {{-3,-3,7},   TEX_STREET2,0,  DEF_EAST},  {{-3,-3,3},   TEX_STREET2,0,  DEF_EAST},
  {{-3,-3,-1},  TEX_STREET2,0,  DEF_EAST},  {{-3,-3,-5},  TEX_STREET2,0,  DEF_EAST},
  {{-3,-3,-9},  TEX_STREET2,0,  DEF_EAST},  {{-3,-3,-13}, TEX_STREET2,0,  DEF_EAST},
  {{-3,-3,-17}, TEX_STREET4,90, DEF_NORTH}, {{-7,-3,-17}, TEX_STREET1,90, DEF_NORTH},
  {{-11,-3,-17},TEX_STREET3,180,DEF_WEST},  {{-11,-3,-13},TEX_STREET2,180,DEF_WEST},
  {{-11,-3,-9}, TEX_STREET2,180,DEF_WEST},  {{-11,-3,-5}, TEX_STREET2,180,DEF_WEST},
  {{-11,-3,-1}, TEX_STREET2,180,DEF_WEST},  {{-11,-3,3},  TEX_STREET2,180,DEF_WEST},
  {{-11,-3,7},  TEX_STREET2,180,DEF_WEST},  {{-11,-3,11}, TEX_STREET5,0,  DEF_NORTH},
  {{-15,-3,11}, TEX_STREET1,90, DEF_NORTH}, {{-19,-3,11}, TEX_STREET1,90, DEF_NORTH}
};

pathCube fullPath[2200];