#include "kingdom_main.h"

//funkcija koja sve prikazuje
void windowDisplay(void){
    glClearColor(0.8,0.8,0.8,0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();
}

void windowKey(unsigned char key,int x,int y){
  
  //ESC da se izadje
  if(key==27)
      exit(0);
}

//menjanje ekrana
void windowReshape(int width,int height){
    windowHeight=height;
    windowWidth=width;
    
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,width,height,0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}