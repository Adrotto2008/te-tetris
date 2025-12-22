#ifndef GIOCO_HPP
#define GIOCO_HPP

#ifdef __linux__
#include "utilita_linux.hpp"
#else
#include "utilita.hpp"
#endif

#include "online.hpp"
#include "campo.hpp"
#include "grafica.hpp"
#include "input.hpp"
#include "tetramino.hpp"
#include "punteggio.hpp"
#include <chrono>
#include <thread>

class Gioco{

    public:

        /*-------------VARIABILI GLOBALI DI IMPOSTAZIONI-----------*/

        TipoPartita TIPO_PARTITA = TipoPartita::NORMALE;
        TipoColori TIPO_COLORI = TipoColori::NORMALE;
        char BLOCCO_GHOST_SINISTRA[4] = "█"; //blocco intero usato dai ghost block 219
        char BLOCCO_GHOST_DESTRA[4] = "█"; //blocco intero usato dai ghost block 219
        char BLOCCO_SINISTRA[4] = "█"; //metà blocco usato per la parte sinistra
        char BLOCCO_DESTRA[4]   = "█"; //metà blocco usato per la parte destra

        /*-------------METODI----------------*/
        void partitaSinglePlayer();
        void multiPlayerStanza(std::string& nome);
        void opzioniStanza(Online* online, RoomDTO stanza, bool owner = false);
        void listaStanze(Online* online, std::string& nome);
        void partitaMultiPlayer();
        void opzioni();
        void comandi();

};

extern Gioco gioco;

#endif