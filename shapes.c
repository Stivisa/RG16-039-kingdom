#include "kingdom_main.h"

//Funkcije za iscrtavanje osnovnih figura

/*Crtamo kvadrate, 
*ali zavisno od parametra da bi mogli da 
*primenimo u crtanju drugih figura
*/
void square(int s, int a, int b, int c, int d)
{
    glBegin(GL_POLYGON);

    //crtamo prednju stranu
    if (s == 1) {
	  glNormal3f(0, 0, 1);
    }
    //zadnja strana
    else if (s == 2) {
	  glNormal3f(0, 0, -1);
    }
    //desna strana
    else if (s == 3) {
	  glNormal3f(1, 0, 0);
    }
    //leva strana
    else if (s == 4) {
	  glNormal3f(-1, 0, 0);
    }
    //gornja strana
    else if (s == 5) {
	  glNormal3f(0, 1, 0);
    }
    //donja strana
    else if (s == 6) {
	  glNormal3f(0, -1, 0);
    }
    glTexCoord2f(0, 0);
    glVertex3fv(cube_v[a]);
    glTexCoord2f(1, 0);
    glVertex3fv(cube_v[b]);
    glTexCoord2f(1, 1);
    glVertex3fv(cube_v[c]);
    glTexCoord2f(0, 1);
    glVertex3fv(cube_v[d]);

    glEnd();
}

/*Crtamo kocku
 * Na x,y,z kordinatama
 * dimenzija dx,dy,dz
 * rotiranje za th oko y ose
*/
void cube(double x, double y, double z, double dx, double dy, double dz,
	  double th)
{

    float emissions[] = { 0, 0, 0.01 * emission, 1 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shinyvec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissions);

    //ukljucujemo teksture
    if (renderMode == DEF_RENDER) {
	  glEnable(GL_TEXTURE_2D);
	  //Koristimo trenutnu teksturu
	  glBindTexture(GL_TEXTURE_2D, currentTexture);
    }

    glPushMatrix();

    //Transformisemo kocku
    glTranslated(x, y, z);
    glRotated(th, 0, 1, 0);
    glScaled(dx, dy, dz);

    //prednja strana 
    square(1, 4, 5, 6, 7);
    //zadnja strana
    square(2, 3, 0, 1, 2);
    //desna strana
    square(3, 5, 6, 2, 1);
    //leva strana
    square(4, 7, 4, 0, 3);
    //gornja strana
    square(5, 6, 7, 3, 2);
    //donja strana
    square(6, 0, 4, 5, 1);

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

//Crtamo najvisu tacku
void vertex(double th, double ph)
{
    double x = Sin(th) * Cos(ph);
    double y = Cos(th) * Cos(ph);
    double z = Sin(ph);

    glNormal3d(x, y, z);
    glTexCoord2d(th / 360.0, ph / 180.0 + 0.5);
    glVertex3d(x, y, z);
}

//crtamo krug precnika r
void circle(int r)
{
    int th;
    glRotated(90, 1, 0, 0);
    glScaled(r, r, r);
    glBegin(GL_QUAD_STRIP);
    for (th = 0; th <= 360; th += 2 * DEF_D) {
	  vertex(th, 0);
	  vertex(th, 1);
    }
    glEnd();
}

//crtamo loptu
void sphere(double x, double y, double z, double r, double rot)
{
    int th, ph;

    float yellow[] = { 1.0, 1.0, 0.0, 1.0 };
    float emissions[] = { 0.0, 0.0, 0.01 * emission, 1.0 };
    glMaterialfv(GL_FRONT, GL_SHININESS, shinyvec);
    glMaterialfv(GL_FRONT, GL_SPECULAR, yellow);
    glMaterialfv(GL_FRONT, GL_EMISSION, emissions);

    //koristimo teksture
    if (renderMode == DEF_RENDER) {
	  glEnable(GL_TEXTURE_2D);
	  glBindTexture(GL_TEXTURE_2D, currentTexture);
    }

    glPushMatrix();

    //pozicioniranje i skaliranje
    glTranslated(x, y, z);
    glScaled(r, r, r);
    glRotated(rot, 0, 1, 0);

    //crtanje lopte
    for (ph = -90; ph < 90; ph += DEF_D) {
	  glBegin(GL_QUAD_STRIP);
	  for (th = 0; th <= 360; th += 2 * DEF_D) {
	    vertex(th, ph);
	    vertex(th, ph + DEF_D);
	  }
	  glEnd();
    }
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

//crtamo kupu
void cone(double x, double y, double z, double r, double h, int deg)
{
    int k;

    if (renderMode == DEF_RENDER) {
	  glEnable(GL_TEXTURE_2D);
	  glBindTexture(GL_TEXTURE_2D, currentTexture);
    }

    glPushMatrix();

    //Transformacije
    glTranslated(x, y, z);
    glScaled(r, h, r);

    glRotated(-90, 1, 0, 0);

    //strane
    glBegin(GL_TRIANGLES);
	  for (k = 0; k <= 360; k += deg) {
		glNormal3f(0, 0, 1);
		glTexCoord2f(0.5, 0.5);
		glVertex3f(0, 0, 1);

		glNormal3f(Cos(k), Sin(k), r);
		glTexCoord2f((double) 1 / 2 * Cos(k) + 0.5, (double) 1 / 2 * Sin(k) + 0.5);
		glVertex3f(Cos(k), Sin(k), 0);

		glNormal3f(Cos(k + deg), Sin(k + deg), r);
		glTexCoord2f((double) 1 / 2 * Cos(k + deg) + 0.5, (double) 1 / 2 * Sin(k + deg) + 0.5);
		glVertex3f(Cos(k + deg), Sin(k + deg), 0);
    }
    glEnd();

    //donji krug 
    glRotated(90, 1, 0, 0);
    glBegin(GL_TRIANGLES);
	  glNormal3f(0, -1, 0);
	  for (k = 0; k <= 360; k += deg) {
		glTexCoord2f(0.5, 0.5);
		glVertex3f(0, 0, 0);
		glTexCoord2f(0.5 * Cos(k) + 0.5, 0.5 * Sin(k) + 0.5);
		glVertex3f(Cos(k), 0, Sin(k));
		glTexCoord2f(0.5 * Cos(k + deg) + 0.5, 0.5 * Sin(k + deg) + 0.5);
		glVertex3f(Cos(k + deg), 0, Sin(k + deg));
	  }
    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

//crtamo valjak
void cylinder(double x, double y, double z, double r, double h)
{
    int i, k;
    if (renderMode == DEF_RENDER) {
	  glEnable(GL_TEXTURE_2D);
	  glBindTexture(GL_TEXTURE_2D, currentTexture);
    }

    glPushMatrix();

    //Transformacije
    glTranslated(x, y, z);
    glScaled(r, h, r);

    //strane
    glBegin(GL_QUAD_STRIP);
	  for (k = 0; k <= 360; k += DEF_D) {
		glNormal3f(Cos(k), 0, Sin(k));
		glTexCoord2f(-Cos(k), Sin(k));
		glVertex3f(Cos(k), +1, Sin(k));

		glTexCoord2f(Cos(k), Sin(k));
		glVertex3f(Cos(k), -1, Sin(k));
	  }
    glEnd();

    //Crtamo gornji i donji trougao
    for (i = 1; i >= -1; i -= 2) {
	  glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0, i, 0);
		glTexCoord2f(0.5, 0.5);
		glVertex3f(0, i, 0);
		for (k = 0; k <= 360; k += DEF_D) {
		  glTexCoord2f(0.5 * Cos(k) + 0.5, 0.5 * Sin(k) + 0.5);
		  glVertex3f(i * Cos(k), i, Sin(k));
		}
	  glEnd();
    }

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

/*
 *  Crtanje piramide 
 *     na (x,y,z)
 *     dimenzija (dx,dy,dz)
 *     rotiranje za th ugao oko y ose
 */
void pyramid(double x, double y, double z,
	     double dx, double dy, double dz, double th)
{
    glPushMatrix();

    //transformisemo kocku
    glTranslated(x, y, z);
    glRotated(th, 0, 1, 0);
    glScaled(dx, dy, dz);

    cone(0, 0, 0, 1, 1, 90);

    glPopMatrix();
}


/*
 *  Crtamo zvezdu
 *     na (x, y, z)
 *     dimenzija dx, dy, dz
 *     rotirane za th ugao oko y ose
 */
void star(double x, double y, double z,
	  double dx, double dy, double dz, double th)
{
    glPushMatrix();
    glTranslated(x, y, z);
    glRotated(th, 0, 1, 0);
    glScaled(dx, dy, dz);

    pyramid(0, 0.5, 0, 1, 3, 1, 0);

    //zadnja strana
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    pyramid(0, 0.5, 0, 1, 3, 1, 90);
    glPopMatrix();

    //prednja strana
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    pyramid(0, 0.5, 0, 1, 3, 1, 0);
    glPopMatrix();

    //desna strana
    glPushMatrix();
    glRotatef(-90, 0, 0, 1);
    pyramid(0, 0.5, 0, 1, 3, 1, 90);
    glPopMatrix();

    //leva strana
    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    pyramid(0, 0.5, 0, 1, 3, 1, -90);
    glPopMatrix();

    //donji deo zvezde
    glPushMatrix();
    glRotatef(180, 1, 0, 0);
    pyramid(0, 0.5, 0, 1, 3, 1, 0);
    glPopMatrix();

    glPopMatrix();
}

/*
 *  Crtamo siljkove
 *     na (x, y, z)
 *     precnika r, visine h,
 *     rotirano za ox oko x ose
 *     rotirano za oy oko y ose
 *     rotirano za oz oko y ose
 */
void spike(double x, double y, double z,
	   double r, double h, int deg, double ox, double oy, double oz)
{
    currentTexture = textures[TEX_SPIKE];
    glPushMatrix();
    glRotated(oz, 0, 0, 1);
    glRotated(oy, 0, 1, 0);
    glRotated(ox, 1, 0, 0);

    cone(x, y, z, r, h, deg);
    glPopMatrix();
    currentTexture = textures[TEX_DEFAULT];
}
