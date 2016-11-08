#include "kingdom_main.h"

void initialize(void){
  screenInit();
  
}

void screenInit(void){
    screen=glutCreateSubWindow(window, 0, 0,windowWidth,windowHeight);
    
    glutDisplayFunc(screenDisplay);
    glutReshapeFunc(screenReshape);
    glutKeyboardFunc(windowKey);
}