typedef struct _point {
  float x;
  float y;
  float z;
} point;

typedef struct _rgb {
  int r;
  int g;
  int b;
} rgb;

typedef struct _soldier {
  int id;
  int type;
  point translation;
  point scale;
  point rotation;
  int texture;
  rgb rgb;
  
  //podaci u igrici
  char* name;
  int damage;
  int health;
  int money;
  double speed;
  int inPlay;
} soldier;

typedef struct _pathCube {
  point p;
  int texture;
  int rotation;
  int dir;
} pathCube;

typedef struct _tower {
  int id;
  int type;
  int inPlay;
  point translation;
  point scale;
  point rotation;
  int texture;
  rgb rgb;
  //podaci u igrici
  char* name;
  int level;
  int range;
  int damage;
  int fireRate;
  double lastFired;
  int cost;
  char* description;
} tower;


typedef struct _wave {
  int id;
  int number;
  soldier s[DEF_MINION_PER_WAVE_SIZE];
} wave;



typedef struct _shot {
  int inPlay;
  point p;
  int texture;
  int damage;
} shot;