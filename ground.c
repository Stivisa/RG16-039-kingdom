#include "kingdom_main.h"

/*funkcije za crtanje zemlje i mreze 
 * radi lakseg crtanja drugih objekata
 */

// crtanje Axes
void drawAxes(void){
  //duzina axes-a
  const double len=5.0;
  printf("%d",axes);
  
  //crtamo x,y,z osu radi lakseg snalazenja u okruzenju
  if (axes==0) {
    glDisable(GL_LIGHTING);
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINES);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(len,0.0,0.0);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(0.0,len,0.0);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(0.0,0.0,len);
    glEnd();
    
    /*glRasterPos3d(len,0.0,0.0);
    glRasterPos3d(0.0,len,0.0);
    glRasterPos3d(0.0,0.0,len);
    */
    glEnable(GL_LIGHTING);
  }

}

//crtanje grid-a
void drawGrid(void)
{
  // crtanje grida 
  if (grid==0) {
    int i,j;
    glDisable(GL_LIGHTING);
    glColor3f(1.0,1.0,1.0);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(2,1);
    glBegin(GL_LINES);
    // horizontalno po z
    for (i=-21;i<21;i+=2){
      for (j=-19;j<23;j+=40){
        glVertex3d(i,-2.8,j);
      }
    }
   // horizonalno po x
    for (i=-19;i<23;i+=2){
      for (j=-21;j<20;j+=40){
        glVertex3d(j,-2.8,i);
      }
    }
    glEnd();
    glDisable(GL_POLYGON_OFFSET_FILL);
    glEnable(GL_LIGHTING);
  }
}

//crtamo zemlje
void drawBoard(void){
    board();
}

//crtanje scene
void drawScene(void){
    
    drawAxes();
    drawGrid();
    drawBoard();
}



