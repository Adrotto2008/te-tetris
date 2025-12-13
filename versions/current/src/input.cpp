#include "input.hpp"

// inizializzo gli array contenenti gli input

std::array<char, 3> ROTAZIONE = {'W', 'w', 72};
std::array<char, 2> ROTAZIONE_DOPPIA = {'Z', 'z'};
std::array<char, 2> ROTAZIONE_ANTIORARIA = {'R', 'r'};
std::array<char, 3> SINISTRA = {'A', 'a', 75};
std::array<char, 3> DESTRA = {'D', 'd', 77};
std::array<char, 3> CADUTA_VELOCE = {'Q', 'q', 80};
std::array<char, 3> CADUTA_ISTANTANEA = {'S', 's', 32};
std::array<char, 2> CAMBIO = {'C', 'c'};

// classe dell'input 

void Input::scan(){
    input = 0;
    input =_getch();
    if(input == 0 || input == 224)  input = _getch();
}

TipoGiro Input::rotazione(){
    for(char c : ROTAZIONE){
        if(input == c){
            return TipoGiro::ORARIA;
        }
            
    }
    for(char c : ROTAZIONE_ANTIORARIA){
        if(input == c){
            return TipoGiro::ANTIORARIA;
        }
            
    }
    for(char c : ROTAZIONE_DOPPIA){
        if(input == c){
            return TipoGiro::DOPPIA;
        }
            
    }
    return TipoGiro::NULLA;
}

bool Input::destra(){
    for(char c : DESTRA){
        if(input == c){
            return true;
        }
    }
    return false;
}

bool Input::sinistra(){
    for(char c : SINISTRA){
        if(input == c){
            return true;
        }
    }
    return false;
}

bool Input::cadutaVeloce(){
    for(char c : CADUTA_VELOCE){
        if(input == c){
            return true;
        }
    }
    return false;
}

bool Input::cadutaIstantanea(){
    for(char c : CADUTA_ISTANTANEA){
        if(input == c){
            return true;
        }
            
    }
    return false;
}

bool Input::cambio(){
    for(char c : CAMBIO){
        if(input == c){
            return true;
        }
    }
    return false;
}
