#include "kingdom_main.h"


//crtamo tablu na kojoj ce biti smestene staze i zemlja
void board(void)
{
    int i, j;
    glPushMatrix();

    //vezujemo teksturu
    currentTexture = textures[TEX_GRASS];
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, currentTexture);

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

    //if  (renderMode == DEF_RENDER) {
    glDisable(GL_TEXTURE_2D);
    currentTexture = textures[TEX_DEFAULT];
    //}
    glPopMatrix();
}

//praviomo model soldier-a
void soldierModel(soldier s2)
{
    //crtamo vojnika
    glPushMatrix();
    glTranslated(s2.translation.x, s2.translation.y, s2.translation.z);
    glRotated(s2.rotation.y, 0, 1, 0);
	glRotated(s2.rotation.x,1,0,0);
	glRotated(s2.rotation.z,0,0,1);
    glScaled(s2.scale.x, s2.scale.y, s2.scale.z);
    glColor3f((double) s2.rgb.r / 100, (double) s2.rgb.g / 100,
	      (double) s2.rgb.b / 100);
    glCallList(s2.type);

    glPopMatrix();

}
