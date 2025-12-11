#include "tetramino.hpp"

using namespace std;

int Tetramino::id_tetramini = '0' - 1;

Tetramino::Tetramino(){
    this->inizializza();
    this->controllo_colore();
}

//Constructor per creare un tetramino con delle caratteristiche predefinite, senza generare un nuovo id e tipo
Tetramino::Tetramino(int id_definito, short tipo_definito){
    this->in_movimento = true;
    this->id_tetramino = id_definito;
    this->tipo = tipo_definito;
    this->controllo_colore();
}

//Metodo che assegna il colore del tetramino in base al tipo
void Tetramino::controllo_colore(){
    switch(tipo){ //tutti gli indici pari indicano [ mentre quelli dispari ]
    case tetramino_i:
        colore = ciano; 
        p[0] = {CAMPO_CENTRO, 2};
        p[1] = {CAMPO_CENTRO + 1, 2};
        p[2] = {CAMPO_CENTRO, 1};
        p[3] = {CAMPO_CENTRO + 1, 1};
        p[4] = {CAMPO_CENTRO, 3};
        p[5] = {CAMPO_CENTRO + 1, 3};
        p[6] = {CAMPO_CENTRO, 4};
        p[7] = {CAMPO_CENTRO + 1, 4};
        break;
    case tetramino_j:
        colore = blu; 
        p[0] = {CAMPO_CENTRO, 2};
        p[1] = {CAMPO_CENTRO + 1, 2};
        p[2] = {CAMPO_CENTRO, 1};
        p[3] = {CAMPO_CENTRO + 1, 1};
        p[4] = {CAMPO_CENTRO, 3};
        p[5] = {CAMPO_CENTRO + 1, 3};
        p[6] = {CAMPO_CENTRO - 2, 3};
        p[7] = {CAMPO_CENTRO - 1, 3};
        
        break;
    case tetramino_l:
        colore = arancione;
        p[0] = {CAMPO_CENTRO, 2};
        p[1] = {CAMPO_CENTRO + 1, 2};
        p[2] = {CAMPO_CENTRO, 1};
        p[3] = {CAMPO_CENTRO + 1, 1};
        p[4] = {CAMPO_CENTRO, 3};
        p[5] = {CAMPO_CENTRO + 1, 3};
        p[6] = {CAMPO_CENTRO + 2, 3};
        p[7] = {CAMPO_CENTRO + 3, 3};
        
        break;
    case tetramino_o:
        colore = giallo; 
        p[0] = {CAMPO_CENTRO, 1};
        p[1] = {CAMPO_CENTRO + 1, 1};
        p[2] = {CAMPO_CENTRO + 2, 1};
        p[3] = {CAMPO_CENTRO + 3, 1};
        p[4] = {CAMPO_CENTRO, 2};
        p[5] = {CAMPO_CENTRO + 1, 2};
        p[6] = {CAMPO_CENTRO + 2, 2};
        p[7] = {CAMPO_CENTRO + 3, 2};
    
        break;
    case tetramino_z:
        colore = rosso;
        p[0] = {CAMPO_CENTRO, 1};
        p[1] = {CAMPO_CENTRO + 1, 1};
        p[2] = {CAMPO_CENTRO - 2, 1};
        p[3] = {CAMPO_CENTRO - 1, 1};
        p[4] = {CAMPO_CENTRO, 2};
        p[5] = {CAMPO_CENTRO + 1, 2};
        p[6] = {CAMPO_CENTRO + 2, 2};
        p[7] = {CAMPO_CENTRO + 3, 2};

        break;
    case tetramino_s:
        colore = verde; 
        p[0] = {CAMPO_CENTRO, 1};
        p[1] = {CAMPO_CENTRO + 1, 1};
        p[2] = {CAMPO_CENTRO + 2, 1};
        p[3] = {CAMPO_CENTRO + 3, 1};
        p[4] = {CAMPO_CENTRO, 2};
        p[5] = {CAMPO_CENTRO + 1, 2};
        p[6] = {CAMPO_CENTRO - 2, 2};
        p[7] = {CAMPO_CENTRO - 1, 2};
        break;
    case tetramino_t:
        colore = magenta;
        p[0] = {CAMPO_CENTRO, 1};
        p[1] = {CAMPO_CENTRO + 1, 1};
        p[2] = {CAMPO_CENTRO - 2, 1};
        p[3] = {CAMPO_CENTRO - 1, 1};
        p[4] = {CAMPO_CENTRO + 2, 1};
        p[5] = {CAMPO_CENTRO + 3, 1};
        p[6] = {CAMPO_CENTRO, 2};
        p[7] = {CAMPO_CENTRO + 1, 2};
        break;
    //Se non è nessuno è bianco ma in teoria non dovrebbe mai esserlo
    default:
        this->colore = 32;
        return;
    }
}

//Metodo che assegna il valore del tetramino corrente
bool Tetramino::inizializza(){
    this->in_movimento = true;
    this->id_tetramini++;	
    this->tipo = this->random_tetramino();// da ristrutturare facendo la funzione che genera la coda di tetramini nel futuro, probabilmente anche da un'altra parte
    //tipo = tetramino_i;
    //Controllo che tipo di tetramino è tramite l'enum TetraminoTipo e gli assegno il colore e le cordinate
    

    this->id_tetramino = id_tetramini;
    this->in_movimento = true;

    return 1;

}

//Metodo che crea un tipo casuale di tetramino da 1 a 7 
short Tetramino::random_tetramino(){
        
    return 1 + rand() % (7 - 1 + 1);//min + rand()%(max - min + 1)
    
}

//Metodo che imposta il colore nella casella del campo associata
void Tetramino::stampa_colore(){

    for(short i = 0; i < 8; i++){
        campo.casella[p[i].Y][p[i].X].colore = colore;
    }

}

//Metodo che controlla se il tetramino puo girare
bool Tetramino::puo_girare() {

    COORD temp[8];

    for(short i = 0; i < 8; i++){
        if(i % 2 == 0){
            temp[i] = p[i];
        }

    }

    if(tipo == tetramino_i){

        if(rotazione % 2 == 0){

            temp[2]={(short)(temp[0].X + 2), temp[0].Y};
            temp[4]={(short)(temp[0].X - 2), temp[0].Y};
            temp[6]={(short)(temp[0].X - 4), temp[0].Y};

        } else {

            temp[2]={temp[0].X, (short)(temp[0].Y - 1)};
            temp[4]={temp[0].X, (short)(temp[0].Y + 1)};
            temp[6]={temp[0].X, (short)(temp[0].Y + 2)};

        }

        

    } else if(tipo == tetramino_t){
        
        if(rotazione == 0){

            temp[2]={(short)(temp[0].X - 2), (short)(temp[0].Y)};
            temp[4]={(short)(temp[0].X), (short)(temp[0].Y + 1)};
            temp[6]={(short)(temp[0].X), (short)(temp[0].Y - 1)};

        } else if(rotazione == 1){

            temp[2]={(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[4]={(short)(temp[0].X - 2), (short)(temp[0].Y)};
            temp[6]={(short)(temp[0].X), (short)(temp[0].Y - 1)};

        } else if(rotazione == 2){

            temp[2]={(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[4]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[6]={(short)(temp[0].X), (short)(temp[0].Y + 1)};

        }else{

            temp[2]={(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[4]={(short)(temp[0].X - 2), (short)(temp[0].Y)};
            temp[6]={(short)(temp[0].X), (short)(temp[0].Y + 1)};

        }

    } else if(tipo == tetramino_l){

        if(rotazione == 0){

            temp[2]={(short)(temp[0].X - 2), (short)(temp[0].Y)};
            temp[4]={(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y + 1)};

        } else if(rotazione == 1){

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y + 1)};
            temp[4]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y - 1)};

        } else if(rotazione == 2){

            temp[2]={(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[4]={(short)(temp[0].X + 2), (short)(temp[0].Y - 1)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y)};

        }else{

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[4]={(short)(temp[0].X), (short)(temp[0].Y + 1)};
            temp[6]={(short)(temp[0].X + 2), (short)(temp[0].Y + 1)};

        }

    } else if(tipo == tetramino_j){

        if(rotazione == 0){

            temp[2]={(short)(temp[0].X - 2), (short)(temp[0].Y)};
            temp[4]={(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y - 1)};

        } else if(rotazione == 1){

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y + 1)};
            temp[4]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[6]={(short)(temp[0].X + 2), (short)(temp[0].Y - 1)};

        } else if(rotazione == 2){

            temp[2]={(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[4]={(short)(temp[0].X + 2), (short)(temp[0].Y + 1)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y)};

        }else{

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[4]={(short)(temp[0].X), (short)(temp[0].Y + 1)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y + 1)};

        }

    } else if(tipo == tetramino_z){

        if(rotazione % 2 == 0){

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[4]={(short)(temp[0].X - 2), (short)(temp[0].Y)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y + 1)};

        } else {

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[4]={(short)(temp[0].X - 2), (short)(temp[0].Y - 1)};
            temp[6]={(short)(temp[0].X + 2), (short)(temp[0].Y)};

        }

    } else if(tipo == tetramino_s){

        if(rotazione % 2 == 0){

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[4]={(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[6]={(short)(temp[0].X + 2), (short)(temp[0].Y + 1)};

        } else {

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[4]={(short)(temp[0].X + 2), (short)(temp[0].Y - 1)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y)};

        }

    }
    
    for(short i = 0; i < 8; i++){

        if(i % 2 == 1){
            temp[i].Y = temp[i - 1].Y;
            temp[i].X = temp[i - 1].X + 1;
        }

    }

    for(short i = 0; i < 8; i++){

        if(temp[i].X <= -1 || temp[i].X >= CAMPO_LUNGHEZZA - 2){
            return 0;
        }

        if(temp[i].Y <= 0 || temp[i].Y >= CAMPO_ALTEZZA - 2){
            return 0;
        }

        if(campo.casella[temp[i].Y][temp[i].X].id != 32 && campo.casella[temp[i].Y][temp[i].X].id != id_tetramino){
            return 0;
        }

    }


    return 1;
}

//Metodo che effettua il giramento del tetramino
void Tetramino::gira(){

    COORD temp[8];

    for(short i = 0; i < 8; i++){
        if(i % 2 == 0){
            temp[i] = p[i];
        }

        campo.casella[p[i].Y][p[i].X].id = 32;
        campo.casella[p[i].Y][p[i].X].blocco = 32;
    }

    if(tipo == tetramino_i){

        if(rotazione % 2 == 0){

            temp[2]={(short)(temp[0].X + 2), temp[0].Y};
            temp[4]={(short)(temp[0].X - 2), temp[0].Y};
            temp[6]={(short)(temp[0].X - 4), temp[0].Y};

        } else {

            temp[2]={temp[0].X, (short)(temp[0].Y - 1)};
            temp[4]={temp[0].X, (short)(temp[0].Y + 1)};
            temp[6]={temp[0].X, (short)(temp[0].Y + 2)};

        }

        

    } else if(tipo == tetramino_t){
        
        if(rotazione == 0){

            temp[2]={(short)(temp[0].X - 2), (short)(temp[0].Y)};
            temp[4]={(short)(temp[0].X), (short)(temp[0].Y + 1)};
            temp[6]={(short)(temp[0].X), (short)(temp[0].Y - 1)};

        } else if(rotazione == 1){

            temp[2]={(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[4]={(short)(temp[0].X - 2), (short)(temp[0].Y)};
            temp[6]={(short)(temp[0].X), (short)(temp[0].Y - 1)};

        } else if(rotazione == 2){

            temp[2]={(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[4]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[6]={(short)(temp[0].X), (short)(temp[0].Y + 1)};

        }else{

            temp[2]={(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[4]={(short)(temp[0].X - 2), (short)(temp[0].Y)};
            temp[6]={(short)(temp[0].X), (short)(temp[0].Y + 1)};

        }

    } else if(tipo == tetramino_l){

        if(rotazione == 0){

            temp[2]={(short)(temp[0].X - 2), (short)(temp[0].Y)};
            temp[4]={(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y + 1)};

        } else if(rotazione == 1){

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y + 1)};
            temp[4]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y - 1)};

        } else if(rotazione == 2){

            temp[2]={(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[4]={(short)(temp[0].X + 2), (short)(temp[0].Y - 1)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y)};

        }else{

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[4]={(short)(temp[0].X), (short)(temp[0].Y + 1)};
            temp[6]={(short)(temp[0].X + 2), (short)(temp[0].Y + 1)};

        }

    } else if(tipo == tetramino_j){

        if(rotazione == 0){

            temp[2]={(short)(temp[0].X - 2), (short)(temp[0].Y)};
            temp[4]={(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y - 1)};

        } else if(rotazione == 1){

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y + 1)};
            temp[4]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[6]={(short)(temp[0].X + 2), (short)(temp[0].Y - 1)};

        } else if(rotazione == 2){

            temp[2]={(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[4]={(short)(temp[0].X + 2), (short)(temp[0].Y + 1)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y)};

        }else{

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[4]={(short)(temp[0].X), (short)(temp[0].Y + 1)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y + 1)};

        }

    } else if(tipo == tetramino_z){

        if(rotazione % 2 == 0){

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[4]={(short)(temp[0].X - 2), (short)(temp[0].Y)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y + 1)};

        } else {

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[4]={(short)(temp[0].X - 2), (short)(temp[0].Y - 1)};
            temp[6]={(short)(temp[0].X + 2), (short)(temp[0].Y)};

        }

    } else if(tipo == tetramino_s){

        if(rotazione % 2 == 0){

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[4]={(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[6]={(short)(temp[0].X + 2), (short)(temp[0].Y + 1)};

        } else {

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[4]={(short)(temp[0].X + 2), (short)(temp[0].Y - 1)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y)};

        }

    }


    

    rotazione++;
    if(rotazione == 5) rotazione = 0;      

    for(short i = 0; i < 8; i++){

        if(i % 2 == 1){
            temp[i].Y = temp[i - 1].Y;
            temp[i].X = temp[i - 1].X + 1;
        }

    }

    for(short i = 0; i < 8; i++){

        p[i] = temp[i];

    }



}

//Metodo che imposta gli id del tetramino corrente sul campo
void Tetramino::stampa_id(){
    
    for(short i = 0; i < 8; i++){
        campo.casella[p[i].Y][p[i].X].id = id_tetramino;
    }

}

//Metodo che controlla se c'è un tetramino sotto quello corrente ---COLLISIONI---
bool Tetramino::puo_cadere(){

    for(short i = 0; i < 8; i++) {

        if(p[i].Y + 1  >= CAMPO_ALTEZZA - 2){
            in_movimento = false;
            return false;
        }
            

        if(campo.casella[p[i].Y+1][p[i].X].id != 32 && campo.casella[p[i].Y+1][p[i].X].id != id_tetramino){
            in_movimento = false;
            posizione_cursore(coord_fine);
            printf("  : %d", campo.casella[p[i].Y+1][p[i].X].id);
            return false;
        }
            
        
    }

    in_movimento = true;
    return true;

}

//Metodo che controlla se c'è un tetramino o altro a destra di quello corrente ---COLLISIONI---
bool Tetramino::puo_destra(){

    for(short i = 0; i < 8; i++) {

        if(p[i].X + 1  >= CAMPO_LUNGHEZZA - 2){
            //in_movimento = false; in teoria dovrebbe ancora poter cadere
            return false;
        }
            

        if(campo.casella[p[i].Y][p[i].X + 1].id != 32 && campo.casella[p[i].Y][p[i].X + 1].id != id_tetramino){
            //in_movimento = false; in teoria dovrebbe ancora poter cadere
            return false; 
        }
            
        
    }

    this->in_movimento = true;
    return true;

}

//Metodo che controlla se c'è un tetramino o altro a sinistra di quello corrente ---COLLISIONI---
bool Tetramino::puo_sinistra(){

    for(short i = 0; i < 8; i++) {

        if(p[i].X - 1  <= -1){
            //in_movimento = false; in teoria dovrebbe ancora poter cadere
            return false;
        }
            

        if(campo.casella[p[i].Y][p[i].X - 1].id != 32 && campo.casella[p[i].Y][p[i].X - 1].id != id_tetramino){
            //in_movimento = false; in teoria dovrebbe ancora poter cadere
            return false; 
        }
            
        
    }

    this->in_movimento = true;
    return true;

}

//Metodo che stampa il tetramino corrente
void Tetramino::stampa(){

    for(short i = 0; i < 8; i++){
        if(i % 2 == 0){
            campo.casella[p[i].Y][p[i].X].blocco = BLOCCO_SINISTRA;
        } else {
            campo.casella[p[i].Y][p[i].X].blocco = BLOCCO_DESTRA;
        }
    }
    this->stampa_colore();

}

//Metodo che effettua la caduta lenta del tetramino
void Tetramino::caduta_lenta(){
    
    for(short i = 0; i < 8; i++){
        campo.casella[p[i].Y][p[i].X].id = 32;
        campo.casella[p[i].Y][p[i].X].blocco = 32;
        campo.casella[p[i].Y][p[i].X].colore = bianco;
        p[i].Y+= 1;
    }

    this->sleep = 300;

}

//Metodo che effettua la caduta veloce del tetramino
void Tetramino::caduta_veloce(){
    
    for(short i = 0; i < 8; i++){
        campo.casella[p[i].Y][p[i].X].id = 32;
        campo.casella[p[i].Y][p[i].X].blocco = 32;
        campo.casella[p[i].Y][p[i].X].colore = bianco;
        p[i].Y+= 1;
    }

    this->sleep = 50;

}

void Tetramino::caduta_istantanea(){

    for(short i = 0; i < 8; i++){
        campo.casella[p[i].Y][p[i].X].id = 32;
        campo.casella[p[i].Y][p[i].X].blocco = 32;
        campo.casella[p[i].Y][p[i].X].colore = bianco;
    }

    while(1){

        for(short i = 0; i < 8; i++){
            
            if(campo.casella[p[i].Y + 1][p[i].X].id != 32 && campo.casella[p[i].Y + 1][p[i].X].id != id_tetramino || p[i].Y + 1 >= CAMPO_ALTEZZA - 2){
                this->in_movimento = false;
                return;
            }

        }

        for(short i = 0; i < 8; i++){
            this->p[i].Y+=1;
        }

    }

}

//Metodo che crea un blocco fantasma nella parte inferiore del campo per sapere dove atterrer�  il tetramino
COORD* Tetramino::ghost_block(){

    this->stampa_id();

    static COORD p_ghost[8];

    for(short i = 0; i < 8; i++){

        p_ghost[i].X = p[i].X;
        p_ghost[i].Y = p[i].Y;

    }

    while(1){

        for(short i = 0; i < 8; i++){
            
            if(campo.casella[p_ghost[i].Y + 1][p_ghost[i].X].id != 32 && campo.casella[p_ghost[i].Y + 1][p_ghost[i].X].id != id_tetramino || p_ghost[i].Y + 1 >= CAMPO_ALTEZZA - 2){
                this->stampa();
                return p_ghost;
            }

        }

        for(short i = 0; i < 8; i++){
            p_ghost[i].Y+=1;
        }

    }


}

//Metodo che effettua lo spostamento a destra del tetramino
void Tetramino::sposta_destra(){
    
    for(short i = 0; i < 8; i++){
        campo.casella[p[i].Y][p[i].X].id = 32;
        campo.casella[p[i].Y][p[i].X].blocco = 32;
        campo.casella[p[i].Y][p[i].X].colore = bianco;
        p[i].X+= 2;
    }

}

//Metodo che effettua lo spostamento a sinistra del tetramino
void Tetramino::sposta_sinistra(){

    for(short i = 0; i < 8; i++){
        campo.casella[p[i].Y][p[i].X].id = 32;
        campo.casella[p[i].Y][p[i].X].blocco = 32;
        campo.casella[p[i].Y][p[i].X].colore = bianco;
        p[i].X-= 2;
    }

}

void Tetramino::pulisci(bool is_ghost_block ){

    COORD* posizione_tetramino;

    if(is_ghost_block){
        
        posizione_tetramino = this->ghost_block();
        
    }else{
        
        posizione_tetramino = p;
        
    }

    for(short i = 0; i < 8; i++){

        cursore_manuale(posizione_tetramino[i].X + 1, posizione_tetramino[i].Y + 1);
        printf("%c", 32);

    }

}

void Tetramino::sparisci(){

    for(short i = 0; i < 8; i++){
            
        campo.casella[p[i].Y][p[i].X].id = 32;
        campo.casella[p[i].Y][p[i].X].blocco = 32;
        campo.casella[p[i].Y][p[i].X].colore = bianco;

    }

}

//Distruttore del tetramino, serve per controllare che è stato ristrutto o effettuare qualcosa 
Tetramino::~Tetramino(){
    cursore_manuale(1, CAMPO_ALTEZZA + 2);
    //printf("distruttooo %3d",id_tetramino);
}
