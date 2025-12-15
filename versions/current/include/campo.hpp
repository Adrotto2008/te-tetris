#ifndef CAMPO_HPP
#define CAMPO_HPP

#include "costanti.hpp"
#include "grafica.hpp"
#include "punteggio.hpp"
#include <stdio.h>

typedef struct{

    char colore;
    char blocco;
    int id;

} Casella;

class Campo {

    public:
    
        Casella casella[CAMPO_ALTEZZA - 2][CAMPO_LUNGHEZZA - 2];

        void inizializza();
        void stampa(COORD posizione_tetramino[], COORD backup_posizione_tetramino[], COORD posizione_ghost_block[], bool in_movimento);
        void stampaTotale(short posizione_riga);
        void scesa(short linee_riempite, short posizione_riga);
        short controlloPunti();
        bool controlloPrimaLinea();

};

extern Campo campo;

#endif