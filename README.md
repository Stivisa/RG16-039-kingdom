# RG16-039-kingdom
Kingdom

Tip igre Tower Defense

Komande u igri:
 - Osnovne komande za igru:
 >- **space** - startovanje igre
 >- **p** - pauziranje igre
 >- **r** - resetovanje igre na početak
 >- **q** - cheat, dodavanje para u igri
 >- **c** - ukljucivanje oblasti napada kula
 >- **-** - udaljivanje od mape
 >- **+** - približavanje mapi
 >- **m** - kretanje svetlosti
 >- **M** - okretanje vrhova kula
 >- **w** - ukljucuje previewe
 >- **f** - iskljucuje, ukljucuje sumu
 
 - Komande za kontrolisanje osvetljenja:
 >- **l** - ukljucivanje svetlosti
 >- **<** - levi smer kretanja svetlosti
 >- **>** - desni smer kretanja svetlosti
 >- **a** - smanjenje ambient light-a
 >- **A** - povecavanje ambient light-a
 >- **d** - smanjuje diffuse level
 >- **D** - povecava diffuse level
 >- **s** - smanjuje specular level
 >- **S** - povecava specular level
 >- **e** - smanjuje emission
 >- **E** - povecava emission
 >- **n** - smanjuje shininess
 >- **N** - povecava shininess
 
 -Komande za debagovanje 
 >- **x** - ukljucenje ose
 >- **g** - ukljucuje mrezu
 >- **v** - ukljucuje prikaz vrednosti


Osnovna raspodela koda:
  - **kingdom_main.c** -inicijalizacija GLUT-a
  - **kingdom_main.h**  -osnovne biblioteke i eksterne promenljive
  - **defines.h** - definicije globalnih promenljivih
  - **globals.c** - inicijlizacija globalnih promenljivih
  - **general.c**  -funkcije opste upotrebe kao restartovanje promenljivih,trazenje pozicija misa ..
  - **drawing.c**   -funkcije za iscrtavanje zemlje
  - **init.c**     -funkcije za inicijalizaciju programa
  - **screen.c**  -funckcije za inicijalizaciju i menjanje projekcije
  - **window.c**  -inicijalizacija pocetnog prozora
  - **loadObject.c** -funkcija za ucitavanja objekta iz .obj fajla
  - **loadTexture.c** -funkcije za ucitavanja teksutra iz .bmp slika
  - **models.c** -funkcije za pravljenje modela 
  - **print.c** -funkcije za ispis slova na odredjenim kordinatama i ispsi gresaka
  - **sidebar.c** -funkcija za inicijalizaciju i pravlenje sporednog prozora
  - **structs.h** -osnovne strukture koje se koriste u projektu