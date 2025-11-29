//#ifndef C___LIBRARY_H
//#define C___LIBRARY_H
#ifndef ARKLIGHT_H
#define ARKLIGHT_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <winbase.h>
#include <math.h>
#include <direct.h>
#include <time.h>
#include <conio.h>
#include <limits.h>

void cursore_manuale(int x, int y);

COORD posizione_attuale();

void pulisci();

void cursore_alto(COORD* coord_posizione, int delta);

void cursore_basso(COORD* coord_posizione, int delta);

void cursore_sinistra(COORD* coord_posizione, int delta);

void cursore_destra(COORD* coord_posizione, int delta);

void posizione_cursore(COORD coord_posizione);

void cornice(int margine_sinistro, int margine_superiore, int margine_destro, int margine_inferiore, char carattere);

void set_color(int color);

void box_spazi(const char* text);

void box(const char* text);

void box_colore(const char* text, int color);

void funzioni_utili();

void scan(char *variabile);

void array0();

void matrici0();

void array_rand();

void matrici_rand();

void printarray();

void print_matrici();

void print_matrici_special();

void nascondi_cursore();

void mostra_cursore();

void cmd_grande();

int is_sorted();

void bubblesort();

void selectionsort();

void mergesort();

void cerca_numero();

// radix sort array

int ottieni_cifra(int numero, int exp);

int ottieni_massimo(int arr[], int n);

#endif

// COSTANTI

// COLORI

#define RESET   "\033[0m"
#define NERO    "\033[30m"
#define ROSSO   "\033[31m"
#define VERDE   "\033[32m"
#define GIALLO  "\033[33m"
#define BLU     "\033[34m"
#define MAGENTA "\033[35m"
#define CIANO   "\033[36m"
#define BIANCO  "\033[37m"
#define ARANCIONE "\033[38;5;208m"
#define VIOLA "\033[38;5;129m"
#define GRIGIO "\033[38;5;245m"
#define MARRONE "\033[38;5;94m"

#define BLU_CHIARO "\033[38;5;123m"
#define VERDE_CHIARO "\033[38;5;82m"
#define GIALLO_CHIARO "\033[38;5;226m"
#define ROSSO_CHIARO "\033[38;5;196m"
#define VERDE_SCURO "\033[38;5;34m"
#define GIALLO_SCURO "\033[38;5;220m"
#define BLU_SCURO "\033[38;5;24m"
#define MAGENTA_CHIARO "\033[38;5;201m"
#define CIANO_CHIARO "\033[38;5;51m"
#define GRIGIO_CHIARO "\033[38;5;250m"
#define VIOLA_CHIARO "\033[38;5;135m"
#define LIGHT_RED "\033[38;5;9m"
#define LIGHT_GREEN "\033[38;5;10m"
#define LIGHT_YELLOW "\033[38;5;11m"
#define LIGHT_BLUE "\033[38;5;12m"
#define LIGHT_MAGENTA "\033[38;5;13m"
#define LIGHT_CYAN "\033[38;5;14m"
#define DARK_GRAY "\033[38;5;8m"

// LETTERE

#define A 133 // à
#define E 138 // è
#define I 141 // ì
#define O 149 // ò
#define U 151 // ù
#define SEGRETO "5350" // ?

#define A_ 192 // À
#define E_ 212 // È
#define I_ 222 // Ì
#define O_ 224 // Ò
#define U_ 233 // Ù


// FONT

#define F_RESET "\x1b[0m"
#define GRASSETTO "\x1b[1m"
#define SOTTOLINEATO "\x1b[4m"
#define INVERTI "\x1b[7m"
#define BARRATO "\x1b[9m"
#define ATTENUATO "\x1b[2m"

// CURSORE

#define CURSORE_INVISIBILE "\033[?25l"
#define CURSORE_VISIBILE "\033[?25h"

// C___LIBRARY_H
