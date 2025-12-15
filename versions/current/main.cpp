#include "costanti.hpp"
#include "campo.hpp"
#include "grafica.hpp"
#include "input.hpp"
#include "tetramino.hpp"
#include "utilita.hpp"
#include "punteggio.hpp"
#include "gioco.hpp"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

/*
    creare un timer per l'input che entro quei secondi puoi muoverti
    creare un timer quando richiami può cadere, nel main controlli se ritorna false e fai ripartire il ciclo dell'input, all'inizio dell'input devi controllare entrambi i cicli
*/

void menu();

int main(void){

    cmd_grande();
    Input input;
    std::string nome;

    printf(CURSORE_INVISIBILE);
    system("chcp 65001");
    pulisci();
    scritta(100, "hey player, come ti chiami?\n");
    std::getline(std::cin, nome);

    short i;
    bool uscita = false;
    bool uscita_menu = false;

    do{

        uscita = false;
        uscita_menu = false;

        menu();
        
        i = static_cast<short>(CordinateOpzioni::SINGLEPLAYER);

        cursore_manuale(PADDING + 13, i);
        printf(">");

        do{

            if(kbhit()){

                input.scan();

                if(input.azione() == TipoInput::GIROORARIO){// freccia in alto
                    
                    cursore_manuale(PADDING + 13, i);
                    printf(" ");

                    i -= 2;

                    if(i < static_cast<short>(CordinateOpzioni::SINGLEPLAYER)) i = static_cast<short>(CordinateOpzioni::ESCI);
                }

                if(input.azione() == TipoInput::CADUTAVELOCE){// freccia in basso
                    
                    cursore_manuale(PADDING + 13, i);
                    printf(" ");

                    i += 2;

                    if(i > static_cast<short>(CordinateOpzioni::ESCI)) i = static_cast<short>(CordinateOpzioni::SINGLEPLAYER);
                }

                cursore_manuale(PADDING + 13, i);
                printf(">");

                if(input.azione() == TipoInput::CADUTAISTANTANEA){ //spazio o invio
                    
                    switch(i){

                        case static_cast<short>(CordinateOpzioni::SINGLEPLAYER):
                            gioco.partitaSinglePlayer();
                            uscita_menu = true;
                            break;

                        case static_cast<short>(CordinateOpzioni::MULTIPLAYER):
                            break;

                        case static_cast<short>(CordinateOpzioni::OPZIONI):
                            gioco.opzioni();
                            break;

                        case static_cast<short>(CordinateOpzioni::COMANDI):
                            gioco.comandi();
                            break;

                        case static_cast<short>(CordinateOpzioni::CREDITI):
                            break;

                        case static_cast<short>(CordinateOpzioni::ESCI):
                            uscita_menu = true;
                            uscita = true;
                            break;

                    }

                }

            }
        
        }while(!uscita_menu);

        

    }while(!uscita);


    posizione_cursore(coord_fine);

    return 0;

}

void menu(){
    
    printf(VERDE);
    pulisci();

    cornice(0, 0, 67, 25);

    short i = 3;
    cursore_manuale(PADDING, i++);
    scritta(5, " _____ _____     _____ _____ ___________ _____ _____ ");
    cursore_manuale(PADDING, i++);
    scritta(5, "|_   _|  ___|   |_   _|  ___|_   _| ___ \\_   _/  ___|");
    cursore_manuale(PADDING, i++);
    scritta(5, "  | | | |__ ______| | | |__   | | | |_/ / | | \\ `--. ");
    cursore_manuale(PADDING, i++);
    scritta(5, "  | | |  __|______| | |  __|  | | |    /  | |  `--. \\");
    cursore_manuale(PADDING, i++);
    scritta(5, "  | | | |___      | | | |___  | | | |\\ \\ _| |_/\\__/ /");
    cursore_manuale(PADDING, i++);
    scritta(5, "  \\_/ \\____/      \\_/ \\____/  \\_/ \\_| \\_|\\___/\\____/ ");

    cursore_manuale(PADDING + 15, static_cast<short>(CordinateOpzioni::SINGLEPLAYER));
    printf("singleplayer");
    cursore_manuale(PADDING + 15, static_cast<short>(CordinateOpzioni::MULTIPLAYER));
    printf("multiplayer");
    cursore_manuale(PADDING + 15, static_cast<short>(CordinateOpzioni::OPZIONI));
    printf("opzioni");
    cursore_manuale(PADDING + 15, static_cast<short>(CordinateOpzioni::COMANDI));
    printf("comandi");
    cursore_manuale(PADDING + 15, static_cast<short>(CordinateOpzioni::CREDITI));
    printf("crediti");
    cursore_manuale(PADDING + 15, static_cast<short>(CordinateOpzioni::ESCI));
    printf("esci");

}
