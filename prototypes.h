
//generalne funckije iz general.c
void redisplayAll(void);
void reset(void);
void setCurrentTowerData(int type);

//funckije iz init.c
void initialize(void);
void screenInit(void);
void sidebarInit(void);
void initTextures(void);
void initSoldier(void);
void initObjs(void);
void initPath(void);
void initBackground(void);
void initDefaultTowers(void);

//funckije iz draw.c
void drawAxes(void);
void drawGrid(void);
void drawScene(void);
void drawBoard(void);
void drawSoldier(void);
void drawParameters(void);
void drawLight(void);
void drawPath(void);
void drawBackground(double d);
void drawObjects(void);
void drawKeep(void);

//funckije za glavni ekran window.c
void windowDisplay(void);
void windowKey(unsigned char key,int x,int y);
void windowReshape(int width, int height);
void windowVisable(int vis);
void windowSpecial(int key,int x,int y);


//funckije za ekran iz screen.c
void displayInit(void);
void displayEye(void);
void screenDisplay(void);
void screenProject(double fov, double asp, double dim);
void screenReshape(int width, int height);



//funkcije iz models.c
void board();
void soldierModel(soldier m);
void pathBlock(pathCube p);
void path(void);
void crate(double x, double y, double z,double dx,double dy,double dz,double th);
void wall(double x, double y, double z,double dx,double dy,double dz,double th);
void keep(double x, double y, double z,double dx,double dy,double dz,double th);

//ucitavanje BMP fajl loadTexBMP
unsigned int loadTexBMP(char *file);

//funkcije za stampanje i greske u fajlu print.c
void printv(va_list args, const char* format);
void print(const char* format , ...);
void printAt(int x,int y, const char* format , ...);
void errCheck(char* where);
void fatal(const char* format, ...);

//funkcije iz sidebar.c
void sidebarDisplay(void);
void sidebarReshape(int width, int height);

//funkcje iz loadObject.c
int loadOBJ(char *file);

//funkcije iz shapes.c
void square(int s,int a,int b,int c, int d);
void cube(double x,double y, double z, double dx, double dy, double dz, double th);
void vertex(double th,double ph);
void circle(int r);
void sphere(double x,double y,double z,double r,double rot);
void cone(double x,double y,double z,double r,double h,int deg);
void cylinder(double x,double y,double z,double r,double h);
void pyramid(double x, double y, double z,double dx, double dy, double dz,double th);
void star(double x, double y, double z,double dx, double dy, double dz,double th);
void spike(double x, double y, double z,double r,double h,int deg,double ox,double oy,double oz);

//Kule (towers.c)
void basicTower(tower t);
void advancedTower(tower t);
void coneTower(tower t);
void advancedConeTower(tower t);
void squareTower(tower t);
void advancedSquareTower(tower t);
void fireTower(tower t);
void advanceFireTower(tower t);
void iceTower(tower t);
void advanceIceTower(tower t);
void earthTower(tower t);
void advanceEarthTower(tower t);

