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
    
        float punti = 0;
        short combo = 0;
        bool spin(TipoTetramino tipo, COORD p0, TipoInput input);
        bool t_spin(TipoTetramino tipo, COORD p0, TipoInput input);
        short lineeRiempite(short linee_riempite);
        void comboAttuale(short linee_riempite);
        void cadutaLenta(short linee_percorse);
        void cadutaVeloce(short linee_percorse);
        void cadutaIstantanea(short linee_percorse);
        void tetrisCompleto();


};

extern Punteggio punteggio;

#endif