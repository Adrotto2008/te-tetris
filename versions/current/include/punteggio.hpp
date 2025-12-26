#ifndef PUNTEGGIO_HPP
#define PUNTEGGIO_HPP


#include "costanti.hpp"
#include "grafica.hpp"
#include "campo.hpp"
#include <cstdlib>
#include <ctime>
#include <stdio.h>

class Punteggio {

    
    public :
    
        short livello = 1;
        int n_linee_completate = 0;
        float punti = 0;
        short combo = 0;
        bool spin(TipoTetramino tipo, COORD p0, TipoInput input);
        bool t_spin(TipoTetramino tipo, COORD p0, TipoInput input);
        void lineeRiempite();
        void comboAttuale();
        void cadutaLenta(short linee_percorse);
        void cadutaVeloce(short linee_percorse);
        void cadutaIstantanea(short linee_percorse);
        void tetrisCompleto();
        void nuovo_livello();


};

extern Punteggio punteggio;

#endif