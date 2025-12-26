#ifndef UTILITA_LINUX_HPP
#define UTILITA_LINUX_HPP

#include "costanti.hpp"

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
#include <clocale>

#include <nlohmann/json.hpp>
#include <httplib.h>
#include <ixwebsocket/IXWebSocket.h>

// POSIX
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

// ---- Costanti ----
#define GRID_ROWS (CAMPO_ALTEZZA - 2)
#define GRID_COLS (CAMPO_LUNGHEZZA - 2)
#define MAX_PLAYERS 2
#define MAX_STR_LEN 64

// ---- DTO ----
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

// ---- Conversioni ----
json casellaToJson(const CasellaDTO& c);
CasellaDTO casellaFromJson(const json& j);

json messageToJson(const MessageDTO& m);
MessageDTO messageFromJson(const json& j);

GameStartedDTO gameStartedFromJson(const json& j);
RoomDTO roomFromJson(const json& j);

// ---- Conversioni automatiche JSON ----
void to_json(json& j, const MessageDTO& m);
void from_json(const json& j, MessageDTO& m);

void to_json(json& j, const RoomDTO& r);
void from_json(const json& j, RoomDTO& r);

void to_json(json& j, const GameStartedDTO& g);
void from_json(const json& j, GameStartedDTO& g);

// ---- Variabili globali ----
extern int timer_input;
extern int timer_input_origine;
extern int timer_caduta;
extern int timer_caduta_origine;

// ---- Config ----
std::string apri_config();
std::string inizializza_config();
void salva_config(std::string nome = "");
void scrivi_due_tasti(ordered_json& config, const char* chiave, const char& a, const char& b);
void carica_due_tasti(const ordered_json& config, const char* chiave, char& a, char& b);

// ---- Timer ----
void countdown_input(int ms);
void countdown_caduta(int ms);

// ---- Console ----
void disabilita_echo();
void ripristina_echo();
void scritta(int dormi, const std::string& testo);
void cursore_manuale(short x, short y);
void posizione_cursore(COORD coord);
void cursore_alto(COORD* coord, short delta);
void cursore_basso(COORD* coord, short delta);
void cursore_sinistra(COORD* coord, short delta);
void cursore_destra(COORD* coord, short delta);
COORD posizione_attuale();
void nascondi_cursore();
void mostra_cursore();
void pulisci();
void cmd_grande(); // stub su Linux

// ---- Input stile Windows ----
int _getch();
bool kbhit();

#endif
