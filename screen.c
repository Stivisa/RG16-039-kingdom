#include "kingdom_main.h"

//inicijalizacija ekrana
void displayInit(void)
{
    glClearColor(0.8, 0.8, 0.8, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |
	    GL_STENCIL_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
}

//racunanje odakle gledamo
void displayEye(void)
{
    double Ex = -2 * dim * Sin(th) * Cos(ph);
    double Ey = 2 * dim * Sin(ph);
    double Ez = 2 * dim * Cos(th) * Sin(ph);
    //th=th+90;
    gluLookAt(Ex + ecX, Ey, Ez + ecZ, ecX, ecY, ecZ, 0, Cos(ph), 0);
}

//prikazivanje scene
void screenDisplay(void)
{
    //ciscenje ekrana i postavljane kamere
    displayInit();
    displayEye();

    drawScene();

    glFlush();
    glutSwapBuffers();
}

//odredjivanje projekcije
void screenProject(double fov, double asp, double dim)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, asp, dim / 16, 16 * dim);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//menjnaje sike kada dodje do menjanje velicine prozora
void screenReshape(int width, int height)
{
    //postavljamo odgovarajucu proporciju
    asp = (height > 0) ? (double) width / height : 1;
    windowWidth = width;

    //postavljanje viewport-a za ceo prozora
    glViewport(0, 0, width, height);
    screenProject(fov, asp, dim);
}
