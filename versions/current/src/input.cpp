#include "input.hpp"

// inizializzo gli array contenenti gli input

std::array<char, 3> ROTAZIONE = {'W', 'w', 72};
std::array<char, 2> ROTAZIONE_DOPPIA = {'Z', 'z'};
std::array<char, 2> ROTAZIONE_ANTIORARIA = {'R', 'r'};
std::array<char, 3> SINISTRA = {'A', 'a', 75};
std::array<char, 3> DESTRA = {'D', 'd', 77};
std::array<char, 3> CADUTA_VELOCE = {'S', 's', 80};
std::array<char, 4> CADUTA_ISTANTANEA = {'Q', 'q', 32, 13};
std::array<char, 2> CAMBIO = {'C', 'c'};

// classe dell'input 

void Input::scan(){
    input = 0;
    input =_getch();
    if(input == 0 || input == 224)  input = _getch();
}

TipoInput Input::azione(){

    if(destra() == TipoInput::DESTRA){
        return TipoInput::DESTRA;
    }

    if(sinistra() == TipoInput::SINISTRA){
        return TipoInput::SINISTRA;
    }

    if(cadutaVeloce() == TipoInput::CADUTAVELOCE){
        return TipoInput::CADUTAVELOCE;
    }

    if(cadutaIstantanea() == TipoInput::CADUTAISTANTANEA){
        return TipoInput::CADUTAISTANTANEA;
    }

    if(cambio() == TipoInput::CAMBIO){
        return TipoInput::CAMBIO;
    }

    if(rotazione() != TipoInput::NULLA){
        return rotazione();
    }

    return TipoInput::NULLA;

}

TipoInput Input::rotazione(){
    for(char c : ROTAZIONE){
        if(input == c){
            return TipoInput::GIROORARIO;
        }
            
    }
    for(char c : ROTAZIONE_ANTIORARIA){
        if(input == c){
            return TipoInput::GIROANTIORARIO;
        }
            
    }
    for(char c : ROTAZIONE_DOPPIA){
        if(input == c){
            return TipoInput::GIRODOPPIO;
        }
            
    }
    return TipoInput::NULLA;
}

TipoInput Input::destra(){
    for(char c : DESTRA){
        if(input == c){
            return TipoInput::DESTRA;
        }
    }
    return TipoInput::NULLA;
}

TipoInput Input::sinistra(){
    for(char c : SINISTRA){
        if(input == c){
            return TipoInput::SINISTRA;
        }
    }
    return TipoInput::NULLA;
}

TipoInput Input::cadutaVeloce(){
    for(char c : CADUTA_VELOCE){
        if(input == c){
            return TipoInput::CADUTAVELOCE;
        }
    }
    return TipoInput::NULLA;
}

TipoInput Input::cadutaIstantanea(){
    for(char c : CADUTA_ISTANTANEA){
        if(input == c){
            return TipoInput::CADUTAISTANTANEA;
        }
            
    }
    return TipoInput::NULLA;
}

TipoInput Input::cambio(){
    for(char c : CAMBIO){
        if(input == c){
            return TipoInput::CAMBIO;
        }
    }
    return TipoInput::NULLA;
}
