
//generalne funckije iz general.c
void redisplayAll(void);
void reset(void);

//funckije iz init.c
void initialize(void);
void screenInit(void);

//funckije iz ground.c
void drawAxes(void);
void drawGrid(void);
void drawScene(void);

//funckije za glavni ekran window.c
void windowDisplay(void);
void windowKey(unsigned char key,int x,int y);
void windowReshape(int width, int height);


//funckije za ekran iz screen.c
void displayInit(void);
void displayEye(void);
void screenDisplay(void);
void screenProject(double fov, double asp, double dim);
void screenReshape(int width, int height);


