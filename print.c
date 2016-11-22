#include "kingdom_main.h"

//Funckije za stampanje gresaka i slova na odredjenim pozicijama.


//definisemo duzinu stringa
#define SIZE 8192

//ispisujemo tekst kao raster zbog razlicitih velicina ekrana
void printv(va_list args, const char *format)
{
    char buffer[SIZE];
    char *ch = buffer;

    //pretvaramo parametre u string 
    vsnprintf(buffer, SIZE, format, args);

    //prestavljamo karakter po karatker na datoj poziciji
    /*while(*ch){
       glutBitmapCharacter(fontStyle, *ch++);
       } */

}

//metoda za ispis
void print(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    printv(args, format);
    va_end(args);
}

//ispis stringa na odredjenu poziciju
void printAt(int x, int y, const char *format, ...)
{
    va_list args;
    glWindowPos2i(x, y);
    va_start(args, format);
    printv(args, format);
    va_end(args);
}

//ispis OpenGl gresaka na stderr izlaz
void errCheck(char *error)
{
    int err = glGetError();
    if (err) {
	fprintf(stderr, "ERROR: %s [%s]\n", gluErrorString(err), error);
    }

}

//fatalna  greska ispis na stderr i prekidanje programa
void fatal(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    exit(1);
}
