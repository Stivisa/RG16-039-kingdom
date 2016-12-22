
//definisemo aproksimaciju kosinusa i sinusa u stepenima
#define Cos(x) (cos(x*3.1415927/180))
#define Sin(x) (sin(x*3.1415927/180))

//Odredjivanje velicine niza
#define Length(x) (sizeof(x)/sizeof *(x))

// pocetne vrednosti ekrana 
#define DEF_FULL_SCREEN 0
#define DEF_WINDOW_HEIGHT 800
#define DEF_WINDOW_WIDTH 1000

//prostor izmedju glavnog prozora i pomocnog
#define DEF_SPACER 10

//sidebar velicina
#define DEF_SIDEBAR_HEIGHT 200

//velicina teksta
#define DEF_TEXT_Y_OFFSET 20

// pocetne vredneosti projekcije
#define DEF_ASP 1
#define DEF_DIM 25
#define DEF_TH 250
#define DEF_PH 40
#define DEF_FOV 55
#define DEF_ECX 2
#define DEF_ECY 0
#define DEF_ECZ 4

// ukljucuje/iskljucujemo sta crtamo
#define DEF_AXES 0
#define DEF_GRID 0
#define DEF_D 5
#define DEF_VALS 0
#define DEF_SHOW_ATTACK 0

//definicije tekstura
#define TEX_DEFAULT 0
#define TEX_BRICK 1
#define TEX_FIRE 2
#define TEX_ICE 3
#define TEX_EARTH 4
#define TEX_POISON 5
#define TEX_SPIKE 6
#define TEX_GRASS 7
#define TEX_WOOD 8
#define TEX_BRICK2 9
#define TEX_CRATE 10
#define TEX_STREET1 11
#define TEX_STREET2 12
#define TEX_STREET3 13
#define TEX_STREET4 14
#define TEX_STREET5 15
#define TEX_STREET6 16

//Pozadina
#define BACK_FRONT 0
#define BACK_RIGHT 1
#define BACK_LEFT 2
#define BACK_BACK 3
#define BACK_UP 4
#define BACK_DOWN 5

/*  Shadows  */
#define DEF_D_FLOOR 45
#define DEF_Y_FLOOR -3

//Vojnici
#define DEF_SOLDIER_OBJ 0

//kule
#define DEF_CURRENT_OBJS_SIZE 57
#define DEF_LAST_CURRENT_OBJECT 0
#define DEF_OBJ_SEL 0
#define DEF_PREVIEW 1
#define DEF_RENDER 1
#define DEF_SELECT 2
#define DEF_CURRENT_RED 5
#define DEF_CURRENT_GREEN 5
#define DEF_CURRENT_BLUE 5
#define DEF_CURRENT_TOWER_NAME "Basic"
#define DEF_CURRENT_TOWER_RANGE 5
#define DEF_CURRENT_TOWER_DAMAGE 5
#define DEF_CURRENT_TOWER_FIRE_RATE 4
#define DEF_CURRENT_TOWER_COST 10
#define DEF_CURRENT_TOWER_DESCRIPTION "A basic tower"
#define DEF_LAST_CURRENT_OBJECT 0
#define DEF_TOWER_TH 0

//svetlost
#define DEF_LIGHT 1
#define DEF_DISTANCE 40
#define DEF_AMBIENT 35
#define DEF_DIFFUSE 100
#define DEF_EMISSION 0
#define DEF_SPECULAR 0
#define DEF_SHININESS 0
#define DEF_L_Y 0
#define DEF_L_PH 90

#define DEF_RENDER 1


//putanja
#define DEF_FULL_PATH_LEN 50
#define DEF_NORTH 270
#define DEF_EAST 180
#define DEF_SOUTH 90
#define DEF_WEST 0
#define DEF_PATH_LEN 45


//definicanje objekata napravljenih u igri kule, piramide ...
#define OBJ_FIRE 1
#define OBJ_FIRE2 2
#define OBJ_ICE 3
#define OBJ_ICE2 4
#define OBJ_EARTH 5
#define OBJ_EARTH2 6
#define OBJ_BASIC 7
#define OBJ_ADV 8
#define OBJ_CONE 9
#define OBJ_ADV_CONE 10
#define OBJ_SQUARE 11
#define OBJ_ADV_SQUARE 12