#include "input.hpp"
#include <chrono>
#include <algorithm>



// classe dell'input 

void Input::scan(){

    input = 0;

    // inizializza controller una sola volta (se possibile)
    if(!controllerReady){
        //controllerReady = controller.init();
    }

    #if defined(__linux__) || defined(_WIN32)

    if(controllerReady){
        controller.update();

        // Debounce / edge-detection: consideriamo solo la transizione da
        // non premuto -> premuto per evitare ripetizioni multiple.

        auto now = std::chrono::steady_clock::now();
        auto setInputIfEmpty = [&](char value) {
            if (input == 0) {
                input = value;
            }
        };

        // --- D-Pad --- (muoversi)
        bool leftActive = (controller.axisValue(6) < -10000 || controller.axisValue(0) < -10000);
        {
                    auto &last = lastAxisTime[0];
                    if(leftActive){
                        if(!controllerAxisState[0]){
                            // transition: immediate trigger
                            countSinistra++;
                            input = 75; // SINISTRA
                            last = now;
                        } else {
                            // held: repeat at CONTROLLER_REPEAT_MS
                            if(last.time_since_epoch().count() != 0){
                                long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
                                if(elapsed >= CONTROLLER_REPEAT_MS){
                                    countSinistra++;
                                    input = 75;
                                    last = now;
                                }
                            }
                        }
                    }
                    controllerAxisState[0] = leftActive;
        }

        bool rightActive = (controller.axisValue(6) > 10000 || controller.axisValue(0) > 10000);
        {
            auto &last = lastAxisTime[1];
            if(rightActive){
                if(!controllerAxisState[1]){
                    countDestra++;
                    input = 77; // DESTRA
                    last = now;
                } else if(last.time_since_epoch().count() != 0){
                    long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
                    if(elapsed >= CONTROLLER_REPEAT_MS){
                        countDestra++;
                        input = 77;
                        last = now;
                    }
                }
            }
            controllerAxisState[1] = rightActive;
        }

        bool downActive = (controller.axisValue(7) > 10000 || controller.axisValue(1) > 10000);
        {
            auto &last = lastAxisTime[2];
            if(downActive){
                if(!controllerAxisState[2]){
                    countCadutaVeloce++;
                    input = 80; // CADUTA VELOCE
                    last = now;
                } else if(last.time_since_epoch().count() != 0){
                    long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
                    if(elapsed >= CONTROLLER_REPEAT_MS){
                        countCadutaVeloce++;
                        input = 80;
                        last = now;
                    }
                }
            }
            controllerAxisState[2] = downActive;
        }

        // --- Pulsanti principali (A/B/X/Y) ---
        {
            bool cur = controller.buttonPressed(0);
            auto &last = lastButtonTime[0];
            if(cur){
                if(!controllerButtonState[0]){
                    // transition
                    countGiroOrario++;
                    input = 72; // GIRO ORARIO
                    last = now;
                } else if(last.time_since_epoch().count() != 0){
                    long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
                    if(elapsed >= CONTROLLER_REPEAT_MS){
                        countGiroOrario++;
                        input = 72;
                        last = now;
                    }
                }
            }
            controllerButtonState[0] = cur;
        }

        {
            bool cur = controller.buttonPressed(1);
            auto &last = lastButtonTime[1];
            if(cur){
                if(!controllerButtonState[1]){
                    countCadutaIstantanea++;
                    input = 32; // CADUTA ISTANTANEA
                    last = now;
                } else if(last.time_since_epoch().count() != 0){
                    long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
                    if(elapsed >= CONTROLLER_REPEAT_MS){
                        countCadutaIstantanea++;
                        input = 32;
                        last = now;
                    }
                }
            }
            controllerButtonState[1] = cur;
        }

        {
            bool cur = controller.buttonPressed(2);
            auto &last = lastButtonTime[2];
            if(cur){
                if(!controllerButtonState[2]){
                    countGiroDoppio++;
                    input = 90; // GIRO DOPPIO
                    last = now;
                } else if(last.time_since_epoch().count() != 0){
                    long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
                    if(elapsed >= CONTROLLER_REPEAT_MS){
                        countGiroDoppio++;
                        input = 90;
                        last = now;
                    }
                }
            }
            controllerButtonState[2] = cur;
        }

        {
            bool cur = controller.buttonPressed(3);
            auto &last = lastButtonTime[3];
            if(cur){
                if(!controllerButtonState[3]){
                    countCambio++;
                    input = 67; // CAMBIO
                    last = now;
                } else if(last.time_since_epoch().count() != 0){
                    long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
                    if(elapsed >= CONTROLLER_REPEAT_MS){
                        countCambio++;
                        input = 67;
                        last = now;
                    }
                }
            }
            controllerButtonState[3] = cur;
        }

        // --- Tasti laterali ---
        {
            bool cur = controller.buttonPressed(4);
            auto &last = lastButtonTime[4];
            if(cur){
                if(!controllerButtonState[4]){
                    countRotAntiOraria++;
                    setInputIfEmpty(82); // ROTAZIONE ANTI ORARIA
                    last = now;
                } else if(last.time_since_epoch().count() != 0){
                    long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
                    if(elapsed >= CONTROLLER_REPEAT_MS){
                        countRotAntiOraria++;
                        setInputIfEmpty(82);
                        last = now;
                    }
                }
            }
            controllerButtonState[4] = cur;
        }

        {
            bool cur = controller.buttonPressed(5);
            auto &last = lastButtonTime[5];
            if(cur){
                if(!controllerButtonState[5]){
                    countRotOraria++;
                    setInputIfEmpty(72); // ROTAZIONE ORARIA
                    last = now;
                } else if(last.time_since_epoch().count() != 0){
                    long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
                    if(elapsed >= CONTROLLER_REPEAT_MS){
                        countRotOraria++;
                        setInputIfEmpty(72);
                        last = now;
                    }
                }
            }
            controllerButtonState[5] = cur;
        }

        bool ltActive = (controller.axisValue(4) > 10000);
        {
            auto &last = lastAxisTime[3];
            if(ltActive){
                if(!controllerAxisState[3]){
                    countRotAntiOraria++;
                    input = 82; // ROTAZIONE ANTI ORARIA
                    last = now;
                } else if(last.time_since_epoch().count() != 0){
                    long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
                    if(elapsed >= CONTROLLER_REPEAT_MS){
                        countRotAntiOraria++;
                        input = 82;
                        last = now;
                    }
                }
            }
            controllerAxisState[3] = ltActive;
        }

        bool rtActive = (controller.axisValue(5) > 10000);
        {
            auto &last = lastAxisTime[4];
            if(rtActive){
                if(!controllerAxisState[4]){
                    countRotOraria++;
                    input = 72; // ROTAZIONE ORARIA
                    last = now;
                } else if(last.time_since_epoch().count() != 0){
                    long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
                    if(elapsed >= CONTROLLER_REPEAT_MS){
                        countRotOraria++;
                        input = 72;
                        last = now;
                    }
                }
            }
            controllerAxisState[4] = rtActive;
        }

        // --- Joypad destro ---
        bool joyRXPos = (controller.axisValue(2) > 10000);
        {
            auto &last = lastAxisTime[5];
            if(joyRXPos){
                if(!controllerAxisState[5]){
                    countGiroOrario++;
                    setInputIfEmpty(72); // GIRO ORARIO
                    last = now;
                } else if(last.time_since_epoch().count() != 0){
                    long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
                    if(elapsed >= CONTROLLER_REPEAT_MS){
                        countGiroOrario++;
                        setInputIfEmpty(72);
                        last = now;
                    }
                }
            }
            controllerAxisState[5] = joyRXPos;
        }

        bool joyRXNeg = (controller.axisValue(2) < -10000);
        {
            auto &last = lastAxisTime[6];
            if(joyRXNeg){
                if(!controllerAxisState[6]){
                    countRotAntiOraria++;
                    setInputIfEmpty(82); // GIRO ANTI ORARIO
                    last = now;
                } else if(last.time_since_epoch().count() != 0){
                    long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
                    if(elapsed >= CONTROLLER_REPEAT_MS){
                        countRotAntiOraria++;
                        setInputIfEmpty(82);
                        last = now;
                    }
                }
            }
            controllerAxisState[6] = joyRXNeg;
        }

        bool joyRYPos = (controller.axisValue(3) > 10000);
        {
            auto &last = lastAxisTime[7];
            if(joyRYPos){
                if(!controllerAxisState[7]){
                    countCadutaIstantanea++;
                    setInputIfEmpty(13); // CADUTA ISTANTANEA
                    last = now;
                } else if(last.time_since_epoch().count() != 0){
                    long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
                    if(elapsed >= CONTROLLER_REPEAT_MS){
                        countCadutaIstantanea++;
                        setInputIfEmpty(13);
                        last = now;
                    }
                }
            }
            controllerAxisState[7] = joyRYPos;
        }

        bool joyRYNeg = (controller.axisValue(3) < -10000);
        {
            auto &last = lastAxisTime[8];
            if(joyRYNeg){
                if(!controllerAxisState[8]){
                    countCambio++;
                    setInputIfEmpty(67); // CAMBIO
                    last = now;
                } else if(last.time_since_epoch().count() != 0){
                    long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
                    if(elapsed >= CONTROLLER_REPEAT_MS){
                        countCambio++;
                        setInputIfEmpty(67);
                        last = now;
                    }
                }
            }
            controllerAxisState[8] = joyRYNeg;
        }

        // --- D-Pad up (no analog up) ---
        bool dpadUp = (controller.axisValue(7) < -10000);
        {
            auto &last = lastAxisTime[9];
            if(dpadUp){
                if(!controllerAxisState[9]){
                    countGiroOrario++;
                    setInputIfEmpty(72); // GIRO ORARIO (d-pad up)
                    last = now;
                } else if(last.time_since_epoch().count() != 0){
                    long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
                    if(elapsed >= CONTROLLER_REPEAT_MS){
                        countGiroOrario++;
                        setInputIfEmpty(72);
                        last = now;
                    }
                }
            }
            controllerAxisState[9] = dpadUp;
        }

        // --- Back (ESC) / Start (Invio) ---
        {
            bool cur = controller.buttonPressed(6); // Back
            auto &last = lastButtonTime[6];
            if(cur){
                if(!controllerButtonState[6]){
                    countEsc++;
                    input = 27; // ESC
                    last = now;
                } else if(last.time_since_epoch().count() != 0){
                    long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
                    if(elapsed >= CONTROLLER_REPEAT_MS){
                        countEsc++;
                        input = 27;
                        last = now;
                    }
                }
            }
            controllerButtonState[6] = cur;
        }

        {
            bool cur = controller.buttonPressed(7); // Start
            auto &last = lastButtonTime[7];
            if(cur){
                if(!controllerButtonState[7]){
                    countCadutaIstantanea++;
                    input = 13; // INVIO / CADUTA ISTANTANEA
                    last = now;
                } else if(last.time_since_epoch().count() != 0){
                    long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
                    if(elapsed >= CONTROLLER_REPEAT_MS){
                        countCadutaIstantanea++;
                        input = 13;
                        last = now;
                    }
                }
            }
            controllerButtonState[7] = cur;
        }

        // --- L3 / R3 per sensibilità - / + ---
        {
            bool cur = controller.buttonPressed(8); // L3
            auto &last = lastButtonTime[8];
            if(cur){
                if(!controllerButtonState[8]){
                    CONTROLLER_REPEAT_MS = std::max(30, CONTROLLER_REPEAT_MS - 10);
                    input = '-';
                    last = now;
                } else if(last.time_since_epoch().count() != 0){
                    long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
                    if(elapsed >= CONTROLLER_REPEAT_MS){
                        CONTROLLER_REPEAT_MS = std::max(30, CONTROLLER_REPEAT_MS - 10);
                        input = '-';
                        last = now;
                    }
                }
            }
            controllerButtonState[8] = cur;
        }

        {
            bool cur = controller.buttonPressed(9); // R3
            auto &last = lastButtonTime[9];
            if(cur){
                if(!controllerButtonState[9]){
                    CONTROLLER_REPEAT_MS = std::min(400, CONTROLLER_REPEAT_MS + 10);
                    input = '+';
                    last = now;
                } else if(last.time_since_epoch().count() != 0){
                    long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
                    if(elapsed >= CONTROLLER_REPEAT_MS){
                        CONTROLLER_REPEAT_MS = std::min(400, CONTROLLER_REPEAT_MS + 10);
                        input = '+';
                        last = now;
                    }
                }
            }
            controllerButtonState[9] = cur;
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

            if (input == '-')
                CONTROLLER_REPEAT_MS = std::max(30, CONTROLLER_REPEAT_MS - 10);

            if (input == '+')
                CONTROLLER_REPEAT_MS = std::min(400, CONTROLLER_REPEAT_MS + 10);

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

    if(input == '-'){
        return TipoInput::SENSIBILITA_MENO;
    }

    if(input == '+'){
        return TipoInput::SENSIBILITA_PIU;
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
