#include "costanti.hpp"
#include "campo.hpp"
#include "grafica.hpp"
#include "input.hpp"
#include "tetramino.hpp"
#include "utilita.hpp"
#include "punteggio.hpp"
#include <chrono>
#include <thread>

/*
    creare un timer per l'input che entro quei secondi puoi muoverti
    creare un timer quando richiami può cadere, nel main controlli se ritorna false e fai ripartire il ciclo dell'input, all'inizio dell'input devi controllare entrambi i cicli
*/

using namespace std;
using namespace chrono;

int main(void){

    printf(BIANCO);
    cmd_grande();
    nascondi_cursore();
    pulisci();

    // disegno la cornice del campo
    cornice(0, 0, CAMPO_LUNGHEZZA, CAMPO_ALTEZZA);
    // disegno la cornice dei tetramini futuri
    cornice(CAMPO_LUNGHEZZA + 4, 0, FUTURI_LUNGHEZZA, FUTURI_ALTEZZA + 1); 
    cornice(CAMPO_LUNGHEZZA + 4 + FUTURI_LUNGHEZZA - 1, 0, FUTURI_LUNGHEZZA, FUTURI_ALTEZZA + 1);
    cornice(CAMPO_LUNGHEZZA + 4 + FUTURI_LUNGHEZZA + - 1 + FUTURI_LUNGHEZZA - 1, 0, FUTURI_LUNGHEZZA, FUTURI_ALTEZZA + 1);
    // disegno la cornice del tetramino di riserva
    cornice(CAMPO_LUNGHEZZA + 4, FUTURI_ALTEZZA + 2, FUTURI_LUNGHEZZA, CAMPO_ALTEZZA - FUTURI_ALTEZZA - 2); 

    COORD backup_tetramino[8] = {0, 0};
    
    Input input;
    campo.inizializza(); 

    Tetramino* CodaTetramini[4] = {NULL};
    Tetramino* RiservaTetramino[2] = {NULL};
    short sostituzioni = 0;

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

        posizione_cursore(coord_punteggio);
        printf("punteggio : %.0f", punteggio.punti);
        
        

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

                
                if(_kbhit() || azione_ultima_speranza != TipoInput::NULLA){    

                    if(azione_ultima_speranza == TipoInput::NULLA){
                        input.input = 0;
                        input.scan();
                    }else{
                        azione_ultima_speranza = TipoInput::NULLA;
                    }

                    if(input.cambio() == TipoInput::CAMBIO && puo_sostituire){

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
                            CodaTetramini[0]->pulisci(TipoTetramino::NORMALE);
                            punteggio.cadutaVeloce(CodaTetramini[0]->cadutaVeloce());
                        }

                        if(input.destra() == TipoInput::DESTRA && CodaTetramini[0]->puo_destra() == Collisioni::LIBERO){
                            CodaTetramini[0]->pulisci(TipoTetramino::NORMALE);
                            CodaTetramini[0]->pulisci(TipoTetramino::GHOST);
                            CodaTetramini[0]->sposta_destra();
                        }

                        if(input.sinistra() == TipoInput::SINISTRA && CodaTetramini[0]->puo_sinistra() == Collisioni::LIBERO){
                            CodaTetramini[0]->pulisci(TipoTetramino::NORMALE);
                            CodaTetramini[0]->pulisci(TipoTetramino::GHOST);
                            CodaTetramini[0]->sposta_sinistra();
                        }

                        if(input.rotazione() == TipoInput::GIROORARIO && CodaTetramini[0]->puo_girare(TipoInput::GIROORARIO) == Collisioni::LIBERO) {
                            CodaTetramini[0]->pulisci(TipoTetramino::NORMALE);
                            CodaTetramini[0]->pulisci(TipoTetramino::GHOST);
                            CodaTetramini[0]->gira(TipoInput::GIROORARIO);
                        }else 
                        
                        if(input.rotazione() == TipoInput::GIROANTIORARIO && CodaTetramini[0]->puo_girare(TipoInput::GIROANTIORARIO) == Collisioni::LIBERO) { 
                            CodaTetramini[0]->pulisci(TipoTetramino::NORMALE);
                            CodaTetramini[0]->pulisci(TipoTetramino::GHOST);
                            CodaTetramini[0]->gira(TipoInput::GIROANTIORARIO);
                        }else

                        if(input.rotazione() == TipoInput::GIRODOPPIO && CodaTetramini[0]->puo_girare(TipoInput::GIRODOPPIO) == Collisioni::LIBERO) { 
                            CodaTetramini[0]->pulisci(TipoTetramino::NORMALE);
                            CodaTetramini[0]->pulisci(TipoTetramino::GHOST);
                            CodaTetramini[0]->gira(TipoInput::GIRODOPPIO);
                        }



                        if(input.cadutaIstantanea() == TipoInput::CADUTAISTANTANEA){
                            CodaTetramini[0]->pulisci(TipoTetramino::NORMALE);
                            CodaTetramini[0]->pulisci(TipoTetramino::GHOST);
                            timer_input = 0;
                            punteggio.cadutaIstantanea(CodaTetramini[0]->caduta_istantanea());
                            
                        }
                        
                    }

                    CodaTetramini[0]->stampa();
                    campo.stampa(CodaTetramini[0]->p, backup_tetramino, CodaTetramini[0]->ghost_block(), CodaTetramini[0]->in_movimento);

                    
                }

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

    return 0;

}
