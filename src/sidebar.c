#include "kingdom_main.h"

//prikazivanje dodatnog prozora
void sidebarDisplay(void)
{
    int line = 1;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    sidebarRow(windowWidth / 2, DEF_SIDEBAR_HEIGHT - 20, -1, "KINGDOM");
    setFont("helvetica", 16);
    printAt(10, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line, "WAVE: %d out of %d", waveNumber, lastWave);
    printAt(10, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line, "SCORE: %d", score);
    printAt(10, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line, "LIVES: %d", lives);
    printAt(10, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line, "MONEY: %d", money);
    printAt(10, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line, "SCROLLS: %d", scrolls);

    //Ove pozicije moraju da se potrefe sa klikom misa
    setFont("helvetica", 12);

	line = 2;
    sidebarRow(windowWidth / 5 - 5, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line, -1,
				"Select a tower to build:");
    setFont("helvetica", 16);
    sidebarRow(windowWidth / 5, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line,
				DEF_OBJ_SEL, "[0] none");
    sidebarRow(windowWidth / 5, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line, OBJ_BASIC,
				"[1] basic");
    sidebarRow(windowWidth / 5, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line, OBJ_ADV,
				"[2] advanced");
    sidebarRow(windowWidth / 5, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line, OBJ_SQUARE,
				"[3] square");
    sidebarRow(windowWidth / 5, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line, OBJ_FIRE,
			  "[4] fire");

	line = 3;
    sidebarRow(windowWidth / 3, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line, OBJ_FIRE2,
			  "[5] advanced fire");
    sidebarRow(windowWidth / 3, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line, OBJ_ICE,
			  "[6] ice");
    sidebarRow(windowWidth / 3, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line, OBJ_ICE2,
			  "[7] advanced ice");
    sidebarRow(windowWidth / 3, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line, OBJ_EARTH,
			  "[8] earth");
    sidebarRow(windowWidth / 3, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line, OBJ_EARTH2,
			  "[9] advanced earth");

    line = 2;
    setFont("helvetica", 12);
    glColor3fv(white);
    printAt(windowWidth / 2 + 30, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line, "INFO");
    printAt(windowWidth / 2 + 30, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line, "%s", info);
    printAt(windowWidth / 2 + 30, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line, "TOWER INFO");
    if (objectSelected != DEF_OBJ_SEL || objectPicked != DEF_OBJ_PICKED) {
	  printAt(windowWidth / 2 + 30, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line, "Name: %s", currentTowerName);
	  printAt(windowWidth / 2 + 30, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line,
			  "Cost: %d", currentTowerCost);
	  printAt(windowWidth / 2 + 30, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line,
			  "Damage: %d", currentTowerDamage);
	  printAt(windowWidth / 2 + 30, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line,
			"Range: %d", currentTowerRange);
	  printAt(windowWidth / 2 + 30, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line,
			"Fire Rate: %d", currentTowerFireRate);

	  line = 6;
	  printAt(windowWidth / 2 + 130, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line,"Description:");
	  printAt(windowWidth / 2 + 130, DEF_SIDEBAR_HEIGHT - DEF_TEXT_Y_OFFSET * ++line, "   %s", currentTowerDescription);
    }
    if (debug){
	  //printAt(5, windowHeight-DEF_TEXT_Y_OFFSET*++line, "Object Picked: %d", objectPicked);
	}
	setFont("helvetica", 18);


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

//dodaje red teksta sa na x,y
void sidebarRow(int x, int y, int obj, char *text)
{
    glColor3fv(white);
    if (objectSelected == obj) {
	  glColor3f(1, 0, 1);
    }
    printAt(x, y, text);
    glColor3fv(white);
}


/*
 Funkcije za kada je mis pritisnut na sidebar
 */
void sidebarMouse(int btn, int state, int x, int y)
{
    int lineUp1 = 2;
    int lineDown1 = 3;
	int lineUp2=2;
	int lineDown2=3;
    //Samo levi klik misa
    if (btn != GLUT_LEFT_BUTTON || state != GLUT_DOWN){
	  return;
	}
    //Pozicija odakle startuje mis
    if (y < DEF_SIDEBAR_HEIGHT-5 && y >= 5) {
	  if (y >= DEF_TEXT_Y_OFFSET * ++lineUp1 + 5 && y < DEF_TEXT_Y_OFFSET * ++lineDown1 + 9 && x>=windowWidth/5 && x<windowWidth/3){
	    changeObjectSelected(DEF_OBJ_SEL);
	  }else if (y >= DEF_TEXT_Y_OFFSET * ++lineUp1 + 9 && y < DEF_TEXT_Y_OFFSET * ++lineDown1 + 9 && x>=windowWidth/5 && x<windowWidth/3){
	    changeObjectSelected(OBJ_BASIC);
	  }else if (y >= DEF_TEXT_Y_OFFSET * ++lineUp1 + 9 && y < DEF_TEXT_Y_OFFSET * ++lineDown1 + 9 && x>=windowWidth/5 && x<windowWidth/3){
	    changeObjectSelected(OBJ_ADV);
	  }else if (y >= DEF_TEXT_Y_OFFSET * ++lineUp1 + 9 && y < DEF_TEXT_Y_OFFSET * ++lineDown1 + 9 && x>=windowWidth/5 && x<windowWidth/3){
	    changeObjectSelected(OBJ_SQUARE);
	  }else if (y >= DEF_TEXT_Y_OFFSET * ++lineUp1 + 9 && y < DEF_TEXT_Y_OFFSET * ++lineDown1 + 9 && x>=windowWidth/5 && x<windowWidth/3){
	    changeObjectSelected(OBJ_FIRE);
	  }else if (y >= DEF_TEXT_Y_OFFSET * ++lineUp2 + 9 && y < DEF_TEXT_Y_OFFSET * ++lineDown2 + 9 && x>=windowWidth/3 && x<windowWidth/2){
	    changeObjectSelected(OBJ_FIRE2);
	  }else if (y >= DEF_TEXT_Y_OFFSET * ++lineUp2 + 9 && y < DEF_TEXT_Y_OFFSET * ++lineDown2 + 9 && x>=windowWidth/3 && x<windowWidth/2){
	    changeObjectSelected(OBJ_ICE);
	  }else if (y >= DEF_TEXT_Y_OFFSET * ++lineUp2 + 9 && y < DEF_TEXT_Y_OFFSET * ++lineDown2 + 9 && x>=windowWidth/3 && x<windowWidth/2){
	    changeObjectSelected(OBJ_ICE2);
	  }else if (y >= DEF_TEXT_Y_OFFSET * ++lineUp2 + 9 && y < DEF_TEXT_Y_OFFSET * ++lineDown2 + 9 && x>=windowWidth/3 && x<windowWidth/2){
	    changeObjectSelected(OBJ_EARTH);
	  }else if (y >= DEF_TEXT_Y_OFFSET * ++lineUp2 + 9 && y < DEF_TEXT_Y_OFFSET * ++lineDown2 + 9 && x>=windowWidth/3 && x<windowWidth/2){
	    changeObjectSelected(OBJ_EARTH2);
	  }
	}
    redisplayAll();
}
