#ifdef __linux__
#include "utilita_linux.hpp"
#else
#include "utilita.hpp"
#endif
#include "costanti.hpp"
#include "campo.hpp"
#include "grafica.hpp"
#include "input.hpp"
#include "audio.hpp"
#include "tetramino.hpp"
#include "punteggio.hpp"
#include "gioco.hpp"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>


void menu();

int main(void){

    cmd_grande();
    Input input;
    std::string nome;
    
    pulisci();
    printf(CURSORE_INVISIBILE);
    nome = apri_config();

    AudioManager audio;
    audio.caricaMusiche("../sounds/music/menu");
    audio.setVolumeMusica(AUDIO_MUSICA);

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

            audio.aggiornaMusica();

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
                            audio.fermaMusica();
                            gioco.partitaSinglePlayer();
                            uscita_menu = true;
                            break;

                        case static_cast<short>(CordinateOpzioni::MULTIPLAYER):
                            gioco.multiPlayerStanza(nome);
                            uscita_menu = true;
                            break;

                        case static_cast<short>(CordinateOpzioni::OPZIONI):
                            audio.fermaMusica();
                            gioco.opzioni();
                            uscita_menu = true;
                            break;

                        case static_cast<short>(CordinateOpzioni::COMANDI):
                            audio.fermaMusica();
                            gioco.comandi();
                            uscita_menu = true;
                            break;

                        case static_cast<short>(CordinateOpzioni::CREDITI):
                            audio.fermaMusica();
                            break;

                        case static_cast<short>(CordinateOpzioni::ESCI):
                            uscita_menu = true;
                            uscita = true;
                            break;

                    }

                    audio.setVolumeMusica(AUDIO_MUSICA);

                }

            }
        
        }while(!uscita_menu);

        

    }while(!uscita);

    audio.fermaMusica();
    posizione_cursore(coord_fine);
    ripristina_echo();
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
