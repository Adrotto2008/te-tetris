#ifndef INPUT_HPP
#define INPUT_HPP

// Su Linux includiamo la classe reale del controller Linux.
// Su Windows includiamo la classe reale del controller Windows.
// Su altre piattaforme usiamo un placeholder minimale.
#if defined(__linux__)
#include "utilita_linux.hpp"
#include "controller_linux.hpp"
#elif defined(_WIN32)
#include "utilita.hpp"
#include "controller_windows.hpp"
#else
#include "utilita.hpp"
typedef struct {
    int i;
    //bool init();
} Controller;
#endif

#include "costanti.hpp"

#include <array>
#include <chrono>

/*------------CLASSE------------*/
class Input {
public:
    char input = 0;
    Controller controller;
    bool controllerReady = false;
    bool controllerButtonState[16] = {false};
    bool controllerAxisState[12] = {false};
    // timestamps per trigger (steady_clock)
    std::chrono::steady_clock::time_point lastButtonTime[16];
    std::chrono::steady_clock::time_point lastAxisTime[12];

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