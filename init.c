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
}

//inicijalizacija ekrana
void screenInit(void)
{
    screen = glutCreateSubWindow(window, 0, 0, windowWidth - DEF_SPACER,
				 windowHeight-DEF_SIDEBAR_HEIGHT-DEF_SPACER);

    glutDisplayFunc(screenDisplay);
    glutReshapeFunc(screenReshape);
    glutKeyboardFunc(windowKey);
}

//funkcija za inicijalizaciju prozora sa opcijama
void sidebarInit(void)
{
    sidebar =
	glutCreateSubWindow(window,0, windowHeight-DEF_SIDEBAR_HEIGHT,
			    windowWidth, DEF_SIDEBAR_HEIGHT);
    glutDisplayFunc(sidebarDisplay);
    glutReshapeFunc(sidebarReshape);
    glutKeyboardFunc(windowKey);

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
  int i,j;
  pathCube currentPath, nextPath, addedPath;
  // 4/50 = 0.08  
  double moveFactor = 0.08;
  fullPath[0] = pathCubes[0];

  //duzina puta
  for (i=0;i<(DEF_PATH_LEN-1);i++) {
    addedPath = currentPath = pathCubes[i];
    nextPath = pathCubes[i+1];

    
    for (j=0;j<DEF_FULL_PATH_LEN;j++) {
      /*dodaj x */
      if (currentPath.p.x > nextPath.p.x) addedPath.p.x -= moveFactor;
      else if (currentPath.p.x < nextPath.p.x) addedPath.p.x += moveFactor;
      /*dodaj z */
      if (currentPath.p.z > nextPath.p.z) addedPath.p.z -= moveFactor;
      else if (currentPath.p.z < nextPath.p.z) addedPath.p.z += moveFactor;
      fullPath[i*50+j] = addedPath;
    }
  }
}


//funkcija za inicijalizaciju objekta
void initObjs(void)
{
    soldierObj = loadOBJ("Ninja.obj");
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
    soldier s1 = { 0, soldierObj, {16, 0, -0.5}, {10, 10, 10},
    {-90, 260, 0}, 0, {1, 1, 1}, "F16", 1, 5, 5, 1, 1
    };
    s=s1;

}
