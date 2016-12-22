#include "kingdom_main.h"

//tesrianje gita ne radi kako treba

//Funkcije za resetovanje podesavanja

void redisplayAll(void)
{

    glutSetWindow(screen);
    //menjamo poziciju glavnog prozora
    screenReshape(windowWidth,
		  windowHeight - DEF_SPACER - DEF_SIDEBAR_HEIGHT);
    glutPostRedisplay();

    //menjamo velicinu sporednog prozora
    glutSetWindow(sidebar);
    sidebarReshape(windowWidth, DEF_SIDEBAR_HEIGHT);
    glutPostRedisplay();
}

void reset(void)
{
	int i;
    //resetovanje projekcije
    asp = DEF_ASP;
    dim = DEF_DIM;
    th = DEF_TH;
    ph = DEF_PH;
    fov = DEF_FOV;
    ecX = DEF_ECX;
    ecY = DEF_ECY;
    ecZ = DEF_ECZ;

    // resetovanje crtanja
    axes = DEF_AXES;
    grid = DEF_GRID;
	vals = DEF_VALS;

	//resetujemo svetlost
	light     = DEF_LIGHT;
	distance  = DEF_DISTANCE;
	ambient   = DEF_AMBIENT;
	diffuse   = DEF_DIFFUSE;
	emission  = DEF_EMISSION;
	specular  = DEF_SPECULAR;
	shininess = DEF_SHININESS;
	lightY    = DEF_L_Y;
	
	//restartovanje objekata
	for (i=0;i<DEF_CURRENT_OBJS_SIZE;i++) {
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
	preview_tower.name = "pregled";
	
    //resetovanje tekstura
    currentTexture = TEX_DEFAULT;
    currentTextureSelected = TEX_DEFAULT;
}

//postavljanje informacija o kulama
void setCurrentTowerData(int type)
{
  currentTextureSelected = tower_data[type-1].texture;
  currentTowerName = tower_data[type-1].name;
  currentTowerRange = tower_data[type-1].range;
  currentTowerDamage = tower_data[type-1].damage;
  currentTowerFireRate = tower_data[type-1].fireRate;
  currentTowerCost = tower_data[type-1].cost;
  currentTowerDescription = tower_data[type-1].description;
}
