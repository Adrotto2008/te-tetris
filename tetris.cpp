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

//Costanti
#define CAMPO_ALTEZZA 25
#define CAMPO_LUNGHEZZA 30
#define CAMPO_CENTRO CAMPO_LUNGHEZZA / 2
#define BLOCCO 219 //Blocco intero

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

enum Colori {
    rosso = -1,
    ciano = -2,
    blu = -3,
    arancione = -4,
    giallo = -5,
    verde = -6,
    magenta = -7,
    bianco = -8
};

//Variabili globali
char campo[CAMPO_ALTEZZA - 2][CAMPO_LUNGHEZZA - 2][2] = {0}; //ok allora per il momento TEORICAMENTE (non ho provato visto che abbiamo solo un tetramino )funziona, ma è lentissimo visto che fa 13 volte il lavoro, quidni direi di ottimizzarlo mettendo che la posto di 32 quando c'è il rosso la cella vale -1 etc.
COORD coord_posizione_campo = {1, 1}; // messsa manualmente da rivedere
COORD coord_fine = {0, CAMPO_ALTEZZA + 10}; //Posizione finale del cursore 

//Funzioni
void inizializza_campo();
COORD posizione_attuale();
void stampa_campo();
void cornice(int margine_sinistro, int margine_superiore, int margine_destro, int margine_inferiore);
void cursore_manuale(short x, short y);
COORD posizione_attuale();
void pulisci();
void cursore_alto(COORD* coord_posizione, int delta);
void cursore_basso(COORD* coord_posizione, int delta);
void cursore_sinistra(COORD* coord_posizione, int delta);
void cursore_destra(COORD* coord_posizione, int delta);
void posizione_cursore(COORD coord_posizione);
void nascondi_cursore();
void mostra_cursore();

//Classe tetramino generale
class Tetramino {
    
    	private :
    	
    	//Variabili
        int id_tetramino;
        COORD p[4]; //Coordinate dei 4 punti
        int rotazione;
        int tipo;
        char colore;
	    static int id_tetramini;
    	
		public :
	    
	    bool in_movimento; //Serve per capire se il tetramino è in movimento o se è stato posizionato 
        
        Tetramino(){
        	int tipo_tetramino = random_tetramino();// da ristrutturare facendo la funzione che genera la coda di tetramini nel futuro, probabilmente anche da un'altra parte
        	inizializza(tipo_tetramino);
		}

        //Metodo che assegna il valore del tetramino corrente
        void inizializza(int tipo_tetramino){
            id_tetramini++;	
            tipo = tipo_tetramino;//cambia tipo
            //Controllo che tipo di tetramino è tramite l'enum TetraminoTipo e gli assegno il colore e le cordinate
            switch(tipo){ //bisogna creare la variabile tipo
            case tetramino_i:
                colore = ciano; // Assegna il colore CIANO
                p[0] = {CAMPO_CENTRO, 1};
	            p[1] = {CAMPO_CENTRO, 2};
	            p[2] = {CAMPO_CENTRO, 3};
				p[3] = {CAMPO_CENTRO, 4};
                break;
            case tetramino_j:
                colore = blu; // Assegna il colore VIOLA
                p[0] = {CAMPO_CENTRO, 1};
	            p[1] = {CAMPO_CENTRO, 2};
	            p[2] = {CAMPO_CENTRO, 3};
				p[3] = {CAMPO_CENTRO - 1, 3};
                break;
            case tetramino_l:
                colore = arancione; // Assegna il colore ARANCIONE
                p[0] = {CAMPO_CENTRO, 1};
	            p[1] = {CAMPO_CENTRO, 2};
	            p[2] = {CAMPO_CENTRO, 3};
				p[3] = {CAMPO_CENTRO + 1, 3};
                break;
            case tetramino_o:
                colore = giallo; // Assegna il colore GIALLO
                p[0] = {CAMPO_CENTRO, 1};
	            p[1] = {CAMPO_CENTRO + 1, 1};
	            p[2] = {CAMPO_CENTRO, 2};
				p[3] = {CAMPO_CENTRO + 1, 2};
                break;
            case tetramino_s:
                colore = verde; // Assegna il colore VERDE
                p[0] = {CAMPO_CENTRO, 1};
	            p[1] = {CAMPO_CENTRO - 1, 1};
	            p[2] = {CAMPO_CENTRO, 2};
				p[3] = {CAMPO_CENTRO + 1, 2};
                break;
            case tetramino_z:
                colore = rosso; // Assegna il colore ROSSO
                p[0] = {CAMPO_CENTRO, 1};
	            p[1] = {CAMPO_CENTRO + 1, 1};
	            p[2] = {CAMPO_CENTRO, 2};
				p[3] = {CAMPO_CENTRO - 1, 2};
                break;
            case tetramino_t:
                colore = magenta; // Assegna il colore MAGENTA
                p[0] = {CAMPO_CENTRO, 1};
	            p[1] = {CAMPO_CENTRO - 1, 1};
	            p[2] = {CAMPO_CENTRO + 1, 1};
				p[3] = {CAMPO_CENTRO, 2};
                break;
            //Se non è nessuno è bianco ma in teoria non dovrebbe mai esserlo
            default:
                colore = 32;
                p[0] = {0, 0};
	            p[1] = {0, 0};
	            p[2] = {0, 0};
				p[3] = {0, 0};
                break;
            }

            id_tetramino = id_tetramini;
            in_movimento = true;
            rotazione = 0;

        }
        
        int random_tetramino(){
        	if(!id_tetramini)
        		srand(time(NULL));
        		
        	return 1 + rand() % (7 - 1 + 1);//min + rand()%(max - min + 1)
        	
		}

        void stampa_colore(){ //prova

            for(int i = 0; i < 4; i++){
                campo[p[i].Y][p[i].X][1] = colore;
            }

        }
        
        //Metodo che controlla se il tetramino puo girare
        bool puo_girare() {
            COORD centro = p[0];

            for(int i = 0; i < 4; i++) {
                
                //distanza dei punti x e y dal centro
                int dx = p[i].X - centro.X;
                int dy = p[i].Y - centro.Y;

                //Coordinate dopo lo spostamento 
                int tempX = centro.X - dy + 1;
                int tempY = centro.Y + dx;

                //Controllo che con lo spoostamento non esco dai bordi
                if(tempX <= 0 || tempX >= CAMPO_LUNGHEZZA - 2) return false;
                if(tempY <= 0 || tempY >= CAMPO_ALTEZZA - 2) return false;
                
                //Controllo che con lo spostamento non sostituisco un altro tetramino
                if(campo[tempY][tempX][0] != 32 && campo[tempY][tempX][0] != id_tetramino) return false;
            }

            return true;
        }

        
        void gira(){
            COORD centro = p[0];

            for(int i = 0; i < 4; i++){
                    
                campo[p[i].X][p[i].Y][0] = 32;

                short dx = p[i].X - centro.X;
                short dy = p[i].Y - centro.Y;

                short nuovaX = centro.X - dy;
                short nuovaY = centro.Y + dx;

                p[i] = {nuovaX, nuovaY};
                
            }
        }

        //Metodo che stampa gli id del tetramino corrente sul campo
        void stampa_id(){ // ho un dubbio, forse l'id del tetramino resta anche quando è caduto in tutte le posizioni in cui è stato, in questo modo se dovesse cadere
                          // un seconod tetramino, vedrebbe in posizioni vuote l'id di tutti i tetramini prima bloccandosi in aria, stessa cosa con i colori
                          // in qualche modo dovremmo eliminare le posizioni precedenti dell'id e del colore proprio come facciamo per l'estetica del tetramino
                          // forse dovremmo fare questa cosa all'interno di caduta_lenta sposta_sinistra e sposta_destra, cioè togliere dall posizione di prima il colore e l'id
                          //in più nella posizione di prima se c'è il colore devo trovare un modo per far stampare lo spazio anche se c'è il colore, 32 != ROSSO
            for(int i = 0; i < 4; i++){
                campo[p[i].Y][p[i].X][0] = id_tetramino;
            }

        }

        //Metodo che controlla se c'è un tetramino sotto quello corrente ---COLLISIONI---
        bool puo_cadere(){

            for(int i = 0; i < 4; i++) {

                if(p[i].Y + 1  == CAMPO_ALTEZZA - 2){
                    in_movimento = false;
                    return false;
                }
                    

                if(campo[p[i].Y+1][p[i].X][0] != 32 && campo[p[i].Y+1][p[i].X][0] != id_tetramino){
                    in_movimento = false;
                    return false;
                }
                    
                
            }

            in_movimento = true;
            return true;

        }

        //Metodo che controlla se c'è un tetramino o altro a destra di quello corrente ---COLLISIONI---
        bool puo_destra(){

            for(int i = 0; i < 4; i++) {

                if(p[i].X + 1  == CAMPO_LUNGHEZZA - 2){
                    //in_movimento = false; in teoria dovrebbe ancora poter cadere
                    return false;
                }
                    

                if(campo[p[i].Y][p[i].X + 1][0] != 32 && campo[p[i].Y][p[i].X + 1][0] != id_tetramino){
                    //in_movimento = false; in teoria dovrebbe ancora poter cadere
                    return false; 
                }
                    
                
            }

            in_movimento = true;
            return true;

        }

        //Metodo che controlla se c'è un tetramino o altro a sinistra di quello corrente ---COLLISIONI---
        bool puo_sinistra(){

            for(int i = 0; i < 4; i++) {

                if(p[i].X - 1  == 0){
                    //in_movimento = false; in teoria dovrebbe ancora poter cadere
                    return false;
                }
                    

                if(campo[p[i].Y][p[i].X - 1][0] != 32 && campo[p[i].Y][p[i].X - 1][0] != id_tetramino){
                    //in_movimento = false; in teoria dovrebbe ancora poter cadere
                    return false; 
                }
                    
                
            }

            in_movimento = true;
            return true;

        }

        //Metodo che stampa il tetramino corrente
        void stampa(){

            for(int i = 0; i < 4; i++){
                campo[p[i].Y][p[i].X][0] = BLOCCO;
            }
            stampa_colore();

        }

        //Metodo che effettua la caduta del tetramino
        void caduta_lenta(){
            
            for(int i = 0; i < 4; i++){
                campo[p[i].Y][p[i].X][0] = 32;
                campo[p[i].Y][p[i].X][1] = bianco;
                p[i].Y+= 1;
            }

        }

        //Metodo che effettua lo spostamento a destra del tetramino
        void sposta_destra(){
            
            for(int i = 0; i < 4; i++){
                campo[p[i].Y][p[i].X][0] = 32;
                campo[p[i].Y][p[i].X][1] = bianco;
                p[i].X+= 1;
            }

        }

        //Metodo che effettua lo spostamento a sinistra del tetramino
        void sposta_sinistra(){

            for(int i = 0; i < 4; i++){
                campo[p[i].Y][p[i].X][0] = 32;
                campo[p[i].Y][p[i].X][1] = bianco;
                p[i].X-= 1;
            }

        }
        
        //Distruttore del tetramino, serve per controllare che è stato ristrutto o effettuare qualcosa 
		~Tetramino(){
			cursore_manuale(1, CAMPO_ALTEZZA + 2);
			printf("distrutto %3d",id_tetramino);
		}

};
int Tetramino::id_tetramini = 0;

int main(void){

    pulisci();
    inizializza_campo();
    cornice(0, 0, CAMPO_LUNGHEZZA, CAMPO_ALTEZZA);

    Tetramino* tetramino;
    char input;
    char ROTAZIONE = 's';

    nascondi_cursore();



	for(int j = 0; j < 500; j++){

        tetramino = new Tetramino();
		
		for(int i = 0; i < CAMPO_ALTEZZA - 2; i++){//FARE in_movimento

	        input = 0;
	        if(_kbhit()){
	            input =_getch();
	            input = tolower(input);
	        }
	
	
	        
	        tetramino->stampa_id(); // bisogna richiamarlo prima di fare un controllo quindi io forse lo metterei dentro ad ogni controllo all'inizio ma forse
	
	        if(tetramino->in_movimento){
	
	            
	            if(input == 'd' && tetramino->puo_destra()){
	                tetramino->sposta_destra();
	            }
	
	
	            if(input == 'a' && tetramino->puo_sinistra()){
	                tetramino->sposta_sinistra();
	            }
	            
	            if(tetramino->puo_cadere()) {
	                tetramino->caduta_lenta();
	            }
	            
	            if(input == ROTAZIONE && tetramino->puo_girare()) {
	                tetramino->gira();
	            }
	            
	        }
	        
	        tetramino->stampa();
	        
	        stampa_campo();
	        Sleep(200);
	    }
		
		delete(tetramino);
		
	}

    

    posizione_cursore(coord_fine);
    return 0;

}







//Funzione che inizializza il campo
void inizializza_campo(){

    for(int i = 0; i < CAMPO_ALTEZZA - 2; i++){

        for(int j = 0; j < CAMPO_LUNGHEZZA - 2; j++){

            campo[i][j][0] = 32;
            campo[i][j][1] = bianco;
            
        }

    }

}

//Funzione che stampa la matrice campo
void stampa_campo(){

    for(int i = 0; i < CAMPO_ALTEZZA - 2; i++){

        cursore_manuale(1, i + 1);

        for(int j = 0; j < CAMPO_LUNGHEZZA - 2; j++){
        	
        	char casella_colore = campo[i][j][1];
			char casella = campo[i][j][0];
			
            //Controllo se all'interno della casella si trova un colore e lo stampo cambiando il colore del terminale FA LAGGARE TUTTO SISTEMAAAAAAAAAAAAAAA

			switch(casella_colore){
				
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
	
			campo[i][j][0] = casella;

            printf("%c", casella);
            
        }

    }

}

//Funzione che disegna una cornice inserendo i 4 angoli di contorno (modificata solo per tetris!)
void cornice(int margine_sinistro, int margine_superiore, int margine_destro, int margine_inferiore){
    COORD start;

    //imposto le cordinate in maniera assoluta per non andare fuori dallo schermo
    start.X = abs(margine_sinistro);
    start.Y = abs(margine_superiore);


    COORD coord = start;

    for (int j = 0; j < margine_inferiore; j++) {
        posizione_cursore(coord);
        for (int i = 0; i < margine_destro; i++) {
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
        fflush(stdout);
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

void cursore_alto(COORD* coord_posizione, int delta){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    coord_posizione->Y -= delta;
    posizione_cursore(*coord_posizione);
}

void cursore_basso(COORD* coord_posizione, int delta){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    coord_posizione->Y += delta;
    posizione_cursore(*coord_posizione);
}

void cursore_sinistra(COORD* coord_posizione, int delta){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    coord_posizione->X -= delta;
    posizione_cursore(*coord_posizione);
}

void cursore_destra(COORD* coord_posizione, int delta){
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
