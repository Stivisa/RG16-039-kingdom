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