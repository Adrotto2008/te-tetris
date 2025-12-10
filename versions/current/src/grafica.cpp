#include "grafica.hpp"

COORD coord_tetramino_futuro = {CAMPO_LUNGHEZZA + 13, 2};
COORD coord_secondo_tetramino_futuro = {CAMPO_LUNGHEZZA + 13 + 18, 2};
COORD coord_terzo_tetramino_futuro = {CAMPO_LUNGHEZZA + 13 + 18 + 19, 2};
COORD coord_tetramino_riserva = {CAMPO_LUNGHEZZA + 13, FUTURI_ALTEZZA + 4};
COORD coord_posizione_campo = {1, 1};
COORD coord_punteggio = {CAMPO_LUNGHEZZA + FUTURI_LUNGHEZZA + 7, FUTURI_ALTEZZA + 5};
COORD coord_fine = {0, CAMPO_ALTEZZA + 10};

void cornice(short margine_sinistro, short margine_superiore, short margine_destro, short margine_inferiore){

    COORD start;

    //imposto le cordinate in maniera assoluta per non andare fuori dallo schermo
    start.X = abs(margine_sinistro);
    start.Y = abs(margine_superiore);

    COORD coord = start;

    for (short j = 0; j < margine_inferiore; j++) {
        posizione_cursore(coord);
        for (short i = 0; i < margine_destro; i++) {
            if (j == 0 || j == margine_inferiore - 1) { // margini inferiore e superiore
                
                if(i == 0 || i == margine_destro - 1){// angoli
                    putchar('+');
                }else {
                    putchar('-');
                }
                
            } else if (i == 0 || i == margine_destro - 1) { //margini laterali
                putchar('|');
            } else {
                putchar(' ');
            }
        }

        coord.Y += 1;
    }

    coord.Y += 5;
    posizione_cursore(coord);

}