#include "kingdom_main.h"
//funkcija za inicijalizaciju svega
void initialize(void){
  screenInit();
  initTextures();
}

//inicijalizacija ekrana
void screenInit(void){
    screen=glutCreateSubWindow(window, 0, 0,windowWidth,windowHeight);
    
    glutDisplayFunc(screenDisplay);
    glutReshapeFunc(screenReshape);
    glutKeyboardFunc(windowKey);
}

//funkcija za inicijalizaciju tekstura
void initTextures(void){
  textures[TEX_GRASS]=loadTexBMP("images/txGrass.bmp");
}