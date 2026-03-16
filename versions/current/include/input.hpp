#ifndef INPUT_HPP
#define INPUT_HPP

#ifdef __linux__
#include "utilita_linux.hpp"
#include "controller_linux.hpp"
#else
#include "utilita.hpp"
#endif

#include "costanti.hpp"

#include <array>

/*------------CLASSE------------*/
class Input {
public:
    char input = 0;
    Controller controller;
    bool controllerReady = false;
    bool controllerButtonState[16] = {false};
    bool controllerAxisState[8] = {false};

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

    int countSinistra = 0;
    int countDestra = 0;
    int countCadutaVeloce = 0;
    int countGiroOrario = 0;
    int countCadutaIstantanea = 0;
    int countGiroDoppio = 0;
    int countCambio = 0;
    int countRotAntiOraria = 0;
    int countRotOraria = 0;
    int countEsc = 0;
};
/*------------------------------*/

#endif