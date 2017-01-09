#include "kingdom_main.h"

//funkcije za ucitavanje tekstura

//obrcemo n bitova
static void reverse(void *x, const int n)
{
    int k;
    char *ch = (char *) x;
    for (k = 0; k < n / 2; k++) {
	  char tmp = ch[k];
	  ch[k] = ch[n - 1 - k];
	  ch[n - 1 - k] = tmp;
    }
}

//ucitavanje tekstura iz BMP fajlova
unsigned int loadTexBMP(char *file)
{
    unsigned int texture;	//ime teksture
    FILE *f;			//otvoreni fajl
    unsigned short magic;	//tip slike
    unsigned int dx, dy, size;	//dimenzije slike
    unsigned short nbp, bpp;	//bitovi po pikselu
    unsigned char *image;	//podaci o slici
    unsigned int k;		//provere kompresije

    //otvaramo fajl citamo binarno
    f = fopen(file, "rb");
    if (f == NULL){
	  fatal("Ne moze da se otvori fajl %s\n", file);
	}
    //proveravamo magiju slike
    if (fread(&magic, 2, 1, f) != 1){
	  fatal("Ne mozemo da citamo magiju is fajla %s\n", file);
	}  
    if (magic != 0x4D42 && magic != 0x424D){
	  fatal("Slika %s nije BMP\n", file);
	}  
    //citamo header fajla
    if (fseek(f, 16, SEEK_CUR) || fread(&dx, 4, 1, f) != 1
		|| fread(&dy, 4, 1, f) != 1 || fread(&nbp, 2, 1, f) != 1
		|| fread(&bpp, 2, 1, f) != 1 || fread(&k, 4, 1, f) != 1){
	 
	  fatal("Ne  moze da procitamo header iz %s\n", file);
	}

    //u slucaju velikih masina obrcemo sliku
    if (magic == 0x424D) {
	  reverse(&dx, 4);
	  reverse(&dy, 4);
	  reverse(&nbp, 2);
	  reverse(&bpp, 2);
	  reverse(&k, 4);
    }
    //Proveravamo velicinu slike
    if (dx < 1 || dx > 65536){
	  fatal("%s sirina slike je van obsega: %d\n", file, dx);
	}  
    if (dy < 1 || dy > 65536){
	  fatal("%s slika ima preveliku visinu: %d\n", file, dy);
	}  
    if (nbp != 1){
	  fatal("%s bit planes is not 1: %d\n", file, nbp);
	}  
    if (bpp != 24){
	  fatal("%s bitova po slici nije 24: %d\n", file, bpp);
	}
	if (k != 0){
	  fatal("%s kompresija nije podrzana\n", file);
	}
	
    //Alokacija memorije za sliku
    size = 3 * dx * dy;
    image = (unsigned char *) malloc(size * sizeof(unsigned char));
    if (image == NULL){
	  fatal("Neuspela alokacija %s\n", file);
	}  
    // Skacemo na podatek vezane za sliku i citamo ih
    if (fseek(f, 20, SEEK_CUR) || fread(image, size, 1, f) != 1){
	  fatal("Greska pri citanju slike %s\n", file);
	}  
    fclose(f);
    /*  Pretvaramo (BGR -> RGB) */
    for (k = 0; k < size; k += 3) {
	  unsigned char temp = image[k];
	  image[k] = image[k + 2];
	  image[k + 2] = temp;
    }

    //Proveravamo da li je slika dobro ucitana
    errCheck("LoadTexBMP");

    //Generisemo 2D teksturu
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    //Kopiramo sliku
    glTexImage2D(GL_TEXTURE_2D, 0, 3, dx, dy, 0, GL_RGB, GL_UNSIGNED_BYTE,
		 image);
    if (glGetError()){
	  fatal("Error in glTexImage2D %s %dx%d\n", file, dx, dy);
	}  
    //Skaliramo linerano ako slika nije dobre velcine
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    //Oslobadjamo memoriju
    free(image);

    //Vracamo ime teksture
    return texture;

}
