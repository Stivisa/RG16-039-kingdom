#include "kingdom_main.h"

void redisplayAll(void){
  
    glutSetWindow(screen);
    screenReshape(windowWidth,windowHeight);
    glutPostRedisplay();
}

void reset(void){
 //resetovanje projekcije
  asp  = DEF_ASP;
  dim  = DEF_DIM;
  th   = DEF_TH;
  ph   = DEF_PH;
  fov  = DEF_FOV;
  ecX  = DEF_ECX;
  ecY  = DEF_ECY;
  ecZ  = DEF_ECZ;  

  // resetovanje crtanja
  axes = DEF_AXES;
  grid = DEF_GRID;

}