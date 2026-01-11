#include "grafica.hpp"



void stampa_riserva_tetramino(TipoTetramino tipo, int colore){

    char tetramino[8][8][4] = {0};

    // Stampa il colore prima della stampa
    stampa_colori(colore);

    stampa_tetramini_rozzi(tipo, tetramino);

    // Stampa i tetramini usando le matrici
    for(short i = 0; i < 8; i++) {
        posizione_cursore({coord_tetramino_riserva.X, (short)(coord_tetramino_riserva.Y + i)});
        for(short j = 0; j < 8; j++) {
            printf("%s", tetramino[i][j][0] != '\0' ? tetramino[i][j] : " ");
        }
    }   

}

void stampa_coda_tetramini(TipoTetramino tipo1, TipoTetramino tipo2, TipoTetramino tipo3, int colore1, int colore2, int colore3) {

    char tetramino[3][8][8][4] = {0};
    COORD coord_futuro[3] = {coord_tetramino_futuro, coord_secondo_tetramino_futuro, coord_terzo_tetramino_futuro};
    TipoTetramino tipo[3] = {tipo1, tipo2, tipo3};
    int colori[3] = {colore1, colore2, colore3};

    for(short j = 0; j < 3; j++) {

        // Stampa il colore prima della stampa
        stampa_colori(colori[j]);

        // Imposta la forma del tetramino senza printf di colore
        stampa_tetramini_rozzi(tipo[j], tetramino[j]);

        // Stampa i tetramini usando le matrici
        for(short i = 0; i < 8; i++) {
            posizione_cursore({coord_futuro[j].X, (short)(coord_futuro[j].Y + i)});
            for(short k = 0; k < 8; k++) {
                printf("%s", tetramino[j][i][k][0] != '\0' ? tetramino[j][i][k] : " ");
            }
        }
    }
}

void stampa_tetramini_rozzi(TipoTetramino tipo, char tetramino[8][8][4]){

    switch(tipo){ 
        case TipoTetramino::I:
            strcpy(tetramino[2][1], BLOCCO_SINISTRA);
            strcpy(tetramino[3][1], BLOCCO_SINISTRA);
            strcpy(tetramino[4][1], BLOCCO_SINISTRA);
            strcpy(tetramino[5][1], BLOCCO_SINISTRA);
            strcpy(tetramino[2][2], BLOCCO_DESTRA);
            strcpy(tetramino[3][2], BLOCCO_DESTRA);
            strcpy(tetramino[4][2], BLOCCO_DESTRA);
            strcpy(tetramino[5][2], BLOCCO_DESTRA);
            break;
        case TipoTetramino::J:
            strcpy(tetramino[0][2], BLOCCO_SINISTRA);
            strcpy(tetramino[1][2], BLOCCO_SINISTRA);
            strcpy(tetramino[2][0], BLOCCO_SINISTRA);
            strcpy(tetramino[2][2], BLOCCO_SINISTRA);
            strcpy(tetramino[0][3], BLOCCO_DESTRA);
            strcpy(tetramino[1][3], BLOCCO_DESTRA);
            strcpy(tetramino[2][1], BLOCCO_DESTRA);
            strcpy(tetramino[2][3], BLOCCO_DESTRA);
            break;
        case TipoTetramino::L:
            strcpy(tetramino[0][1], BLOCCO_SINISTRA);
            strcpy(tetramino[1][1], BLOCCO_SINISTRA);
            strcpy(tetramino[2][1], BLOCCO_SINISTRA);
            strcpy(tetramino[2][3], BLOCCO_SINISTRA);
            strcpy(tetramino[0][2], BLOCCO_DESTRA);
            strcpy(tetramino[1][2], BLOCCO_DESTRA);
            strcpy(tetramino[2][2], BLOCCO_DESTRA);
            strcpy(tetramino[2][4], BLOCCO_DESTRA);
            break;
        case TipoTetramino::O:
            strcpy(tetramino[0][0], BLOCCO_SINISTRA);
            strcpy(tetramino[0][2], BLOCCO_SINISTRA);
            strcpy(tetramino[1][0], BLOCCO_SINISTRA);
            strcpy(tetramino[1][2], BLOCCO_SINISTRA);
            strcpy(tetramino[0][1], BLOCCO_DESTRA);
            strcpy(tetramino[0][3], BLOCCO_DESTRA);
            strcpy(tetramino[1][1], BLOCCO_DESTRA);
            strcpy(tetramino[1][3], BLOCCO_DESTRA);
            break;
        case TipoTetramino::Z:
            strcpy(tetramino[0][0], BLOCCO_SINISTRA);
            strcpy(tetramino[0][2], BLOCCO_SINISTRA);
            strcpy(tetramino[1][2], BLOCCO_SINISTRA);
            strcpy(tetramino[1][4], BLOCCO_SINISTRA);
            strcpy(tetramino[0][1], BLOCCO_DESTRA);
            strcpy(tetramino[0][3], BLOCCO_DESTRA);
            strcpy(tetramino[1][3], BLOCCO_DESTRA);
            strcpy(tetramino[1][5], BLOCCO_DESTRA);
            break;
        case TipoTetramino::S:
            strcpy(tetramino[0][2], BLOCCO_SINISTRA);
            strcpy(tetramino[0][4], BLOCCO_SINISTRA);
            strcpy(tetramino[1][0], BLOCCO_SINISTRA);
            strcpy(tetramino[1][2], BLOCCO_SINISTRA);
            strcpy(tetramino[0][3], BLOCCO_DESTRA);
            strcpy(tetramino[0][5], BLOCCO_DESTRA);
            strcpy(tetramino[1][1], BLOCCO_DESTRA);
            strcpy(tetramino[1][3], BLOCCO_DESTRA);
            break;
        case TipoTetramino::T:
            strcpy(tetramino[0][0], BLOCCO_SINISTRA);
            strcpy(tetramino[0][2], BLOCCO_SINISTRA);
            strcpy(tetramino[0][4], BLOCCO_SINISTRA);
            strcpy(tetramino[1][2], BLOCCO_SINISTRA);
            strcpy(tetramino[0][1], BLOCCO_DESTRA);
            strcpy(tetramino[0][3], BLOCCO_DESTRA);
            strcpy(tetramino[0][5], BLOCCO_DESTRA);
            strcpy(tetramino[1][3], BLOCCO_DESTRA);
            break;

        case TipoTetramino::SL:
            strcpy(tetramino[0][4], BLOCCO_SINISTRA);
            strcpy(tetramino[1][2], BLOCCO_SINISTRA);
            strcpy(tetramino[0][5], BLOCCO_DESTRA);
            strcpy(tetramino[1][3], BLOCCO_DESTRA);
            break;
        case TipoTetramino::BSL:
            strcpy(tetramino[1][2], BLOCCO_SINISTRA);
            strcpy(tetramino[0][0], BLOCCO_SINISTRA);
            strcpy(tetramino[2][4], BLOCCO_SINISTRA);
            strcpy(tetramino[3][6], BLOCCO_SINISTRA);
            strcpy(tetramino[1][3], BLOCCO_DESTRA);
            strcpy(tetramino[0][1], BLOCCO_DESTRA);
            strcpy(tetramino[2][5], BLOCCO_DESTRA);
            strcpy(tetramino[3][7], BLOCCO_DESTRA);
            break;
        case TipoTetramino::Y:
            strcpy(tetramino[1][4], BLOCCO_SINISTRA);
            strcpy(tetramino[2][4], BLOCCO_SINISTRA);
            strcpy(tetramino[0][2], BLOCCO_SINISTRA);
            strcpy(tetramino[0][6], BLOCCO_SINISTRA);
            strcpy(tetramino[1][5], BLOCCO_DESTRA);
            strcpy(tetramino[2][5], BLOCCO_DESTRA);
            strcpy(tetramino[0][3], BLOCCO_DESTRA);
            strcpy(tetramino[0][7], BLOCCO_DESTRA);
            break;
        case TipoTetramino::P:
            strcpy(tetramino[0][4], BLOCCO_SINISTRA);
            strcpy(tetramino[0][5], BLOCCO_DESTRA);
            break;
        case TipoTetramino::V:
            strcpy(tetramino[1][4], BLOCCO_SINISTRA);
            strcpy(tetramino[0][2], BLOCCO_SINISTRA);
            strcpy(tetramino[0][6], BLOCCO_SINISTRA);
            strcpy(tetramino[1][5], BLOCCO_DESTRA);
            strcpy(tetramino[0][3], BLOCCO_DESTRA);
            strcpy(tetramino[0][7], BLOCCO_DESTRA);
            break;
        case TipoTetramino::M:
            strcpy(tetramino[2][4], BLOCCO_SINISTRA);
            strcpy(tetramino[1][2], BLOCCO_SINISTRA);
            strcpy(tetramino[0][4], BLOCCO_SINISTRA);
            strcpy(tetramino[1][6], BLOCCO_SINISTRA);
            strcpy(tetramino[2][5], BLOCCO_DESTRA);
            strcpy(tetramino[1][3], BLOCCO_DESTRA);
            strcpy(tetramino[0][5], BLOCCO_DESTRA);
            strcpy(tetramino[1][7], BLOCCO_DESTRA);
            break;
        case TipoTetramino::C:
            strcpy(tetramino[1][2], BLOCCO_SINISTRA);
            strcpy(tetramino[0][4], BLOCCO_SINISTRA);
            strcpy(tetramino[2][2], BLOCCO_SINISTRA);
            strcpy(tetramino[3][4], BLOCCO_SINISTRA);
            strcpy(tetramino[1][3], BLOCCO_DESTRA);
            strcpy(tetramino[0][5], BLOCCO_DESTRA);
            strcpy(tetramino[2][3], BLOCCO_DESTRA);
            strcpy(tetramino[3][5], BLOCCO_DESTRA);
            break;
    }

}

void stampa_colori(int colore){

    switch (colore) {
        case static_cast<int>(rosso):           printf(ROSSO_CHIARO);   break;
        case static_cast<int>(ciano):           printf(CIANO);          break;
        case static_cast<int>(blu):             printf(BLU_CHIARO);     break;
        case static_cast<int>(arancione):       printf(ARANCIONE);      break;
        case static_cast<int>(giallo):          printf(GIALLO_CHIARO);  break;
        case static_cast<int>(verde):           printf(VERDE_CHIARO);   break;
        case static_cast<int>(magenta_chiaro):  printf(MAGENTA_CHIARO); break;

        case static_cast<int>(marrone):         printf(MARRONE);        break;
        case static_cast<int>(light_green):     printf(LIGHT_GREEN);    break;
        case static_cast<int>(blu_scuro):       printf(BLU_SCURO);      break;
        case static_cast<int>(ciano_chiaro):    printf(CIANO_CHIARO);   break;
        case static_cast<int>(light_yellow):    printf(LIGHT_YELLOW);   break;
        case static_cast<int>(magenta):         printf(MAGENTA);        break;
        case static_cast<int>(bianco):          printf(BIANCO);         break;
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