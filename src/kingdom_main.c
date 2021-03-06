#include "kingdom_main.h"

//glavna funckija koja sve startuje
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL | GLUT_DOUBLE);
    glutInitWindowSize(windowWidth, windowHeight);

    window = glutCreateWindow(windowName);

    if (DEF_FULL_SCREEN) {
	  glutFullScreen();
    }
    glutDisplayFunc(windowDisplay);
    glutReshapeFunc(windowReshape);
    glutKeyboardFunc(windowKey);
    glutSpecialFunc(windowSpecial);

    //funckija za postavljanje sve na pocetne vrednosti
    reset();
    //funckija za inicijlizaciju pogleda
    initialize();

    redisplayAll();
    //ulazak u glavnu petlju
    glutMainLoop();
    return 0;
}
