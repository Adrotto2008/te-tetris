#ifndef INPUT_HPP
#define INPUT_HPP

#include "costanti.hpp"
#ifdef __linux__
#include "utilita_linux.hpp"
#else
#include "utilita.hpp"
#endif

#include <array>

/*------------CLASSE------------*/
class Input {
public:
    char input = 0;

    void scan();      
    bool valido();
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