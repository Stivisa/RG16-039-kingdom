typedef struct point {
  float x;
  float y;
  float z;
} point;

typedef struct rgb {
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

typedef struct pathCube {
  point p;
  int texture;
  int rotation;
  int dir;
} pathCube;
