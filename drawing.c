#include "kingdom_main.h"

/*funkcije za crtanje zemlje i mreze 
 * radi lakseg crtanja drugih objekata
 */

// crtanje Axes
void drawAxes(void)
{
    //duzina axes-a
    const double len = 5.0;
    printf("%d", axes);

    //crtamo x,y,z osu radi lakseg snalazenja u okruzenju
    if (axes == 0) {
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(len, 0.0, 0.0);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, len, 0.0);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, len);
	glEnd();

	glRasterPos3d(len,0.0,0.0);
	print("X");
	glRasterPos3d(0.0,len,0.0);
	print("Y");
	glRasterPos3d(0.0,0.0,len);
	print("Z");
	
	glEnable(GL_LIGHTING);
    }

}

//Ispisujemo parametre, pomaze pri doredjivanju svetlosti i ostalih dodataka
void drawParameters(void)
{
  if (vals) {
    glColor3fv(white);
    
    printAt(5,5,"Angle=%d,%d  Dim=%.1f FOV=%d Light=%s",
	    th,ph,dim,fov,light?"On":"Off");
    if (light) {
      printAt(5,45,"Distance=%d Elevation=%.1f",distance,lightY);
      printAt(5,25,"Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",
	      ambient,diffuse,specular,emission,shinyvec[0]);
    }
  }
}

//crtanje grid-a
void drawGrid(void)
{
    // crtanje grida 
    if (grid == 0) {
	int i, j;
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(2, 1);
	glBegin(GL_LINES);
	// horizontalno po z
	for (i = -21; i < 21; i += 2) {
	    for (j = -19; j < 23; j += 40) {
		glVertex3d(i, -2.8, j);
	    }
	}
	// horizonalno po x
	for (i = -19; i < 23; i += 2) {
	    for (j = -21; j < 20; j += 40) {
		glVertex3d(j, -2.8, i);
	    }
	}
	glEnd();
	glDisable(GL_POLYGON_OFFSET_FILL);
	glEnable(GL_LIGHTING);
    }
}

/*  
 *  Cratmo pozadinu, postavljamo kutiju sa slikama neba
 */
void drawBackground(double D)
{
  glColor3fv(white);
  glEnable(GL_TEXTURE_2D);

  /* strane */
  glBindTexture(GL_TEXTURE_2D,backgrounds[BACK_RIGHT]);
  glBegin(GL_QUADS);
  glTexCoord2f(0,0); glVertex3f(-D,-D,-D);
  glTexCoord2f(1,0); glVertex3f(+D,-D,-D);
  glTexCoord2f(1,1); glVertex3f(+D,+D,-D);
  glTexCoord2f(0,1); glVertex3f(-D,+D,-D);
  glEnd();

  glBindTexture(GL_TEXTURE_2D,backgrounds[BACK_FRONT]);
  glBegin(GL_QUADS);
  glTexCoord2f(0,0); glVertex3f(+D,-D,-D);
  glTexCoord2f(1,0); glVertex3f(+D,-D,+D);
  glTexCoord2f(1,1); glVertex3f(+D,+D,+D);
  glTexCoord2f(0,1); glVertex3f(+D,+D,-D);
  glEnd();
  
  glBindTexture(GL_TEXTURE_2D,backgrounds[BACK_LEFT]);
  glBegin(GL_QUADS);
  glTexCoord2f(0,0); glVertex3f(+D,-D,+D);
  glTexCoord2f(1,0); glVertex3f(-D,-D,+D);
  glTexCoord2f(1,1); glVertex3f(-D,+D,+D);
  glTexCoord2f(0,1); glVertex3f(+D,+D,+D);
  glEnd();

  glBindTexture(GL_TEXTURE_2D,backgrounds[BACK_BACK]);
  glBegin(GL_QUADS);
  glTexCoord2f(0,0); glVertex3f(-D,-D,+D);
  glTexCoord2f(1,0); glVertex3f(-D,-D,-D);
  glTexCoord2f(1,1); glVertex3f(-D,+D,-D);
  glTexCoord2f(0,1); glVertex3f(-D,+D,+D);
  glEnd();

  /* gornji deo */
  glBindTexture(GL_TEXTURE_2D,backgrounds[BACK_UP]);
  glBegin(GL_QUADS);
  glTexCoord2f(0,0); glVertex3f(-D,+D,-D);
  glTexCoord2f(1,0); glVertex3f(+D,+D,-D);
  glTexCoord2f(1,1); glVertex3f(+D,+D,+D);
  glTexCoord2f(0,1); glVertex3f(-D,+D,+D);
  glEnd();

  /* donji deo */
  glBindTexture(GL_TEXTURE_2D,backgrounds[BACK_DOWN]);
  glBegin(GL_QUADS);
  glTexCoord2f(1,1); glVertex3f(+D,-D,-D);
  glTexCoord2f(0,1); glVertex3f(-D,-D,-D);
  glTexCoord2f(0,0); glVertex3f(-D,-D,+D);
  glTexCoord2f(1,0); glVertex3f(+D,-D,+D);
  glEnd();

  glDisable(GL_TEXTURE_2D);
}

//crtamo zemlje
void drawBoard(void)
{
    board();
}

//crtamo vojnika
void drawSoldier(void)
{
    //int i, k;
    soldierModel(s);



}

/*
 *  crtamo put
 */
void drawPath(void)
{
  path();
}

//cramo svetlost, sferu ako nam zatreba
void drawLight(void){
  //ako je svetlost aktivirano ili ne
  if (light==1) {
    
    float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
    float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
    float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
    //Pozicija svetlosti
    float Position[]  = {lightY,distance*Sin(lightPh),distance*Cos(lightPh),1.0};

    //Crtamo poziciju svetla kao sferu
    glColor3f(1.0, 1.0, 1.0);
    sphere(Position[0],Position[1],Position[2] , 0.1,0);
    //Normalizacija vektora
    glEnable(GL_NORMALIZE);
    //Ukljucujemo osvetljenje
    glEnable(GL_LIGHTING);
   
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
   
    glEnable(GL_LIGHT0);
   
	glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
    glLightfv(GL_LIGHT0,GL_POSITION,Position);
  }
  else
    glDisable(GL_LIGHTING);
}

void drawKeep(void)
{
  keep(-32,0,10, 1,1,1, 0);
}



//cratnje objekata kula
void drawObjects(void)
{
  int i;

  /* preview tower */
  if (preview_tower.id != DEF_OBJ_SEL) {
    tower t = {preview_tower.id,preview_tower.type,preview_tower.inPlay,
	       {preview_tower.translation.x,preview_tower.translation.y,preview_tower.translation.z},
	       {1,1,1},{0,0,0},preview_tower.texture,{1,1,1},
	       preview_tower.name,1,preview_tower.range,preview_tower.damage,
	       preview_tower.fireRate,0,preview_tower.cost};

    /* awesome opacity for the preview */
	showAttackRadius = 1;
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE,GL_ONE_MINUS_DST_COLOR);
    if (t.type == OBJ_BASIC) basicTower(t);
    else if (t.type == OBJ_ADV){
	  advancedTower(t); 
	}
    else if (t.type == OBJ_CONE){ 
	  coneTower(t);
	}
    else if (t.type == OBJ_ADV_CONE){
	  advancedConeTower(t);
	}
    else if (t.type == OBJ_SQUARE){
	  squareTower(t);
	}
    else if (t.type == OBJ_ADV_SQUARE){
	  advancedSquareTower(t);
	}
    else if (t.type == OBJ_FIRE){ 
	  fireTower(t);
	}
    else if (t.type == OBJ_FIRE2){ 
	  advanceFireTower(t);
	}  
    else if (t.type == OBJ_ICE){
	  iceTower(t);
	}
    else if (t.type == OBJ_ICE2){
	  advanceIceTower(t);
	} 
    else if (t.type == OBJ_EARTH){
	  earthTower(t);
	} 
    else if (t.type == OBJ_EARTH2){
	  advanceEarthTower(t);
	}
    glDisable(GL_BLEND);
	showAttackRadius = 0;
  }

  /* towers */
  for (i = 0; i < Length(towers); i++) {
    if (towers[i].inPlay) {
      tower t = {0,towers[i].type,towers[i].inPlay,
		 {towers[i].translation.x,towers[i].translation.y,towers[i].translation.z},
		 {1,1,1},{0,0,0},towers[i].texture,
		 {towers[i].rgb.r,towers[i].rgb.g,towers[i].rgb.b},
		 towers[i].name,towers[i].level,towers[i].range,towers[i].damage,
		 towers[i].fireRate,towers[i].lastFired,towers[i].cost,towers[i].description};

      /* draw the objects */
      if (renderMode == DEF_SELECT) {
	glDisable(GL_DITHER);
	glDisable(GL_LIGHTING);
	glColor3ub(towers[i].rgb.r,towers[i].rgb.g,towers[i].rgb.b);
      }
      if (t.type == OBJ_BASIC) basicTower(t);
      else if (t.type == OBJ_ADV) advancedTower(t);
      else if (t.type == OBJ_CONE) coneTower(t);
      else if (t.type == OBJ_ADV_CONE) advancedConeTower(t);
      else if (t.type == OBJ_SQUARE) squareTower(t);
      else if (t.type == OBJ_ADV_SQUARE) advancedSquareTower(t);
      else if (t.type == OBJ_FIRE) fireTower(t);
      else if (t.type == OBJ_FIRE2) advanceFireTower(t);
      else if (t.type == OBJ_ICE) iceTower(t);
      else if (t.type == OBJ_ICE2) advanceIceTower(t);
      else if (t.type == OBJ_EARTH) earthTower(t);
      else if (t.type == OBJ_EARTH2) advanceEarthTower(t);
      
      if (renderMode == DEF_SELECT) {
	glEnable(GL_DITHER);
	glEnable(GL_LIGHTING);
      }
    }
  }
}

//crtanje scene
void drawScene(void)
{

    //drawAxes();
    //drawGrid();
	drawBackground(3.5*dim);
    drawLight();
    
	drawBoard();
	drawPath();
	//drawSoldier();
	//cube(2,2,2,4,4,4,1);
	//circle(2);
	//sphere(6,6,20,10,3);
	//cone(2,2,-15,6,10,1);
	//cylinder(5,5,-30,6,10);
	drawKeep();
	drawObjects();
}