
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

//definicije tekstura
#define TEX_DEFAULT 0
#define TEX_GRASS 7

/*  Shadows  */
#define DEF_D_FLOOR 45
#define DEF_Y_FLOOR -3

//Vojnici
#define DEF_SOLDIER_OBJ 0