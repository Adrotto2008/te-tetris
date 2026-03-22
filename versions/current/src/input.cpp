#include "input.hpp"



// classe dell'input 

void Input::scan(){

    input = 0;

    // inizializza controller una sola volta
    if(!controllerReady){
        //controllerReady = controller.init();
    }

    #ifdef __linux__

    if(controllerReady){
        controller.update();

        // --- D-Pad --- (muoversi)
        if(controller.axisValue(6) < -10000 || controller.axisValue(0) < -10000){
            countSinistra++;
            input = 75; // SINISTRA
        }
        if(controller.axisValue(6) > 10000 || controller.axisValue(0) > 10000){
            countDestra++;
            input = 77; // DESTRA
        }
        if(controller.axisValue(7) > 10000 || controller.axisValue(1) > 10000){
            countCadutaVeloce++;
            input = 80; // CADUTA VELOCE
        }

        // --- Pulsanti principali ---
        if(controller.buttonPressed(0)){ // A
            countGiroOrario++;
            input = 72; // GIRO ORARIO
        }
        if(controller.buttonPressed(1)){ // B
            countCadutaIstantanea++;
            input = 32; // CADUTA ISTANTANEA
        }
        if(controller.buttonPressed(2)){ // X
            countGiroDoppio++;
            input = 90; // GIRO DOPPIO
        }
        if(controller.buttonPressed(3)){ // Y
            countCambio++;
            input = 67; // CAMBIO
        }

        // --- Tasti laterali ---
        if(controller.buttonPressed(4)){ // LB
            countRotAntiOraria++;
            input = 82; // ROTAZIONE ANTI ORARIA
        }
        if(controller.buttonPressed(5)){ // RB
            countRotOraria++;
            input = 72; // ROTAZIONE ORARIA
        }
        if(controller.axisValue(4) > 10000){ // LT
            countRotAntiOraria++;
            input = 82; // ROTAZIONE ANTI ORARIA
        }
        if(controller.axisValue(5) > 10000){ // RT
            countRotOraria++;
            input = 72; // ROTAZIONE ORARIA
        }

        // --- Joypad destro ---
        if(controller.axisValue(2) > 10000){
            countGiroOrario++;
            input = 72; // GIRO ORARIO
        }
        if(controller.axisValue(2) < -10000){
            countRotAntiOraria++;
            input = 82; // GIRO ANTI ORARIO
        }
        if(controller.axisValue(3) > 10000){
            countCadutaIstantanea++;
            input = 13; // CADUTA ISTANTANEA
        }
        if(controller.axisValue(3) < -10000){
            countCambio++;
            input = 67; // CAMBIO
        }

        // --- Start come ESC ---
        if(controller.buttonPressed(7)){
            countEsc++;
            input = 27;
        }
    }

    #endif


    // se il controller non ha dato input → controlla tastiera
    if(input == 0){

        if(kbhit()){

            input = _getch();
            

    #ifdef __linux__

            if (input == 27){

                if (kbhit()){

                    char input_2 = _getch();
                    char input_3 = _getch();

                    if (input_2 == '['){

                        switch (input_3){

                            case 'A': input = 72; break;
                            case 'B': input = 80; break;
                            case 'C': input = 77; break;
                            case 'D': input = 75; break;

                        }
                    }
                }
            }

            if (input == '\n')
                input = 13;

    #else

            if(input == 0 || input == 224)
                input = _getch();

    #endif

        }

    }

}

bool Input::valido(){
    
    for (char c: CARATTERI_POSSIBILI){
        if(c == input)
            return true;
    }
    
    return false;

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