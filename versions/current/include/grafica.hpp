#ifndef GRAFICA_HPP
#define GRAFICA_HPP

#include "costanti.hpp"
#include "utilita.hpp"
#include <windows.h>

extern COORD coord_tetramino_futuro;
extern COORD coord_secondo_tetramino_futuro;
extern COORD coord_terzo_tetramino_futuro;
extern COORD coord_tetramino_riserva;
extern COORD coord_posizione_campo;
extern COORD coord_punteggio;
extern COORD coord_fine;

void cornice(short margine_sinistro, short margine_superiore, short margine_destro, short margine_inferiore);

#endif