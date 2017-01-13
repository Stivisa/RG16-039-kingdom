#include "kingdom_main.h"

/*
 *  Funkcije za detekciju pucnja sa vojnikom
 */

/*
 * Poredimo svakog vojnika sa sferom koja je ispaljena iz kule da bi utvrdili
 *   da li je doslo do udarca. Ovo nije prava detekcija sudara, posto samo poredimo objekete jedne uz druge,
 *  umesto da proveravamo povrsine objekata da li se dodiruju
*/
void checkCollisions(void)
{
    int i, j;
    //Porlazimo kroz pucnjeve
    for (i = 0; i < Length(shots); i++) {
	  shot s = shots[i];
	  if (s.inPlay) {
		// prolazimo kroz sve vojnike u talasu
		for (j = 0; j < Length(waves[waveNumber - 1].s); j++) {
		  if (waves[waveNumber - 1].s[j].inPlay) {
			point origin = s.p;
			point target = waves[waveNumber - 1].s[j].translation;
			point tScale = waves[waveNumber - 1].s[j].scale;
			double distance = sqrt((origin.x - target.x) * (origin.x - target.x) +
			                      (origin.z - target.z) * (origin.z - target.z));
		  
			if (distance < 5 * tScale.x) {
			  //Ako je pogodak , oduzimamo stetu od vojnikovih health-a i izbacujemo pucanj sa scene
			  int health = calculateDamageToMinion(waveNumber - 1, j, i);
			  removeShot(i);
			  //provaravamo helte vojnika, ako su ispod nule, izbacujemo ga
			  if (health <= 0){
			    removeMinion(waveNumber - 1, j);
			  }
			  if (debug) {
			    printf("\n shot  i     :%d\n", i);
			    printf("shot  loc  x:%f\n", origin.x);
			    printf("shot  loc  y:%f\n", origin.y);
			    printf("shot  loc  z:%f\n", origin.z);
			    printf("minion j    :%d\n", j);
			    printf("minion loc x:%f\n", target.x);
			    printf("minion loc y:%f\n", target.y);
			    printf("minion loc z:%f\n", target.z);
			    printf("minion scale:%f\n", tScale.x);
			    printf("distance    :%f\n", distance);
			  }
			  break;
			}
		  }
		}
	  }
    }
}

/*    Proveravamo domet kule, da bi znali da li da pucamo na vojnika
 *  TODO: Formula bas nije tacna, puca samo kada udje u domet, ne i kad je na granici.
 */
void checkTowerRange(void)
{
  int i, j;
  for (i = 0; i < Length(towers); i++) {
	if (towers[i].inPlay) {
	  //Proveravamo kada je kula ispalila poslenji hitac, ako je proslo vise od fireRate pucamo novi
	  time_t fireShot;
	  double timeDiff;
	  fireShot = time(NULL);
	  timeDiff = difftime(fireShot, towers[i].lastFired);
	  if (towers[i].lastFired == 0 || timeDiff > towers[i].fireRate) {
		for (j = 0; j < Length(waves[waveNumber - 1].s); j++) {
		  if (waves[waveNumber - 1].s[j].inPlay) {
			point origin = towers[i].translation;
			point target = waves[waveNumber - 1].s[j].translation;
			point tScale = waves[waveNumber - 1].s[j].scale;
			double distance = sqrt((origin.x - target.x) * (origin.x -target.x) +
								  (origin.z - target.z) * (origin.z -target.z)) - tScale.x;
			
			//Proveravamo da li smo u opsegu napada
			if (distance < towers[i].range) {
			    shot s = { 1, {origin.x, origin.y, origin.z}, towers[i].texture, towers[i].damage };
			    time_t shotFired;
			    shots[lastShot] = s;
			    shotFired = time(NULL);
			    towers[i].lastFired = shotFired;
			    lastShot++;
			    if (debug) {
				  printf("\npew pew\n");
				  printf("fireshot: %f\n", (double) fireShot);
				  printf("timediff: %f\n", timeDiff);
				  printf("checking tower range\n");
				  printf ("target in range- fire ze missiles!\n");
				  printf("tower i     :%d\n", i);
				  printf("tower loc  x:%f\n", origin.x);
				  printf("tower loc  y:%f\n", origin.y);
				  printf("tower loc  z:%f\n", origin.z);
				  printf("tower range :%d\n", towers[i].range);
				  printf("minion j    :%d\n", j);
				  printf("minion loc x:%f\n", target.x);
				  printf("minion loc y:%f\n", target.y);
				  printf("minion loc z:%f\n", target.z);
				  printf("minion scale:%f\n", tScale.x);
				  printf("distance    :%f\n", distance);
				}

			    break;
			}
		  }
		}
	  }
	}
  }

  
}
