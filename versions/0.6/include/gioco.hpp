#ifndef GIOCO_HPP
#define GIOCO_HPP

#include "costanti.hpp"
#include "campo.hpp"
#include "grafica.hpp"
#include "input.hpp"
#include "tetramino.hpp"
#include "utilita.hpp"
#include "punteggio.hpp"
#include <chrono>
#include <thread>

class Gioco{

    public:
        void partitaSinglePlayer();
        void listaStanze();
        void partitaMultiPlayer();
        void opzioni();
        void comandi();

};

extern Gioco gioco;

#endif