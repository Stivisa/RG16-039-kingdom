#include "kingdom_main.h"

//prikazivanje dodatnog prozora
void sidebarDisplay(void)
{
    //int line = 1;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glFlush();
    glutSwapBuffers();
}

 //Menjanje prozora ako dodje do promene velicine

void sidebarReshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, height, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.3, 0.3, 0.3, 0.0);
}
