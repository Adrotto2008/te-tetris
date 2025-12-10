#ifndef UTILITA_HPP
#define UTILITA_HPP

#include "costanti.hpp"
#include "grafica.hpp"
#include <windows.h>
#include <cstdio>

// Funzioni di stampa tetramino
void stampa_riserva_tetramino(short tipo);
void stampa_coda_tetramini(short tipo1, short tipo2, short tipo3);

// Funzioni cursore
void cursore_manuale(short x, short y);
void posizione_cursore(COORD coord_posizione);
void cursore_alto(COORD* coord_posizione, short delta);
void cursore_basso(COORD* coord_posizione, short delta);
void cursore_sinistra(COORD* coord_posizione, short delta);
void cursore_destra(COORD* coord_posizione, short delta);
COORD posizione_attuale();
void nascondi_cursore();
void mostra_cursore();
void pulisci();
void cmd_grande();


#endif