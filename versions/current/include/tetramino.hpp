#ifndef TETRAMINO_HPP
#define TETRAMINO_HPP

#include "costanti.hpp"
#include "grafica.hpp"
#include "campo.hpp"
#include <cstdlib>
#include <ctime>
#include <stdio.h>


class Tetramino {

private:

    short rotazione = 0;
    char colore = 0;
    static int id_tetramini;

    bool inizializza();
    short random_tetramino();
    void controllo_colore();

public:

    short sleep;
    int id_tetramino;
    short tipo = 0;
    COORD p[8];
    bool in_movimento = true;

    Tetramino();
    Tetramino(int id_definito, short tipo_definito);
    ~Tetramino();

    bool puo_girare(short tipo_rotazione);
    void gira(short tipo_rotazione);
    void stampa();
    void stampa_colore();
    void stampa_id();
    bool puo_cadere();
    bool puo_destra();
    bool puo_sinistra();
    void caduta_lenta();
    void cadutaVeloce();
    void caduta_istantanea();
    COORD* ghost_block();
    void sposta_destra();
    void sposta_sinistra();
    void pulisci(bool is_ghost_block);
    void sparisci();

};

#endif