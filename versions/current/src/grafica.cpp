#include "grafica.hpp"

COORD coord_tetramino_futuro = {CAMPO_LUNGHEZZA + 13, 2};
COORD coord_secondo_tetramino_futuro = {CAMPO_LUNGHEZZA + 13 + 18, 2};
COORD coord_terzo_tetramino_futuro = {CAMPO_LUNGHEZZA + 13 + 18 + 19, 2};
COORD coord_tetramino_riserva = {CAMPO_LUNGHEZZA + 13, FUTURI_ALTEZZA + 4};
COORD coord_posizione_campo = {1, 1};
COORD coord_punteggio = {CAMPO_LUNGHEZZA + FUTURI_LUNGHEZZA + 7, FUTURI_ALTEZZA + 5};
COORD coord_fine = {0, CAMPO_ALTEZZA + 10};

void stampa_riserva_tetramino(TipoTetramino tipo){

    char tetramino[8][8][4] = {0};

    switch(tipo){ 
        case TipoTetramino::I:
            strcpy(tetramino[2][1], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[3][1], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[4][1], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[5][1], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[2][2], gioco.BLOCCO_DESTRA);
            strcpy(tetramino[3][2], gioco.BLOCCO_DESTRA);
            strcpy(tetramino[4][2], gioco.BLOCCO_DESTRA);
            strcpy(tetramino[5][2], gioco.BLOCCO_DESTRA);
            printf(CIANO);
            break;
        case TipoTetramino::J:
            strcpy(tetramino[0][2], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[1][2], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[2][0], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[2][2], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[0][3], gioco.BLOCCO_DESTRA);
            strcpy(tetramino[1][3], gioco.BLOCCO_DESTRA);
            strcpy(tetramino[2][1], gioco.BLOCCO_DESTRA);
            strcpy(tetramino[2][3], gioco.BLOCCO_DESTRA);
            printf(BLU_CHIARO);
            break;
        case TipoTetramino::L:
            strcpy(tetramino[0][1], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[1][1], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[2][1], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[2][3], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[0][2], gioco.BLOCCO_DESTRA);
            strcpy(tetramino[1][2], gioco.BLOCCO_DESTRA);
            strcpy(tetramino[2][2], gioco.BLOCCO_DESTRA);
            strcpy(tetramino[2][4], gioco.BLOCCO_DESTRA);
            printf(ARANCIONE);
            break;
        case TipoTetramino::O:
            strcpy(tetramino[0][0], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[0][2], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[1][0], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[1][2], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[0][1], gioco.BLOCCO_DESTRA);
            strcpy(tetramino[0][3], gioco.BLOCCO_DESTRA);
            strcpy(tetramino[1][1], gioco.BLOCCO_DESTRA);
            strcpy(tetramino[1][3], gioco.BLOCCO_DESTRA);
            printf(GIALLO_CHIARO);
            break;
        case TipoTetramino::Z:
            strcpy(tetramino[0][0], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[0][2], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[1][2], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[1][4], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[0][1], gioco.BLOCCO_DESTRA);
            strcpy(tetramino[0][3], gioco.BLOCCO_DESTRA);
            strcpy(tetramino[1][3], gioco.BLOCCO_DESTRA);
            strcpy(tetramino[1][5], gioco.BLOCCO_DESTRA);
            printf(ROSSO_CHIARO);
            break;
        case TipoTetramino::S:
            strcpy(tetramino[0][2], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[0][4], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[1][0], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[1][2], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[0][3], gioco.BLOCCO_DESTRA);
            strcpy(tetramino[0][5], gioco.BLOCCO_DESTRA);
            strcpy(tetramino[1][1], gioco.BLOCCO_DESTRA);
            strcpy(tetramino[1][3], gioco.BLOCCO_DESTRA);
            printf(VERDE_CHIARO);
            break;
        case TipoTetramino::T:
            strcpy(tetramino[0][0], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[0][2], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[0][4], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[1][2], gioco.BLOCCO_SINISTRA);
            strcpy(tetramino[0][1], gioco.BLOCCO_DESTRA);
            strcpy(tetramino[0][3], gioco.BLOCCO_DESTRA);
            strcpy(tetramino[0][5], gioco.BLOCCO_DESTRA);
            strcpy(tetramino[1][3], gioco.BLOCCO_DESTRA);
            printf(MAGENTA_CHIARO);
            break;
    }

    // Stampa i tetramini usando le matrici
    for(short i = 0; i < 8; i++) {
        posizione_cursore({coord_tetramino_riserva.X, (short)(coord_tetramino_riserva.Y + i)});
        for(short j = 0; j < 8; j++) {
            printf("%s", tetramino[i][j][0] != '\0' ? tetramino[i][j] : " ");
        }
    }

}

void stampa_coda_tetramini(TipoTetramino tipo1, TipoTetramino tipo2, TipoTetramino tipo3){    //non avevo sbatti

    char tetramino[3][8][8][4] = {0};

    COORD coord_futuro[3] = {coord_tetramino_futuro, coord_secondo_tetramino_futuro, coord_terzo_tetramino_futuro};
    TipoTetramino tipo[3] = {tipo1, tipo2, tipo3};

    for(short j = 0; j < 3; j++){

        switch(tipo[j]){ 
            case TipoTetramino::I:
                strcpy(tetramino[j][2][1], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][3][1], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][4][1], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][5][1], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][2][2], gioco.BLOCCO_DESTRA);
                strcpy(tetramino[j][3][2], gioco.BLOCCO_DESTRA);
                strcpy(tetramino[j][4][2], gioco.BLOCCO_DESTRA);
                strcpy(tetramino[j][5][2], gioco.BLOCCO_DESTRA);
                printf(CIANO);
                break;
            case TipoTetramino::J:
                strcpy(tetramino[j][0][2], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][1][2], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][2][0], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][2][2], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][0][3], gioco.BLOCCO_DESTRA);
                strcpy(tetramino[j][1][3], gioco.BLOCCO_DESTRA);
                strcpy(tetramino[j][2][1], gioco.BLOCCO_DESTRA);
                strcpy(tetramino[j][2][3], gioco.BLOCCO_DESTRA);
                printf(BLU_CHIARO);
                break;
            case TipoTetramino::L:
                strcpy(tetramino[j][0][1], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][1][1], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][2][1], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][2][3], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][0][2], gioco.BLOCCO_DESTRA);
                strcpy(tetramino[j][1][2], gioco.BLOCCO_DESTRA);
                strcpy(tetramino[j][2][2], gioco.BLOCCO_DESTRA);
                strcpy(tetramino[j][2][4], gioco.BLOCCO_DESTRA);
                printf(ARANCIONE);
                break;
            case TipoTetramino::O:
                strcpy(tetramino[j][0][0], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][0][2], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][1][0], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][1][2], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][0][1], gioco.BLOCCO_DESTRA);
                strcpy(tetramino[j][0][3], gioco.BLOCCO_DESTRA);
                strcpy(tetramino[j][1][1], gioco.BLOCCO_DESTRA);
                strcpy(tetramino[j][1][3], gioco.BLOCCO_DESTRA);
                printf(GIALLO_CHIARO);
                break;
            case TipoTetramino::Z:
                strcpy(tetramino[j][0][0], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][0][2], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][1][2], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][1][4], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][0][1], gioco.BLOCCO_DESTRA);
                strcpy(tetramino[j][0][3], gioco.BLOCCO_DESTRA);
                strcpy(tetramino[j][1][3], gioco.BLOCCO_DESTRA);
                strcpy(tetramino[j][1][5], gioco.BLOCCO_DESTRA);
                printf(ROSSO_CHIARO);
                break;
            case TipoTetramino::S:
                strcpy(tetramino[j][0][2], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][0][4], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][1][0], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][1][2], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][0][3], gioco.BLOCCO_DESTRA);
                strcpy(tetramino[j][0][5], gioco.BLOCCO_DESTRA);
                strcpy(tetramino[j][1][1], gioco.BLOCCO_DESTRA);
                strcpy(tetramino[j][1][3], gioco.BLOCCO_DESTRA);
                printf(VERDE_CHIARO);
                break;
            case TipoTetramino::T:
                strcpy(tetramino[j][0][0], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][0][2], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][0][4], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][1][2], gioco.BLOCCO_SINISTRA);
                strcpy(tetramino[j][0][1], gioco.BLOCCO_DESTRA);
                strcpy(tetramino[j][0][3], gioco.BLOCCO_DESTRA);
                strcpy(tetramino[j][0][5], gioco.BLOCCO_DESTRA);
                strcpy(tetramino[j][1][3], gioco.BLOCCO_DESTRA);
                printf(MAGENTA_CHIARO);
                break;
            }

                
        // Stampa i tetramini usando le matrici
        for(short i = 0; i < 8; i++) {
            posizione_cursore({coord_futuro[j].X, (short)(coord_futuro[j].Y + i)});
            for(short k = 0; k < 8; k++) {
                printf("%s", tetramino[j][i][k][0] != '\0' ? tetramino[j][i][k] : " ");
            }
        }

    }

}

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