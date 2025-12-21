/*
RISOLVI GIRA E CADUTA VELOCE E GHOST BLOCK, HO CAMBIATO 0 CON 32 
controllare la tonalit�  dei colori
controllare le posizioni di tutti i p[] nella funzione inizializza mettendo p[0] come centro per il giramento dei tetramini
modificare la funzione gira e aggiungere delle cordinate p[] perchè la lunghezza dovrebbe raddoppiarsi
rivedere le funzioni di controllo di spostamento per i bordi, e giro per eventuali bug(forse sono dovuti a stampa_campo)
-------ottimizzare la funzione stampa_campo() : non fargli stampare tutto il campo ogni volta, ma solo quando serve, e solo le parti modificate
togliere lo sleep e utilizzare i thread per la stampa, e l'input e i controlli di collisione, probebilmente ne servono 3
creare una coda di generazione dei tetramini per vedere i prossimi tetramini richiamando/modificando random_tetramino()
s*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <winbase.h>
#include <math.h>
#include <direct.h>
#include <time.h>
#include <conio.h>
#include <limits.h>
#include <iostream>
// riga 58 e 153 433 circa



// COSTANTI

#define CAMPO_ALTEZZA 25
#define CAMPO_LUNGHEZZA 15
#define CAMPO_CENTRO CAMPO_LUNGHEZZA / 2
#define FUTURI_ALTEZZA 10
#define FUTURI_LUNGHEZZA 20
#define FUTURI_SECONDO (FUTURI_LUNGHEZZA - (CAMPO_LUNGHEZZA + 4) / 3)
#define FUTURI_CENTRO CAMPO_LUNGHEZZA + 4 + ((FUTURI_LUNGHEZZA - (CAMPO_LUNGHEZZA + 4)) / 2)
#define BLOCCO 219 //Blocco intero

// INPUT

#define ROTAZIONE 'w' 
#define CADUTA_VELOCE 'q'
#define CADUTA_ISTANTANEA 's'

/* non so perchè ma lagga se si usano questo comandi
#define ROTAZIONE 72 // freccia in alto
#define CADUTA_VELOCE 80 // freccia giù
#define CADUTA_ISTANTANEA 32 // barra spaziatrice
#define SINISTRA 75 //freccia sinistra
#define DESTRA 77 // freccia destra 
#define CAMBIO 'c' // per il tetramino di riserva
*/

// CURSORE

#define CURSORE_INVISIBILE "\033[?25l"
#define CURSORE_VISIBILE "\033[?25h"

// COLORI

#define RESET   "\033[0m"
#define NERO    "\033[30m"
#define ROSSO   "\033[31m"
#define VERDE   "\033[32m"
#define GIALLO  "\033[33m"
#define BLU     "\033[34m"
#define MAGENTA "\033[35m"
#define CIANO   "\033[36m"
#define BIANCO  "\033[37m"
#define ARANCIONE "\033[38;5;208m"
#define VIOLA "\033[38;5;129m"
#define GRIGIO "\033[38;5;245m"
#define MARRONE "\033[38;5;94m"

#define BLU_CHIARO "\033[38;5;123m"
#define VERDE_CHIARO "\033[38;5;82m"
#define GIALLO_CHIARO "\033[38;5;226m"
#define ROSSO_CHIARO "\033[38;5;196m"
#define VERDE_SCURO "\033[38;5;34m"
#define GIALLO_SCURO "\033[38;5;220m"
#define BLU_SCURO "\033[38;5;24m"
#define MAGENTA_CHIARO "\033[38;5;201m"
#define CIANO_CHIARO "\033[38;5;51m"
#define GRIGIO_CHIARO "\033[38;5;250m"
#define VIOLA_CHIARO "\033[38;5;135m"
#define LIGHT_RED "\033[38;5;9m"
#define LIGHT_GREEN "\033[38;5;10m"
#define LIGHT_YELLOW "\033[38;5;11m"
#define LIGHT_BLUE "\033[38;5;12m"
#define LIGHT_MAGENTA "\033[38;5;13m"
#define LIGHT_CYAN "\033[38;5;14m"
#define DARK_GRAY "\033[38;5;8m"

using namespace std;


//Enum per assegnare a ogni tipo di tetramino un valore e riconoscerlo nel codice
enum TetraminoTipo {
    tetramino_i = 1,
    tetramino_j = 2,
    tetramino_l = 3,
    tetramino_o = 4,
    tetramino_s = 5,
    tetramino_z = 6,
    tetramino_t = 7
};

enum  Colori {
    rosso = -1,
    ciano = -2,
    blu = -3,
    arancione = -4,
    giallo = -5,
    verde = -6,
    magenta = -7,
    bianco = -8
};

class Campo{
	
	public:
		   char colore;
		   char blocco;
		   int id;
	
};

//Variabili globali

Campo campo[CAMPO_ALTEZZA - 2][CAMPO_LUNGHEZZA - 2]; //ok allora per il momento TEORICAMENTE (non ho provato visto che abbiamo solo un tetramino )funziona, ma è lentissimo visto che fa 13 volte il lavoro, quidni direi di ottimizzarlo mettendo che la posto di 32 quando c'è il rosso la cella vale -1 etc.
COORD coord_tetramino_futuro = {CAMPO_LUNGHEZZA + 13, 4};
COORD coord_secondo_tetramino_futuro = {CAMPO_LUNGHEZZA + 13 + 18, 4};
COORD coord_terzo_tetramino_futuro = {CAMPO_LUNGHEZZA + 13 + 18 + 19, 4};
COORD coord_tetramino_riserva = {CAMPO_LUNGHEZZA + 13, FUTURI_ALTEZZA + 8};
COORD coord_posizione_campo = {1, 1}; // messsa manualmente da rivedere
COORD coord_punteggio = {CAMPO_LUNGHEZZA + FUTURI_LUNGHEZZA + 7, FUTURI_ALTEZZA + 5};
COORD coord_fine = {0, CAMPO_ALTEZZA + 10}; //Posizione finale del cursore 

//Funzioni
short controllo_punti();
void scesa_campo(short linee_riempite, short posizione_linea);
void stampa_coda_tetramini(short tipo1, short tipo2, short tipo3);
void stampa_riserva_tetramino(short tipo);
void inizializza_campo();
COORD posizione_attuale();
void pulisci_tetramino(COORD posizione_tetramino[]);
void sparisci_tetramino(COORD posizione_tetramino[]);
void stampa_campo_totale();
void stampa_campo(COORD posizione_tetramin[], COORD backup_posizione_tetramino[], COORD posizione_ghost_block[], bool in_movimento);
void cornice(short margine_sinistro, short margine_superiore, short margine_destro, short margine_inferiore);
void cursore_manuale(short x, short y);
COORD posizione_attuale();
void pulisci();
void cursore_alto(COORD* coord_posizione, short delta);
void cursore_basso(COORD* coord_posizione, short delta);
void cursore_sinistra(COORD* coord_posizione, short delta);
void cursore_destra(COORD* coord_posizione, short delta);
void posizione_cursore(COORD coord_posizione);
void nascondi_cursore();
void mostra_cursore();
void cmd_grande();

//Classe tetramino generale
class Tetramino {
    
    	private :
    	
    	//Variabili

        short rotazione = 0;
        
        char colore = 0;
	    static int id_tetramini;
    	
		public :

        short sleep;
        int id_tetramino = 0;
        short tipo = 0;
	    COORD p[4]; //Coordinate dei 4 punti
	    bool in_movimento = true; //Serve per capire se il tetramino è in movimento o se è stato posizionato 
        
        Tetramino(){
        	this->inizializza();
            this->controllo_colore();
		}

        //Constructor per creare un tetramino con delle caratteristiche predefinite, senza generare un nuovo id e tipo
        Tetramino(int id_definito, short tipo_definito){
        	this->in_movimento = true;
            this->id_tetramino = id_definito;
            this->tipo = tipo_definito;
            this->controllo_colore();
		}

        //Metodo che assegna il colore del tetramino in base al tipo
        void controllo_colore(){
            switch(tipo){
            case tetramino_i:
                colore = ciano; 
                p[0] = {CAMPO_CENTRO, 2};
	            p[1] = {CAMPO_CENTRO, 1};
	            p[2] = {CAMPO_CENTRO, 3};
				p[3] = {CAMPO_CENTRO, 4};
                break;
            case tetramino_j:
                colore = blu; 
                p[0] = {CAMPO_CENTRO, 2};
	            p[1] = {CAMPO_CENTRO, 1};
	            p[2] = {CAMPO_CENTRO, 3};
				p[3] = {CAMPO_CENTRO - 1, 3};
                break;
            case tetramino_l:
                colore = arancione;
                p[0] = {CAMPO_CENTRO, 2};
	            p[1] = {CAMPO_CENTRO, 1};
	            p[2] = {CAMPO_CENTRO, 3};
				p[3] = {CAMPO_CENTRO + 1, 3};
                break;
            case tetramino_o:
                colore = giallo; 
                p[0] = {CAMPO_CENTRO, 1};
	            p[1] = {CAMPO_CENTRO + 1, 1};
	            p[2] = {CAMPO_CENTRO, 2};
				p[3] = {CAMPO_CENTRO + 1, 2};
                break;
            case tetramino_s:
                colore = verde;
                p[0] = {CAMPO_CENTRO, 1};
	            p[1] = {CAMPO_CENTRO - 1, 1};
	            p[2] = {CAMPO_CENTRO, 2};
				p[3] = {CAMPO_CENTRO + 1, 2};
                break;
            case tetramino_z:
                colore = rosso; 
                p[0] = {CAMPO_CENTRO, 1};
	            p[1] = {CAMPO_CENTRO + 1, 1};
	            p[2] = {CAMPO_CENTRO, 2};
				p[3] = {CAMPO_CENTRO - 1, 2};
                break;
            case tetramino_t:
                colore = magenta;
                p[0] = {CAMPO_CENTRO, 1};
	            p[1] = {CAMPO_CENTRO - 1, 1};
	            p[2] = {CAMPO_CENTRO + 1, 1};
				p[3] = {CAMPO_CENTRO, 2};
                break;
            //Se non è nessuno è bianco ma in teoria non dovrebbe mai esserlo
            default:
                this->colore = 32;
                return;
            }
        }

        //Metodo che assegna il valore del tetramino corrente
        bool inizializza(){
            this->id_tetramini++;	
            this->tipo = this->random_tetramino();// da ristrutturare facendo la funzione che genera la coda di tetramini nel futuro, probabilmente anche da un'altra parte
            //tipo = tetramino_i;
            //Controllo che tipo di tetramino è tramite l'enum TetraminoTipo e gli assegno il colore e le cordinate
            

            this->id_tetramino = id_tetramini;
            this->in_movimento = true;

            return 1;

        }
        
        //Metodo che crea un tipo casuale di tetramino da 1 a 7 
        short random_tetramino(){
        		
        	return 1 + rand() % (7 - 1 + 1);//min + rand()%(max - min + 1)
        	
		}

        //Metodo che imposta il colore nella casella del campo associata
        void stampa_colore(){

            for(short i = 0; i < 4; i++){
                campo[p[i].Y][p[i].X].colore = colore;
            }

        }
        
        //Metodo che controlla se il tetramino puo girare
        short puo_girare() {

            //if(tipo == tetramino_o)
            //    return -1;

            COORD centro = p[0];

            for(short i = 0; i < 4; i++) {
                
                //distanza dei punti x e y dal centro
                COORD distanza = {(short)(p[i].X - centro.X), (short)(p[i].Y - centro.Y)};

                //Coordinate dopo lo spostamento
                COORD temp = {(short)(centro.X - distanza.Y), (short)(centro.Y + distanza.X)};

                //Controllo che con lo spoostamento non esco dai bordi
                if(temp.X <= 0 || temp.X >= CAMPO_LUNGHEZZA - 2) return 0;
                if(temp.Y <= 0 || temp.Y >= CAMPO_ALTEZZA - 2) return 0;
                
                //Controllo che con lo spostamento non sostituisco un altro tetramino
                if(campo[temp.Y][temp.X].id != 32 && campo[temp.Y][temp.X].id != id_tetramino) return 0;
            }

            return 1;
        }

        //Metodo che effettua il giramento del tetramino (modificare raddoppiando le x?)
        void gira(){
            
            COORD centro = p[0];

            for(short i = 0; i < 4; i++){
                    
                campo[p[i].Y][p[i].X].id = 32;
                campo[p[i].Y][p[i].X].blocco = 32;

                COORD distanza = {(short)(p[i].X - centro.X), (short)(p[i].Y - centro.Y)};

                COORD nuova = {(short)(centro.X - distanza.Y), (short)(centro.Y + distanza.X)};

                p[i] = {nuova.X, nuova.Y};
                
            }
        }

        //Metodo che imposta gli id del tetramino corrente sul campo
        void stampa_id(){
            
            for(short i = 0; i < 4; i++){
                campo[p[i].Y][p[i].X].id = id_tetramino;
            }

        }

        //Metodo che controlla se c'è un tetramino sotto quello corrente ---COLLISIONI---
        bool puo_cadere(){

            for(short i = 0; i < 4; i++) {

                if(p[i].Y + 1  >= CAMPO_ALTEZZA - 2){
                    in_movimento = false;
                    return false;
                }
                    

                if(campo[p[i].Y+1][p[i].X].id != 32 && campo[p[i].Y+1][p[i].X].id != id_tetramino){
                    in_movimento = false;
                    return false;
                }
                    
                
            }

            in_movimento = true;
            return true;

        }

        //Metodo che controlla se c'è un tetramino o altro a destra di quello corrente ---COLLISIONI---
        bool puo_destra(){

            for(short i = 0; i < 4; i++) {

                if(p[i].X + 1  == CAMPO_LUNGHEZZA - 2){
                    //in_movimento = false; in teoria dovrebbe ancora poter cadere
                    return false;
                }
                    

                if(campo[p[i].Y][p[i].X + 1].id != 32 && campo[p[i].Y][p[i].X + 1].id != id_tetramino){
                    //in_movimento = false; in teoria dovrebbe ancora poter cadere
                    return false; 
                }
                    
                
            }

            this->in_movimento = true;
            return true;

        }

        //Metodo che controlla se c'è un tetramino o altro a sinistra di quello corrente ---COLLISIONI---
        bool puo_sinistra(){

            for(short i = 0; i < 4; i++) {

                if(p[i].X - 1  == -1){
                    //in_movimento = false; in teoria dovrebbe ancora poter cadere
                    return false;
                }
                    

                if(campo[p[i].Y][p[i].X - 1].id != 32 && campo[p[i].Y][p[i].X - 1].id != id_tetramino){
                    //in_movimento = false; in teoria dovrebbe ancora poter cadere
                    return false; 
                }
                    
                
            }

            this->in_movimento = true;
            return true;

        }

        //Metodo che stampa il tetramino corrente
        void stampa(){

            for(short i = 0; i < 4; i++){
                campo[p[i].Y][p[i].X].blocco = BLOCCO;
            }
            this->stampa_colore();

        }

        //Metodo che effettua la caduta lenta del tetramino
        void caduta_lenta(){
            
            for(short i = 0; i < 4; i++){
                campo[p[i].Y][p[i].X].id = 32;
                campo[p[i].Y][p[i].X].blocco = 32;
				campo[p[i].Y][p[i].X].colore = bianco;
                p[i].Y+= 1;
            }

            this->sleep = 300;

        }

        //Metodo che effettua la caduta veloce del tetramino
        void caduta_veloce(){
            
            for(short i = 0; i < 4; i++){
            	campo[p[i].Y][p[i].X].id = 32;
                campo[p[i].Y][p[i].X].blocco = 32;
                campo[p[i].Y][p[i].X].colore = bianco;
                p[i].Y+= 1;
            }

            this->sleep = 50;

        }

        void caduta_istantanea(){

            for(short i = 0; i < 4; i++){
            	campo[p[i].Y][p[i].X].id = 32;
                campo[p[i].Y][p[i].X].blocco = 32;
                campo[p[i].Y][p[i].X].colore = bianco;
            }

            while(1){

                for(short i = 0; i < 4; i++){
                    
                    if(campo[p[i].Y + 1][p[i].X].id != 32 && campo[p[i].Y + 1][p[i].X].id != id_tetramino || p[i].Y + 1 >= CAMPO_ALTEZZA - 2){
                        this->in_movimento = false;
                        return;
                    }

                }

                for(short i = 0; i < 4; i++){
                    this->p[i].Y+=1;
                }

            }

        }

        //Metodo che crea un blocco fantasma nella parte inferiore del campo per sapere dove atterrer�  il tetramino
        COORD* ghost_block(){

            this->stampa_id();

            static COORD p_ghost[4];

            for(short i = 0; i < 4; i++){

                p_ghost[i].X = p[i].X;
                p_ghost[i].Y = p[i].Y;

            }

            while(1){

                for(short i = 0; i < 4; i++){
                    
                    if(campo[p_ghost[i].Y + 1][p_ghost[i].X].id != 32 && campo[p_ghost[i].Y + 1][p_ghost[i].X].id != id_tetramino || p_ghost[i].Y + 1 >= CAMPO_ALTEZZA - 2){
                        this->stampa();
                        return p_ghost;
                    }

                }

                for(short i = 0; i < 4; i++){
                    p_ghost[i].Y+=1;
                }

            }


        }

        //Metodo che effettua lo spostamento a destra del tetramino
        void sposta_destra(){
            
            for(short i = 0; i < 4; i++){
            	campo[p[i].Y][p[i].X].id = 32;
                campo[p[i].Y][p[i].X].blocco = 32;
                campo[p[i].Y][p[i].X].colore = bianco;
                p[i].X+= 1;
            }

        }

        //Metodo che effettua lo spostamento a sinistra del tetramino
        void sposta_sinistra(){

            for(short i = 0; i < 4; i++){
            	campo[p[i].Y][p[i].X].id = 32;
                campo[p[i].Y][p[i].X].blocco = 32;
                campo[p[i].Y][p[i].X].colore = bianco;
                p[i].X-= 1;
            }

        }
        
        //Distruttore del tetramino, serve per controllare che è stato ristrutto o effettuare qualcosa 
		~Tetramino(){
			cursore_manuale(1, CAMPO_ALTEZZA + 2);
			//printf("distruttooo %3d",id_tetramino);
		}

};
//Variabile globale per la classe Tetramino contenente il contatore degli id
int Tetramino::id_tetramini = '1' - 1; //inizio da '1' solo perchè in caso di bug è più semplice da capire all'inizio ma si può mettere 0

int main(void){

    printf(BIANCO);
    cmd_grande();
    nascondi_cursore();
   
    srand(time(NULL));
    pulisci();
    inizializza_campo();

    // disegno la cornice del campo
    cornice(0, 0, CAMPO_LUNGHEZZA, CAMPO_ALTEZZA);
    // disegno la cornice dei tetramini futuri
    cornice(CAMPO_LUNGHEZZA + 4, 0, FUTURI_LUNGHEZZA, FUTURI_ALTEZZA); 
    cornice(CAMPO_LUNGHEZZA + 4 + FUTURI_LUNGHEZZA - 1, 0, FUTURI_LUNGHEZZA, FUTURI_ALTEZZA);
    cornice(CAMPO_LUNGHEZZA + 4 + FUTURI_LUNGHEZZA + - 1 + FUTURI_LUNGHEZZA - 1, 0, FUTURI_LUNGHEZZA, FUTURI_ALTEZZA);
    // disegno la cornice del tetramino di riserva
    cornice(CAMPO_LUNGHEZZA + 4, FUTURI_ALTEZZA + 2, FUTURI_LUNGHEZZA, CAMPO_ALTEZZA - FUTURI_ALTEZZA - 2); 

    char input;
    COORD backup_tetramino[4] = {0, 0};
    
    

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

        short linee_riempite = controllo_punti();

        posizione_cursore(coord_punteggio);
        if(linee_riempite > 0)      punteggio += linee_riempite * 100;
        printf("punteggio : %3d", punteggio);
        
		bool puo_sostituire = true;

		while(CodaTetramini[0]->in_movimento){//FARE in_movimento

            pulisci_tetramino(CodaTetramini[0]->ghost_block());

	        input = 0;
	        if(_kbhit()){
	            input =_getch();
	            input = tolower(input);
	        }

            //salvo le cordinate in dei backup
            for(short k = 0; k < 4; k++){
                backup_tetramino[k] = CodaTetramini[0]->p[k];
            }
	
            
	        
	        // bisogna richiamarlo prima di fare un controllo quindi io forse lo metterei dentro ad ogni controllo all'inizio ma forse
	
	        if(CodaTetramini[0]->in_movimento){
	            CodaTetramini[0]->stampa_id(); 
	            
                if(input == 'c' && puo_sostituire){

                    puo_sostituire = false; //in questo modo posso effettuare una sostituzione per tetramino
                    sostituzioni++;

                    if(sostituzioni != 2){ // != 2 perchè la prima volta lo puoi fare 2 volte quindi è un modo rozzo per evitare il bug                    

                        sparisci_tetramino(CodaTetramini[0]->p);
                        pulisci_tetramino(CodaTetramini[0]->p);

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
                
                if(input == 'd' && CodaTetramini[0]->puo_destra()){
	                CodaTetramini[0]->sposta_destra();
	            }else

	            if(input == 'a' && CodaTetramini[0]->puo_sinistra()){
	                CodaTetramini[0]->sposta_sinistra();
	            }

                if(input == ROTAZIONE && CodaTetramini[0]->puo_girare() == 1) {
	                CodaTetramini[0]->gira();
	            }

                if(input == CADUTA_ISTANTANEA){
                    pulisci_tetramino(CodaTetramini[0]->p);
                    CodaTetramini[0]->caduta_istantanea();
                }
                
                if(_kbhit()){
                    input =_getch();
                    input = tolower(input);
                    goto INPUT;
                }  



                if(CodaTetramini[0]->puo_cadere()) {

                    if(input == CADUTA_VELOCE){
                        CodaTetramini[0]->caduta_veloce();
                    }else{
                        CodaTetramini[0]->caduta_lenta();
                    }
	                
	            }

	            
	            
	        }
	        
            
	        CodaTetramini[0]->stampa();

	        stampa_campo(CodaTetramini[0]->p, backup_tetramino, CodaTetramini[0]->ghost_block(), CodaTetramini[0]->in_movimento);
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

void stampa_riserva_tetramino(short tipo){

    char tetramino[4][4] = {0};

    switch(tipo){ 
        case tetramino_i:
            tetramino[0][1] = BLOCCO;
            tetramino[1][1] = BLOCCO;
            tetramino[2][1] = BLOCCO;
            tetramino[3][1] = BLOCCO;
            printf(CIANO);
            break;
        case tetramino_j:
            tetramino[0][1] = BLOCCO;
            tetramino[1][1] = BLOCCO;
            tetramino[2][0] = BLOCCO;
            tetramino[2][1] = BLOCCO;
            printf(BLU_CHIARO);
            break;
        case tetramino_l:
            tetramino[0][1] = BLOCCO;
            tetramino[1][1] = BLOCCO;
            tetramino[2][1] = BLOCCO;
            tetramino[2][2] = BLOCCO;
            printf(ARANCIONE);
            break;
        case tetramino_o:
            tetramino[0][0] = BLOCCO;
            tetramino[0][1] = BLOCCO;
            tetramino[1][0] = BLOCCO;
            tetramino[1][1] = BLOCCO;
            printf(GIALLO_CHIARO);
            break;
        case tetramino_s:
            tetramino[0][0] = BLOCCO;
            tetramino[0][1] = BLOCCO;
            tetramino[1][1] = BLOCCO;
            tetramino[1][2] = BLOCCO;
            printf(VERDE_CHIARO);
            break;
        case tetramino_z:
            tetramino[0][1] = BLOCCO;
            tetramino[0][2] = BLOCCO;
            tetramino[1][0] = BLOCCO;
            tetramino[1][1] = BLOCCO;
            printf(ROSSO_CHIARO);
            break;
        case tetramino_t:
            tetramino[0][0] = BLOCCO;
            tetramino[0][1] = BLOCCO;
            tetramino[0][2] = BLOCCO;
            tetramino[1][1] = BLOCCO;
            printf(MAGENTA_CHIARO);
            break;
    }

    // Stampa i tetramini usando le matrici
    for(short i = 0; i < 4; i++) {
        posizione_cursore({coord_tetramino_riserva.X, (short)(coord_tetramino_riserva.Y + i)});
        for(short j = 0; j < 4; j++) {
            printf("%c", tetramino[i][j] ? tetramino[i][j] : ' ');
        }
    }

}

void stampa_coda_tetramini(short tipo1, short tipo2, short tipo3){    //non avevo sbatti

    char tetramino[3][4][4] = {0};

    COORD coord_futuro[3] = {coord_tetramino_futuro, coord_secondo_tetramino_futuro, coord_terzo_tetramino_futuro};
    short tipo[3] = {tipo1, tipo2, tipo3};

    for(short j = 0; j < 3; j++){

        switch(tipo[j]){ 
            case tetramino_i:
                tetramino[j][0][1] = BLOCCO;
                tetramino[j][1][1] = BLOCCO;
                tetramino[j][2][1] = BLOCCO;
                tetramino[j][3][1] = BLOCCO;
                printf(CIANO);
                break;
            case tetramino_j:
                tetramino[j][0][1] = BLOCCO;
                tetramino[j][1][1] = BLOCCO;
                tetramino[j][2][0] = BLOCCO;
                tetramino[j][2][1] = BLOCCO;
                printf(BLU_CHIARO);
                break;
            case tetramino_l:
                tetramino[j][0][1] = BLOCCO;
                tetramino[j][1][1] = BLOCCO;
                tetramino[j][2][1] = BLOCCO;
                tetramino[j][2][2] = BLOCCO;
                printf(ARANCIONE);
                break;
            case tetramino_o:
                tetramino[j][0][0] = BLOCCO;
                tetramino[j][0][1] = BLOCCO;
                tetramino[j][1][0] = BLOCCO;
                tetramino[j][1][1] = BLOCCO;
                printf(GIALLO_CHIARO);
                break;
            case tetramino_s:
                tetramino[j][0][0] = BLOCCO;
                tetramino[j][0][1] = BLOCCO;
                tetramino[j][1][1] = BLOCCO;
                tetramino[j][1][2] = BLOCCO;
                printf(VERDE_CHIARO);
                break;
            case tetramino_z:
                tetramino[j][0][1] = BLOCCO;
                tetramino[j][0][2] = BLOCCO;
                tetramino[j][1][0] = BLOCCO;
                tetramino[j][1][1] = BLOCCO;
                printf(ROSSO_CHIARO);
                break;
            case tetramino_t:
                tetramino[j][0][0] = BLOCCO;
                tetramino[j][0][1] = BLOCCO;
                tetramino[j][0][2] = BLOCCO;
                tetramino[j][1][1] = BLOCCO;
                printf(MAGENTA_CHIARO);
                break;
            }

                
        // Stampa i tetramini usando le matrici
        for(short i = 0; i < 4; i++) {
            posizione_cursore({coord_futuro[j].X, (short)(coord_futuro[j].Y + i)});
            for(short k = 0; k < 4; k++) {
                printf("%c", tetramino[j][i][k] ? tetramino[j][i][k] : ' ');
            }
        }

    }

}

//Funzione che inizializza il campo
void inizializza_campo(){

    for(short i = 0; i < CAMPO_ALTEZZA - 2; i++){

        for(short j = 0; j < CAMPO_LUNGHEZZA - 2; j++){

            campo[i][j].id = 32;
            campo[i][j].blocco = 32;
            campo[i][j].colore = bianco;
            
        }

    }

}

void pulisci_tetramino(COORD posizione_tetramino[]){

    for(short i = 0; i < 4; i++){

        cursore_manuale(posizione_tetramino[i].X + 1, posizione_tetramino[i].Y + 1);
        printf("%c", 32);

    }

}

short controllo_punti(){

    bool linea_riempita;
    short linee_riempite = 0;
    short posizione_riga = 0;

    for(short i = CAMPO_ALTEZZA - 2 - 1; i >= 0; i--){

        linea_riempita = true;

        for(short j = 0; j < CAMPO_LUNGHEZZA - 2; j++){

            if(campo[i][j].id == 32){
                linea_riempita = false;
            }

        }

        if(linea_riempita){
            if(posizione_riga == 0)
                posizione_riga = i;
            linee_riempite++;
        }

    }

    if(linee_riempite != 0){
        scesa_campo(linee_riempite, posizione_riga);
    }
    
    return linee_riempite;

}

void scesa_campo(short linee_riempite, short posizione_riga){

    if(linee_riempite == 0) return;

    for(short i = 0; i < linee_riempite; i++){

        for(short j = posizione_riga; j >= 1; j--){

            for(short k = 0; k < CAMPO_LUNGHEZZA - 2; k++){

                campo[j][k].id = campo[j - 1][k].id;
                campo[j][k].blocco = campo[j - 1][k].blocco;
                campo[j][k].colore = campo[j - 1][k].colore;

            }

        }

    }

    

    stampa_campo_totale();

}

void sparisci_tetramino(COORD posizione_tetramino[]){

    for(short i = 0; i < 4; i++){
			  
        campo[posizione_tetramino[i].Y][posizione_tetramino[i].X].id = 32;
        campo[posizione_tetramino[i].Y][posizione_tetramino[i].X].blocco = 32;
        campo[posizione_tetramino[i].Y][posizione_tetramino[i].X].colore = bianco;

    }

}

void stampa_campo_totale(){ //da ottimizzare in qualche modo? il problema è lo switch

    for(short i = 0; i < CAMPO_ALTEZZA - 2; i++){

        cursore_manuale(1, i + 1);

        for(short j = 0; j < CAMPO_LUNGHEZZA - 2; j++){

            switch(campo[i][j].colore){
				
                case bianco : 
                    printf(BIANCO);
                    break;
                case rosso : 
                    printf(ROSSO_CHIARO);
                    break;
                case ciano : 
                    printf(CIANO);
                    break;
                case blu : 
                    printf(BLU_CHIARO);
                    break;
                case arancione : 
                    printf(ARANCIONE);
                    break;
                case giallo : 
                    printf(GIALLO_CHIARO);
                    break;
                case verde : 
                    printf(VERDE_CHIARO);
                    break;
                case magenta : 
                    printf(MAGENTA_CHIARO);
                    break;
                
            }

            printf("%c", campo[i][j].blocco);

        }

    }

}

//Funzione che stampa la matrice campo
void stampa_campo(COORD posizione_tetramino[], COORD backup_posizione_tetramino[], COORD posizione_ghost_block[], bool in_movimento){

    for(short i = 0; i < 4; i++){
        cursore_manuale(backup_posizione_tetramino[i].X + 1, backup_posizione_tetramino[i].Y + 1);
        printf("%c", 32);
    }

    if(in_movimento){

        printf(GRIGIO);
        for(short i = 0; i < 4; i++){
            cursore_manuale(posizione_ghost_block[i].X + 1, posizione_ghost_block[i].Y + 1);
            printf("%c", BLOCCO);
        }

    }

    switch(campo[posizione_tetramino[0].Y][posizione_tetramino[0].X].colore){
				
        case bianco : 
            printf(BIANCO);
            break;
        case rosso : 
            printf(ROSSO_CHIARO);
            break;
        case ciano : 
            printf(CIANO);
            break;
        case blu : 
            printf(BLU_CHIARO);
            break;
        case arancione : 
            printf(ARANCIONE);
            break;
        case giallo : 
            printf(GIALLO_CHIARO);
            break;
        case verde : 
            printf(VERDE_CHIARO);
            break;
        case magenta : 
            printf(MAGENTA_CHIARO);
            break;
        
    }

    for(short i = 0; i < 4; i++){
        cursore_manuale(posizione_tetramino[i].X + 1, posizione_tetramino[i].Y + 1);
        printf("%c", campo[posizione_tetramino[i].Y][posizione_tetramino[i].X].blocco);
    }
    
    posizione_cursore(coord_fine);
    printf("%c", 32);

    
}

//Funzione che disegna una cornice inserendo i 4 angoli di contorno (modificata solo per tetris!)
void cornice(short margine_sinistro, short margine_superiore, short margine_destro, short margine_inferiore){

    COORD start;

    //imposto le cordinate in maniera assoluta per non andare fuori dallo schermo
    start.X = abs(margine_sinistro);
    start.Y = abs(margine_superiore);

    COORD coord = start;

    for (short j = 0; j < margine_inferiore; j++) {
        posizione_cursore(coord);
        for (short i = 0; i < margine_destro; i++) {
            if (j == 0 || j == margine_inferiore - 1) { // margini inferiore e superiore
                
                if(i == 0 || i == margine_destro - 1){// angoli
                    putchar('+');
                }else {
                    putchar('-');
                }
                
            } else if (i == 0 || i == margine_destro - 1) { //margini laterali
                putchar('|');
            } else {
                putchar(' ');
            }
        }

        coord.Y += 1;
    }

    coord.Y += 5;
    posizione_cursore(coord);

}

void cursore_manuale(short x, short y){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord_posizione = {x, y};
    posizione_cursore(coord_posizione);
}

void pulisci(){
    system("cls");
}

COORD posizione_attuale() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    return csbi.dwCursorPosition;
}

void cursore_alto(COORD* coord_posizione, short delta){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    coord_posizione->Y -= delta;
    posizione_cursore(*coord_posizione);
}

void cursore_basso(COORD* coord_posizione, short delta){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    coord_posizione->Y += delta;
    posizione_cursore(*coord_posizione);
}

void cursore_sinistra(COORD* coord_posizione, short delta){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    coord_posizione->X -= delta;
    posizione_cursore(*coord_posizione);
}

void cursore_destra(COORD* coord_posizione, short delta){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    coord_posizione->X += delta;
    posizione_cursore(*coord_posizione);
}

void posizione_cursore(COORD coord_posizione){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, coord_posizione);
}

void nascondi_cursore(){

    printf(CURSORE_INVISIBILE);

}

void mostra_cursore(){

    printf(CURSORE_VISIBILE);

}

void cmd_grande(){

    HWND hwnd = GetConsoleWindow(); // Ottieni il manico della finestra del terminale
    ShowWindow(hwnd, SW_MAXIMIZE);

}
