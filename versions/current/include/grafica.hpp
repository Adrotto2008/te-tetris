#ifndef GRAFICA_HPP
#define GRAFICA_HPP

#include "costanti.hpp"
#include "gioco.hpp"
#ifdef __linux__
#include "utilita_linux.hpp"
#else
#include "utilita.hpp"
#endif

// Funzioni di stampa tetramino
void stampa_riserva_tetramino(TipoTetramino tipo, int colore);
void stampa_coda_tetramini(TipoTetramino tipo1, TipoTetramino tipo2, TipoTetramino tipo3, int colore1, int colore2, int colore3);

void cornice(short margine_sinistro, short margine_superiore, short margine_destro, short margine_inferiore);

#endif