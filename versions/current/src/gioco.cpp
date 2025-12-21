#include "gioco.hpp"

using namespace std;
using namespace chrono;

Gioco gioco;

void Gioco::partitaSinglePlayer(){

    printf(BIANCO);
    cmd_grande();
    nascondi_cursore();
    pulisci();

    // disegno la cornice del campo
    cornice(0, 0, CAMPO_LUNGHEZZA, CAMPO_ALTEZZA);
    // disegno la cornice dei tetramini futuri
    cornice(CAMPO_LUNGHEZZA + 4, 0, FUTURI_LUNGHEZZA, FUTURI_ALTEZZA + 1); 
    cornice(CAMPO_LUNGHEZZA + 4 + FUTURI_LUNGHEZZA - 1, 0, FUTURI_LUNGHEZZA, FUTURI_ALTEZZA + 1);
    cornice(CAMPO_LUNGHEZZA + 4 + FUTURI_LUNGHEZZA - 1 + FUTURI_LUNGHEZZA - 1, 0, FUTURI_LUNGHEZZA, FUTURI_ALTEZZA + 1);
    // disegno la cornice del tetramino di riserva
    cornice(CAMPO_LUNGHEZZA + 4, FUTURI_ALTEZZA + 2, FUTURI_LUNGHEZZA, CAMPO_ALTEZZA - FUTURI_ALTEZZA - 2); 

    COORD backup_tetramino[8] = {0, 0};
    
    Input input;
    campo.inizializza(); 

    Tetramino* CodaTetramini[4] = {NULL};
    Tetramino* RiservaTetramino[2] = {NULL};
    short sostituzioni = 0;
    TipoInput ultima_azione = TipoInput::NULLA;

    for(short i = 0; i < 3; i++){
        CodaTetramini[i] = new Tetramino();
    }

    /*------------------CONTROLLO PERDITA--------------------*/ // continua fino a quando non perdi
	for(short j = 0; !CodaTetramini[0]->perdita(); j++){


        short ultima_speranza = 0;

        
        /*------------------GENERAZIONE TETRAMINO FUTURO--------------------*/

        CodaTetramini[3] = new Tetramino();

        /*------------------STAMPA TETRAMINI FUTURI--------------------*/

        stampa_coda_tetramini(CodaTetramini[1]->tipo, CodaTetramini[2]->tipo, CodaTetramini[3]->tipo);

        /*------------------PUNTEGGIO--------------------*/        

        if(campo.controlloPrimaLinea()){
            punteggio.tetrisCompleto();
        }

        punteggio.comboAttuale(punteggio.lineeRiempite(campo.controlloPunti()));        
        

		bool puo_sostituire = true;

		while(CodaTetramini[0]->in_movimento){//FARE in_movimento

            //salvo le cordinate nei backup
            for(short k = 0; k < 8; k++){
                backup_tetramino[k] = CodaTetramini[0]->p[k];
            }

            CodaTetramini[0]->stampa_id(); 
            CodaTetramini[0]->stampa();
            campo.stampa(CodaTetramini[0]->p, backup_tetramino, CodaTetramini[0]->ghost_block(), CodaTetramini[0]->in_movimento);

            /*-----------GESTIONE DELL'INPUT-----------------*/
            
            TipoInput azione_ultima_speranza = TipoInput::NULLA;
            prova:
            timer_input = 500;
            thread countdownInput(countdown_input, timer_input);

            while(timer_input){

                
                if(kbhit() || azione_ultima_speranza != TipoInput::NULLA){    

                    if(azione_ultima_speranza == TipoInput::NULLA){
                        input.input = 0;
                        input.scan();
                    }else{
                        azione_ultima_speranza = TipoInput::NULLA;
                    }

                    if(input.cambio() == TipoInput::CAMBIO && puo_sostituire){

                        ultima_azione == TipoInput::CAMBIO;
                        puo_sostituire = false; //in questo modo posso effettuare una sostituzione per tetramino
                        sostituzioni++;

                        if(sostituzioni != 2){ // != 2 perchè la prima volta lo puoi fare 2 volte quindi è un modo rozzo per evitare il bug                    

                            
                            CodaTetramini[0]->pulisci(TipoTetramino::NORMALE);
                            CodaTetramini[0]->in_movimento = false;
                            CodaTetramini[0]->pulisci(TipoTetramino::GHOST);
                            CodaTetramini[0]->sparisci();

                            if(sostituzioni == 1){
                                RiservaTetramino[0] = new Tetramino(CodaTetramini[0]->id_tetramino, CodaTetramini[0]->tipo);
                                stampa_riserva_tetramino(RiservaTetramino[0]->tipo);
                                countdownInput.join();
                                goto PRIMO_CAMBIO;
                            } else {
                                RiservaTetramino[1] = new Tetramino(CodaTetramini[0]->id_tetramino, CodaTetramini[0]->tipo);
                                delete(CodaTetramini[0]);
                                CodaTetramini[0] = new Tetramino(RiservaTetramino[0]->id_tetramino, RiservaTetramino[0]->tipo);
                                delete(RiservaTetramino[0]);
                                RiservaTetramino[0] = new Tetramino(RiservaTetramino[1]->id_tetramino, RiservaTetramino[1]->tipo);
                                delete(RiservaTetramino[1]);
                            }
                            
                            stampa_riserva_tetramino(RiservaTetramino[0]->tipo);

                        }

                    }else{

                        if(input.cadutaVeloce() == TipoInput::CADUTAVELOCE && CodaTetramini[0]->puo_cadere() == Collisioni::LIBERO){
                            ultima_azione = TipoInput::CADUTAVELOCE;
                            CodaTetramini[0]->pulisci(TipoTetramino::NORMALE);
                            punteggio.cadutaVeloce(CodaTetramini[0]->cadutaVeloce());
                        }

                        if(input.destra() == TipoInput::DESTRA && CodaTetramini[0]->puo_destra() == Collisioni::LIBERO){
                            ultima_azione = TipoInput::DESTRA;
                            CodaTetramini[0]->pulisci(TipoTetramino::NORMALE);
                            CodaTetramini[0]->pulisci(TipoTetramino::GHOST);
                            CodaTetramini[0]->sposta_destra();
                        }

                        if(input.sinistra() == TipoInput::SINISTRA && CodaTetramini[0]->puo_sinistra() == Collisioni::LIBERO){
                            ultima_azione = TipoInput::SINISTRA;
                            CodaTetramini[0]->pulisci(TipoTetramino::NORMALE);
                            CodaTetramini[0]->pulisci(TipoTetramino::GHOST);
                            CodaTetramini[0]->sposta_sinistra();
                        }

                        if(input.rotazione() == TipoInput::GIROORARIO && CodaTetramini[0]->puo_girare(TipoInput::GIROORARIO) == Collisioni::LIBERO) {
                            ultima_azione = TipoInput::GIROORARIO;
                            CodaTetramini[0]->pulisci(TipoTetramino::NORMALE);
                            CodaTetramini[0]->pulisci(TipoTetramino::GHOST);
                            CodaTetramini[0]->gira(TipoInput::GIROORARIO);
                        }else 
                        
                        if(input.rotazione() == TipoInput::GIROANTIORARIO && CodaTetramini[0]->puo_girare(TipoInput::GIROANTIORARIO) == Collisioni::LIBERO) { 
                            ultima_azione = TipoInput::GIROANTIORARIO;
                            CodaTetramini[0]->pulisci(TipoTetramino::NORMALE);
                            CodaTetramini[0]->pulisci(TipoTetramino::GHOST);
                            CodaTetramini[0]->gira(TipoInput::GIROANTIORARIO);
                        }else

                        if(input.rotazione() == TipoInput::GIRODOPPIO && CodaTetramini[0]->puo_girare(TipoInput::GIRODOPPIO) == Collisioni::LIBERO) { 
                            ultima_azione = TipoInput::GIRODOPPIO;
                            CodaTetramini[0]->pulisci(TipoTetramino::NORMALE);
                            CodaTetramini[0]->pulisci(TipoTetramino::GHOST);
                            CodaTetramini[0]->gira(TipoInput::GIRODOPPIO);
                        }

                        if(input.uscita() == TipoInput::ESCI){
                            countdownInput.join();
                            return;
                        }

                        if(input.cadutaIstantanea() == TipoInput::CADUTAISTANTANEA){
                            ultima_azione = TipoInput::CADUTAISTANTANEA;
                            CodaTetramini[0]->pulisci(TipoTetramino::NORMALE);
                            CodaTetramini[0]->pulisci(TipoTetramino::GHOST);
                            timer_input = 0;
                            punteggio.cadutaIstantanea(CodaTetramini[0]->caduta_istantanea());
                            
                        }

                        
                        
                    }

                    CodaTetramini[0]->stampa();
                    campo.stampa(CodaTetramini[0]->p, backup_tetramino, CodaTetramini[0]->ghost_block(), CodaTetramini[0]->in_movimento);

                    

                    

                }

                posizione_cursore(coord_punteggio);
                printf("punteggio : %.0f", punteggio.punti);

            }

            countdownInput.join();

            /*---------------------CADUTA--------------------*/

            if(CodaTetramini[0]->puo_cadere() == Collisioni::LIBERO) {

                CodaTetramini[0]->pulisci(TipoTetramino::NORMALE);

                punteggio.cadutaLenta(CodaTetramini[0]->caduta_lenta());
                                
            }else{

                if(CodaTetramini[0]->in_movimento){
    
                    timer_caduta = 500;
                    thread countdownCaduta(countdown_caduta, timer_caduta);

                    while(timer_caduta){

                        input.input = 0;
                        if(kbhit()){
                            
                            input.scan();
                            azione_ultima_speranza = input.azione();
                            if(azione_ultima_speranza == TipoInput::CADUTAVELOCE || azione_ultima_speranza == TipoInput::CADUTAISTANTANEA)
                                azione_ultima_speranza = TipoInput::NULLA;

                            if(azione_ultima_speranza != TipoInput::NULLA && ultima_speranza < 4){
                                ultima_speranza++;
                                countdownCaduta.join();
                                goto prova;
                            }
                        }

                    }

                    countdownCaduta.join();
                    
                    
                    CodaTetramini[0]->in_movimento = false;
                }
                
            }        
        
            /*---------------STAMPA DEL TETRAMINO------------*/ /*--------------STAMPA DEL GHOSTBLOCK------------*/

	        CodaTetramini[0]->stampa();           

	        campo.stampa(CodaTetramini[0]->p, backup_tetramino, CodaTetramini[0]->ghost_block(), CodaTetramini[0]->in_movimento);
            
	    }
        punteggio.t_spin(CodaTetramini[0]->tipo, CodaTetramini[0]->p[0], ultima_azione);
		PRIMO_CAMBIO:
        /*---------ELIMINAZIONE DALLA MEMORIA------------*/

		delete(CodaTetramini[0]);

        /*--------GIRO DELLA CODA CON I FUTURI-----------*/

        for(short i = 0; i < 3; i++){
            CodaTetramini[i] = CodaTetramini[i+1];
        }

	}

    campo.stampa(CodaTetramini[0]->p, backup_tetramino, CodaTetramini[0]->ghost_block(), CodaTetramini[0]->in_movimento);
    posizione_cursore(coord_fine);
    printf("hai perso");
    printf(BIANCO);
    getchar();
    getchar();

    return;

}

void Gioco::multiPlayerStanza(std::string& nome){

    int scelta;

    enum class STANZA{
        CREARE = 1,
        UNIRE = 2,
        ESCI = 0
    };

    Online online("100.72.208.113", 8080);

    online.login(nome);

    pulisci();
    printf("cosa vuoi fare?\n\n");

    printf("1. creare una stanza\n");
    printf("2. unirti a una stanza\n\n");

    scanf("%d", &scelta);

    if(scelta == static_cast<short>(STANZA::CREARE)){

        std::string nome_stanza;
        pulisci();
        getchar(); printf("nome della stanza : "); getline(cin, nome_stanza);

        opzioniStanza(&online, online.createRoom(nome_stanza), true);

    }

    if(scelta == static_cast<short>(STANZA::UNIRE)){

        listaStanze(&online, nome);

    }

    if(scelta == static_cast<short>(STANZA::ESCI)){

        return;

    }

}

void Gioco::opzioniStanza(Online* online, RoomDTO stanza, bool owner){

    pulisci();

    Input input;
    bool esci = false;

    online->subscribe<MessageDTO>("/user/queue/private",
        [](const MessageDTO& msg) {
            printf("negro");
        }
    );  

    printf("stanza : %s\n\n", stanza.name);
    printf("    players : \n");
    printf("player 1 : %s(owner) player 2 : %s\n",stanza.members[0], stanza.members[1]);

    if(owner)
        printf("premi invio per iniziare/continuare la partita");
    else
        printf("in attesa che %s inizi la partita", stanza.members[0]);


    do{

        if(kbhit()){
            input.scan();

            if(input.azione() == TipoInput::ESCI){
                esci = true;
            }

            if(input.azione() == TipoInput::CADUTAISTANTANEA){

                if(owner){
                    
                //  do 
                    
                }

            }

        }

    }while(!esci);

}

void Gioco::listaStanze(Online* online, std::string& nome){    
    
    pulisci();
    bool esci = false;
    Input input;
    cornice(0, 0, 30, 50);
    short i = 5;
    COORD posizione;
    std::vector<RoomDTO> stanze = online->getAvailableRooms();
    short stanze_massime = 50;

    cursore_manuale(5, 2);
    
    printf("stanze : (%d/%hd) ", stanze.size(), stanze_massime);

    for(size_t j = 0; j < stanze.size(); j++, i += 5){

        cursore_manuale(5, i);
        printf("  %-*s", strlen(stanze[j].name) + 2, stanze[j].name);

    }

    i = 5;

    do{

        if(kbhit()){

            input.scan();

            if(input.azione() == TipoInput::CADUTAVELOCE){

                posizione = posizione_attuale(); posizione.X--;
                posizione_cursore(posizione);
                printf(" ");
                i += 5;

                if(i > 45) i = 5;

                cursore_manuale(5, i);

                printf(">");

            }

            if(input.azione() == TipoInput::GIROORARIO){

                posizione = posizione_attuale(); posizione.X--;
                posizione_cursore(posizione);
                printf(" ");
                i -= 5;

                if(i < 5) i = 45;

                cursore_manuale(5, i);

                printf(">");

            }

            if(input.azione() == TipoInput::ESCI){

                return;

            }



        }


    }while(!esci);

}

void Gioco::opzioni(){

    cornice(0, 0, 67, 25);

    short i = 5;
    
    cursore_manuale(PADDING, i++);
    scritta(5, "  ___  _____ _____ ___ ___ ___ _   _ ");
    cursore_manuale(PADDING, i++);
    scritta(5, " / _ \\|  _  |_   _|_ _/ _ \\_ _| \\ | |");
    cursore_manuale(PADDING, i++);
    scritta(5, "| | | | | | | | |  | | | | | ||  \\| |");
    cursore_manuale(PADDING, i++);
    scritta(5, "| |_| | |_| | | |  | | |_| | || |\\  |");
    cursore_manuale(PADDING, i++);
    scritta(5, " \\___/|_____| |_| |___\\___/___|_| \\_|");

    



}

void Gioco::comandi(){
    system("chcp 65001");

    printf(CURSORE_INVISIBILE);
    pulisci();
    COORD posizione_att;
    Input input;
    bool esci = false;

    cornice(0, 0, 120, 25);

    short i = 3;
    
    cursore_manuale(PADDING, i++);
    scritta(5, "  ___  _____ _____ ___ ___ ___ _   _ ");
    cursore_manuale(PADDING, i++);
    scritta(5, " / _ \\|  _  |_   _|_ _/ _ \\_ _| \\ | |");
    cursore_manuale(PADDING, i++);
    scritta(5, "| | | | | | | | |  | | | | | ||  \\| |");
    cursore_manuale(PADDING, i++);
    scritta(5, "| |_| | |_| | | |  | | |_| | || |\\  |");
    cursore_manuale(PADDING, i++);
    scritta(5, " \\___/|_____| |_| |___\\___/___|_| \\_|");

    i = 11;

    cursore_manuale(5, i);
    printf("%-30s : ", "spostamento verso destra");
    for(short i = 0, c; i < 2; i++){
        c = DESTRA[i];
        printf("%2c", c);
    }
    printf(" →");

    cursore_manuale(5, i+=2);
    printf("%-30s : ", "spostamento verso sinistra");
    for(short i = 0, c; i < 2; i++){
        c = SINISTRA[i];
        printf("%2c", c);
    }
    printf(" ←");

    cursore_manuale(5, i+=2);
    printf("%-30s : ", "caduta veloce");
    for(short i = 0, c; i < 2; i++){
        c = CADUTA_VELOCE[i];
        printf("%2c", c);
    }
    posizione_cursore(posizione_att);
    printf(" ↓");

    cursore_manuale(5, i+=2);
    printf("%-30s : ", "caduta istantanea");
    for(short i = 0, c; i < 2; i++){
        c = CADUTA_ISTANTANEA[i];
        printf("%2c", c);
    }
    printf(" [SPAZIO]");
    printf(" [INVIO]");

    cursore_manuale(5, i+=2);
    printf("esci");

    cursore_manuale(65, i=11);
    printf("%-30s : ", "giro orario");
    for(short i = 0, c; i < 2; i++){
        c = ROTAZIONE[i];
        printf("%2c", c);
    }
    printf(" ↑");

    cursore_manuale(65, i+=2);
    printf("%-30s : ", "giro antiorario");
    for(short i = 0, c; i < 2; i++){
        c = ROTAZIONE_ANTIORARIA[i];
        printf("%2c", c);
    }

    cursore_manuale(65, i+=2);
    printf("%-30s : ", "giro doppio");
    for(short i = 0, c; i < 2; i++){
        c = ROTAZIONE_DOPPIA[i];
        printf("%2c", c);
    }

    cursore_manuale(65, i+=2);
    printf("%-30s : ", "cambio");
    for(short i = 0, c = 0; i < 2; i++){
        c = CAMBIO[i];
        printf("%2c", c);
    }

    cursore_manuale(65, i+=2);
    printf("reset");

    i = static_cast<short>(CordinateComandi::DESTRA);
    short j = 2;
    
    cursore_manuale(j, i);
    printf(">");


    do{  

        if(kbhit()){

            input.scan();

            if(input.azione() == TipoInput::GIROORARIO){// freccia in alto
                    
                cursore_manuale(j, i);
                printf(" ");

                i -= 2;

                if(i < static_cast<short>(CordinateComandi::DESTRA)) i = static_cast<short>(CordinateComandi::ESCI);
            }

            if(input.azione() == TipoInput::CADUTAVELOCE){// freccia in basso
                
                cursore_manuale(j, i);
                printf(" ");

                i += 2;

                if(i > static_cast<short>(CordinateComandi::ESCI)) i = static_cast<short>(CordinateComandi::DESTRA);
        

            }

            if(input.azione() == TipoInput::SINISTRA){// freccia in alto
                    
                cursore_manuale(j, i);
                printf(" ");

                j -= 60;

                if(j < 2) j = 62;
            
                
            }

            if(input.azione() == TipoInput::DESTRA){// freccia in alto
                    
                cursore_manuale(j, i);
                printf(" ");

                j += 60;

                if(j > 65) j = 2;                    
                

            }

            if(input.azione() == TipoInput::CADUTAISTANTANEA){ //spazio o invio
                    short h = 0;
                    bool esci_piccolo = false;
                    char nuovo = 0;
                switch(i){

                    case static_cast<short>(CordinateComandi::DESTRA):
                        printf(CURSORE_VISIBILE);

                        if(j == 2){
                            h = 39;
                            
                            do{
                                cursore_manuale(h, static_cast<short>(CordinateComandi::DESTRA));
                                
                                if(kbhit()){
                                    input.scan();

                                    if(input.azione() == TipoInput::DESTRA){
                                        h += 2;
                                        if(h > 41) h = 39;
                                    } else if (input.azione() == TipoInput::SINISTRA){
                                        h -= 2;
                                        if(h < 39) h = 41;
                                    } else if (input.azione() == TipoInput::ESCI){
                                        esci_piccolo = true;
                                    } else if (input.azione() == TipoInput::CADUTAISTANTANEA){
                                        do{
                                            nuovo = _getch();
                                        }while((nuovo < 'a' || nuovo > 'z') && (nuovo < 'A' || nuovo > 'Z'));
                                        printf("%c", nuovo);
                                        if(h == 39) DESTRA[0] = nuovo; else DESTRA[1] = nuovo;
                                    }
                                    
                                }
                            }while(!esci_piccolo);
                                
                            printf(CURSORE_INVISIBILE);


                        }else if (j == 62){
                            h = 99;

                            do{
                                cursore_manuale(h, static_cast<short>(CordinateComandi::DESTRA));
                                
                                if(kbhit()){
                                    input.scan();

                                    if(input.azione() == TipoInput::DESTRA){
                                        h += 2;
                                        if(h > 101) h = 99;
                                    } else if (input.azione() == TipoInput::SINISTRA){
                                        h -= 2;
                                        if(h < 99) h = 101;
                                    } else if (input.azione() == TipoInput::ESCI){
                                        esci_piccolo = true;
                                    } else if (input.azione() == TipoInput::CADUTAISTANTANEA){
                                        do{
                                            nuovo = _getch();
                                        }while((nuovo < 'a' || nuovo > 'z') && (nuovo < 'A' || nuovo > 'Z'));
                                        printf("%c", nuovo);
                                        if(h == 39) ROTAZIONE[0] = nuovo; else ROTAZIONE[1] = nuovo;
                                    }
                                    
                                }
                            }while(!esci_piccolo);
                        }
                        break;

                    case static_cast<short>(CordinateComandi::SINISTRA):

                        printf(CURSORE_VISIBILE);

                        if(j == 2){
                            h = 39;
                            
                            do{
                                cursore_manuale(h, static_cast<short>(CordinateComandi::SINISTRA));
                                
                                if(kbhit()){
                                    input.scan();

                                    if(input.azione() == TipoInput::DESTRA){
                                        h += 2;
                                        if(h > 41) h = 39;
                                    } else if (input.azione() == TipoInput::SINISTRA){
                                        h -= 2;
                                        if(h < 39) h = 41;
                                    } else if (input.azione() == TipoInput::ESCI){
                                        esci_piccolo = true;
                                    } else if (input.azione() == TipoInput::CADUTAISTANTANEA){
                                        do{
                                            nuovo = _getch();
                                        }while((nuovo < 'a' || nuovo > 'z') && (nuovo < 'A' || nuovo > 'Z'));
                                        printf("%c", nuovo);
                                        if(h == 39) SINISTRA[0] = nuovo; else SINISTRA[1] = nuovo;
                                    }
                                    
                                }
                            }while(!esci_piccolo);
                                
                            printf(CURSORE_INVISIBILE);


                        }else if (j == 62){
                            h = 99;

                            do{
                                cursore_manuale(h, static_cast<short>(CordinateComandi::SINISTRA));
                                
                                if(kbhit()){
                                    input.scan();

                                    if(input.azione() == TipoInput::DESTRA){
                                        h += 2;
                                        if(h > 101) h = 99;
                                    } else if (input.azione() == TipoInput::SINISTRA){
                                        h -= 2;
                                        if(h < 99) h = 101;
                                    } else if (input.azione() == TipoInput::ESCI){
                                        esci_piccolo = true;
                                    } else if (input.azione() == TipoInput::CADUTAISTANTANEA){
                                        do{
                                            nuovo = _getch();
                                        }while((nuovo < 'a' || nuovo > 'z') && (nuovo < 'A' || nuovo > 'Z'));
                                        printf("%c", nuovo);
                                        if(h == 39) ROTAZIONE_ANTIORARIA[0] = nuovo; else ROTAZIONE_ANTIORARIA[1] = nuovo;
                                    }
                                    
                                }
                            }while(!esci_piccolo);
                        }                        
                        break;

                    case static_cast<short>(CordinateComandi::CADUTAVELOCE):
                        printf(CURSORE_VISIBILE);

                        if(j == 2){
                            h = 39;
                            
                            do{
                                cursore_manuale(h, static_cast<short>(CordinateComandi::CADUTAVELOCE));
                                
                                if(kbhit()){
                                    input.scan();

                                    if(input.azione() == TipoInput::DESTRA){
                                        h += 2;
                                        if(h > 41) h = 39;
                                    } else if (input.azione() == TipoInput::SINISTRA){
                                        h -= 2;
                                        if(h < 39) h = 41;
                                    } else if (input.azione() == TipoInput::ESCI){
                                        esci_piccolo = true;
                                    } else if (input.azione() == TipoInput::CADUTAISTANTANEA){
                                        do{
                                            nuovo = _getch();
                                        }while((nuovo < 'a' || nuovo > 'z') && (nuovo < 'A' || nuovo > 'Z'));
                                        printf("%c", nuovo);
                                        if(h == 39) CADUTA_VELOCE[0] = nuovo; else CADUTA_VELOCE[1] = nuovo;
                                    }
                                    
                                }
                            }while(!esci_piccolo);
                                
                            printf(CURSORE_INVISIBILE);


                        }else if (j == 62){
                            h = 99;

                            do{
                                cursore_manuale(h, static_cast<short>(CordinateComandi::CADUTAVELOCE));
                                
                                if(kbhit()){
                                    input.scan();

                                    if(input.azione() == TipoInput::DESTRA){
                                        h += 2;
                                        if(h > 101) h = 99;
                                    } else if (input.azione() == TipoInput::SINISTRA){
                                        h -= 2;
                                        if(h < 99) h = 101;
                                    } else if (input.azione() == TipoInput::ESCI){
                                        esci_piccolo = true;
                                    } else if (input.azione() == TipoInput::CADUTAISTANTANEA){
                                        do{
                                            nuovo = _getch();
                                        }while((nuovo < 'a' || nuovo > 'z') && (nuovo < 'A' || nuovo > 'Z'));
                                        printf("%c", nuovo);
                                        if(h == 39) ROTAZIONE_DOPPIA[0] = nuovo; else ROTAZIONE_DOPPIA[1] = nuovo;
                                    }
                                    
                                }
                            }while(!esci_piccolo);
                        }
                        break;

                    case static_cast<short>(CordinateComandi::CADUTAISTANTANEA):
                        printf(CURSORE_VISIBILE);

                        if(j == 2){
                            h = 39;
                            
                            do{
                                cursore_manuale(h, static_cast<short>(CordinateComandi::CADUTAISTANTANEA));
                                
                                if(kbhit()){
                                    input.scan();

                                    if(input.azione() == TipoInput::DESTRA){
                                        h += 2;
                                        if(h > 41) h = 39;
                                    } else if (input.azione() == TipoInput::SINISTRA){
                                        h -= 2;
                                        if(h < 39) h = 41;
                                    } else if (input.azione() == TipoInput::ESCI){
                                        esci_piccolo = true;
                                    } else if (input.azione() == TipoInput::CADUTAISTANTANEA){
                                        do{
                                            nuovo = _getch();
                                        }while((nuovo < 'a' || nuovo > 'z') && (nuovo < 'A' || nuovo > 'Z'));
                                        printf("%c", nuovo);
                                        if(h == 39) CADUTA_ISTANTANEA[0] = nuovo; else CADUTA_ISTANTANEA[1] = nuovo;
                                    }
                                    
                                }
                            }while(!esci_piccolo);
                                
                            printf(CURSORE_INVISIBILE);


                        }else if (j == 62){
                            h = 99;

                            do{
                                cursore_manuale(h, static_cast<short>(CordinateComandi::CADUTAISTANTANEA));
                                
                                if(kbhit()){
                                    input.scan();

                                    if(input.azione() == TipoInput::DESTRA){
                                        h += 2;
                                        if(h > 101) h = 99;
                                    } else if (input.azione() == TipoInput::SINISTRA){
                                        h -= 2;
                                        if(h < 99) h = 101;
                                    } else if (input.azione() == TipoInput::ESCI){
                                        esci_piccolo = true;
                                    } else if (input.azione() == TipoInput::CADUTAISTANTANEA){
                                        do{
                                            nuovo = _getch();
                                        }while((nuovo < 'a' || nuovo > 'z') && (nuovo < 'A' || nuovo > 'Z'));
                                        printf("%c", nuovo);
                                        if(h == 39) CAMBIO[0] = nuovo; else CAMBIO[1] = nuovo;
                                    }
                                    
                                }
                            }while(!esci_piccolo);
                        }
                        break;

                    case static_cast<short>(CordinateComandi::ESCI):

                        
                        
                        if(j == 62){
                            ROTAZIONE[0] = 'W'; ROTAZIONE[1] = 'w';
                            ROTAZIONE_DOPPIA[0] = 'Z'; ROTAZIONE_DOPPIA[1] = 'z';
                            ROTAZIONE_ANTIORARIA[0] = 'R'; ROTAZIONE_ANTIORARIA[1] = 'r';
                            SINISTRA[0] = 'A'; SINISTRA[1] = 'a';
                            DESTRA[0] = 'D'; DESTRA[1] = 'd';
                            CADUTA_VELOCE[0] = 'S'; CADUTA_VELOCE[1] = 's';
                            CADUTA_ISTANTANEA[0] = 'Q'; CADUTA_ISTANTANEA[1] = 'q';
                            CAMBIO[0] = 'C'; CAMBIO[1] = 'c';
                            salva_config();
                            apri_config();
                        }

                        esci = true;
                        break;

                }

            }


        cursore_manuale(j, i);
        printf(">");
        }



    }while(!esci);

    system("chcp 850");
    setlocale(LC_ALL, "");
    salva_config();
}