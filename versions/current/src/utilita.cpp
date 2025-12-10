#include "utilita.hpp"

using namespace std;


void stampa_riserva_tetramino(short tipo){

    char tetramino[8][8] = {0};

    switch(tipo){ 
        case tetramino_i:
            tetramino[2][1] = BLOCCO_SINISTRA;
            tetramino[3][1] = BLOCCO_SINISTRA;
            tetramino[4][1] = BLOCCO_SINISTRA;
            tetramino[5][1] = BLOCCO_SINISTRA;
            tetramino[2][2] = BLOCCO_DESTRA;
            tetramino[3][2] = BLOCCO_DESTRA;
            tetramino[4][2] = BLOCCO_DESTRA;
            tetramino[5][2] = BLOCCO_DESTRA;
            printf(CIANO);
            break;
        case tetramino_j:
            tetramino[0][2] = BLOCCO_SINISTRA;
            tetramino[1][2] = BLOCCO_SINISTRA;
            tetramino[2][0] = BLOCCO_SINISTRA;
            tetramino[2][2] = BLOCCO_SINISTRA;
            tetramino[0][3] = BLOCCO_DESTRA;
            tetramino[1][3] = BLOCCO_DESTRA;
            tetramino[2][1] = BLOCCO_DESTRA;
            tetramino[2][3] = BLOCCO_DESTRA;
            printf(BLU_CHIARO);
            break;
        case tetramino_l:
            tetramino[0][1] = BLOCCO_SINISTRA;
            tetramino[1][1] = BLOCCO_SINISTRA;
            tetramino[2][1] = BLOCCO_SINISTRA;
            tetramino[2][3] = BLOCCO_SINISTRA;
            tetramino[0][2] = BLOCCO_DESTRA;
            tetramino[1][2] = BLOCCO_DESTRA;
            tetramino[2][2] = BLOCCO_DESTRA;
            tetramino[2][4] = BLOCCO_DESTRA;
            printf(ARANCIONE);
            break;
        case tetramino_o:
            tetramino[0][0] = BLOCCO_SINISTRA;
            tetramino[0][2] = BLOCCO_SINISTRA;
            tetramino[1][0] = BLOCCO_SINISTRA;
            tetramino[1][2] = BLOCCO_SINISTRA;
            tetramino[0][1] = BLOCCO_DESTRA;
            tetramino[0][3] = BLOCCO_DESTRA;
            tetramino[1][1] = BLOCCO_DESTRA;
            tetramino[1][3] = BLOCCO_DESTRA;
            printf(GIALLO_CHIARO);
            break;
        case tetramino_z:
            tetramino[0][0] = BLOCCO_SINISTRA;
            tetramino[0][2] = BLOCCO_SINISTRA;
            tetramino[1][2] = BLOCCO_SINISTRA;
            tetramino[1][4] = BLOCCO_SINISTRA;
            tetramino[0][1] = BLOCCO_DESTRA;
            tetramino[0][3] = BLOCCO_DESTRA;
            tetramino[1][3] = BLOCCO_DESTRA;
            tetramino[1][5] = BLOCCO_DESTRA;
            printf(ROSSO_CHIARO);
            break;
        case tetramino_s:
            tetramino[0][2] = BLOCCO_SINISTRA;
            tetramino[0][4] = BLOCCO_SINISTRA;
            tetramino[1][0] = BLOCCO_SINISTRA;
            tetramino[1][2] = BLOCCO_SINISTRA;
            tetramino[0][3] = BLOCCO_DESTRA;
            tetramino[0][5] = BLOCCO_DESTRA;
            tetramino[1][1] = BLOCCO_DESTRA;
            tetramino[1][3] = BLOCCO_DESTRA;
            printf(VERDE_CHIARO);
            break;
        case tetramino_t:
            tetramino[0][0] = BLOCCO_SINISTRA;
            tetramino[0][2] = BLOCCO_SINISTRA;
            tetramino[0][4] = BLOCCO_SINISTRA;
            tetramino[1][2] = BLOCCO_SINISTRA;
            tetramino[0][1] = BLOCCO_DESTRA;
            tetramino[0][3] = BLOCCO_DESTRA;
            tetramino[0][5] = BLOCCO_DESTRA;
            tetramino[1][3] = BLOCCO_DESTRA;
            printf(MAGENTA_CHIARO);
            break;
    }

    // Stampa i tetramini usando le matrici
    for(short i = 0; i < 8; i++) {
        posizione_cursore({coord_tetramino_riserva.X, (short)(coord_tetramino_riserva.Y + i)});
        for(short j = 0; j < 8; j++) {
            printf("%c", tetramino[i][j] ? tetramino[i][j] : ' ');
        }
    }

}

void stampa_coda_tetramini(short tipo1, short tipo2, short tipo3){    //non avevo sbatti

    char tetramino[3][8][8] = {0};

    COORD coord_futuro[3] = {coord_tetramino_futuro, coord_secondo_tetramino_futuro, coord_terzo_tetramino_futuro};
    short tipo[3] = {tipo1, tipo2, tipo3};

    for(short j = 0; j < 3; j++){

        switch(tipo[j]){ 
            case tetramino_i:
                tetramino[j][2][1] = BLOCCO_SINISTRA;
                tetramino[j][3][1] = BLOCCO_SINISTRA;
                tetramino[j][4][1] = BLOCCO_SINISTRA;
                tetramino[j][5][1] = BLOCCO_SINISTRA;
                tetramino[j][2][2] = BLOCCO_DESTRA;
                tetramino[j][3][2] = BLOCCO_DESTRA;
                tetramino[j][4][2] = BLOCCO_DESTRA;
                tetramino[j][5][2] = BLOCCO_DESTRA;
                printf(CIANO);
                break;
            case tetramino_j:
                tetramino[j][0][2] = BLOCCO_SINISTRA;
                tetramino[j][1][2] = BLOCCO_SINISTRA;
                tetramino[j][2][0] = BLOCCO_SINISTRA;
                tetramino[j][2][2] = BLOCCO_SINISTRA;
                tetramino[j][0][3] = BLOCCO_DESTRA;
                tetramino[j][1][3] = BLOCCO_DESTRA;
                tetramino[j][2][1] = BLOCCO_DESTRA;
                tetramino[j][2][3] = BLOCCO_DESTRA;
                printf(BLU_CHIARO);
                break;
            case tetramino_l:
                tetramino[j][0][1] = BLOCCO_SINISTRA;
                tetramino[j][1][1] = BLOCCO_SINISTRA;
                tetramino[j][2][1] = BLOCCO_SINISTRA;
                tetramino[j][2][3] = BLOCCO_SINISTRA;
                tetramino[j][0][2] = BLOCCO_DESTRA;
                tetramino[j][1][2] = BLOCCO_DESTRA;
                tetramino[j][2][2] = BLOCCO_DESTRA;
                tetramino[j][2][4] = BLOCCO_DESTRA;
                printf(ARANCIONE);
                break;
            case tetramino_o:
                tetramino[j][0][0] = BLOCCO_SINISTRA;
                tetramino[j][0][2] = BLOCCO_SINISTRA;
                tetramino[j][1][0] = BLOCCO_SINISTRA;
                tetramino[j][1][2] = BLOCCO_SINISTRA;
                tetramino[j][0][1] = BLOCCO_DESTRA;
                tetramino[j][0][3] = BLOCCO_DESTRA;
                tetramino[j][1][1] = BLOCCO_DESTRA;
                tetramino[j][1][3] = BLOCCO_DESTRA;
                printf(GIALLO_CHIARO);
                break;
            case tetramino_z:
                tetramino[j][0][0] = BLOCCO_SINISTRA;
                tetramino[j][0][2] = BLOCCO_SINISTRA;
                tetramino[j][1][2] = BLOCCO_SINISTRA;
                tetramino[j][1][4] = BLOCCO_SINISTRA;
                tetramino[j][0][1] = BLOCCO_DESTRA;
                tetramino[j][0][3] = BLOCCO_DESTRA;
                tetramino[j][1][3] = BLOCCO_DESTRA;
                tetramino[j][1][5] = BLOCCO_DESTRA;
                printf(ROSSO_CHIARO);
                break;
            case tetramino_s:
                tetramino[j][0][2] = BLOCCO_SINISTRA;
                tetramino[j][0][4] = BLOCCO_SINISTRA;
                tetramino[j][1][0] = BLOCCO_SINISTRA;
                tetramino[j][1][2] = BLOCCO_SINISTRA;
                tetramino[j][0][3] = BLOCCO_DESTRA;
                tetramino[j][0][5] = BLOCCO_DESTRA;
                tetramino[j][1][1] = BLOCCO_DESTRA;
                tetramino[j][1][3] = BLOCCO_DESTRA;
                printf(VERDE_CHIARO);
                break;
            case tetramino_t:
                tetramino[j][0][0] = BLOCCO_SINISTRA;
                tetramino[j][0][2] = BLOCCO_SINISTRA;
                tetramino[j][0][4] = BLOCCO_SINISTRA;
                tetramino[j][1][2] = BLOCCO_SINISTRA;
                tetramino[j][0][1] = BLOCCO_DESTRA;
                tetramino[j][0][3] = BLOCCO_DESTRA;
                tetramino[j][0][5] = BLOCCO_DESTRA;
                tetramino[j][1][3] = BLOCCO_DESTRA;
                printf(MAGENTA_CHIARO);
                break;
            }

                
        // Stampa i tetramini usando le matrici
        for(short i = 0; i < 8; i++) {
            posizione_cursore({coord_futuro[j].X, (short)(coord_futuro[j].Y + i)});
            for(short k = 0; k < 8; k++) {
                printf("%c", tetramino[j][i][k] ? tetramino[j][i][k] : ' ');
            }
        }

    }

}


void cursore_manuale(short x, short y){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord_posizione = {x, y};
    posizione_cursore(coord_posizione);
}

void pulisci(){
    system("cls");
}

COORD posizione_attuale() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    return csbi.dwCursorPosition;
}

void cursore_alto(COORD* coord_posizione, short delta){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    coord_posizione->Y -= delta;
    posizione_cursore(*coord_posizione);
}

void cursore_basso(COORD* coord_posizione, short delta){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    coord_posizione->Y += delta;
    posizione_cursore(*coord_posizione);
}

void cursore_sinistra(COORD* coord_posizione, short delta){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    coord_posizione->X -= delta;
    posizione_cursore(*coord_posizione);
}

void cursore_destra(COORD* coord_posizione, short delta){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    coord_posizione->X += delta;
    posizione_cursore(*coord_posizione);
}

void posizione_cursore(COORD coord_posizione){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, coord_posizione);
}

void nascondi_cursore(){

    printf(CURSORE_INVISIBILE);

}

void mostra_cursore(){

    printf(CURSORE_VISIBILE);

}

void cmd_grande(){

    HWND hwnd = GetConsoleWindow(); // Ottieni il manico della finestra del terminale
    ShowWindow(hwnd, SW_MAXIMIZE);

}
