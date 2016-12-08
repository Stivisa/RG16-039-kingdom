#include "kingdom_main.h"

//tesrianje gita ne radi kako treba

//Funkcije za resetovanje podesavanja

void redisplayAll(void)
{

    glutSetWindow(screen);
    //menjamo poziciju glavnog prozora
    screenReshape(windowWidth,
		  windowHeight - DEF_SPACER - DEF_SIDEBAR_HEIGHT);
    glutPostRedisplay();

    //menjamo velicinu sporednog prozora
    glutSetWindow(sidebar);
    sidebarReshape(windowWidth, DEF_SIDEBAR_HEIGHT);
    glutPostRedisplay();
}

void reset(void)
{
    //resetovanje projekcije
    asp = DEF_ASP;
    dim = DEF_DIM;
    th = DEF_TH;
    ph = DEF_PH;
    fov = DEF_FOV;
    ecX = DEF_ECX;
    ecY = DEF_ECY;
    ecZ = DEF_ECZ;

    // resetovanje crtanja
    axes = DEF_AXES;
    grid = DEF_GRID;


    //resetovanje tekstura
    currentTexture = TEX_DEFAULT;
    currentTextureSelected = TEX_DEFAULT;
}
