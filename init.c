#include "kingdom_main.h"

//funkcija za inicijalizaciju svega
void initialize(void)
{
    sidebarInit();
    screenInit();
	
	initTextures();
	initObjs();
	initSoldier();
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
    textures[TEX_GRASS] = loadTexBMP("images/txGrass.bmp");
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
