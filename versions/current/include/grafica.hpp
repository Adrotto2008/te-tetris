#ifndef GRAFICA_HPP
#define GRAFICA_HPP

#include "costanti.hpp"
#include "utilita.hpp"
#include <winsock2.h>
#include <windows.h>

extern COORD coord_tetramino_futuro;
extern COORD coord_secondo_tetramino_futuro;
extern COORD coord_terzo_tetramino_futuro;
extern COORD coord_tetramino_riserva;
extern COORD coord_posizione_campo;
extern COORD coord_punteggio;
extern COORD coord_fine;

// Funzioni di stampa tetramino
void stampa_riserva_tetramino(TipoTetramino tipo);
void stampa_coda_tetramini(TipoTetramino tipo1, TipoTetramino tipo2, TipoTetramino tipo3);

void cornice(short margine_sinistro, short margine_superiore, short margine_destro, short margine_inferiore);

#endif