#ifndef CAMPO_HPP
#define CAMPO_HPP

#include "costanti.hpp"
#include "grafica.hpp"
#include "gioco.hpp"
#include "punteggio.hpp"
#include <stdio.h>

typedef struct{

    char colore;
    char blocco[4];
    int id;

} Casella;

class Campo {

    public:
    
        short linee_riempite = 0;
        short posizione_riga = 0;
        Casella casella[CAMPO_ALTEZZA - 2][CAMPO_LUNGHEZZA - 2];

        void inizializza();
        void stampa(COORD posizione_tetramino[], COORD backup_posizione_tetramino[], COORD posizione_ghost_block[], bool in_movimento);
        void stampaTotale();
        void scesa();
        void controlloPunti();
        bool controlloPrimaLinea();
        void animazione_linea_liberata();

};

extern Campo campo;

#endif