#ifndef INPUT_HPP
#define INPUT_HPP

#include "costanti.hpp"
#ifdef __linux__
#include "utilita_linux.hpp"
#else
#include "utilita.hpp"
#endif

#include <array>

/*------------INPUT-------------*/
extern std::array<char, 3> ROTAZIONE;        // freccia su
extern std::array<char, 2> ROTAZIONE_ANTIORARIA;        
extern std::array<char, 2> ROTAZIONE_DOPPIA;        
extern std::array<char, 3> SINISTRA;        // freccia sinistra
extern std::array<char, 3> DESTRA;          // freccia destra
extern std::array<char, 3> CADUTA_VELOCE;   // freccia giù
extern std::array<char, 4> CADUTA_ISTANTANEA; // barra spaziatrice
extern std::array<char, 2> CAMBIO;          // tasto cambio
extern std::array<char, 1> ESCI;  
/*------------------------------*/

/*------------CLASSE------------*/
class Input {
public:
    char input = 0;

    void scan();      
    TipoInput azione();
    TipoInput rotazione();       
    TipoInput destra();
    TipoInput sinistra();
    TipoInput cadutaVeloce();
    TipoInput cadutaIstantanea();
    TipoInput cambio();
    TipoInput uscita();
};
/*------------------------------*/

#endif