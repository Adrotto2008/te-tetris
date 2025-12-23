#include "input.hpp"



// classe dell'input 

void Input::scan(){
    input = 0;
    input = _getch();
    #ifdef __linux__
    if (input == 27){

        if (kbhit()){
        
            char input_2 = _getch();
            char input_3 = _getch();
            if (input_2 == '['){
                switch (input_3){

                case 'A':
                    input = 72;
                    break;
                case 'B':
                    input = 80;
                    break;
                case 'C':
                    input = 77;
                    break;
                case 'D':
                    input = 75;
                    break;

                }
            }

        }
        
    }

    if (input == '\n')  input = 13;
    

    #else
    if(input == 0 || input == 224)  input = _getch();
    #endif

    
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

    if(uscita() != TipoInput::NULLA){
        return uscita();
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

TipoInput Input::uscita(){
    for(char c : ESCI){
        if(input == c){
            return TipoInput::ESCI;
        }
    }
    return TipoInput::NULLA;
}