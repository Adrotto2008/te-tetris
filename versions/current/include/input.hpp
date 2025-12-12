#ifndef INPUT_HPP
#define INPUT_HPP

#include <array>
#include <conio.h>

/*------------INPUT-------------*/
extern std::array<char, 3> ROTAZIONE;        // freccia su
extern std::array<char, 2> ROTAZIONE_ANTIORARIA;        
extern std::array<char, 2> ROTAZIONE_DOPPIA;        
extern std::array<char, 3> SINISTRA;        // freccia sinistra
extern std::array<char, 3> DESTRA;          // freccia destra
extern std::array<char, 3> CADUTA_VELOCE;   // freccia giù
extern std::array<char, 3> CADUTA_ISTANTANEA; // barra spaziatrice
extern std::array<char, 2> CAMBIO;          // tasto cambio
/*------------------------------*/

/*------------CLASSE------------*/
class Input {
public:
    char input = 0;

    void scan();      
    bool rotazione();   
    bool rotazioneDoppia();  
    bool rotazioneAntiOraria();       
    bool destra();
    bool sinistra();
    bool cadutaVeloce();
    bool cadutaIstantanea();
    bool cambio();
};
/*------------------------------*/

#endif