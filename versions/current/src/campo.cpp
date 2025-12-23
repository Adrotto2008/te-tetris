#include "campo.hpp"

using namespace std;

Campo campo;

void Campo::inizializza() {
    for(short i = 0; i < CAMPO_ALTEZZA - 2; i++){
        for(short j = 0; j < CAMPO_LUNGHEZZA - 2; j++){
            casella[i][j].id = 32;
            casella[i][j].blocco[0] = ' '; casella[i][j].blocco[1] = '\0';
            casella[i][j].colore = bianco;
        }
    }
}

void Campo::stampa(COORD posizione_tetramino[], COORD backup_posizione_tetramino[], COORD posizione_ghost_block[], bool in_movimento) {
    
    /*-----------PULIZIA VECCHIO TETRAMINO----------------------*/
    for(short i = 0; i < 8; i++){
        cursore_manuale(backup_posizione_tetramino[i].X + 1, backup_posizione_tetramino[i].Y + 1);
        printf("%c", 32);
    }

    /*-----------STAMPA GHOST BLOCK----------------------*/
    if(in_movimento){
        printf(GRIGIO);
        for(short i = 0; i < 8; i++){
            cursore_manuale(posizione_ghost_block[i].X + 1, posizione_ghost_block[i].Y + 1);
            if(i%2==0)
                printf("%s", BLOCCO_GHOST_SINISTRA);
            else 
                printf("%s", BLOCCO_GHOST_DESTRA);
            }
    }

    /*-----------CONTROLLO COLORI TETRAMINO----------------------*/
    switch(casella[posizione_tetramino[0].Y][posizione_tetramino[0].X].colore){
        case bianco : printf(BIANCO); break;
        case rosso : printf(ROSSO_CHIARO); break;
        case ciano : printf(CIANO); break;
        case blu : printf(BLU_CHIARO); break;
        case arancione : printf(ARANCIONE); break;
        case giallo : printf(GIALLO_CHIARO); break;
        case verde : printf(VERDE_CHIARO); break;
        case magenta : printf(MAGENTA_CHIARO); break;
    }

    /*-----------STAMPA TETRAMINO----------------------*/
    for(short i = 0; i < 8; i++){
        cursore_manuale(posizione_tetramino[i].X + 1, posizione_tetramino[i].Y + 1);
        printf("%s", casella[posizione_tetramino[i].Y][posizione_tetramino[i].X].blocco);
    }
    
    posizione_cursore(coord_fine);
    printf("%c", 32);
}

void Campo::stampaTotale(short posizione_riga) {

    for(short i = 0; i <= posizione_riga; i++){

        cursore_manuale(1, i + 1);
        for(short j = 0; j < CAMPO_LUNGHEZZA - 2; j++){
            switch(casella[i][j].colore){
                case bianco : printf(BIANCO); break;
                case rosso : printf(ROSSO_CHIARO); break;
                case ciano : printf(CIANO); break;
                case blu : printf(BLU_CHIARO); break;
                case arancione : printf(ARANCIONE); break;
                case giallo : printf(GIALLO_CHIARO); break;
                case verde : printf(VERDE_CHIARO); break;
                case magenta : printf(MAGENTA_CHIARO); break;
            }
            printf("%s", casella[i][j].blocco);
        }
    }
}

void Campo::scesa(short linee_riempite, short posizione_riga) {
    if(linee_riempite == 0) return;

    for(short i = 0; i < linee_riempite; i++){
        for(short j = posizione_riga; j >= 1; j--){
            for(short k = 0; k < CAMPO_LUNGHEZZA - 2; k++){
                casella[j][k] = casella[j-1][k];
            }
        }
    }
    stampaTotale(posizione_riga);
}

short Campo::controlloPunti() {
    bool linea_riempita;
    short linee_riempite = 0;
    short posizione_riga = 0;

    for(short i = CAMPO_ALTEZZA - 3; i >= 0; i--){
        linea_riempita = true;
        for(short j = 0; j < CAMPO_LUNGHEZZA - 2; j++){
            if(casella[i][j].id == 32)
                linea_riempita = false;
        }
        if(linea_riempita){
            if(posizione_riga == 0) posizione_riga = i;
            linee_riempite++;
        }
    }

    if(linee_riempite != 0)
        scesa(linee_riempite, posizione_riga);

    return linee_riempite;
}

bool Campo::controlloPrimaLinea(){
    for(short i = 0; i < CAMPO_LUNGHEZZA - 2; i++){
        if(campo.casella[CAMPO_ALTEZZA - 2][i].id != 32){
            return false;
        }
    }
    return true;
}