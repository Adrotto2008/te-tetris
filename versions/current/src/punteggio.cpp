#include "punteggio.hpp"

Punteggio punteggio;

bool Punteggio::t_spin(TipoTetramino tipo, COORD p0, TipoInput input){

    short contatore = 0;

    if(tipo == TipoTetramino::T){

        if(input == TipoInput::GIROORARIO || input == TipoInput::GIROANTIORARIO || input == TipoInput::GIRODOPPIO){

            if(p0.Y - 1 < 0 && p0.X - 1 <= -1){ contatore++;}
            else if(campo.casella[p0.Y - 1][p0.X - 1].id != 32){ contatore++; }

            if(p0.Y - 1 < 0 && p0.X + 2 >= CAMPO_LUNGHEZZA - 2){ contatore++; }
            else if(campo.casella[p0.Y - 1][p0.X + 2].id != 32){ contatore++; }

            if(p0.Y - 1 >= CAMPO_ALTEZZA - 2 && p0.X  - 1 <= -1){ contatore++; }
            else if(campo.casella[p0.Y + 1][p0.X - 1].id != 32){ contatore++; }

            if(p0.Y - 1 >= CAMPO_ALTEZZA - 2 && p0.X + 2 >= CAMPO_LUNGHEZZA - 2){ contatore++; }
            else if(campo.casella[p0.Y + 1][p0.X + 2].id != 32){ contatore++; }

            if(contatore >= 3){
                printf("t_spin!!!");
                punti += 200;
                return true;
            }

        }

    }

    return false;

}

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