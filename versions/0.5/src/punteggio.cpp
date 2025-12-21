#include "punteggio.hpp"

Punteggio punteggio;

short Punteggio::lineeRiempite(short linee_riempite){

        /*---------------------LINEE---------------------*/
        switch(linee_riempite){

            case 1 :
                punti += 100;
                break;

            case 2 :
                punti += 300;
                break;

            case 3 :
                punti += 500;
                break;

            case 4 : // tetris!
                punti += 800;
                break;


        }

        return linee_riempite;

}

void Punteggio::comboAttuale(short linee_riempite){

    if(!linee_riempite){
        combo = 0;
    } else {
        combo++;
    }

    if(combo > 1 ){
            punti *= 1.1;
            punti += combo * 50;
    }

}

void Punteggio::cadutaLenta(short linee_percorse){
    punti += linee_percorse;
}

void Punteggio::cadutaVeloce(short linee_percorse){
    punti += 2 * linee_percorse;
}

void Punteggio::cadutaIstantanea(short linee_percorse){
    punti += 3 * linee_percorse;
}

void Punteggio::tetrisCompleto(){
    punti += 7777;
}