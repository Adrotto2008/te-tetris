#ifndef GIOCO_HPP
#define GIOCO_HPP

#include "costanti.hpp"
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