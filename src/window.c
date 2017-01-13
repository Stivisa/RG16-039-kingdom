#include "kingdom_main.h"

//funkcija koja sve prikazuje
void windowDisplay(void)
{
    glClearColor(0.8, 0.8, 0.8, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();
}

//funkcija za osnovne komande u igrici
void windowKey(unsigned char key, int x, int y)
{
    /*  Prekid na ESC */
    if (key == 27){
	  exit(0);
    //Space za pocetak igre ili slanje novog talasa
	}else if (key == 32) {
	  if(gameStarted == DEF_GAME_STARTED){
		gameStarted = 1;
	    gamePaused = 0;
	    waveNumber = 1;
	    timer(1);
	  }else{
	    //Za sada dozvoljeno samo jedan talas u jednom trenutku
	    if (waveNumber < DEF_LAST_WAVE) {
		  int i, inPlay = 0;
		  for (i = 0; i < Length(waves[waveNumber - 1].s); i++) {
		    if (waves[waveNumber - 1].s[i].inPlay == 1){
			  inPlay = 1;
			}
		  }
		  if (inPlay == 0)
		    waveNumber++;
		  }
	  }

    //resetovanje igre na pocetak
	}else if (key == 'r' || key == 'R'){
	  reset();
    //Cheat za pare
	}else if (key == 'q'){
	  money += 100;
    //Ukljucujemo ose
	}else if (key == 'x' || key == 'X'){
	  axes = 1 - axes;
    //Ukljucujemo mrezu
	}else if (key == 'g' || key == 'G'){
	  grid = 1 - grid;
    //Ukljucujemo radijus napda
	}else if (key == 'c' || key == 'C'){
	  showAttackRadius = 1 - showAttackRadius;
    //Menjamo da li vrednosti da budu prikazane na ekranu
	}else if (key == 'v' || key == 'V'){
	  vals = 1 - vals;
    //Menjano ugao gledanja
	}else if (key == '-' && key > 1){
	  fov--;
	}else if (key == '+' && key < 179){
	  fov++;
    //Menjanmo dim
	}else if (key == 'i' && dim > 1){
	  dim -= 0.2;
	}else if (key == 'I'){
	  dim += 0.2;
    //Usporavamo animaciju
	}else if (key == 'z'){
	  slowAnimate();
    //Prikaz svetlosti
	}else if (key == 'm'){
	  moveLightB = 1 - moveLightB;
    //Pauziranja igre
	}else if (key == 'p'){
	  gamePaused = 1 - gamePaused;
    //Okretanje vrhova kula
	}else if (key == 'M'){
	  moveTowerTopsB = 1 - moveTowerTopsB;
      //Ukljucenje svetlosti
	}else if (key == 'l' || key == 'L'){
	  light = 1 - light;
    //Kretanje svetlosti koji pravac
	}else if (key == '<'){
	  lightPh -= 1;
	}else if (key == '>'){
	  lightPh += 1;
    //Visina svetlosti
	}else if (key == '['){
	  lightY -= 0.1;
	}else if (key == ']'){
	  lightY += 0.1;
    // Ambient level
	}else if (key == 'a' && ambient > 0){
	  ambient -= 5;
	}else if (key == 'A' && ambient < 100){
	  ambient += 5;
    // Diffuse level
	}else if (key == 'd' && diffuse > 0){
	  diffuse -= 5;
	}else if (key == 'D' && diffuse < 100){
	  diffuse += 5;
    //  Specular level
	}else if (key == 's' && specular > 0){
	  specular -= 5;
	}else if (key == 'S' && specular < 100){
	  specular += 5;
    //  Emission level
	}else if (key == 'e' && emission > 0){
	  emission -= 5;
	}else if (key == 'E' && emission < 100){
	  emission += 5;
    //  Shininess level
	}else if (key == 'n' && shininess > -1){
	  shininess -= 1;
	}else if (key == 'N' && shininess < 7){
	  shininess += 1;
	//ukljucenje iskljucenje sume, zbog optimizacije igre, nizak fps
	}else if(key == 'f'){ 
	   forest= 1 - forest; 
    //Selekcija kula
	}else if (key == '4'){
	  changeObjectSelected(OBJ_FIRE);
	}else if (key == '5'){
	  changeObjectSelected(OBJ_FIRE2);
	}else if (key == '6'){
	  changeObjectSelected(OBJ_ICE);
	}else if (key == '7'){
	  changeObjectSelected(OBJ_ICE2);
	}else if (key == '8'){
	  changeObjectSelected(OBJ_EARTH);
	}else if (key == '9'){
	  changeObjectSelected(OBJ_EARTH2);
	}else if (key == '0'){
	  changeObjectSelected(DEF_OBJ_SEL);
	}else if (key == '1'){
	  changeObjectSelected(OBJ_BASIC);
	}else if (key == '2'){
	  changeObjectSelected(OBJ_ADV);
	}else if(key == '3'){
	  changeObjectSelected(OBJ_SQUARE);
    //preview ukljucenje
	}else if (key == 'w' || key == 'W') {
	  preview = 1 - preview;
	  //restartujemo na pocetnu kulu ako je preview ukljucen
	  if (preview == DEF_PREVIEW){
	    preview_tower.id = DEF_OBJ_SEL;
	  }

    //Backspace i delete za brisanje kula
	}else if (key == 8 || key == 127) {
	  if (objectPicked != DEF_OBJ_PICKED) {
	    towers[objectPicked].id = DEF_OBJ_PICKED;
	    towers[objectPicked].type = DEF_OBJ_SEL;
	    towers[objectPicked].translation.x = 0;
	    towers[objectPicked].translation.z = 0;
	    towers[objectPicked].texture = 0;
	    towers[objectPicked].rgb.r = 0;
	    towers[objectPicked].rgb.g = 0;
	    towers[objectPicked].rgb.b = 0;
	    towers[objectPicked].inPlay = 0;
	    objectPicked = DEF_OBJ_PICKED;
	    if (debug)
		  printf("Killed current object picked ID: %d\n", objectPicked);
	  }
    }

    /* Sijanje prebacivanje sa (-1 => 0) */
    shinyvec[0] = shininess < 0 ? 0 : pow(2.0, shininess);

    redisplayAll();
}

//funkcija za specijalne komande
//rotacija kamere, pomeranje kamere
void windowSpecial(int key, int x, int y)
{
    int modifiers = glutGetModifiers();

    //Stiskamo SHIFT da bi aktivirali pomeranje kamere
    if (modifiers == GLUT_ACTIVE_SHIFT) {
	  //rotacija levo desno
	  if (key == GLUT_KEY_RIGHT) {
	    th += 5;
	  } else if (key == GLUT_KEY_LEFT) {
	    th -= 5;

	  //pomeranje gore dole
	  }else if (key == GLUT_KEY_UP) {
	    ph += 5;
	  }else if (key == GLUT_KEY_DOWN) {
	    ph -= 5;
	  }

    //u drugim slucajevima samo pomeri ekran
	}else {

	  if (key == GLUT_KEY_RIGHT) {
	    ecZ -= .5;
	  } else if (key == GLUT_KEY_LEFT) {
		 ecZ += .5;
	  } else if (key == GLUT_KEY_UP) {
	    ecX -= .5;
	  } else if (key == GLUT_KEY_DOWN) {
	    ecX += .5;
	  }
    }

    //Ostavljamo isti ugao
    th %= 360;
    ph %= 360;

    redisplayAll();
}

//menjanje ekrana
void windowReshape(int width, int height)
{
    windowHeight = height;
    windowWidth = width;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, height, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //menjamo velicinu glavnog prozora
    glutSetWindow(screen);
    glutPositionWindow(0, 0);
    glutReshapeWindow(windowWidth, windowHeight - DEF_SIDEBAR_HEIGHT - DEF_SPACER);

    //menjamo velicinu pod prozora
    glutSetWindow(sidebar);
    glutPositionWindow(0, windowHeight - DEF_SIDEBAR_HEIGHT);
    glutReshapeWindow(windowWidth, DEF_SIDEBAR_HEIGHT);

}
