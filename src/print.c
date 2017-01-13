#include "kingdom_main.h"

//Funckije za stampanje gresaka i slova na odredjenim pozicijama.


//definisemo duzinu stringa
#define SIZE 8192

/*
 * ispisujemo tekst kao rasterski zbog razlicitih velicina ekrana
 * argumenti: va_list args - lista argumenata koja je prosledjena koja treba da se stampa 
 * 							 tj broj argumenata moze da varira
 *			  const char *format - format ispisa teksta
 * 
 */
void printv(va_list args, const char *format)
{
    char buffer[SIZE];
    char *ch = buffer;

    //pretvaramo parametre u string 
    vsnprintf(buffer, SIZE, format, args);

    //prestavljamo karakter po karatker na datoj poziciji
    while (*ch) {
	  glutBitmapCharacter(fontStyle, *ch++);
    }

}

/*
 * Funkcija postavljamo font teksta
 * argumenti: char *name - naziv fonta
 * 			  int size - velicina fonta
 * 
 */

void setFont(char *name, int size)
{
    if (strcmp(name, "helvetica") == 0) {
	  if (size == 10){
	    fontStyle = GLUT_BITMAP_HELVETICA_10;
	  }else if (size == 12){
	    fontStyle = GLUT_BITMAP_HELVETICA_12;
	  }else if (size == 18)
	    fontStyle = GLUT_BITMAP_HELVETICA_18;
    }else if (strcmp(name, "times roman") == 0) {
	  if (size == 24)
	    fontStyle = GLUT_BITMAP_TIMES_ROMAN_24;
    }
}


/*
 * Funkcija za ispis teksta u terminal
 * argumenti: const char *format - format ispisa teksta
 * 			  ... - oznacava da funkcija moze da primi proizvoljan broj argumentata
 */
void print(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    printv(args, format);
    va_end(args);
}

/*
 * Ispisuje tekst na odredjenu poziciju na ekranu
 * argumenti: int x - pozicija teksta na x osi
 * 			  int y - pozicija teksta na y osi
 * 			  const char *format - format ispisa teksta
 *			  ... -proizvoljan broj argumenata koji moze biti ispisan
 *
 */
void printAt(int x, int y, const char *format, ...)
{
    va_list args;
    glWindowPos2i(x, y);
    va_start(args, format);
    printv(args, format);
    va_end(args);
}

/*
 * Ispis OpenGl gresaka na standarni izlaz za greske (stderr)
 * argumenti: char *error - opis greske
 * 
 */
void errCheck(char *error)
{
    int err = glGetError();
    if (err) {
	  fprintf(stderr, "ERROR: %s [%s]\n", gluErrorString(err), error);
    }

}

/* 
 * Ispis fatalnih  gresaka na stderr i prekidanje programa
 * argumenti: const char *format - format ispisa greske
 * 			  ... - porizvoljni argumenti za detaljniji ispis greske
 * 
 */
void fatal(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    exit(1);
}
