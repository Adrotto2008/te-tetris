#ifndef COSTANTI_HPP
#define COSTANTI_HPP




/*-----------COSTANTI----------------*/

/*------------CORDINATE---------*/
#define CAMPO_ALTEZZA 27 // 27
#define CAMPO_LUNGHEZZA 20 // 20
#define CAMPO_CENTRO CAMPO_LUNGHEZZA / 2

#define PADDING 7
#define PADDING_COMANDI 3

#define FUTURI_ALTEZZA 10
#define FUTURI_LUNGHEZZA 20
#define FUTURI_SECONDO (FUTURI_LUNGHEZZA - (CAMPO_LUNGHEZZA + 4) / 3)
#define FUTURI_CENTRO CAMPO_LUNGHEZZA + 4 + ((FUTURI_LUNGHEZZA - (CAMPO_LUNGHEZZA + 4)) / 2)

/*-------------BLOCCHI----------*/
#define BLOCCO 219 //blocco intero usato dai ghost block
#define BLOCCO_SINISTRA '[' //metà blocco usato per la parte sinistra
#define BLOCCO_DESTRA   ']' //metà blocco usato per la parte destra

/*-----------------------------------*/


/*------------COLORI------------*/
#define RESET   "\033[0m"
#define NERO    "\033[30m"
#define ROSSO   "\033[31m"
#define VERDE   "\033[32m"
#define GIALLO  "\033[33m"
#define BLU     "\033[34m"
#define MAGENTA "\033[35m"
#define CIANO   "\033[36m"
#define BIANCO  "\033[37m"
#define ARANCIONE "\033[38;5;208m"
#define VIOLA "\033[38;5;129m"
#define GRIGIO "\033[38;5;245m"
#define MARRONE "\033[38;5;94m"

#define BLU_CHIARO "\033[38;5;123m"
#define VERDE_CHIARO "\033[38;5;82m"
#define GIALLO_CHIARO "\033[38;5;226m"
#define ROSSO_CHIARO "\033[38;5;196m"
#define VERDE_SCURO "\033[38;5;34m"
#define GIALLO_SCURO "\033[38;5;220m"
#define BLU_SCURO "\033[38;5;24m"
#define MAGENTA_CHIARO "\033[38;5;201m"
#define CIANO_CHIARO "\033[38;5;51m"
#define GRIGIO_CHIARO "\033[38;5;250m"
#define VIOLA_CHIARO "\033[38;5;135m"
#define LIGHT_RED "\033[38;5;9m"
#define LIGHT_GREEN "\033[38;5;10m"
#define LIGHT_YELLOW "\033[38;5;11m"
#define LIGHT_BLUE "\033[38;5;12m"
#define LIGHT_MAGENTA "\033[38;5;13m"
#define LIGHT_CYAN "\033[38;5;14m"
#define DARK_GRAY "\033[38;5;8m"
/*------------------------------*/


/*-----------CURSORE-------------*/
#define CURSORE_INVISIBILE "\033[?25l"
#define CURSORE_VISIBILE "\033[?25h"
/*------------------------------*/


/*--------------ENUMS----------------*/

/*----------CORDINATE------------*/
enum class CordinateOpzioni{
    SINGLEPLAYER = 12,
    MULTIPLAYER = 14,
    OPZIONI = 16,
    COMANDI = 18,
    CREDITI = 20,
    ESCI = 22
};

enum class CordinateComandi{
    DESTRA = 11,
    SINISTRA = 13,
    CADUTAVELOCE = 15,
    CADUTAISTANTANEA = 17,
    GIROORARIO = 11,
    GIROANTIORARIO = 13,
    GIRODOPPIO = 15,
    CAMBIO = 17,
    ESCI = 19
};
/*-------------TIPI-------------*/ // gli ultimi 2 sono usati per la pulizia, non sono dei tipi di tetramini ma se è vero o ghostblock
enum class TipoTetramino {
    I = 1,
    J = 2,
    L = 3,
    O = 4,
    S = 5,
    Z = 6,
    T = 7,
    NORMALE = 8,
    GHOST
};

/*------------COLORI------------*/
enum Colori {
    rosso = -1,
    ciano = -2,
    blu = -3,
    arancione = -4,
    giallo = -5,
    verde = -6,
    magenta = -7,
    bianco = -8
};

/*----------COLLISIONI----------*/

enum class Collisioni{
    FUORI,
    COLLISIONE,
    LIBERO
};

/*------------INPUT------------*/

enum class TipoInput{
    DESTRA,
    SINISTRA,
    GIROORARIO,
    GIROANTIORARIO,
    GIRODOPPIO,
    CADUTAVELOCE,
    CADUTAISTANTANEA,
    CAMBIO,
    ESCI,
    NULLA
};

#endif