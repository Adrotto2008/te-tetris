#ifndef __linux__
#ifndef UTILITA_HPP
#define UTILITA_HPP


#include <winsock2.h>
#include <ws2tcpip.h>
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
#include <random>

#include <nlohmann/json.hpp>
#include <httplib.h>
#include <ixwebsocket/IXWebSocket.h>

#include "costanti.hpp"
#include "input.hpp"

// Usiamo nlohmann::json standard
using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

#define GRID_ROWS (CAMPO_ALTEZZA - 2)
#define GRID_COLS (CAMPO_LUNGHEZZA - 2)
#define MAX_PLAYERS 2
#define MAX_STR_LEN 64

// --- DTO ---
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

// --- Funzioni DTO/JSON ---
ordered_json casellaToJson(const CasellaDTO& c);
CasellaDTO casellaFromJson(const ordered_json& j);

ordered_json messageToJson(const MessageDTO& m);
MessageDTO messageFromJson(const ordered_json& j);

GameStartedDTO gameStartedFromJson(const ordered_json& j);
RoomDTO roomFromJson(const ordered_json& j);

// --- Conversioni automatiche JSON ---
void to_json(ordered_json& j, const MessageDTO& m);
void from_json(const ordered_json& j, MessageDTO& m);

void to_json(ordered_json& j, const RoomDTO& r);
void from_json(const ordered_json& j, RoomDTO& r);

void to_json(ordered_json& j, const GameStartedDTO& g);
void from_json(const ordered_json& j, GameStartedDTO& g);

// --- Variabili globali ---
extern int timer_input;
extern int timer_input_origine;
extern int timer_caduta;
extern int timer_caduta_origine;
extern int timer_scambio;
extern ordered_json config;

// --- Configurazione ---
std::string apri_config();
std::string inizializza_config();
void salva_config(std::string nome = "");
void scrivi_due_tasti(ordered_json& config, const char* chiave, const char& a, const char& b);
void carica_due_tasti(const ordered_json& config, const char* chiave, char& a, char& b);

// --- Countdown ---
void countdown_input(int tempo);
void countdown_caduta(int tempo);

// --- Terminale/Console (compatibilità Linux) ---
void cmd_type();
void disabilita_echo();
void ripristina_echo();

// --- Output e cursore ---
void scritta(int dormi, const std::string& testo);
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

// --- Input ---
//int _getch();
//bool kbhit();

// --- Random ---
int numero_casuale(int min, int max);

#endif // UTILITA_HPP
#endif // __linux__