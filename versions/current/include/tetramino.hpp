#ifndef TETRAMINO_HPP
#define TETRAMINO_HPP

#include "punteggio.hpp"
#include "costanti.hpp"
#include "grafica.hpp"
#include "gioco.hpp"
#include "campo.hpp"
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <random>


class Tetramino {

private:

    short rotazione = 0;    
    static int id_tetramini;

    bool inizializza();
    TipoTetramino random_tetramino();
    void controllo_colore();
    void controllo_tipo();

public:

    int colore = 0;
    short sleep;
    int id_tetramino;
    TipoTetramino tipo;
    COORD p[8];
    bool in_movimento = true;

    Tetramino();
    Tetramino(int id_definito, TipoTetramino tipo_definito, int colore);
    ~Tetramino();

    Collisioni puo_girare(TipoInput tipo_rotazione);
    void gira(TipoInput tipo_rotazione);
    void stampa();
    bool perdita();
    void stampa_colore();
    void stampa_id();
    Collisioni puo_cadere();
    Collisioni puo_destra();
    Collisioni puo_sinistra();
    short caduta_lenta();
    short cadutaVeloce();
    short caduta_istantanea();
    COORD* ghost_block();
    void sposta_destra();
    void sposta_sinistra();
    void pulisci(TipoTetramino is_ghost_block);
    void sparisci();

};

#endif