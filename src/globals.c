#include "kingdom_main.h"

// Opste globalne promenljive
char *windowName = "Kindoms Tower Defense";	//Naziv prozora
int windowHeight = DEF_WINDOW_HEIGHT;	//pocetna visina prozora
int windowWidth = DEF_WINDOW_WIDTH;	//pocetna sirina prozora
GLuint window, screen, sidebar;

int debug = DEF_DEBUG;

//stil fonta
GLvoid *fontStyle = DEF_FONT_STYLE;

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
int vals = DEF_VALS;
int showAttackRadius = DEF_SHOW_ATTACK;
int forest = DEF_FOREST;
//teksture
unsigned int textures[17];	//sadrzi nase teksture
int currentTexture = TEX_DEFAULT;	//ako nije postavljeno nista
int currentTextureSelected = TEX_DEFAULT;	//ako nista nije selektovano
int backgrounds[6];

//Detekcija sudara
int showCollisionDetection = DEF_COLLISION;	//Da li hocemo da se vide sfere oko vojnika
int lastShot = DEF_LAST_SHOT;
shot shots[200];		//Pucnjevi koji su igri, maks 200


//Globalne za animaciju
char *info = DEF_INFO;
int gameStarted = DEF_GAME_STARTED;	//Definisemo da li je igra startovana
int gamePaused = DEF_GAME_PAUSED;	//Pauziranje igre
int gameSpeed = DEF_GAME_SPEED;	//Brzina igre
int moveLightB = DEF_MOVE_LIGHT;	//Kretanje svetlosti
int lightPh = DEF_L_PH;		//Visina svetlosti
int moveTowerTopsB = DEF_MOVE_TOWER_TOPS;	//Definisanje da li vrh kule treba da se okrece
int towerTh = DEF_TOWER_TH;	//Vrh od ledene kule da li da se okrece

//Podaci za igraca
int lives = DEF_LIVES;
int money = DEF_MONEY;
int scrolls = DEF_SCROLLS;
int score = DEF_SCORE;
int waveNumber = DEF_WAVE;
int lastWave = DEF_LAST_WAVE;




/*  Shadows  */
float N[] = { 0, -1, 0, 0 };	/* normal vector za ravan */
float E[] = { 0, DEF_Y_FLOOR, 0, 0 };	/* tacka ravni*/


//vojnici
int soldierObj = DEF_SOLDIER_OBJ;
wave waves[DEF_LAST_WAVE];	//sadrzi talase vojnika
soldier soldiers[DEF_MINION_PER_WAVE_SIZE];	//Zadrzi vojnike


//kocke
GLfloat cube_v[][3] = {
    {-1.0, -1.0, -1.0}, {+1.0, -1.0, -1.0}, {+1.0, +1.0, -1.0},
    {-1.0, +1.0, -1.0}, {-1.0, -1.0, +1.0}, {+1.0, -1.0, +1.0},
    {+1.0, +1.0, +1.0}, {-1.0, +1.0, +1.0}
};

//Svetlost
int light = DEF_LIGHT;		//Ukljuciti svetlost
int distance = DEF_DISTANCE;	//Daljina svetlosti
int ambient = DEF_AMBIENT;	//ambient intensity in %
int diffuse = DEF_DIFFUSE;	// diffuse intensity %
int emission = DEF_EMISSION;	// emission intensity %
int specular = DEF_SPECULAR;	// specular intensity %
int shininess = DEF_SHININESS;	//odsjaj
float shinyvec[1] = { 1 };	//vrednost odsjaja
float lightY = DEF_L_Y;		//elevation of light
float white[] = { 1, 1, 1, 1 };

//trenutna pozicija misa
int mouseX = 0;
int mouseY = 0;
int mouseZ = 0;


//podaci o kulama
tower towers[DEF_CURRENT_OBJS_SIZE];	//Sadrzi kule koje su u igri, maks je 53
tower preview_tower;		//promenljiva za preview kule
point preview_points[DEF_CURRENT_OBJS_SIZE];	//Sadrzi validne lokacije za smestanje kule
int preview = DEF_PREVIEW;	//odredjivanja da li preview ukljucen
int objectSelected = DEF_OBJ_SEL;	//kula koja ce biti smestena
int lastCurrentObject = DEF_LAST_CURRENT_OBJECT;	//poslednja selektovana kula
int renderMode = DEF_RENDER;	//Odredjuje da li hocemo da iscrtamo objekte
int objectPicked = DEF_OBJ_PICKED;	//Kula koja je selektovana

//Trenutno RGB za selekciju objekta
int currentRed = DEF_CURRENT_RED;
int currentGreen = DEF_CURRENT_GREEN;
int currentBlue = DEF_CURRENT_BLUE;
char *currentTowerName = DEF_CURRENT_TOWER_NAME;
int currentTowerRange = DEF_CURRENT_TOWER_RANGE;
int currentTowerDamage = DEF_CURRENT_TOWER_DAMAGE;
int currentTowerFireRate = DEF_CURRENT_TOWER_FIRE_RATE;
int currentTowerCost = DEF_CURRENT_TOWER_COST;
char *currentTowerDescription = DEF_CURRENT_TOWER_DESCRIPTION;


//definisemo putanju puta koji treba da se iscrta i na kome idu vojnici
pathCube fullPath[2200];

pathCube pathCubes[] = {
    {{25, -3, -1}, TEX_STREET1, 90, DEF_NORTH},
    {{21, -3, -1}, TEX_STREET1, 90, DEF_NORTH},
	{{17, -3, -1}, TEX_STREET1,90, DEF_NORTH},
    {{13, -3, -1}, TEX_STREET6, 270, DEF_EAST},
	{{13, -3, -5}, TEX_STREET2, 0, DEF_EAST},
    {{13, -3, -9}, TEX_STREET2, 0, DEF_EAST},
	{{13, -3, -13}, TEX_STREET2, 0, DEF_EAST},
    {{13, -3, -17}, TEX_STREET4, 90, DEF_NORTH},
	{{9, -3, -17}, TEX_STREET1, 90, DEF_NORTH},
    {{5, -3, -17}, TEX_STREET3, 180, DEF_WEST},
	{{5, -3, -13}, TEX_STREET2, 180, DEF_WEST},
    {{5, -3, -9}, TEX_STREET2, 180, DEF_WEST},
	{{5, -3, -5}, TEX_STREET2, 180, DEF_WEST},
    {{5, -3, -1}, TEX_STREET2, 180, DEF_WEST},
	{{5, -3, 3}, TEX_STREET2, 180, DEF_WEST},
    {{5, -3, 7}, TEX_STREET6, 270, DEF_SOUTH},
	{{9, -3, 7}, TEX_STREET1, 270, DEF_SOUTH},
    {{13, -3, 7}, TEX_STREET1, 270, DEF_SOUTH},
	{{17, -3, 7}, TEX_STREET4, 90, DEF_WEST},
    {{17, -3, 11}, TEX_STREET2, 0, DEF_WEST},
	{{17, -3, 15}, TEX_STREET5, 0, DEF_NORTH},
    {{13, -3, 15}, TEX_STREET1, 90, DEF_NORTH},
	{{9, -3, 15}, TEX_STREET1, 90, DEF_NORTH},
    {{5, -3, 15}, TEX_STREET1, 90, DEF_NORTH},
	{{1, -3, 15}, TEX_STREET1, 90, DEF_NORTH},
    {{-3, -3, 15}, TEX_STREET6, 270, DEF_EAST},
	{{-3, -3, 11}, TEX_STREET2, 0, DEF_EAST},
    {{-3, -3, 7}, TEX_STREET2, 0, DEF_EAST},
	{{-3, -3, 3}, TEX_STREET2, 0, DEF_EAST},
    {{-3, -3, -1}, TEX_STREET2, 0, DEF_EAST},
	{{-3, -3, -5}, TEX_STREET2, 0, DEF_EAST},
    {{-3, -3, -9}, TEX_STREET2, 0, DEF_EAST},
	{{-3, -3, -13}, TEX_STREET2, 0, DEF_EAST},
    {{-3, -3, -17}, TEX_STREET4, 90, DEF_NORTH},
	{{-7, -3, -17},TEX_STREET1, 90, DEF_NORTH},
    {{-11, -3, -17}, TEX_STREET3, 180, DEF_WEST},
	{{-11, -3, -13}, TEX_STREET2, 180, DEF_WEST},
    {{-11, -3, -9}, TEX_STREET2, 180, DEF_WEST},
	{{-11, -3, -5}, TEX_STREET2, 180, DEF_WEST},
    {{-11, -3, -1}, TEX_STREET2, 180, DEF_WEST},
	{{-11, -3, 3}, TEX_STREET2, 180, DEF_WEST},
    {{-11, -3, 7}, TEX_STREET2, 180, DEF_WEST},
	{{-11, -3, 11},TEX_STREET5, 0, DEF_NORTH},
    {{-15, -3, 11}, TEX_STREET1, 90, DEF_NORTH},
	{{-19, -3, 11}, TEX_STREET1, 90, DEF_NORTH}
};




//Osnovne kule
tower default_towers[5] = {
    {0, OBJ_BASIC, 1, {17, 0, -17}, {1, 1, 1}, {0, 0, 0}, TEX_BRICK, {5, 5, 5},
     "Basic", 1, 5, 3, 4, 0, 10, "Description"},
    {0, OBJ_FIRE, 1, {9, 0, -13}, {1, 1, 1}, {0, 0, 0}, TEX_FIRE, {10, 5, 5},
     "Fire", 1, 12, 4, 3, 0, 40, "Description"},
    {0, OBJ_FIRE2, 1, {9, 0, -9}, {1, 1, 1}, {0, 0, 0}, TEX_FIRE, {15, 5, 5},
     "Advanced Fire", 1, 12, 6, 3, 0, 45, "Description"},
    {0, OBJ_ICE, 1, {13, 0, 3}, {1, 1, 1}, {0, 0, 0}, TEX_ICE, {20, 5, 5},
     "Ice", 1, 12, 5, 4, 0, 50, "Description"},
    {0, OBJ_EARTH, 1, {13, 0, 19}, {1, 1, 1}, {0, 0, 0}, TEX_EARTH, {25, 5, 5},
     "Earth", 1, 10, 8, 6, 0, 60, "Description"}
};

//Podaci o kulama
tower tower_data[12] = {
    /*
       id, tip, igri, translation, scale, rotation, teksture, rgb,
       ime, zona napada, napad, brzina napada, koliko kosta, opis
     */
    {0, OBJ_FIRE, 1, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, TEX_FIRE, {5, 5, 5},
     "Fire", 1, 10, 4, 3, 0, 40, "Just your typical fire tower"},
    {0, OBJ_FIRE2, 1, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, TEX_FIRE, {5, 5, 5},
     "Advanced Fire", 1, 12, 6, 3, 0, 45,
     "Just your typical fire tower - with spikes!"},

    {0, OBJ_ICE, 1, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, TEX_ICE, {5, 5, 5},
     "Ice", 1, 10, 5, 4, 0, 50, "Just your typical ice tower"},
    {0, OBJ_ICE2, 1, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, TEX_ICE, {5, 5, 5},
     "Advanced Ice", 1, 12, 7, 4, 0, 55,
     "Just your typical ice tower - with spikes!"},

    {0, OBJ_EARTH, 1, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, TEX_EARTH,{5, 5, 5},
     "Earth", 1, 10, 8, 6, 0, 60, "Just your typical earth tower"},
    {0, OBJ_EARTH2, 1, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, TEX_EARTH,{5, 5, 5},
     "Advanced Earth", 1, 12, 8, 6, 0, 60,
     "Just your typical earth tower - with spikes!"},

    {0, OBJ_BASIC, 1, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, TEX_BRICK,{5, 5, 5},
     "Basic", 1, 5, 3, 4, 0, 10, "A basic tower"},
    {0, OBJ_ADV, 1, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, TEX_BRICK, {5, 5, 5},
     "Advanced", 1, 7, 4, 4, 0, 15, "A basic tower - with spikes!"},

    {0, OBJ_CONE, 1, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, TEX_BRICK, {5, 5, 5},
     "Cone", 1, 7, 6, 4, 0, 20, "A cone tower"},
    {0, OBJ_ADV_CONE, 1, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, TEX_BRICK,{5, 5, 5},
     "Advanced Cone", 1, 9, 6, 4, 0, 25, "A cone tower - with spikes!"},

    {0, OBJ_SQUARE, 1, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, TEX_BRICK, {5, 5, 5},
     "Square", 1, 9, 6, 3, 0, 30, "A square tower"},
    {0, OBJ_ADV_SQUARE, 1, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, TEX_BRICK, {5, 5, 5},
     "Advanced Square", 1, 10, 6, 3, 0, 35, "A square tower - with spikes!"},

};
