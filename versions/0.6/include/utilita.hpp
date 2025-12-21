#ifndef UTILITA_HPP
#define UTILITA_HPP

#include "costanti.hpp"
#include "input.hpp"
#include <winsock2.h>
#include <windows.h>
#include <conio.h>
#include <ixwebsocket/IXWebSocket.h>
#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>
#include <cstring>
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

#define GRID_ROWS CAMPO_ALTEZZA - 2
#define GRID_COLS CAMPO_LUNGHEZZA - 2
#define MAX_PLAYERS 2
#define MAX_STR_LEN 64

struct CasellaDTO {
    int id;
    char colore;
    char blocco;
};

struct MessageDTO {
    char from[MAX_STR_LEN];
    CasellaDTO caselle[GRID_ROWS][GRID_COLS];
    int seed;
    bool GameOver;
    int score;
    char to[MAX_STR_LEN];
};

struct GameStartedDTO {
    int roomId;
    char players[MAX_PLAYERS][MAX_STR_LEN];
    int playerCount;
};

struct RoomDTO {
    int id;
    char owner[MAX_STR_LEN];
    char name[MAX_STR_LEN];
    char members[MAX_PLAYERS][MAX_STR_LEN];
    int memberCount;
};

// --- Funzioni di conversione esplicite ---

// Conversioni Casella
nlohmann::json_abi_v3_11_3::ordered_json casellaToJson(const CasellaDTO& c);
CasellaDTO casellaFromJson(const nlohmann::json_abi_v3_11_3::ordered_json& j);

// Conversioni Message
nlohmann::json_abi_v3_11_3::ordered_json messageToJson(const MessageDTO& m);
MessageDTO messageFromJson(const nlohmann::json_abi_v3_11_3::ordered_json& j);

// Conversioni Room e GameStarted (Solo ricezione/From)
GameStartedDTO gameStartedFromJson(const nlohmann::json_abi_v3_11_3::ordered_json& j);
RoomDTO roomFromJson(const nlohmann::json_abi_v3_11_3::ordered_json& j);








// variabili globali per i thread
extern int timer_input;
extern int timer_caduta;

std::string apri_config();
std::string inizializza_config(bool esiste);
void salva_config();
void scrivi_due_tasti(nlohmann::json_abi_v3_11_3::ordered_json& config, const char* chiave, const char& a, const char& b);
void carica_due_tasti(const nlohmann::json_abi_v3_11_3::ordered_json& config, const char* chiave, char& a, char& b);

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