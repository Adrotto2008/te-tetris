#ifndef __linux__
#ifndef UTILITA_HPP
#define UTILITA_HPP

#include "costanti.hpp"
#include "input.hpp"
#include <winsock2.h>
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdlib>
#include <functional>
#include <map>
#include <optional>
#include <stdexcept>
#include <thread>
#include <nlohmann/json.hpp>
#include <httplib.h>
#include <ixwebsocket/IXWebSocket.h>

// Usiamo nlohmann::json standard
using json = nlohmann::json;

#define GRID_ROWS (CAMPO_ALTEZZA - 2)
#define GRID_COLS (CAMPO_LUNGHEZZA - 2)
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
json casellaToJson(const CasellaDTO& c);
CasellaDTO casellaFromJson(const json& j);

json messageToJson(const MessageDTO& m);
MessageDTO messageFromJson(const json& j);

GameStartedDTO gameStartedFromJson(const json& j);
RoomDTO roomFromJson(const json& j);

// Variabili globali e altre funzioni...
extern int timer_input;
extern int timer_caduta;

std::string apri_config();
std::string inizializza_config(bool esiste);
void salva_config();
void scrivi_due_tasti(nlohmann::ordered_json& config, const char* chiave, const char& a, const char& b);
void carica_due_tasti(const nlohmann::ordered_json& config, const char* chiave, char& a, char& b);

void countdown_input(int seconds);
void countdown_caduta(int seconds);
void scritta(int dormi, std::string stringa);
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
#endif