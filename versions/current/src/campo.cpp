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
                fwrite(BLOCCO_GHOST_SINISTRA, 1, strlen(BLOCCO_GHOST_SINISTRA), stdout);
            else 
                fwrite(BLOCCO_GHOST_DESTRA, 1, strlen(BLOCCO_GHOST_DESTRA), stdout);
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
        fwrite(casella[posizione_tetramino[i].Y][posizione_tetramino[i].X].blocco, 1, strlen(casella[posizione_tetramino[i].Y][posizione_tetramino[i].X].blocco), stdout);
        //printf("%hd", casella[posizione_tetramino[i].Y][posizione_tetramino[i].X].id % 10);
    }
    
    posizione_cursore(coord_fine);
    printf("%c", 32);
}

void Campo::stampaTotale() {

    for(short i = 0; i < CAMPO_ALTEZZA - 2; i++){ // short i = 0; i <= posizione_riga + 1; i++

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

            fwrite(casella[i][j].blocco, 1, strlen(casella[i][j].blocco), stdout);
        }
    }
}

void Campo::scesa() {
    if(linee_riempite == 0) return;

    for(short i = linee_riempite; i >= 0; i--){
        for(short j = posizione_riga[i]; j >= 1; j--){
            for(short k = 0; k < CAMPO_LUNGHEZZA - 2; k++){
                casella[j][k] = casella[j-1][k];
            }
        }
    }

    std::this_thread::sleep_for(10ms);

    stampaTotale();
}

void Campo::controlloPunti() {
    bool linea_riempita;
    linee_riempite = 0;
    for(short i = 0; i < 4; i++) posizione_riga[i] = 0;

    for(short i = CAMPO_ALTEZZA - 3; i >= 0; i--){
        linea_riempita = true;
        for(short j = 0; j < CAMPO_LUNGHEZZA - 2; j++){
            if(casella[i][j].id == 32)
                linea_riempita = false;
        }
        if(linea_riempita){
            if(posizione_riga[linee_riempite] == 0) posizione_riga[linee_riempite] = i;
            linee_riempite++;
        }
    }

    if(linee_riempite != 0){
        //for(short i = 0; i < linee_riempite; i++)   printf("n linee : %hd, riga %hd : %hd  ", linee_riempite, i + 1, posizione_riga[i]);
        //std::this_thread::sleep_for(1000ms);
        animazione_linea_liberata();
        scesa();
    }
        


}

bool Campo::controlloPrimaLinea(){
    for(short i = 0; i < CAMPO_LUNGHEZZA - 2; i++){
        if(campo.casella[CAMPO_ALTEZZA - 2][i].id != 32){
            return false;
        }
    }
    return true;
}

void Campo::animazione_linea_liberata(){

    AudioManager audio;
    audio.setVolumeSuoni(AUDIO_SUONI);

    audio.caricaSuono("linea_singola", "linea_singola");
    audio.caricaSuono("linee_multiple", "linee_multiple");
    audio.caricaSuono("4_linee", "4_linee");

    if(linee_riempite == 1)  audio.suona("linea_singola");
    else if(linee_riempite == 4) audio.suona("4_linee");
    else audio.suona("linee_multiple");

    for(short j = 0; j < linee_riempite; j++){

        cursore_manuale(1, posizione_riga[j] + 1);

        printf(GRIGIO);

        cursore_manuale(1, posizione_riga[j] + 1);
        for(short k = 0; k < CAMPO_LUNGHEZZA - 2; k++) printf("%s", casella[posizione_riga[j]][k].blocco);
        cursore_manuale(1, posizione_riga[j] + 1);
        for(short k = 0; k < CAMPO_LUNGHEZZA - 2; k++) printf("%s", casella[posizione_riga[j]][k].blocco);
        
    }

    std::this_thread::sleep_for(20ms);
    
    for(short j = 0; j < linee_riempite; j++){

        std::this_thread::sleep_for(200ms);

        printf(BIANCO);
        
        cursore_manuale(1, posizione_riga[j] + 1);
        for(short k = 0; k < CAMPO_LUNGHEZZA - 2; k++) printf("%s", casella[posizione_riga[j] ][k].blocco);
        cursore_manuale(1, posizione_riga[j] + 1);
        for(short k = 0; k < CAMPO_LUNGHEZZA - 2; k++) printf("%s", casella[posizione_riga[j]][k].blocco);

    }

    std::this_thread::sleep_for(200ms);

    for(short j = 0; j < linee_riempite; j++){
        
        std::this_thread::sleep_for(200ms);

        printf(GRIGIO);

        cursore_manuale(1, posizione_riga[j] + 1);
        for(short k = 0; k < CAMPO_LUNGHEZZA - 2; k++) printf("%s", casella[posizione_riga[j] ][k].blocco);
        cursore_manuale(1, posizione_riga[j] + 1);
        for(short k = 0; k < CAMPO_LUNGHEZZA - 2; k++) printf("%s", casella[posizione_riga[j] ][k].blocco);

    }

    std::this_thread::sleep_for(50ms);
    
    printf(BIANCO);

    


}