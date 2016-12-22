#include "kingdom_main.h"

//funkcija koja sve prikazuje
void windowDisplay(void)
{
    glClearColor(0.8, 0.8, 0.8, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();
}

//funkcija za osnovne komande u igrici
void windowKey(unsigned char key, int x, int y)
{

    //ESC da se izadje
    if (key == 27)
	  exit(0);
}

//funkcija za specijalne komande
//rotacija kamere, pomeranje kamere
void windowSpecial(int key,int x,int y)
{
  int modifiers = glutGetModifiers();
  
  //Stiskamo SHIFT da bi aktivirali pomeranje kamere
  if (modifiers == GLUT_ACTIVE_SHIFT) {
    //rotacija levo desno
    if (key == GLUT_KEY_RIGHT){
	  th += 5;
	}  
    else if (key == GLUT_KEY_LEFT){
	  th -= 5;
	} 
    //pomeranje gore dole
    else if (key == GLUT_KEY_UP){
	  ph += 5;
	}
    else if (key == GLUT_KEY_DOWN){
	  ph -= 5;
	}
  }
  //u drugim slucajevima samo pomeri ekran
  else {
   
    if (key == GLUT_KEY_RIGHT){
	  ecZ -= .5;
	}
    else if (key == GLUT_KEY_LEFT){
	  ecZ += .5;
	}
    else if (key == GLUT_KEY_UP){
	  ecX -= .5;
	}  
    else if (key == GLUT_KEY_DOWN){
	  ecX += .5;
	} 
  }
  
  //Ostavljamo isti ugao
  th %= 360;
  ph %= 360;

  redisplayAll();
}

//menjanje ekrana
void windowReshape(int width, int height)
{
    windowHeight = height;
    windowWidth = width;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, height, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //menjamo velicinu glavnog prozora
    glutSetWindow(screen);
    glutPositionWindow(0,0);
    glutReshapeWindow(windowWidth,
		      windowHeight - DEF_SIDEBAR_HEIGHT - DEF_SPACER);

    //menjamo velicinu pod prozora
    glutSetWindow(sidebar);
    glutPositionWindow(0,windowHeight - DEF_SIDEBAR_HEIGHT);
    glutReshapeWindow(windowWidth, DEF_SIDEBAR_HEIGHT);

}
