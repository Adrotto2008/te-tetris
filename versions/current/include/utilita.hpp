#ifndef UTILITA_HPP
#define UTILITA_HPP

#include "costanti.hpp"
#include "input.hpp"
#include <winsock2.h>
#include <ixwebsocket/IXWebSocket.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>
#include <httplib.h>
#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdlib>
#include <functional>
#include <map>
#include <optional>
#include <stdexcept>
#include <thread>
#include <conio.h>

typedef struct{

    char colore;
    char blocco;
    int id;

} CasellaDTO;

struct MessageDTO {
    std::string from;
    CasellaDTO caselle[CAMPO_ALTEZZA - 2][CAMPO_ALTEZZA - 2];
    int seed;
    bool GameOver;
    int score;
    std::string to;
};

// variabili globali per i thread
extern int timer_input;
extern int timer_caduta;

std::string apri_config();
std::string inizializza_config(bool esiste);
void salva_config();
void scrivi_due_tasti(nlohmann::json_abi_v3_11_3::ordered_json& config, const char* chiave, const char& a, const char& b);
void carica_due_tasti(const nlohmann::json_abi_v3_11_3::ordered_json& config, const char* chiave, char& a, char& b);

nlohmann::json messageToJson(const MessageDTO& m);
nlohmann::json casellaToJson(const CasellaDTO& c);
CasellaDTO casellaFromJson(const nlohmann::json& j);
MessageDTO messageFromJson(const nlohmann::json& j);

//funzioni thread
void countdown_input(int seconds);
void countdown_caduta(int seconds);

// funzione per mostrare la scritta piano per estetica o skipparla
void scritta(int dormi, std::string stringa);

// Funzioni cursore
void cursore_manuale(short x, short y);
void posizione_cursore(COORD coord_posizione);
void cursore_alto(COORD* coord_posizione, short delta);
void cursore_basso(COORD* coord_posizione, short delta);
void cursore_sinistra(COORD* coord_posizione, short delta);
void cursore_destra(COORD* coord_posizione, short delta);
COORD posizione_attuale();
void nascondi_cursore();
void mostra_cursore();
void pulisci();
void cmd_grande();


#endif