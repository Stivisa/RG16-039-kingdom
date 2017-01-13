#include "kingdom_main.h"


//crtamo tabelu na kojoj ce biti smestene staze i zemlja
void board(void)
{
    int i, j;
    glPushMatrix();

    //vezujemo teksturu
	if (renderMode == DEF_RENDER) {
	  currentTexture = textures[TEX_GRASS];
	  glEnable(GL_TEXTURE_2D);
	  glBindTexture(GL_TEXTURE_2D, currentTexture);
	}
    //crtamo poligon
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(2, 1);
    glColor3f(1, 1, 1);
    glNormal3f(0, 1, 0);
    for (i = -DEF_D_FLOOR; i < DEF_D_FLOOR; i += 2) {
	  glBegin(GL_QUADS);
	  for (j = -DEF_D_FLOOR; j < DEF_D_FLOOR; j += 2) {
	    glTexCoord2f(0, 0);
	    glVertex3f(i, DEF_Y_FLOOR, j);
	    glTexCoord2f(1, 0);
	    glVertex3f(i, DEF_Y_FLOOR, j + 2);
	    glTexCoord2f(1, 1);
	    glVertex3f(i + 2, DEF_Y_FLOOR, j + 2);
	    glTexCoord2f(0, 1);
	    glVertex3f(i + 2, DEF_Y_FLOOR, j);
	  }
	  glEnd();
    }
    glDisable(GL_POLYGON_OFFSET_FILL);

    if (renderMode == DEF_RENDER) {
	  glDisable(GL_TEXTURE_2D);
	  currentTexture = textures[TEX_DEFAULT];
    }
    glPopMatrix();
}

/* Funkcija za crtanje dvorca
 * argumenti: double x - pozicija na x osi
 *			  double y - pozicija na y osi
 * 			  double z - pozicija na z osi
 *			  double dx - velicina po x osi, duzina dvorca
 * 			  double dy - velicina po y osi, visina dvorca
 * 			  double dz - velicina po z osi, sirina dvorca
 *			  double th - ugao prema cemu je dvorac nakrenut
 * 
 */
void keep(double x, double y, double z,
	  double dx, double dy, double dz, double th)
{
    tower t ={ 0, OBJ_ADV_SQUARE, 1, {9, 0, 9}, {1.5, 2, 1.5}, {0, 0, 0},TEX_BRICK2,
			  {1, 1, 1},"Advanced Tower", -1, -1, -1, -1, -1, -1, "Description"
	};
    glPushMatrix();
    glTranslated(x, y, z);
    glRotated(th, 0, 1, 0);
    glScaled(dx, dy, dz);

    //zadnji deo zida
    wall(-9, 0, 5, 1, 1, 1, 0);
    wall(-9, 0, -0.5, 1, 1, 1, 0);
    wall(-9, 0, -6, 1, 1, 1, 0);

    //levi deo zida
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    wall(-9, 0, 5, 1, 1, 1, 0);
    wall(-9, 0, -0.5, 1, 1, 1, 0);
    wall(-9, 0, -6, 1, 1, 1, 0);
    glPopMatrix();

    //desni deo zida
    glPushMatrix();
    glRotated(270, 0, 1, 0);
    wall(-9, 0, 5, 1, 1, 1, 0);
    wall(-9, 0, -0.5, 1, 1, 1, 0);
    wall(-9, 0, -6, 1, 1, 1, 0);
    glPopMatrix();

    //prednji deo zida
    glPushMatrix();
    glRotated(180, 0, 1, 0);
    wall(-9, 0, 5, 1, 1, 1, 0);
    /* gap here */
    wall(-9, 0, -6, 1, 1, 1, 0);
    glPopMatrix();

    //Kule
    advancedSquareTower(t);
    t.translation.x = -9;
    advancedSquareTower(t);
    t.translation.z = -9;
    advancedSquareTower(t);
    t.translation.x = 9;
    advancedSquareTower(t);


    currentTexture = textures[TEX_DEFAULT];
    glPopMatrix();
}

/*
 * Praviomo model soldier-a
 * argumenti: soldier s2 - model vojnika iz object fajla
 * 
 */
void soldierModel(soldier s2)
{
    //crtamo vojnika
    glPushMatrix();
    glTranslated(s2.translation.x, s2.translation.y, s2.translation.z);
    glRotated(s2.rotation.y, 0, 1, 0);
	glScaled(s2.scale.x, s2.scale.y, s2.scale.z);
    glColor3f((double) s2.rgb.r / 100, (double) s2.rgb.g / 100,(double) s2.rgb.b / 100);
    glCallList(s2.type);

	if (showCollisionDetection) {
	  glColor3f(1,1,0);
	  glTranslated(-2,4,-0.5);
	  glutSolidSphere(5,16,16);
	}
	glColor3fv(white);
	
    glPopMatrix();

}


/* 
 * Funkcija za pravljenje zida, koji se kasnije koristi pri konstruisanju dvorca.
 * argumenti: double x - pozicija na x osi
 * 			  double y - pozicija na y osi
 * 			  double z - pozicija na z osi
 * 			  double dx - velicina po x osi, duzina zida
 * 			  double dy - velicina po y osi, visina zida
 * 			  double dz - velicina po z osi, sirina zida
 * 			  double th - ugao rotacije zida 
 * 
 */
void wall(double x, double y, double z,
	  double dx, double dy, double dz, double th)
{
    glPushMatrix();
    glTranslated(x, y, z);
    glRotated(th, 0, 1, 0);
    glScaled(dx, dy, dz);

    currentTexture = textures[TEX_BRICK];

    cube(0, -2, 0, 0.2, 1, 1, 0);
    cube(0, 0, 0, 0.2, 1, 1, 0);
    cube(0, 2, 0, 0.2, 1, 1, 0);
    cube(0, 4, 0, 0.2, 1, 1, 0);

    glPushMatrix();
    glTranslated(0, 0, -2);
    cube(0, -2, 0, 0.2, 1, 1, 0);
    cube(0, 0, 0, 0.2, 1, 1, 0);
    cube(0, 2, 0, 0.2, 1, 1, 0);
    cube(0, 4, 0, 0.2, 1, 1, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 0, 2);
    cube(0, -2, 0, 0.2, 1, 1, 0);
    cube(0, 0, 0, 0.2, 1, 1, 0);
    cube(0, 2, 0, 0.2, 1, 1, 0);
    cube(0, 4, 0, 0.2, 1, 1, 0);
    glPopMatrix();

    /* platform */
    glPushMatrix();
    glTranslated(1, 4, 0);
    glRotated(90, 0, 0, 1);
    glRotated(90, 1, 0, 0);
    cube(0, -2, 0, 0.2, 1, 1, 0);
    cube(0, 0, 0, 0.2, 1, 1, 0);
    cube(0, 2, 0, 0.2, 1, 1, 0);
    glPopMatrix();

    //vrhovi zida
    glPushMatrix();
    glTranslated(0, 5, 0);
    cube(0, 0, 1.3, 0.2, 1, 0.7, 0);
    cube(0, 0, -1.3, 0.2, 1, 0.7, 0);
    glPopMatrix();
    currentTexture = textures[TEX_DEFAULT];

    glPopMatrix();
}


/* 
 * crtamo blokove za put
 * argumenti: pathCube p - kocka gde je iscrtan put
 *
 */ 
void pathBlock(pathCube p)
{
    glPushMatrix();

    if (renderMode == DEF_RENDER) {
	  currentTexture = textures[p.texture];
	  glEnable(GL_TEXTURE_2D);
	  glBindTexture(GL_TEXTURE_2D, currentTexture);
    }
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1, 1);
    glColor3f(1, 1, 1);
    glNormal3f(0, 1, 0);

    glBegin(GL_QUADS);
	  glTexCoord2f(0, 0);
	  glVertex3f(p.p.x - 2, p.p.y, p.p.z - 2);
	  glTexCoord2f(1, 0);
	  glVertex3f(p.p.x - 2, p.p.y, p.p.z + 2);
	  glTexCoord2f(1, 1);
	  glVertex3f(p.p.x + 2, p.p.y, p.p.z + 2);
	  glTexCoord2f(0, 1);
	  glVertex3f(p.p.x + 2, p.p.y, p.p.z - 2);
    glEnd();

    glDisable(GL_POLYGON_OFFSET_FILL);

    if (renderMode == DEF_RENDER) {
	  glDisable(GL_TEXTURE_2D);
	  currentTexture = textures[TEX_DEFAULT];
    }

    glPopMatrix();
}

//put koji se sastoji iz vise blokova puta
void path(void)
{
    int i;
    glPushMatrix();


    for (i = 0; i < DEF_PATH_LEN; i++) {
	  pathBlock(pathCubes[i]);
    }
    currentTexture = textures[TEX_DEFAULT];
    glPopMatrix();
}

/*
 * Model pucnja
 * argumenti: shot s - pucanj kule
 * 
 */
void shotModel(shot s)
{
    glPushMatrix();
    glTranslated(s.p.x, s.p.y, s.p.z);
    currentTexture = textures[s.texture];
    sphere(0, 0, 0, 0.5, towerTh);
    currentTexture = textures[TEX_DEFAULT];
    glPopMatrix();
}


/*
 * Funkcija za crtanje drveta
 * argumenti: double x -pozicija na x osi
 * 			  double y - pozicija na y osi
 * 			  double z - pozicija na z osi
 * 			  double dx - duzina drveta
 * 			  double dy - visina drveta
 * 			  double dz - sirina drveta
 * 			  double th - rotacija po y osi
 * 
 */
void evergreenTree1(double x,double y,double z, double dx,double dy,double dz, double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  //Osnova
  currentTexture = textures[TEX_WOOD];
  cylinder(0,-2,0, 0.3,1.0);
  currentTexture = textures[TEX_POISON];
  //Srednji deo
  cone(0,-2,0, 1.3,2,DEF_D);
  //Vrh
  cone(0,-1,0, 1,2,DEF_D);
  currentTexture = textures[TEX_DEFAULT];

  glPopMatrix();
}

/*
 * Funkcija za crtanje drveta 2
 * argumenti: double x -pozicija na x osi
 * 			  double y - pozicija na y osi
 * 			  double z - pozicija na z osi
 * 			  double dx - duzina drveta
 * 			  double dy - visina drveta
 * 			  double dz - sirina drveta
 * 			  double th - rotacija po y osi
 */
void evergreenTree2(double x,double y,double z, double dx,double dy,double dz, double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  //Osnova
  currentTexture = textures[TEX_WOOD];
  cylinder(0,-2,0, 0.5,1.0);
  currentTexture = textures[TEX_POISON];
  //Srednji deo
  cone(0,-2,0, 1.5,3,DEF_D);
  cone(0,-0.5,0, 1.4,3,DEF_D);
  //Vrh
  cone(0,1,0, 1,2,DEF_D);
  currentTexture = textures[TEX_DEFAULT];

  glPopMatrix();
}

/*
 * Funkcija za crtanje sume, crta 4 drveta zajednoevergreenForest
 * argumenti: double x -pozicija na x osi
 * 			  double y - pozicija na y osi
 * 			  double z - pozicija na z osi
 * 			  double dx - duzina drveta
 * 			  double dy - visina drveta
 * 			  double dz - sirina drveta
 * 			  double th - rotacija po y osi
 */
void evergreenForest(double x,double y,double z, double dx,double dy,double dz, double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);
  //Crtaj sumu
  evergreenTree1(0,0.3,-1, 1,1,1, 0);
  evergreenTree1(1.5,-1.3,-2, 0.5,0.5,0.5, 0);
  evergreenTree2(3,0,0, 1,1,1, 0);
  evergreenTree2(1,1.5,2, 1.5,1.5,1.5, 0);

  glPopMatrix();
}

/*
 * Funkcija za crtanje sume 2, crta 3 sume
 * argumenti: double x -pozicija na x osi
 * 			  double y - pozicija na y osi
 * 			  double z - pozicija na z osi
 * 			  double dx - duzina drveta
 * 			  double dy - visina drveta
 * 			  double dz - sirina drveta
 * 			  double th - rotacija po y osi
 */
void evergreenForest1(double x,double y,double z, double dx,double dy,double dz, double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);
  //crtaj sumu na osnocu sume 1
  evergreenForest(-5,0.3,-5, 1.2,1.2,1.2, 270);
  evergreenForest(0,0,-2, 1,1,1, 180);
  evergreenForest(2,-0.5,-5, 0.8,0.8,0.8, 0);

  glPopMatrix();
}

