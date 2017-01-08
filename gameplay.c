#include "kingdom_main.h"

/*
 *  Osnovne funkcije za gameplay igrice, racunanje da li korisnik moze kupiti kulu
    Stetu koju vojnici nanose i koja se nanosi vojnicima, racunanje para ...
 */


//Funkcija racuna stetu nanetu konkretnom vojniku i vraca trenute helte vojnik
int calculateDamageToMinion(int k, int j, int i)
{
    waves[k].s[j].health -= shots[i].damage;
    return waves[k].s[j].health;
}

    //Odredju da li korisnik moze da kupi datu kulu i postavlja zadate vrednosti za tu kulu

void canUserBuyTower(int newObjectSelected)
{
    if (money >= tower_data[objectSelected - 1].cost) {
	info = "cha-ching$ thanks buddy";
	setCurrentTowerData(objectSelected);
    } else {
	info = "Not enough $$$.";
	objectSelected = DEF_OBJ_SEL;
	preview_tower.id = DEF_OBJ_SEL;
    }
}

/*Modifikuje helte dvorca zavisnosti da li kupujemo ih ili gubimo
ih od strane vojnika
 */
void modifyLives(int die, int damage)
{
    if (die) {
	lives -= damage;
    } else {
	//kupujemo
	lives++;
    }
}

//Modifikujemo novac zavisno da li kupujemo,ubijamo vojnike ili prodajemo

void modifyMoney(int what, int amount)
{
    //kupujemo
    if (what == 0) {
	money -= amount;
    }
    //Ubijamo
    else if (what == 1) {
	money += amount;
    }
    //Prodajemo TODO: treba implementirati
    else if (what == 2) {
	money += amount;
    }
}

/*
 Funkcija za modifikaciju rezultata na osnovu broja talasa
 */
void modifyScore(int k)
{
    score += waveNumber * 5;
}


/*
 *  Funkcija za izbacivanje vojnika iz igre
 */
void removeMinion(int k, int j)
{
    waves[k].s[j].inPlay = 0;
    modifyScore(k + 1);
    modifyMoney(1, waves[k].s[j].money);
}

/*
    Funkcija za izbacivanje pucnja iz igre
 */
void removeShot(int i)
{
    shot s = { 0, {-255, -255, -255}, TEX_DEFAULT, 0 };
    shots[i] = s;
}
