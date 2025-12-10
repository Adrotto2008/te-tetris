#include "costanti.hpp"
#include "campo.hpp"
#include "grafica.hpp"
#include "input.hpp"
#include "tetramino.hpp"
#include "utilita.hpp"

int main(void){

    printf(BIANCO);
    cmd_grande();
    nascondi_cursore();
   
    srand(time(NULL));
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

    Tetramino* CodaTetramini[4] = {NULL};
    Tetramino* RiservaTetramino[2] = {NULL};
    short sostituzioni = 0;
    int punteggio = 0;

    for(short i = 0; i < 3; i++){
        CodaTetramini[i] = new Tetramino();
    }

	for(short j = 0; j < 50; j++){ // numero tetramini totali

        CodaTetramini[3] = new Tetramino();

        stampa_coda_tetramini(CodaTetramini[1]->tipo, CodaTetramini[2]->tipo, CodaTetramini[3]->tipo);

        short linee_riempite = campo.controlloPunti();

        posizione_cursore(coord_punteggio);
        if(linee_riempite > 0)      punteggio += linee_riempite * 100;
        printf("punteggio : %3d", punteggio);
        
		bool puo_sostituire = true;

		while(CodaTetramini[0]->in_movimento){//FARE in_movimento

            CodaTetramini[0]->pulisci(1);

            input.input = 0;
	        if(_kbhit()){
	            input.scan();
	        }

            //salvo le cordinate in dei backup
            for(short k = 0; k < 8; k++){
                backup_tetramino[k] = CodaTetramini[0]->p[k];
            }
	
            
	        
	        // bisogna richiamarlo prima di fare un controllo quindi io forse lo metterei dentro ad ogni controllo all'inizio ma forse
	
	        if(CodaTetramini[0]->in_movimento){
	            CodaTetramini[0]->stampa_id(); 
	            
                if(input.cambio() && puo_sostituire){

                    puo_sostituire = false; //in questo modo posso effettuare una sostituzione per tetramino
                    sostituzioni++;

                    if(sostituzioni != 2){ // != 2 perchè la prima volta lo puoi fare 2 volte quindi è un modo rozzo per evitare il bug                    

                        CodaTetramini[0]->sparisci();
                        CodaTetramini[0]->pulisci(0);

                        if(sostituzioni == 1){
                            RiservaTetramino[0] = new Tetramino(CodaTetramini[0]->id_tetramino, CodaTetramini[0]->tipo);
                            stampa_riserva_tetramino(RiservaTetramino[0]->tipo);
                            break;
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

                }

                INPUT:
                
                if(input.destra() && CodaTetramini[0]->puo_destra()){
	                CodaTetramini[0]->sposta_destra();
	            }else

	            if(input.sinistra() && CodaTetramini[0]->puo_sinistra()){
	                CodaTetramini[0]->sposta_sinistra();
	            }

                if(input.rotazione() && CodaTetramini[0]->puo_girare() == 1) {
	                CodaTetramini[0]->gira();
	            }

                if(input.cadutaIstantanea()){
                    CodaTetramini[0]->pulisci(0);
                    CodaTetramini[0]->caduta_istantanea();
                }
                /*
                if(_kbhit()){
                    input =_getch();
                    input = tolower(input);
                    goto INPUT;
                }  
                */


                if(CodaTetramini[0]->puo_cadere()) {

                    if(input.cadutaVeloce()){
                        CodaTetramini[0]->caduta_veloce();
                    }else{
                        CodaTetramini[0]->caduta_lenta();
                    }
	                
	            }

	            
	            
	        }
	        
            
	        CodaTetramini[0]->stampa();

	        campo.stampa(CodaTetramini[0]->p, backup_tetramino, CodaTetramini[0]->ghost_block(), CodaTetramini[0]->in_movimento);
	        Sleep(CodaTetramini[0]->sleep);
	    }
		
		delete(CodaTetramini[0]);
        
        for(short i = 0; i < 3; i++){
            CodaTetramini[i] = CodaTetramini[i+1];
        }
		
	}

    

    posizione_cursore(coord_fine);
    printf(BIANCO);
    return 0;

}