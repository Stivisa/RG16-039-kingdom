#include "kingdom_main.h"

/* Funkcije za generalne stvari u igrici, od resetavanje sve na pocetna podesavanja
 * do promena u ekranu, izbor objekata, pozicija misa
 */

// Funkcija za menjanje pozicija ekrana i ponovno prikazivanje sve
void redisplayAll(void)
{
    glutSetWindow(screen);
    //menjamo poziciju glavnog prozora
    screenReshape(windowWidth,windowHeight - DEF_SPACER - DEF_SIDEBAR_HEIGHT);
    glutPostRedisplay();

    //menjamo velicinu sporednog prozora
    glutSetWindow(sidebar);
    sidebarReshape(windowWidth, DEF_SIDEBAR_HEIGHT);
    glutPostRedisplay();
}


/* Funkcije za restartovanje igrice na pocetna podesavanja
 * sve globalne promenljive vraca na pocetne vrednosti
 */
void reset(void)
{
    int i;

    //resetujemo stil fonta
    fontStyle = DEF_FONT_STYLE;

    //resetujemo projekciju
    asp = DEF_ASP;
    dim = DEF_DIM;
    th = DEF_TH;
    ph = DEF_PH;
    fov = DEF_FOV;
    ecX = DEF_ECX;
    ecY = DEF_ECY;
    ecZ = DEF_ECZ;

    //resetujemo iscrtavanje pomocnih sredstava
    axes = DEF_AXES;
    grid = DEF_GRID;
    vals = DEF_VALS;

    //resetujemo pucanj i detekciju udarca
    showCollisionDetection = DEF_COLLISION;
    lastShot = DEF_LAST_SHOT;

    //reetujemo promenljive vezane za animaciju
    gameStarted = DEF_GAME_STARTED;
    gamePaused = DEF_GAME_PAUSED;
    gameSpeed = DEF_GAME_SPEED;
    moveLightB = DEF_MOVE_LIGHT;
    lightPh = DEF_L_PH;
    moveTowerTopsB = DEF_MOVE_TOWER_TOPS;
    towerTh = DEF_TOWER_TH;

    //resetujemo pomenljive vezane za status igre
    lives = DEF_LIVES;
    money = DEF_MONEY;
    scrolls = DEF_SCROLLS;
    waveNumber = DEF_WAVE;
    lastWave = DEF_LAST_WAVE;

    //resetujemo ako je objekat selektovan
    for (i = 0; i < DEF_CURRENT_OBJS_SIZE; i++) {
	  towers[i].id = 0;
	  towers[i].type = 0;
	  towers[i].translation.x = 0;
	  towers[i].translation.y = 0;
	  towers[i].translation.z = 0;
	  towers[i].texture = 0;
	  towers[i].rgb.r = 0;
	  towers[i].rgb.g = 0;
	  towers[i].rgb.b = 0;
    }
    preview_tower.id = 0;
    preview_tower.type = 0;
    preview_tower.translation.x = 0;
    preview_tower.translation.y = 0;
    preview_tower.translation.z = 0;
    preview_tower.texture = 0;
    preview_tower.name = "preview";


    //resetujemo promenljive fezane za pregled objekta
    preview = DEF_PREVIEW;
    objectSelected = DEF_OBJ_SEL;
    lastCurrentObject = DEF_LAST_CURRENT_OBJECT;
    renderMode = DEF_RENDER;
    objectPicked = DEF_OBJ_PICKED;
    currentRed = DEF_CURRENT_RED;
    currentGreen = DEF_CURRENT_GREEN;
    currentBlue = DEF_CURRENT_BLUE;

    /*Restartujemo vojnike, ali posto vojnici su u talasima,
	 * onada samo restartujemo talas
	 */
    initWaves();

    //Restartujemo promenljive vezane za svetlost
    light = DEF_LIGHT;
    distance = DEF_DISTANCE;
    ambient = DEF_AMBIENT;
    diffuse = DEF_DIFFUSE;
    emission = DEF_EMISSION;
    specular = DEF_SPECULAR;
    shininess = DEF_SHININESS;
    lightY = DEF_L_Y;

    //Postavljamo teksturu na pocetna podesavanja
    currentTexture = TEX_DEFAULT;
    currentTextureSelected = TEX_DEFAULT;
}

/* Funkcija postavljanje informacija trenutno izabranim kulama
 * arguments: int type - tip kule, defenisan u define.h
 * return: void
 */
void setCurrentTowerData(int type)
{
    currentTextureSelected = tower_data[type - 1].texture;
    currentTowerName = tower_data[type - 1].name;
    currentTowerRange = tower_data[type - 1].range;
    currentTowerDamage = tower_data[type - 1].damage;
    currentTowerFireRate = tower_data[type - 1].fireRate;
    currentTowerCost = tower_data[type - 1].cost;
    currentTowerDescription = tower_data[type - 1].description;
}



/* Funkcija za menjanje koji je objekat izabran
 * arguments: int newObjectSelected - tip kule koja je selektovana definisane u define
 * return: void
 */
 void changeObjectSelected(int newObjectSelected)
{
    objectSelected = newObjectSelected;
    preview_tower.id = objectSelected;
    preview_tower.translation.x = -255;
    preview_tower.translation.y = -255;
    preview_tower.translation.z = -255;
    setCurrentTowerData(objectSelected);
}


/* Funkcija za trazenje pozicija misa
 * arguments: int x - x pozicija misa na ekranu
 *			  int y - y pozicija misa na ekranu
 * return: point point - vreca argument tipa point iz structs.h
 */
point findMousePosition(int x, int y)
{
    point point;
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];

    //uzimamo osnovne informacije iz OpenGL
    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);

    winX = (float)x;
    winY = (float)viewport[3] - (float)y - 1;
    //postavljemo Z pociziju
    glReadPixels(x, (int) winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

    /* postvaljamo posX, posY, posZ */
    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

    //informacije za debagovanje
    if (debug) {
	  printf("x y: %d %d\n", x, y);
	  printf("vp : %d %d\n", viewport[2], viewport[3]);
	  printf("win: %f %f %f\n", winX, winY, winZ);
	  printf("pos: %f %f %f\n", posX, posY, posZ);
    }

    point.x = posX;
    point.y = posY;
    point.z = posZ;

    return point;
}

/* Funkcija pronalazi poziciju iz liste preview_points,
 * gde se nalaze jedine validne kordinate za smestanje kule
 * arguments: int x - x pozicija misa
 * 			  int y - y pozicija misa
 *
 * return: point returnP - vraca validnu poziciju na kojoj moze da se smesti kula
 */
point findPreviewPosition(int x, int y)
{
    point p = findMousePosition(x, y);
    point returnP;
    int finalX = (int) p.x;
    int finalZ = (int) p.z;
    int i, j, exists;
    //Definisemo lose vrednosti za kulu
    returnP.x = DEF_BAD_POINT;
    returnP.y = DEF_BAD_POINT;
    returnP.z = DEF_BAD_POINT;
    exists = 0;

    /*trenutna velicina DEF_CURRENT_OBJS_SIZE je
	*velicina validnih pozicija na koje moze da se smeste kule
    */
    for (i = 0; i < DEF_CURRENT_OBJS_SIZE; i++) {
	  /* proveravamo +/-2 od date tacke, da bi ubrzali pretragu */
	  if (finalX >= (preview_points[i].x - 2)
		  && finalX <= (preview_points[i].x + 2)
		  && finalZ >= (preview_points[i].z - 2)
		  && finalZ <= (preview_points[i].z + 2)) {
		  //Proveravamo trenutne kule u slucaju da nije neka postavljena da datoj poziciji
		  for (j = 0; j < Length(towers); j++) {
			if (towers[j].translation.x == preview_points[i].x &&
			  towers[j].translation.z == preview_points[i].z) {
			  //Kula postoji na datoj poziciji prekidamo petlju
			  exists = 1;
			  break;
			}
		  }
		  //Kula ne postoji, postavljamo preview
		  if (!exists) {
			returnP.x = preview_points[i].x;
			returnP.y = 0;
			returnP.z = preview_points[i].z;
			return returnP;
		  }
	  }
    }
    return returnP;
}


/*
    Inkrementiramo boje da bi dobili jedinstvenu kompoziziju boja za nase biranje objekata
 */
void incrementCurrentRGB(void)
{
    currentRed += 10;
    if (currentRed > 255) {
	  currentRed = 5;
	  currentGreen += 10;
	  if (currentGreen > 255) {
	    currentGreen = 5;
	    currentBlue += 10;
		if (currentBlue > 255) {
		  currentBlue = 5;
	    }
	  }
    }
}

/*
   Odredjujemo boju piksela i poredimo sa bojom naseg objekta da bi videli sta je odabrano
 */
void processPicks(void)
{
    int i;
    GLint viewport[4];
    GLubyte pixel[3];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glReadPixels(mouseX, viewport[3] - mouseY, 1, 1, GL_RGB,GL_UNSIGNED_BYTE, (void *) pixel);

	if (debug){
	  printf("R:%d  G:%d  B:%d\n", pixel[0], pixel[1], pixel[2]);
	}
	for (i = 0; i < Length(towers); i++) {
	  GLint red, green, blue;
	  red = towers[i].rgb.r;
	  green = towers[i].rgb.g;
	  blue = towers[i].rgb.b;
	  //Pornasli smo objekat koji nam je trebao iskacemo iz petlje
	  if (pixel[0] == red && pixel[1] == green && pixel[2] == blue) {
	    objectPicked = i;
	    setCurrentTowerData(towers[i].type);
	    break;
	  }
	  //Objekat nije pronadjen postavljamo default
	  else {
	    objectPicked = DEF_OBJ_PICKED;
	  }
    }
}
