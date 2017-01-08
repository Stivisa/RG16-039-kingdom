#include "kingdom_main.h"

//funkcija za inicijalizaciju svega
void initialize(void)
{
    sidebarInit();
    screenInit();

    initTextures();
    initBackground();
    initObjs();
    initSoldier();
    initPath();
    initDefaultTowers();
    initWaves();
    initShots();
    initPreviewPoints();
}

//inicijalizacija ekrana
void screenInit(void)
{
    screen = glutCreateSubWindow(window, 0, 0, windowWidth - DEF_SPACER,
								  windowHeight - DEF_SIDEBAR_HEIGHT - DEF_SPACER);

    glutDisplayFunc(screenDisplay);
    glutReshapeFunc(screenReshape);
    glutKeyboardFunc(windowKey);
    glutSpecialFunc(windowSpecial);

    glutMouseFunc(screenMouse);
    glutPassiveMotionFunc(screenPmotion);
}

//funkcija za inicijalizaciju prozora sa opcijama
void sidebarInit(void)
{
    sidebar = glutCreateSubWindow(window, 0, windowHeight - DEF_SIDEBAR_HEIGHT,
								  windowWidth, DEF_SIDEBAR_HEIGHT);
    glutDisplayFunc(sidebarDisplay);
    glutReshapeFunc(sidebarReshape);
    glutKeyboardFunc(windowKey);
    glutSpecialFunc(windowSpecial);

    glutMouseFunc(sidebarMouse);

}

//funkcija za inicijalizaciju tekstura
void initTextures(void)
{
    /*
       TEX_DEFAULT 0
       TEX_BRICK 1
       TEX_FIRE 2
       TEX_ICE 3
       TEX_EARTH 4
       TEX_POISON 5
       TEX_SPIKE 6
       TEX_GRASS 7
       TEX_WOOD 8
       TEX_BRICK2 9
       TEX_CRATE 10
       TEX_STREET1 11
       TEX_STREET2 12
       TEX_STREET3 13
       TEX_STREET4 14
       TEX_STREET5 15
       TEX_STREET6 16
     */
    textures[TEX_BRICK] = loadTexBMP("images/txBrick14.bmp");
    textures[TEX_FIRE] = loadTexBMP("images/txlava1.bmp");
    textures[TEX_ICE] = loadTexBMP("images/txIce7.bmp");
    textures[TEX_EARTH] = loadTexBMP("images/txRock5.bmp");
    textures[TEX_POISON] = loadTexBMP("images/txFloor38.bmp");
    textures[TEX_SPIKE] = loadTexBMP("images/txFloor4.bmp");
    textures[TEX_GRASS] = loadTexBMP("images/txGrass.bmp");
    textures[TEX_WOOD] = loadTexBMP("images/txWood3.bmp");
    textures[TEX_BRICK2] = loadTexBMP("images/txBrick13.bmp");
    textures[TEX_CRATE] = loadTexBMP("images/txCrate.bmp");
    textures[TEX_STREET1] = loadTexBMP("images/txStreet1.bmp");
    textures[TEX_STREET2] = loadTexBMP("images/txStreet2.bmp");
    textures[TEX_STREET3] = loadTexBMP("images/txStreet3.bmp");
    textures[TEX_STREET4] = loadTexBMP("images/txStreet4.bmp");
    textures[TEX_STREET5] = loadTexBMP("images/txStreet5.bmp");
    textures[TEX_STREET6] = loadTexBMP("images/txStreet6.bmp");

}

//inicijalizacija tekstura za pozadinu
void initBackground(void)
{
    /*
       BACK_FRONT 0
       BACK_RIGHT 1
       BACK_LEFT 2
       BACK_BACK 3
       BACK_UP 4
       BACK_DOWN 5
     */
    backgrounds[BACK_FRONT] = loadTexBMP("images/txStormydays_front.bmp");
    backgrounds[BACK_RIGHT] = loadTexBMP("images/txStormydays_right.bmp");
    backgrounds[BACK_LEFT] = loadTexBMP("images/txStormydays_left.bmp");
    backgrounds[BACK_BACK] = loadTexBMP("images/txStormydays_back.bmp");
    backgrounds[BACK_UP] = loadTexBMP("images/txStormydays_up.bmp");
    backgrounds[BACK_DOWN] = loadTexBMP("images/txStormydays_down.bmp");
}

//inicijalizacija puta
void initPath(void)
{
    int i, j;
    pathCube currentPath, nextPath, addedPath;
    // 4/50 = 0.08
    double moveFactor = 0.08;
    fullPath[0] = pathCubes[0];

    //duzina puta
    for (i = 0; i < (DEF_PATH_LEN - 1); i++) {
	  addedPath = currentPath = pathCubes[i];
	  nextPath = pathCubes[i + 1];

	  for (j = 0; j < DEF_FULL_PATH_LEN; j++) {
	    /*dodaj x */
	    if (currentPath.p.x > nextPath.p.x){
		  addedPath.p.x -= moveFactor;
		}else if (currentPath.p.x < nextPath.p.x){
		addedPath.p.x += moveFactor;
		}
	    /*dodaj z */
	    if (currentPath.p.z > nextPath.p.z){
		  addedPath.p.z -= moveFactor;
		}else if (currentPath.p.z < nextPath.p.z){
		  addedPath.p.z += moveFactor;
		}
	    fullPath[i * 50 + j] = addedPath;
	  }
    }
}


//funkcija za inicijalizaciju objekta
void initObjs(void)
{
    soldierObj = loadOBJ("kv-1.obj");
}

void initSoldier(void)
{
    /*
       soldier:
       typedef struct soldier {
       int id;
       int type;
       point translation;

       point scale;
       point rotation;
       int texture;
       rgb rgb;

       char* name;
       int damage;
       int health;
       int money;
       int speed;
       int inPlay;
     */
    soldier s1 = { 0, soldierObj, {26, -3.2, -0.5}, {0.1, 0.1, 0.1},
				  {0, 20, 0}, 0, {1, 1, 1}, "Soldier", 1, 5, 5, 1, 1
				 };
    int i;
    for (i = 0; i < DEF_MINION_PER_WAVE_SIZE; i++) {
	  soldiers[i] = s1;
    }

}

/*Inicijalizacija talasa koji ce biti korisceni
 */
void initWaves()
{
    wave wave = { 0, 1 };
    int i, k;

    for (k = 0; k < Length(waves); k++) {
	  for (i = 0; i < Length(soldiers); i++) {
	    //Menjamo status vojnika za svaki talas
	    soldiers[i].scale.x = (k+1)*0.1;
	    soldiers[i].scale.y = (k+1)*0.1;
	    soldiers[i].scale.z = (k+1)*0.1;

	    soldiers[i].damage += k;
	    soldiers[i].health += (15 * k);
	    soldiers[i].money += (5 * k);

	    soldiers[i].rgb.r = 27 + k * 10 + i * 02;
	    soldiers[i].rgb.g = 27 + k * 10 + i * 02;
	    soldiers[i].rgb.b = 27 + k * 10 + i * 02;

	    if (k < 3) {
		  soldiers[i].speed = 5 - k;
		/* minimum speed of 2 */
	    } else {
		  soldiers[i].speed = 2;
	    }
	    //Definisana duzina je 10 ali za svaki talas smanjujemo broj vojnika koji ulaze u igru
	    if (i >= (DEF_MINION_PER_WAVE_SIZE - 2 * k)) {
		  soldiers[i].inPlay = 0;
	    }

	    wave.s[i] = soldiers[i];
	  }
	waves[k] = wave;
    }
}

/*inicijalizacija podataka za pucanj
 */
void initShots()
{
    shot s = { 0, {0, 0, 0}, TEX_DEFAULT, 0 };
    int i;
    for (i = 0; i < 200; i++) {
	  shots[i] = s;
    }
}


//inicijalizacija osnovnih kula
void initDefaultTowers(void)
{
    int i;
    for (i = 0; i < Length(default_towers); i++) {
	  towers[i] = default_towers[i];
    }
    lastCurrentObject = 6;
    currentRed = 35;
}


/*
 *  Inicijalizacija tacaka na koje kula sme da se smesti
 */
void initPreviewPoints(void)
{
    point valid_points[DEF_CURRENT_OBJS_SIZE] = {
	  //Poredjane po redu
	  {17, 0, -17}, {17, 0, -13}, {17, 0, -9}, {17, 0, -5}, {17, 0, 3}, {17, 0, 19},
	  {13, 0, 3}, {13, 0, 11}, {13, 0, 19},
	  {9, 0, -13}, {9, 0, -9}, {9, 0, -5}, {9, 0, -1}, {9, 0, 3}, {9, 0, 11},{9, 0, 19},
	  {5, 0, 11}, {5, 0, 19},
	  {1, 0, -17}, {1, 0, -13}, {1, 0, -9}, {1, 0, -5}, {1, 0, -1}, {1, 0, 3},
	  {1, 0, 7}, {1, 0, 11}, {1, 0, 19},
	  {-3, 0, 19},
	  {-7, 0, -13}, {-7, 0, -9}, {-7, 0, -5}, {-7, 0, -1}, {-7, 0, 3},{-7, 0, 7},
	  {-7, 0, 11}, {-7, 0, 15}, {-7, 0, 19},
	  {-11, 0, 15}, {-11, 0, 19},
	  {-15, 0, -17}, {-15, 0, -13}, {-15, 0, -9}, {-15, 0, -5}, {-15, 0, -1},
	  {-15, 0, 3}, {-15, 0, 7}, {-15, 0, 15}, {-15, 0, 19},
	  {-19, 0, -17}, {-19, 0, -13}, {-19, 0, -9}, {-19, 0, -5}, {-19, 0, -1},
	  {-19, 0, 3}, {-19, 0, 7}, {-19, 0, 15}, {-19, 0, 19},
    };
    int i;
    for (i = 0; i < Length(valid_points); i++) {
	  preview_points[i].x = valid_points[i].x;
	  preview_points[i].y = valid_points[i].y;
	  preview_points[i].z = valid_points[i].z;
    }
}
