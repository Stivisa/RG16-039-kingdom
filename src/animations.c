#include "kingdom_main.h"

//Pocetak funkcija za animaciju

/*
 *Tajmer, da li je igra pauzirana i da li je pokrenuta
 */
void timer(int toggle)
{
    if (gameStarted) {
	    if (gamePaused != DEF_GAME_PAUSED) {
	            moveLight();
	            moveTowerTops();
	            moveShots();
	            checkCollisions();
	            moveMinions();
	            checkCollisions();
	            checkTowerRange();
	    }
	    glutTimerFunc(50, timer, 0);
    }
    redisplayAll();
}

//Prolazimo kroz proces animacija , sve funkcije koje se koriste su ovde ukljucene
void slowAnimate()
{
    moveLight();
    moveTowerTops();
    moveShots();
    checkCollisions();
    moveMinions();
    checkCollisions();
    checkTowerRange();
}

//Funkcija pomera svetlost, tako da imamo osecaj kao da je sunce
void moveLight(void)
{
    if (moveLightB){
	    lightPh = (lightPh + 2) % 360;
    }
}


/* Funkcija pomera vojnika i iz talasa k na poziciju fullPath j
*  argumenti: int k - broj talasa iz kog je vojnika
*             int i - redni broj vojnika kojeg pomeramo
*             int j - pozicija na putu na koju vojnika pomeramo
*/
void moveMinion(int k, int i, int j)
{
    waves[k].s[i].translation.x = fullPath[j].p.x;
    waves[k].s[i].translation.z = fullPath[j].p.z;
    waves[k].s[i].rotation.y = fullPath[j].dir;
}

// Funkcija za pomeranje vojnika
void moveMinions(void)
{
    int i, j, k;
    /* Za svaki talas u igri pomeramo vojnike
       trenutno je implemetnirano samo da jedan talas moze u jednom trenutku da bude aktivan
       ali u slucaju ako budem dalje razvijao igricu, ne zelim da prepravljam mnogo kod
       pa zbog toga je ovako implemetirano preko for petlje
    */
    //  for (k=0;k<waveNumber;k++) {
    for (k = waveNumber - 1; k == waveNumber - 1; k++) {

	//Za svakog vojnika u talasu
	for (i = 0; i < Length(waves[k].s); i++) {
	  int speed = waves[k].s[i].speed;
	  int damage = waves[k].s[i].damage;

	  for (j = 0; j < (DEF_PATH_LEN * DEF_FULL_PATH_LEN); j += speed) {
		//Ako je vojnik u igri i ispred dvorca primi stetu i izbaci vojnika iz igre
		if (waves[k].s[i].inPlay == 1 && waves[k].s[i].translation.x <= -15 &&
			waves[k].s[i].translation.z == 11) {
		  //Vojnik ti nanosi stetu i izbacujemo ga iz igre
		  modifyLives(1, damage);
		  waves[k].s[i].inPlay = 0;
		  break;
		}

		  //Prvi vojnik
		  if (i == 0) {
		    //pocetni ulaz
		    if (waves[k].s[i].translation.x > 25) {
			moveMinion(k, i, 0);
			break;

		    //Ako imamo predhocnu poziciju povecavamo je za 1
            }else if (waves[k].s[i].translation.x == fullPath[j - speed].p.x
			     && waves[k].s[i].translation.z == fullPath[j - speed].p.z) {
			        moveMinion(k, i, j);
			        break;
		    }

		  //Svaki drugi vojnik
		  }else {
		    //prvi prolaz
		    if (fabs(waves[k].s[i - 1].translation.x - waves[k].s[i].translation.x) > ((waves[k].s[i].scale.x) * 20)
			    || fabs(waves[k].s[i - 1].translation.z - waves[k].s[i].translation.z) > 0) {
			  if (waves[k].s[i].translation.x > 25) {
			    moveMinion(k, i, 0);
			    break;

			  //Iz predhodne pozicihe racunamo sledecu
              }else if (waves[k].s[i].translation.x == fullPath[j - speed].p.x
				 && waves[k].s[i].translation.z == fullPath[j - speed].p.z) {
			    moveMinion(k, i, j);
			    break;
			  }
		    }
		  }
	  }
	}
    }
}

//Pomera pucanj ka vojniku
void moveShot(int i, int j, int k)
{
    //Odredjujemo vektor ka vojniku
    point target = waves[j].s[k].translation;
    point origin = shots[i].p;
    double xFactor = 0.0, zFactor = 0.0;
    if (target.x > origin.x){
	   xFactor = 0.5;
	}else if (target.x == origin.x){
	  xFactor = 0.0;
    }else if (target.x < origin.x){
	  xFactor = -0.5;
    }
    if (target.z > origin.z){
	  zFactor = 0.5;
    }else if (target.z == origin.z){
	  zFactor = 0.0;
    }else if (target.z < origin.z){
	  zFactor = -0.5;
    }
    shots[i].p.x += xFactor;
    shots[i].p.z += zFactor;
}

// Pomeramo vise pucnjeva prema najdaljem vojniku u talasu
 void moveShots(void)
{
    int i, j;
    for (i = 0; i < lastShot; i++) {
	    //shot s = shots[i];
	  for (j = 0; j < Length(waves[waveNumber - 1].s); j++) {
	    if (waves[waveNumber - 1].s[j].inPlay) {
		  moveShot(i, waveNumber - 1, j);
		break;		//ispalujemo hitac samo prema prvom vojniku u talasu
	    }
	  }
    }
}

//Animacija kula, okretanje vrhova kula
void moveTowerTops(void)
{
  if (moveTowerTopsB){
	towerTh = (towerTh + 2) % 360;
  }
  
}
