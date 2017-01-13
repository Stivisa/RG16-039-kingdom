#include "kingdom_main.h"

/* FUnkcije koje se nalaze u ovom fajlu pomazu pro obradi glavnog
 * prozora gde se sve animacije odvijaju.
 */


//inicijalizacija ekrana
void displayInit(void)
{
    setFont("helvetica", 18);

    glClearColor(0.8, 0.8, 0.8, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
}

//racunanje odakle gledamo, pozicija kamere
void displayEye(void)
{
    double Ex = -2 * dim * Sin(th) * Cos(ph);
    double Ey = 2 * dim * Sin(ph);
    double Ez = 2 * dim * Cos(th) * Sin(ph);
    //th=th+90;
    gluLookAt(Ex + ecX, Ey, Ez + ecZ, ecX, ecY, ecZ, 0, Cos(ph), 0);
}

//Funckija za inicijalizaciju ekrana, kamere i iscrtavanje scene
void screenDisplay(void)
{
    //ciscenje ekrana i postavljane kamere
    displayInit();
    displayEye();

    drawScene();

    if (renderMode == DEF_SELECT) {
	  processPicks();
	  renderMode = DEF_RENDER;
    }else {
	  glFlush();
	  glutSwapBuffers();
    }

    errCheck("display sanity check");
}

/* 
 * Funkcija za postavljanje matrice projekcije
 * argumenti: double fov - ugao polje pogleda(field of view) u y direkciji
 * 			  double asp - odnos velicina polje pogleda prema x, uglavnom ide x(width)/y(height)
 * 			  double dim - velicina pogleda po z osi
 * 
 */
void screenProject(double fov, double asp, double dim)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, asp, dim / 16, 16 * dim);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*
 * Funkcija za menjanje velicinine prikaza prozora kada korisnik menja velicinu prozora
 * argumenti: int width - sirina novog prozora
 * 			  int height - visina novog prozora
 * 
 */
void screenReshape(int width, int height)
{
    //postavljamo odgovarajucu proporciju
    asp = (height > 0) ? (double) width / height : 1;
    windowWidth = width;

    //postavljanje viewport-a za ceo prozora
    glViewport(0, 0, width, height);
    screenProject(fov, asp, dim);
}


/* 
 * Funkcija za obradu pokreta misa na glavnom prozoru
 * argumenti: int btn - dugme koje je kliknuto
 * 			  int state - u kom stanju je dugme da li je pritisnuto ili pusteno
 * 			  int x - pozicija misa na x osi
 * 			  int y - pozicija misa na y osi
 * 
 */
void screenMouse(int btn, int state, int x, int y)
{
    point p;
    //Izlazimo iz funkcije ako nije pritisnuto levo dugme misa i ako objekat nije selektovan
    if ((btn != GLUT_LEFT_BUTTON || state != GLUT_DOWN)){
	  return;
	}

    p = findPreviewPosition(x, y);
    mouseX = x;
    mouseY = y;
    renderMode = DEF_SELECT;

    //Dodajemo novu kulu
    if (objectSelected != DEF_OBJ_SEL && p.x != DEF_BAD_POINT) {
	  int modifiers = glutGetModifiers();
	  renderMode = DEF_RENDER;
	  //Informacije za igru
	  if (money >= tower_data[objectSelected - 1].cost) {
	    info = "cha-ching$ thanks buddy.";
	    setCurrentTowerData(objectSelected);
	  }else{
	    info = "Not enough $$$.";
	    objectSelected = DEF_OBJ_SEL;
	    preview_tower.id = DEF_OBJ_SEL;
	  }

	  if (objectSelected != DEF_OBJ_SEL) {
	    tower t = { objectSelected, objectSelected, 1, {p.x, p.y, p.z}
		, {1, 1, 1}, {0, 0, 0}, currentTextureSelected,
		{currentRed, currentGreen, currentBlue},
		/* name,level,range,damage,fireRate,lastFired,cost,description */
		currentTowerName, 1, currentTowerRange, currentTowerDamage,
		currentTowerFireRate, 0, currentTowerCost, "Description"
	    };
	    towers[lastCurrentObject] = t;
	    modifyMoney(0, currentTowerCost);

	    //Inkrementiramo rgb zbog selekcije objekata
	    incrementCurrentRGB();

        if (debug){
		  printf("just added object id: %d\n", lastCurrentObject);
		}
	    //Inkrementiramo poslednji selektovan objekat, na 57 se restartuje psoto je na to ogranicen
	    lastCurrentObject++;
	    if (lastCurrentObject == DEF_CURRENT_OBJS_SIZE){
		  lastCurrentObject = 0;
		}
	    //Restartujemo selektovan objekta na default u slucaju kada shift nije pritisnuto
	    if (modifiers != GLUT_ACTIVE_SHIFT) {
		  objectSelected = DEF_OBJ_SEL;
		  preview_tower.id = DEF_OBJ_SEL;
	    }
	  }
    }

    redisplayAll();
}


/*
 * Omogucava da imamo pregled kula u igrici, kada gledamo gde cemo da je smestimo
 * argumenti: int x - preview pozicija kule na x osi
 * 			  int y - preview pozicija kule na y osi
 * 
 */
void screenPmotion(int x, int y)
{
    if (preview && objectSelected != DEF_OBJ_SEL) {
	  point p = findPreviewPosition(x, y);
	  if (p.x != DEF_BAD_POINT) {
	    preview_tower.id = objectSelected;
	    preview_tower.type = objectSelected;
	    preview_tower.inPlay = 1;
	    preview_tower.translation.x = p.x;
	    preview_tower.translation.y = p.y;
	    preview_tower.translation.z = p.z;
	    preview_tower.texture = tower_data[objectSelected - 1].texture;
	    preview_tower.name = tower_data[objectSelected - 1].name;
	    preview_tower.range = tower_data[objectSelected - 1].range;
	    preview_tower.damage = tower_data[objectSelected - 1].damage;
	    preview_tower.fireRate =
		tower_data[objectSelected - 1].fireRate;
	    preview_tower.cost = tower_data[objectSelected - 1].cost;

	    redisplayAll();
	  }
    }
}
