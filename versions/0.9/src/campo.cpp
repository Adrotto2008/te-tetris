#include "campo.hpp"

using namespace std;

Campo campo;

void Campo::inizializza() {
    for(short i = 0; i < CAMPO_ALTEZZA - 2; i++){
        for(short j = 0; j < CAMPO_LUNGHEZZA - 2; j++){
            casella[i][j].id = 32;
            casella[i][j].blocco = " ";
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
                fwrite(BLOCCO_GHOST_SINISTRA.c_str(), 1, BLOCCO_GHOST_SINISTRA.size(), stdout);
            else 
                fwrite(BLOCCO_GHOST_DESTRA.c_str(), 1, BLOCCO_GHOST_DESTRA.size(), stdout);
        }
    }

    /*-----------CONTROLLO COLORI TETRAMINO----------------------*/
    stampa_colori(casella[posizione_tetramino[0].Y][posizione_tetramino[0].X].colore);

    /*-----------STAMPA TETRAMINO----------------------*/
    for(short i = 0; i < 8; i++){
        cursore_manuale(posizione_tetramino[i].X + 1, posizione_tetramino[i].Y + 1);
        fwrite(casella[posizione_tetramino[i].Y][posizione_tetramino[i].X].blocco.c_str(),
               1,
               casella[posizione_tetramino[i].Y][posizione_tetramino[i].X].blocco.size(),
               stdout);
    }
    
    posizione_cursore(coord_fine);
    printf("%c", 32);
}

void Campo::stampaTotale() {

    for(short i = 0; i < CAMPO_ALTEZZA - 2; i++){

        cursore_manuale(1, i + 1);
        for(short j = 0; j < CAMPO_LUNGHEZZA - 2; j++){
            stampa_colori(casella[i][j].colore);        

            fwrite(casella[i][j].blocco.c_str(), 1, casella[i][j].blocco.size(), stdout);
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

void Campo::salita(){

    if(linee_ricevute == 0) return;

    for(short i = 0; i < CAMPO_ALTEZZA - 3; i++){

        for(short k = 0; k < CAMPO_LUNGHEZZA - 2; k++){
            casella[i][k] = casella[i+linee_ricevute][k];
        }
    }

    for(short j = 0; j < linee_ricevute; j++){

        for(short i = 0; i < CAMPO_LUNGHEZZA - 2; i++){
            casella[CAMPO_ALTEZZA-3 - j][i] = casella[0][0];  
        }
    }

    attacco();

    std::this_thread::sleep_for(10ms);

    stampaTotale();
}

void Campo::attacco(){

    if(linee_ricevute == 0) return;

    int vuoto;
    do{
        vuoto = numero_casuale(1, CAMPO_LUNGHEZZA - 3);
    } while(vuoto % 2 == 1);    

    
    for(short i = CAMPO_ALTEZZA - 2 - linee_ricevute; i < CAMPO_ALTEZZA - 2; i++){

        for(short k = 0; k < CAMPO_LUNGHEZZA - 2; k++){

            if(k != vuoto && k != vuoto + 1){
                casella[i][k].colore = grigio_chiaro;
                casella[i][k].id = 1;
                casella[i][k].blocco = (k % 2 == 0 ? BLOCCO_SINISTRA : BLOCCO_DESTRA);
            }
            
        }

    }

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
        for(short k = 0; k < CAMPO_LUNGHEZZA - 2; k++) printf("%s", casella[posizione_riga[j]][k].blocco.c_str());
        cursore_manuale(1, posizione_riga[j] + 1);
        for(short k = 0; k < CAMPO_LUNGHEZZA - 2; k++) printf("%s", casella[posizione_riga[j]][k].blocco.c_str());
        
    }

    std::this_thread::sleep_for(20ms);
    
    for(short j = 0; j < linee_riempite; j++){

        std::this_thread::sleep_for(200ms);

        printf(BIANCO);
        
        cursore_manuale(1, posizione_riga[j] + 1);
        for(short k = 0; k < CAMPO_LUNGHEZZA - 2; k++) printf("%s", casella[posizione_riga[j]][k].blocco.c_str());
        cursore_manuale(1, posizione_riga[j] + 1);
        for(short k = 0; k < CAMPO_LUNGHEZZA - 2; k++) printf("%s", casella[posizione_riga[j]][k].blocco.c_str());

    }

    std::this_thread::sleep_for(200ms);

    for(short j = 0; j < linee_riempite; j++){
        
        std::this_thread::sleep_for(200ms);

        printf(GRIGIO);

        cursore_manuale(1, posizione_riga[j] + 1);
        for(short k = 0; k < CAMPO_LUNGHEZZA - 2; k++) printf("%s", casella[posizione_riga[j]][k].blocco.c_str());
        cursore_manuale(1, posizione_riga[j] + 1);
        for(short k = 0; k < CAMPO_LUNGHEZZA - 2; k++) printf("%s", casella[posizione_riga[j]][k].blocco.c_str());

    }

    std::this_thread::sleep_for(50ms);
    
    printf(BIANCO);
}