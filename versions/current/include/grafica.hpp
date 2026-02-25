#ifndef GRAFICA_HPP
#define GRAFICA_HPP

#ifdef __linux__
#include "utilita_linux.hpp"
#else
#include "utilita.hpp"
#endif

#include "costanti.hpp"
#include "gioco.hpp"


// Funzioni di stampa tetramino
void stampa_riserva_tetramino(TipoTetramino tipo, int colore);
void stampa_coda_tetramini(TipoTetramino tipo1, TipoTetramino tipo2, TipoTetramino tipo3, int colore1, int colore2, int colore3);
void stampa_tetramini_rozzi(TipoTetramino tipo, std::string tetramino[8][8]);
void stampa_colori(int colore);
void cornice(short margine_sinistro, short margine_superiore, short margine_destro, short margine_inferiore);

#endif