#include "costanti.hpp"

// inizializzo gli array contenenti gli input

std::array<char, 80> CARATTERI_POSSIBILI = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    ' ', '(', ')', '[', ']', '{', '}', '<', '>',
    '.', ',', '!', '?', ';', ':', '/', '\\', '|'
};
std::array<char, 3> ROTAZIONE = {'W', 'w', 72};
std::array<char, 2> ROTAZIONE_DOPPIA = {'Z', 'z'};
std::array<char, 2> ROTAZIONE_ANTIORARIA = {'R', 'r'};
std::array<char, 3> SINISTRA = {'A', 'a', 75};
std::array<char, 3> DESTRA = {'D', 'd', 77};
std::array<char, 3> CADUTA_VELOCE = {'S', 's', 80};
std::array<char, 4> CADUTA_ISTANTANEA = {'Q', 'q', 32, 13};
std::array<char, 2> CAMBIO = {'C', 'c'};
std::array<char, 1> ESCI = {27};

/*-------------VARIABILI GLOBALI DI IMPOSTAZIONI-----------*/

TipoPartita TIPO_PARTITA = TipoPartita::NORMALE;
TipoColori TIPO_COLORI = TipoColori::NORMALE;
char BLOCCO_GHOST_SINISTRA[4] = "█"; //blocco intero usato dai ghost block 219
char BLOCCO_GHOST_DESTRA[4] = "█"; //blocco intero usato dai ghost block 219
char BLOCCO_SINISTRA[4] = "█"; //metà blocco usato per la parte sinistra
char BLOCCO_DESTRA[4]   = "█"; //metà blocco usato per la parte destra

/*--------------CORDINATE GLOBALI----------------------*/

COORD coord_tetramino_futuro = {CAMPO_LUNGHEZZA + 13, 2};
COORD coord_secondo_tetramino_futuro = {CAMPO_LUNGHEZZA + 13 + 18, 2};
COORD coord_terzo_tetramino_futuro = {CAMPO_LUNGHEZZA + 13 + 18 + 19, 2};
COORD coord_tetramino_riserva = {CAMPO_LUNGHEZZA + 13, FUTURI_ALTEZZA + 4};
COORD coord_posizione_campo = {1, 1};
COORD coord_punteggio = {CAMPO_LUNGHEZZA + FUTURI_LUNGHEZZA + 7, FUTURI_ALTEZZA + 5};
COORD coord_linee = {CAMPO_LUNGHEZZA + FUTURI_LUNGHEZZA + 7, FUTURI_ALTEZZA + 7};
COORD coord_livello = {CAMPO_LUNGHEZZA + FUTURI_LUNGHEZZA + 7, FUTURI_ALTEZZA + 9};
COORD coord_fine = {0, CAMPO_ALTEZZA + 10};