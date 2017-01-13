#include "kingdom_main.h"

/*
 *  Osnovne funkcije za gameplay igrice, racunanje da li korisnik moze kupiti kulu
 *  Stetu koju vojnici nanose i koja se nanosi vojnicima, racunanje para ...
 *
 */


/*
 * Funkcija racuna stetu nanetu konkretnom vojniku i vraca trenute helte vojnik
 * argumenti: int k - redni broj talasa u kome se vojnik nalazi
 * 			  int j - redni broj vojnika koji je pretrpeo stetu
 * 			  int i - redni broj hitca koji je pogodio vojnika
 * return:  int health - vraca ostale health-e nakon pretrpljenog udarca
 *
 */
int calculateDamageToMinion(int k, int j, int i)
{
    waves[k].s[j].health -= shots[i].damage;
    return waves[k].s[j].health;
}

/*
 * Odredju da li korisnik moze da kupi datu kulu i postavlja zadate vrednosti ukoliko je kula kupljena
 * argumenti: int newObjectSelected - kula koja je izabrana u sidebar-u
 */
void canUserBuyTower(int newObjectSelected)
{
    if (money >= tower_data[newObjectSelected - 1].cost) {
	  info = "cha-ching$ thanks buddy";
	  setCurrentTowerData(newObjectSelected);
    }else {
	  info = "Not enough $$$.";
	  objectSelected = DEF_OBJ_SEL;
	  preview_tower.id = DEF_OBJ_SEL;
    }
}

/* 
 * Modifikuje helte dvorca zavisnosti da li kupujemo ih ili gubimo
 * ih od strane vojnika
 * argumenti: int die - da li je dvorac pretrpio udarac 0 ili 1
 * 			  int damage - koliko je zivota izgubio ako je pretrpeo udarac
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

/*
 * Modifikujemo novac zavisno da li kupujemo,ubijamo vojnike ili prodajemo
 * argumenti: int what - koju operaciju radimo, 0 kupujemo kule, 1 ubijamo vojnike, 2 prodajemo kule
 * 			  int amount - kolicina novca koja se dodaje ili oduzima
 *
 */ 
void modifyMoney(int what, int amount)
{
    //kupujemo
    if (what == 0) {
	  money -= amount;
    
    //Ubijamo
	}else if (what == 1) {
	  money += amount;
    
    //Prodajemo TODO: treba implementirati u verziji 2.0
	}else if (what == 2) {
	  money += amount;
    }
}

/*
 * Funkcija za modifikaciju rezultata na osnovu broja talasa
 * argumenti: int k - broj talasa iz kog je vojnik koji je izbacen
 * 			    
 */
void modifyScore(int k)
{
    score += k * 5;
}


/*
 *  Funkcija za izbacivanje vojnika iz igre
 *  argumenti: int k - broj talas iz kog je vojnik
 * 			   int j - redni broj vojnika kojeg izbacujemo iz igre
 * 
 */
void removeMinion(int k, int j)
{
    waves[k].s[j].inPlay = 0;
    modifyScore(k + 1);
    modifyMoney(1, waves[k].s[j].money);
}

/*
 * Funkcija za izbacivanje pucnja iz igre
 * argumenti: int i - redni broj pucnja koji izbacujemo iz igre
 *
 */
void removeShot(int i)
{
    shot s = { 0, {-255, -255, -255}, TEX_DEFAULT, 0 };
    shots[i] = s;
}
