#include "tetramino.hpp"

#include <iostream>
using namespace std;

int Tetramino::id_tetramini = '0' - 1;
//int Tetramino::id_tetramini = 0;

Tetramino::Tetramino(){
    this->inizializza();
    this->controllo_colore();
    this->controllo_tipo();
}

//Constructor per creare un tetramino con delle caratteristiche predefinite, senza generare un nuovo id e tipo
Tetramino::Tetramino(int id_definito, TipoTetramino tipo_definito, int colore){
    this->in_movimento = true;
    this->id_tetramino = id_definito;
    this->colore = colore;
    this->tipo = tipo_definito;
    this->controllo_tipo();
}

//Metodo che assegna il colore del tetramino in base al tipo
void Tetramino::controllo_colore(){
    switch (tipo) {
        case TipoTetramino::I: colore = ciano;          break;
        case TipoTetramino::J: colore = blu;            break;
        case TipoTetramino::L: colore = arancione;      break;
        case TipoTetramino::O: colore = giallo;         break;
        case TipoTetramino::Z: colore = rosso;          break;
        case TipoTetramino::S: colore = verde;          break;
        case TipoTetramino::T: colore = magenta_chiaro; break;

        case TipoTetramino::SL: colore = marrone;       break;
        case TipoTetramino::BSL: colore = light_green;  break;
        case TipoTetramino::Y: colore = blu_scuro;      break;
        case TipoTetramino::P: colore = ciano_chiaro;   break;
        case TipoTetramino::V: colore = light_yellow;   break;
        case TipoTetramino::M: colore = magenta;        break;
        case TipoTetramino::C: colore = bianco;         break;
    }


    if(TIPO_COLORI == TipoColori::CASUALE){

        std::random_device rd;
        std::mt19937 gen(rd()); // generatore
        std::uniform_int_distribution<int> dis(1, 14); // range incluso

        colore = dis(gen);

        colore *= -1;

    }

    if(TIPO_COLORI == TipoColori::ALTERNATIVO){

        colore -=2;

        if(colore < -14) colore += 13;

    }

    if (TIPO_COLORI == TipoColori::NESSUNO){
        colore = bianco;
    }
    

}

void Tetramino::controllo_tipo(){

    switch (tipo) {

        case TipoTetramino::I:
            p[0] = {CAMPO_CENTRO,     2};
            p[1] = {CAMPO_CENTRO + 1, 2};
            p[2] = {CAMPO_CENTRO,     1};
            p[3] = {CAMPO_CENTRO + 1, 1};
            p[4] = {CAMPO_CENTRO,     3};
            p[5] = {CAMPO_CENTRO + 1, 3};
            p[6] = {CAMPO_CENTRO,     4};
            p[7] = {CAMPO_CENTRO + 1, 4};
            break;

        case TipoTetramino::J:
            p[0] = {CAMPO_CENTRO,     2};
            p[1] = {CAMPO_CENTRO + 1, 2};
            p[2] = {CAMPO_CENTRO,     1};
            p[3] = {CAMPO_CENTRO + 1, 1};
            p[4] = {CAMPO_CENTRO,     3};
            p[5] = {CAMPO_CENTRO + 1, 3};
            p[6] = {CAMPO_CENTRO - 2, 3};
            p[7] = {CAMPO_CENTRO - 1, 3};
            break;

        case TipoTetramino::L:
            p[0] = {CAMPO_CENTRO,     2};
            p[1] = {CAMPO_CENTRO + 1, 2};
            p[2] = {CAMPO_CENTRO,     1};
            p[3] = {CAMPO_CENTRO + 1, 1};
            p[4] = {CAMPO_CENTRO,     3};
            p[5] = {CAMPO_CENTRO + 1, 3};
            p[6] = {CAMPO_CENTRO + 2, 3};
            p[7] = {CAMPO_CENTRO + 3, 3};
            break;

        case TipoTetramino::O:
            p[0] = {CAMPO_CENTRO,     1};
            p[1] = {CAMPO_CENTRO + 1, 1};
            p[2] = {CAMPO_CENTRO + 2, 1};
            p[3] = {CAMPO_CENTRO + 3, 1};
            p[4] = {CAMPO_CENTRO,     2};
            p[5] = {CAMPO_CENTRO + 1, 2};
            p[6] = {CAMPO_CENTRO + 2, 2};
            p[7] = {CAMPO_CENTRO + 3, 2};
            break;

        case TipoTetramino::Z:
            p[0] = {CAMPO_CENTRO,     1};
            p[1] = {CAMPO_CENTRO + 1, 1};
            p[2] = {CAMPO_CENTRO - 2, 1};
            p[3] = {CAMPO_CENTRO - 1, 1};
            p[4] = {CAMPO_CENTRO,     2};
            p[5] = {CAMPO_CENTRO + 1, 2};
            p[6] = {CAMPO_CENTRO + 2, 2};
            p[7] = {CAMPO_CENTRO + 3, 2};
            break;

        case TipoTetramino::S:
            p[0] = {CAMPO_CENTRO,     1};
            p[1] = {CAMPO_CENTRO + 1, 1};
            p[2] = {CAMPO_CENTRO + 2, 1};
            p[3] = {CAMPO_CENTRO + 3, 1};
            p[4] = {CAMPO_CENTRO,     2};
            p[5] = {CAMPO_CENTRO + 1, 2};
            p[6] = {CAMPO_CENTRO - 2, 2};
            p[7] = {CAMPO_CENTRO - 1, 2};
            break;

        case TipoTetramino::T:
            p[0] = {CAMPO_CENTRO,     1};
            p[1] = {CAMPO_CENTRO + 1, 1};
            p[2] = {CAMPO_CENTRO - 2, 1};
            p[3] = {CAMPO_CENTRO - 1, 1};
            p[4] = {CAMPO_CENTRO + 2, 1};
            p[5] = {CAMPO_CENTRO + 3, 1};
            p[6] = {CAMPO_CENTRO,     2};
            p[7] = {CAMPO_CENTRO + 1, 2};
            break;

        case TipoTetramino::SL:
            p[0] = p[4] = {CAMPO_CENTRO,     1};
            p[1] = p[5] = {CAMPO_CENTRO + 1, 1};
            p[2] = p[6] = {CAMPO_CENTRO - 2, 2};
            p[3] = p[7] = {CAMPO_CENTRO - 1, 2};
            break;

        case TipoTetramino::BSL:
            p[0] = {CAMPO_CENTRO,     2};
            p[1] = {CAMPO_CENTRO + 1, 2};
            p[2] = {CAMPO_CENTRO - 2, 1};
            p[3] = {CAMPO_CENTRO - 1, 1};
            p[4] = {CAMPO_CENTRO + 2, 3};
            p[5] = {CAMPO_CENTRO + 3, 3};
            p[6] = {CAMPO_CENTRO + 4, 4};
            p[7] = {CAMPO_CENTRO + 5, 4};
            break;

        case TipoTetramino::Y:
            p[0] = {CAMPO_CENTRO, 2};
            p[1] = {CAMPO_CENTRO + 1, 2};
            p[2] = {CAMPO_CENTRO - 2, 1};
            p[3] = {CAMPO_CENTRO - 1, 1};
            p[4] = {CAMPO_CENTRO + 2, 1};
            p[5] = {CAMPO_CENTRO + 3, 1};
            p[6] = {CAMPO_CENTRO, 3};
            p[7] = {CAMPO_CENTRO + 1, 3};
            break;

        case TipoTetramino::P:
            p[0] = p[2] = p[4] = p[6] = {CAMPO_CENTRO,     1};
            p[1] = p[3] = p[5] = p[7] = {CAMPO_CENTRO + 1, 1};
            break;

        case TipoTetramino::V:
            p[0] = p[6] = {CAMPO_CENTRO,     2};
            p[1] = p[7] = {CAMPO_CENTRO + 1, 2};
            p[2] = {CAMPO_CENTRO - 2, 1};
            p[3] = {CAMPO_CENTRO - 1, 1};
            p[4] = {CAMPO_CENTRO + 2, 1};
            p[5] = {CAMPO_CENTRO + 3, 1};
            break;

        case TipoTetramino::M:
            p[0] = {CAMPO_CENTRO,     3};
            p[1] = {CAMPO_CENTRO + 1, 3};
            p[2] = {CAMPO_CENTRO - 2, 2};
            p[3] = {CAMPO_CENTRO - 1, 2};
            p[4] = {CAMPO_CENTRO,     1};
            p[5] = {CAMPO_CENTRO + 1, 1};
            p[6] = {CAMPO_CENTRO + 2, 2};
            p[7] = {CAMPO_CENTRO + 3, 2};
            break;

        case TipoTetramino::C:
            p[0] = {CAMPO_CENTRO,     2};
            p[1] = {CAMPO_CENTRO + 1, 2};
            p[2] = {CAMPO_CENTRO + 2, 1};
            p[3] = {CAMPO_CENTRO + 3, 1};
            p[4] = {CAMPO_CENTRO,     3};
            p[5] = {CAMPO_CENTRO + 1, 3};
            p[6] = {CAMPO_CENTRO + 2, 4};
            p[7] = {CAMPO_CENTRO + 3, 4};
            break;

    }


}

//Metodo che assegna il valore del tetramino corrente
bool Tetramino::inizializza(){
    this->in_movimento = true;
    this->id_tetramini++;	
    this->tipo = this->random_tetramino();// da ristrutturare facendo la funzione che genera la coda di tetramini nel futuro, probabilmente anche da un'altra parte
    //tipo = TipoTetramino::I;
    //Controllo che tipo di tetramino è tramite l'enum TetraminoTipo e gli assegno il colore e le cordinate
    

    this->id_tetramino = id_tetramini;
    this->in_movimento = true;

    return 1;

}

bool Tetramino::perdita(){
    
    for(short i = 0; i < 8; i++){

        if(p[i].Y < 1){
            return true;
        }

        if(campo.casella[p[i].Y][p[i].X].id != 32 && campo.casella[p[i].Y][p[i].X].id != id_tetramino){
            return true;
        }


    }

    return false;

}

//Metodo che crea un tipo casuale di tetramino da 1 a 7 
TipoTetramino Tetramino::random_tetramino(){
        
    static std::random_device rd;
    static std::mt19937::result_type seed = rd();
    static std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dist = (TIPO_PARTITA == TipoPartita::AVANZATA) ? std::uniform_int_distribution<int>(1,9) : std::uniform_int_distribution<int>(1,7);

    int random = dist(gen);

    if(random > 7){

        std::uniform_int_distribution<int> dist1 = std::uniform_int_distribution<int>(8, 14);

        random = dist1(gen);

    }

    return static_cast<TipoTetramino>(random);

    // prima era così però in teoria dovrebbe essere meglio adesso
    // return static_cast<TipoTetramino>(1 + rand() % (7 - 1 + 1));//min + rand()%(max - min + 1)
    
}

//Metodo che imposta il colore nella casella del campo associata
void Tetramino::stampa_colore(){

    for(short i = 0; i < 8; i++){
        campo.casella[p[i].Y][p[i].X].colore = colore;
    }

}

//Metodo che controlla se il tetramino puo girare
Collisioni Tetramino::puo_girare(TipoInput tipo_rotazione) {

    COORD temp[8];
    
    short rotazione_ipotetica;

    if(tipo_rotazione == TipoInput::GIROORARIO) //antioraria
        rotazione_ipotetica = rotazione;
    else
    if(tipo_rotazione == TipoInput::GIROANTIORARIO) //antioraria
        rotazione_ipotetica+= 2;
    else
    if(tipo_rotazione == TipoInput::GIRODOPPIO) //doppia
        rotazione_ipotetica+=1;

    for(short i = 0; i < 8; i++){
        if(i % 2 == 0){
            temp[i] = p[i];
        }

    }

    if(tipo == TipoTetramino::I){

        if(rotazione_ipotetica % 2 == 0){

            temp[2]={(short)(temp[0].X + 2), temp[0].Y};
            temp[4]={(short)(temp[0].X - 2), temp[0].Y};
            temp[6]={(short)(temp[0].X - 4), temp[0].Y};

        } else {

            temp[2]={temp[0].X, (short)(temp[0].Y - 1)};
            temp[4]={temp[0].X, (short)(temp[0].Y + 1)};
            temp[6]={temp[0].X, (short)(temp[0].Y + 2)};

        }

        

    } else if(tipo == TipoTetramino::T){
        
        

        if(rotazione_ipotetica == 0){

            temp[2]={(short)(temp[0].X - 2), (short)(temp[0].Y)};
            temp[4]={(short)(temp[0].X), (short)(temp[0].Y + 1)};
            temp[6]={(short)(temp[0].X), (short)(temp[0].Y - 1)};

        } else if(rotazione_ipotetica == 1){

            temp[2]={(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[4]={(short)(temp[0].X - 2), (short)(temp[0].Y)};
            temp[6]={(short)(temp[0].X), (short)(temp[0].Y - 1)};

        } else if(rotazione_ipotetica == 2){

            temp[2]={(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[4]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[6]={(short)(temp[0].X), (short)(temp[0].Y + 1)};

        }else{

            temp[2]={(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[4]={(short)(temp[0].X - 2), (short)(temp[0].Y)};
            temp[6]={(short)(temp[0].X), (short)(temp[0].Y + 1)};

        }

    } else if(tipo == TipoTetramino::L){

        if(rotazione_ipotetica == 0){

            temp[2]={(short)(temp[0].X - 2), (short)(temp[0].Y)};
            temp[4]={(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y + 1)};

        } else if(rotazione_ipotetica == 1){

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y + 1)};
            temp[4]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y - 1)};

        } else if(rotazione_ipotetica == 2){

            temp[2]={(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[4]={(short)(temp[0].X + 2), (short)(temp[0].Y - 1)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y)};

        }else{

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[4]={(short)(temp[0].X), (short)(temp[0].Y + 1)};
            temp[6]={(short)(temp[0].X + 2), (short)(temp[0].Y + 1)};

        }

    } else if(tipo == TipoTetramino::J){

        if(rotazione_ipotetica == 0){

            temp[2]={(short)(temp[0].X - 2), (short)(temp[0].Y)};
            temp[4]={(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y - 1)};

        } else if(rotazione_ipotetica == 1){

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y + 1)};
            temp[4]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[6]={(short)(temp[0].X + 2), (short)(temp[0].Y - 1)};

        } else if(rotazione_ipotetica == 2){

            temp[2]={(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[4]={(short)(temp[0].X + 2), (short)(temp[0].Y + 1)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y)};

        }else{

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[4]={(short)(temp[0].X), (short)(temp[0].Y + 1)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y + 1)};

        }

    } else if(tipo == TipoTetramino::Z){

        if(rotazione_ipotetica % 2 == 0){

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[4]={(short)(temp[0].X - 2), (short)(temp[0].Y)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y + 1)};

        } else {

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[4]={(short)(temp[0].X - 2), (short)(temp[0].Y - 1)};
            temp[6]={(short)(temp[0].X + 2), (short)(temp[0].Y)};

        }

    } else if(tipo == TipoTetramino::S){

        if(rotazione_ipotetica % 2 == 0){

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[4]={(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[6]={(short)(temp[0].X + 2), (short)(temp[0].Y + 1)};

        } else {

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[4]={(short)(temp[0].X + 2), (short)(temp[0].Y - 1)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y)};

        }

    } else if(tipo == TipoTetramino::SL){

        if(rotazione_ipotetica % 2 == 0){

            temp[0] = temp[4] = {(short)(temp[0].X), (short)(temp[0].Y + 1)};
            temp[2] = temp[6] = {(short)(temp[2].X), (short)(temp[2].Y - 1)};

        } else {

            temp[0] = temp[4] = {(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[2] = temp[6] = {(short)(temp[2].X), (short)(temp[2].Y + 1)};

        }

    } else if(tipo == TipoTetramino::BSL){

        if(rotazione_ipotetica % 2 == 0){

            temp[0] = {(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[2] = {(short)(temp[2].X + 6), (short)(temp[2].Y)};
            temp[4] = {(short)(temp[4].X - 2), (short)(temp[4].Y)};
            temp[6] = {(short)(temp[6].X - 6), (short)(temp[6].Y)};

        } else {

            temp[0] = {(short)(temp[0].X - 2), (short)(temp[0].Y)};
            temp[2] = {(short)(temp[2].X - 6), (short)(temp[2].Y)};
            temp[4] = {(short)(temp[4].X + 2), (short)(temp[4].Y)};
            temp[6] = {(short)(temp[6].X + 6), (short)(temp[6].Y)};

        }

    } else if(tipo == TipoTetramino::Y){

        if(rotazione_ipotetica == 0){

            temp[2] = {(short)(temp[0].X + 2), (short)(temp[0].Y - 1)};
            temp[4] = {(short)(temp[0].X + 2), (short)(temp[0].Y + 1)};
            temp[6] = {(short)(temp[0].X - 2), (short)(temp[0].Y)};

        } else if (rotazione_ipotetica == 1){

            temp[2] = {(short)(temp[0].X + 2), (short)(temp[0].Y + 1)};
            temp[4] = {(short)(temp[0].X - 2), (short)(temp[0].Y + 1)};
            temp[6] = {(short)(temp[0].X), (short)(temp[0].Y - 1)};

        } else if (rotazione_ipotetica == 2){
 
            temp[2] = {(short)(temp[0].X - 2), (short)(temp[0].Y + 1)};
            temp[4] = {(short)(temp[0].X - 2), (short)(temp[0].Y - 1)};
            temp[6] = {(short)(temp[0].X + 2), (short)(temp[0].Y)};

        } else {

            temp[2] = {(short)(temp[0].X - 2), (short)(temp[0].Y - 1)};
            temp[4] = {(short)(temp[0].X + 2), (short)(temp[0].Y - 1)};
            temp[6] = {(short)(temp[0].X), (short)(temp[0].Y + 1)};       

        }

    } else if(tipo == TipoTetramino::V){

        if(rotazione_ipotetica == 0){

            temp[2] = temp[6] = {(short)(temp[0].X + 2), (short)(temp[0].Y - 1)};
            temp[4] = {(short)(temp[0].X + 2), (short)(temp[0].Y + 1)};

        } else if (rotazione_ipotetica == 1){

            temp[2] = temp[6] = {(short)(temp[0].X + 2), (short)(temp[0].Y + 1)};
            temp[4] = {(short)(temp[0].X - 2), (short)(temp[0].Y + 1)};

        } else if (rotazione_ipotetica == 2){
 
            temp[2] = temp[6] = {(short)(temp[0].X - 2), (short)(temp[0].Y + 1)};
            temp[4] = {(short)(temp[0].X - 2), (short)(temp[0].Y - 1)};

        } else {

            temp[2] = temp[6] = {(short)(temp[0].X - 2), (short)(temp[0].Y - 1)};
            temp[4] = {(short)(temp[0].X + 2), (short)(temp[0].Y - 1)};

        }


    } else if(tipo == TipoTetramino::C){

        if(rotazione_ipotetica == 0){

            temp[2] = {(short)(temp[0].X + 2), (short)(temp[0].Y + 1)};
            temp[4] = {(short)(temp[0].X - 2), (short)(temp[0].Y)};
            temp[6] = {(short)(temp[0].X - 4), (short)(temp[0].Y + 1)};

        } else if (rotazione_ipotetica == 1){

            temp[2] = {(short)(temp[0].X - 2), (short)(temp[0].Y + 1)};
            temp[4] = {(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[6] = {(short)(temp[0].X - 2), (short)(temp[0].Y - 2)};

        } else if (rotazione_ipotetica == 2){
 
            temp[2] = {(short)(temp[0].X - 2), (short)(temp[0].Y - 1)};
            temp[4] = {(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[6] = {(short)(temp[0].X + 4), (short)(temp[0].Y - 1)};

        } else {

            temp[2] = {(short)(temp[0].X + 2), (short)(temp[0].Y - 1)};
            temp[4] = {(short)(temp[0].X), (short)(temp[0].Y + 1)};
            temp[6] = {(short)(temp[0].X + 2), (short)(temp[0].Y + 2)};       

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
            return Collisioni::FUORI;
        }

        if(temp[i].Y <= 0 || temp[i].Y >= CAMPO_ALTEZZA - 2){
            return Collisioni::FUORI;
        }

        if(campo.casella[temp[i].Y][temp[i].X].id != 32 && campo.casella[temp[i].Y][temp[i].X].id != id_tetramino){
            return Collisioni::COLLISIONE;
        }

    }

    return Collisioni::LIBERO;
}

//Metodo che effettua il giramento del tetramino
void Tetramino::gira(TipoInput tipo_rotazione){

    COORD temp[8];

    //if(tipo_rotazione == TipoGiro::ORARIA) 
        //rotazione = rotazione;
    //else
    if(tipo_rotazione == TipoInput::GIROANTIORARIO) 
        rotazione -= 2;
    else
    if(tipo_rotazione == TipoInput::GIRODOPPIO)
        rotazione++;


    if(rotazione < 0) rotazione += 4;
    if(rotazione >= 4) rotazione -= 4; 

    for(short i = 0; i < 8; i++){
        if(i % 2 == 0){
            temp[i] = p[i];
        }

        campo.casella[p[i].Y][p[i].X].id = 32;
        campo.casella[p[i].Y][p[i].X].blocco[0] = 32; campo.casella[p[i].Y][p[i].X].blocco[1] ='\0';
    }

    if(tipo == TipoTetramino::I){

        if(rotazione % 2 == 0){

            temp[2]={(short)(temp[0].X + 2), temp[0].Y};
            temp[4]={(short)(temp[0].X - 2), temp[0].Y};
            temp[6]={(short)(temp[0].X - 4), temp[0].Y};

        } else {

            temp[2]={temp[0].X, (short)(temp[0].Y - 1)};
            temp[4]={temp[0].X, (short)(temp[0].Y + 1)};
            temp[6]={temp[0].X, (short)(temp[0].Y + 2)};

        }

        

    } else if(tipo == TipoTetramino::T){
        
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

    } else if(tipo == TipoTetramino::L){

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

    } else if(tipo == TipoTetramino::J){

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

    } else if(tipo == TipoTetramino::Z){

        if(rotazione % 2 == 0){

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[4]={(short)(temp[0].X - 2), (short)(temp[0].Y)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y + 1)};

        } else {

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[4]={(short)(temp[0].X - 2), (short)(temp[0].Y - 1)};
            temp[6]={(short)(temp[0].X + 2), (short)(temp[0].Y)};

        }

    } else if(tipo == TipoTetramino::S){

        if(rotazione % 2 == 0){

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[4]={(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[6]={(short)(temp[0].X + 2), (short)(temp[0].Y + 1)};

        } else {

            temp[2]={(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[4]={(short)(temp[0].X + 2), (short)(temp[0].Y - 1)};
            temp[6]={(short)(temp[0].X - 2), (short)(temp[0].Y)};

        }

    } else if(tipo == TipoTetramino::SL){

        if(rotazione % 2 == 0){

            temp[0] = temp[4] = {(short)(temp[0].X), (short)(temp[0].Y + 1)};
            temp[2] = temp[6] = {(short)(temp[2].X), (short)(temp[2].Y - 1)};

        } else {

            temp[0] = temp[4] = {(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[2] = temp[6] = {(short)(temp[2].X), (short)(temp[2].Y + 1)};

        }

    } else if(tipo == TipoTetramino::BSL){

        if(rotazione % 2 == 0){

            temp[0] = {(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[2] = {(short)(temp[2].X + 6), (short)(temp[2].Y)};
            temp[4] = {(short)(temp[4].X - 2), (short)(temp[4].Y)};
            temp[6] = {(short)(temp[6].X - 6), (short)(temp[6].Y)};

        } else {

            temp[0] = {(short)(temp[0].X - 2), (short)(temp[0].Y)};
            temp[2] = {(short)(temp[2].X - 6), (short)(temp[2].Y)};
            temp[4] = {(short)(temp[4].X + 2), (short)(temp[4].Y)};
            temp[6] = {(short)(temp[6].X + 6), (short)(temp[6].Y)};

        }

    } else if(tipo == TipoTetramino::Y){

        if(rotazione == 0){

            temp[2] = {(short)(temp[0].X + 2), (short)(temp[0].Y - 1)};
            temp[4] = {(short)(temp[0].X + 2), (short)(temp[0].Y + 1)};
            temp[6] = {(short)(temp[0].X - 2), (short)(temp[0].Y)};

        } else if (rotazione == 1){

            temp[2] = {(short)(temp[0].X + 2), (short)(temp[0].Y + 1)};
            temp[4] = {(short)(temp[0].X - 2), (short)(temp[0].Y + 1)};
            temp[6] = {(short)(temp[0].X), (short)(temp[0].Y - 1)};

        } else if (rotazione == 2){
 
            temp[2] = {(short)(temp[0].X - 2), (short)(temp[0].Y + 1)};
            temp[4] = {(short)(temp[0].X - 2), (short)(temp[0].Y - 1)};
            temp[6] = {(short)(temp[0].X + 2), (short)(temp[0].Y)};

        } else {

            temp[2] = {(short)(temp[0].X - 2), (short)(temp[0].Y - 1)};
            temp[4] = {(short)(temp[0].X + 2), (short)(temp[0].Y - 1)};
            temp[6] = {(short)(temp[0].X), (short)(temp[0].Y + 1)};       

        }

    } else if(tipo == TipoTetramino::V){

        if(rotazione == 0){

            temp[2] = temp[6] = {(short)(temp[0].X + 2), (short)(temp[0].Y - 1)};
            temp[4] = {(short)(temp[0].X + 2), (short)(temp[0].Y + 1)};

        } else if (rotazione == 1){

            temp[2] = temp[6] = {(short)(temp[0].X + 2), (short)(temp[0].Y + 1)};
            temp[4] = {(short)(temp[0].X - 2), (short)(temp[0].Y + 1)};

        } else if (rotazione == 2){
 
            temp[2] = temp[6] = {(short)(temp[0].X - 2), (short)(temp[0].Y + 1)};
            temp[4] = {(short)(temp[0].X - 2), (short)(temp[0].Y - 1)};

        } else {

            temp[2] = temp[6] = {(short)(temp[0].X - 2), (short)(temp[0].Y - 1)};
            temp[4] = {(short)(temp[0].X + 2), (short)(temp[0].Y - 1)};

        }


    } else if(tipo == TipoTetramino::C){

        if(rotazione == 0){

            temp[2] = {(short)(temp[0].X + 2), (short)(temp[0].Y + 1)};
            temp[4] = {(short)(temp[0].X - 2), (short)(temp[0].Y)};
            temp[6] = {(short)(temp[0].X - 4), (short)(temp[0].Y + 1)};

        } else if (rotazione == 1){

            temp[2] = {(short)(temp[0].X - 2), (short)(temp[0].Y + 1)};
            temp[4] = {(short)(temp[0].X), (short)(temp[0].Y - 1)};
            temp[6] = {(short)(temp[0].X - 2), (short)(temp[0].Y - 2)};

        } else if (rotazione == 2){
 
            temp[2] = {(short)(temp[0].X - 2), (short)(temp[0].Y - 1)};
            temp[4] = {(short)(temp[0].X + 2), (short)(temp[0].Y)};
            temp[6] = {(short)(temp[0].X + 4), (short)(temp[0].Y - 1)};

        } else {

            temp[2] = {(short)(temp[0].X + 2), (short)(temp[0].Y - 1)};
            temp[4] = {(short)(temp[0].X), (short)(temp[0].Y + 1)};
            temp[6] = {(short)(temp[0].X + 2), (short)(temp[0].Y + 2)};       

        }
        
    }


    

    rotazione++;
    if(rotazione < 0) rotazione += 4;
    if(rotazione >= 4) rotazione -= 4;      

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
Collisioni Tetramino::puo_cadere(){

    for(short i = 0; i < 8; i++) {

        if(p[i].Y + 1  >= CAMPO_ALTEZZA - 2){
            //in_movimento = false;
            return Collisioni::FUORI;
        }
            

        if(campo.casella[p[i].Y+1][p[i].X].id != 32 && campo.casella[p[i].Y+1][p[i].X].id != id_tetramino){
            //in_movimento = false;
            return Collisioni::COLLISIONE;
        }
            
        
    }

    in_movimento = true;
    return Collisioni::LIBERO;

}

//Metodo che controlla se c'è un tetramino o altro a destra di quello corrente ---COLLISIONI---
Collisioni Tetramino::puo_destra(){

    for(short i = 0; i < 8; i++) {

        if(p[i].X + 1  >= CAMPO_LUNGHEZZA - 2){
            return Collisioni::FUORI;
        }
            

        if(campo.casella[p[i].Y][p[i].X + 1].id != 32 && campo.casella[p[i].Y][p[i].X + 1].id != id_tetramino){
            return Collisioni::COLLISIONE; 
        }
            
        
    }

    this->in_movimento = true;
    return Collisioni::LIBERO;

}

//Metodo che controlla se c'è un tetramino o altro a sinistra di quello corrente ---COLLISIONI---
Collisioni Tetramino::puo_sinistra(){

    for(short i = 0; i < 8; i++) {

        if(p[i].X - 1  <= -1){
            //in_movimento = false; in teoria dovrebbe ancora poter cadere
            return Collisioni::FUORI;
        }
            

        if(campo.casella[p[i].Y][p[i].X - 1].id != 32 && campo.casella[p[i].Y][p[i].X - 1].id != id_tetramino){
            //in_movimento = false; in teoria dovrebbe ancora poter cadere
            return Collisioni::COLLISIONE; 
        }
            
        
    }

    this->in_movimento = true;
    return Collisioni::LIBERO;

}

//Metodo che stampa il tetramino corrente
void Tetramino::stampa(){

    for(short i = 0; i < 8; i++){
        if(i % 2 == 0){
            strcpy(campo.casella[p[i].Y][p[i].X].blocco, BLOCCO_SINISTRA);
        } else {
            strcpy(campo.casella[p[i].Y][p[i].X].blocco, BLOCCO_DESTRA);
        }
        //campo.casella[p[i].Y][p[i].X].blocco[0] = i + '0';
        //campo.casella[p[i].Y][p[i].X].blocco[1] = '\0';
    }
    this->stampa_colore();

}

//Metodo che effettua la caduta lenta del tetramino
short Tetramino::caduta_lenta(){
    
    short linee_percorse = 0;

    for(short i = 0; i < 8; i++){
        campo.casella[p[i].Y][p[i].X].id = 32;
        campo.casella[p[i].Y][p[i].X].blocco[0] = 32; campo.casella[p[i].Y][p[i].X].blocco[1] ='\0';
        campo.casella[p[i].Y][p[i].X].colore = bianco;
        p[i].Y+= 1;
    }

    linee_percorse++;
    this->sleep = 300;

    return linee_percorse;

}

//Metodo che effettua la caduta veloce del tetramino
short Tetramino::cadutaVeloce(){
    
    short linee_percorse = 0;

    for(short i = 0; i < 8; i++){
        campo.casella[p[i].Y][p[i].X].id = 32;
        campo.casella[p[i].Y][p[i].X].blocco[0] = 32; campo.casella[p[i].Y][p[i].X].blocco[1] ='\0';
        campo.casella[p[i].Y][p[i].X].colore = bianco;
        p[i].Y+= 1;
    }

    linee_percorse++;
    this->sleep = 50;

    return linee_percorse;

}

short Tetramino::caduta_istantanea(){

    short linee_percorse = 0;

    for(short i = 0; i < 8; i++){
        campo.casella[p[i].Y][p[i].X].id = 32;
        campo.casella[p[i].Y][p[i].X].blocco[0] = 32; campo.casella[p[i].Y][p[i].X].blocco[1] ='\0';
        campo.casella[p[i].Y][p[i].X].colore = bianco;
    }

    while(1){

        for(short i = 0; i < 8; i++){
            
            if(campo.casella[p[i].Y + 1][p[i].X].id != 32 && campo.casella[p[i].Y + 1][p[i].X].id != id_tetramino || p[i].Y + 1 >= CAMPO_ALTEZZA - 2){
                this->in_movimento = false;
                return linee_percorse;
            }

        }

        for(short i = 0; i < 8; i++){
            this->p[i].Y+=1;
            
        }

        linee_percorse++;
    }

    return linee_percorse;

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
        campo.casella[p[i].Y][p[i].X].blocco[0] = 32; campo.casella[p[i].Y][p[i].X].blocco[1] ='\0';
        campo.casella[p[i].Y][p[i].X].colore = bianco;
        p[i].X+= 2;
    }

}

//Metodo che effettua lo spostamento a sinistra del tetramino
void Tetramino::sposta_sinistra(){

    for(short i = 0; i < 8; i++){
        campo.casella[p[i].Y][p[i].X].id = 32;
        campo.casella[p[i].Y][p[i].X].blocco[0] = 32; campo.casella[p[i].Y][p[i].X].blocco[1] ='\0';
        campo.casella[p[i].Y][p[i].X].colore = bianco;
        p[i].X-= 2;
    }

}

void Tetramino::pulisci(TipoTetramino is_ghost_block ){

    COORD* posizione_tetramino;

    if(is_ghost_block == TipoTetramino::GHOST){
        
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
        campo.casella[p[i].Y][p[i].X].blocco[0] = 32; campo.casella[p[i].Y][p[i].X].blocco[1] ='\0';
        campo.casella[p[i].Y][p[i].X].colore = bianco;

    }

}

//Distruttore del tetramino, serve per controllare che è stato ristrutto o effettuare qualcosa 
Tetramino::~Tetramino(){
    cursore_manuale(1, CAMPO_ALTEZZA + 2);
    //printf("distruttooo %3d",id_tetramino);
}
