#ifndef __linux__
#include "utilita.hpp"

using namespace std;
using namespace chrono;
using namespace chrono_literals;
using ordered_json = nlohmann::ordered_json;

int timer_input;
int timer_input_origine = 1000;
int timer_caduta;
int timer_caduta_origine = 300;
int timer_scambio = 15000;
ordered_json config;

// ---------------- DTO ----------------

ordered_json casellaToJson(const CasellaDTO& c) {
    return ordered_json{{"id", c.id}, {"colore", string(1, c.colore)}, {"blocco", string(1, c.blocco)}};
}

CasellaDTO casellaFromJson(const ordered_json& j) {
    CasellaDTO c;
    c.id = j.at("id").get<int>();
    c.colore = j.at("colore").get<string>()[0];
    c.blocco = j.at("blocco").get<string>()[0];
    return c;
}

ordered_json messageToJson(const MessageDTO& m) {
    ordered_json grid = ordered_json::array();
    for (int r = 0; r < GRID_ROWS; r++) {
        ordered_json row = ordered_json::array();
        for (int c = 0; c < GRID_COLS; c++)
            row.push_back(casellaToJson(m.caselle[r][c]));
        grid.push_back(row);
    }
    return {
        {"from", string(m.from)},
        {"caselle", grid},
        {"seed", m.seed},
        {"GameOver", m.GameOver},
        {"score", m.score},
        {"to", string(m.to)}
    };
}

MessageDTO messageFromJson(const ordered_json& j) {
    MessageDTO m{};
    strncpy_s(m.from, MAX_STR_LEN, j.at("from").get<string>().c_str(), _TRUNCATE);
    strncpy_s(m.to, MAX_STR_LEN, j.at("to").get<string>().c_str(), _TRUNCATE);
    m.seed = j.at("seed").get<int>();
    m.GameOver = j.at("GameOver").get<bool>();
    m.score = j.at("score").get<int>();

    auto grid = j.at("caselle");
    for (int r = 0; r < GRID_ROWS; r++)
        for (int c = 0; c < GRID_COLS; c++)
            m.caselle[r][c] = casellaFromJson(grid[r][c]);

    return m;
}

RoomDTO roomFromJson(const ordered_json& j) {
    RoomDTO r{};
    r.id = j.at("id").get<int>();
    
    strncpy_s(r.owner, MAX_STR_LEN, j.at("owner").get<string>().c_str(), _TRUNCATE);
    strncpy_s(r.name, MAX_STR_LEN, j.at("name").get<string>().c_str(), _TRUNCATE);

    auto mems = j.at("members");
    r.memberCount = min((int)mems.size(), MAX_PLAYERS);

    for (int i = 0; i < r.memberCount; i++) {
        if (!mems[i].is_null())
            strncpy_s(r.members[i], MAX_STR_LEN, mems[i].get<string>().c_str(), _TRUNCATE);
    }

    return r;
}

GameStartedDTO gameStartedFromJson(const ordered_json& j) {
    GameStartedDTO g{};
    g.roomId = j.at("roomId").get<int>();
    auto pls = j.at("players");
    g.playerCount = min((int)pls.size(), MAX_PLAYERS);
    for (int i = 0; i < g.playerCount; i++)
        strncpy_s(g.players[i], MAX_STR_LEN, pls[i].get<string>().c_str(), _TRUNCATE);
    return g;
}

// ---- Conversioni automatiche JSON ----

void to_json(ordered_json& j, const MessageDTO& m) { j = messageToJson(m); }
void from_json(const ordered_json& j, MessageDTO& m) { m = messageFromJson(j); }

void to_json(ordered_json& j, const RoomDTO& r) {
    j = {{"id", r.id}, {"owner", string(r.owner)}, {"name", string(r.name)}, {"members", ordered_json::array()}};
    for(int i = 0; i < r.memberCount; i++)
        j["members"].push_back(string(r.members[i]));
}

void from_json(const ordered_json& j, RoomDTO& r) {
    r.id = j.at("id").get<int>();
    strncpy_s(r.owner, MAX_STR_LEN, j.at("owner").get<string>().c_str(), _TRUNCATE);
    strncpy_s(r.name, MAX_STR_LEN, j.at("name").get<string>().c_str(), _TRUNCATE);
    auto mems = j.at("members");
    r.memberCount = min((int)mems.size(), MAX_PLAYERS);
    for(int i = 0; i < r.memberCount; i++)
        strncpy_s(r.members[i], MAX_STR_LEN, mems[i].get<string>().c_str(), _TRUNCATE);
}

void to_json(ordered_json& j, const GameStartedDTO& g) {
    j = {{"roomId", g.roomId}, {"players", ordered_json::array()}};
    for(int i = 0; i < g.playerCount; i++)
        j["players"].push_back(string(g.players[i]));
}

void from_json(const ordered_json& j, GameStartedDTO& g) {
    g.roomId = j.at("roomId").get<int>();
    auto pls = j.at("players");
    g.playerCount = min((int)pls.size(), MAX_PLAYERS);
    for(int i = 0; i < g.playerCount; i++)
        strncpy_s(g.players[i], MAX_STR_LEN, pls[i].get<string>().c_str(), _TRUNCATE);
}

// ---------------- Config ----------------

string apri_config() {
    ifstream file("config.json");
    if (!file) return inizializza_config();
    
    stringstream ss;
    ss << file.rdbuf();
    config = ordered_json::parse(ss.str());

    // assegna valori agli array
    carica_due_tasti(config, "rotazione", ROTAZIONE[0], ROTAZIONE[1]);
    carica_due_tasti(config, "rotazione_doppia", ROTAZIONE_DOPPIA[0], ROTAZIONE_DOPPIA[1]);
    carica_due_tasti(config, "rotazione_antioraria", ROTAZIONE_ANTIORARIA[0], ROTAZIONE_ANTIORARIA[1]);
    carica_due_tasti(config, "sinistra", SINISTRA[0], SINISTRA[1]);
    carica_due_tasti(config, "destra", DESTRA[0], DESTRA[1]);
    carica_due_tasti(config, "caduta_veloce", CADUTA_VELOCE[0], CADUTA_VELOCE[1]);
    carica_due_tasti(config, "caduta_istantanea", CADUTA_ISTANTANEA[0], CADUTA_ISTANTANEA[1]);
    carica_due_tasti(config, "cambio", CAMBIO[0], CAMBIO[1]);
    BLOCCO_SINISTRA       = config.value("blocco_sinistra", "█");
    BLOCCO_DESTRA         = config.value("blocco_destra", "█");
    BLOCCO_GHOST_SINISTRA = config.value("ghost_block_sinistra", "█");
    BLOCCO_GHOST_DESTRA   = config.value("ghost_block_destra", "█");
    AUDIO_MUSICA = config.at("musica").get<float>();
    AUDIO_SUONI  = config.at("suoni").get<float>();

    std::string nome = config.value("nome", "player");
    file.close();
    return nome;
}

string inizializza_config() {
    string nome;

    scritta(10, "hey player, come ti chiami?");
    getline(cin, nome);
    
    salva_config(nome);

    if(nome == "")
        nome = "player";
    return nome;
}

void salva_config(std::string nome) {

    if (config.is_null())
        config = ordered_json::object();
    
    if(nome != "")
        config["nome"] = nome;

    scrivi_due_tasti(config, "rotazione", ROTAZIONE[0], ROTAZIONE[1]);
    scrivi_due_tasti(config, "rotazione_doppia", ROTAZIONE_DOPPIA[0], ROTAZIONE_DOPPIA[1]);
    scrivi_due_tasti(config, "rotazione_antioraria", ROTAZIONE_ANTIORARIA[0], ROTAZIONE_ANTIORARIA[1]);
    scrivi_due_tasti(config, "sinistra", SINISTRA[0], SINISTRA[1]);
    scrivi_due_tasti(config, "destra", DESTRA[0], DESTRA[1]);
    scrivi_due_tasti(config, "caduta_veloce", CADUTA_VELOCE[0], CADUTA_VELOCE[1]);
    scrivi_due_tasti(config, "caduta_istantanea", CADUTA_ISTANTANEA[0], CADUTA_ISTANTANEA[1]);
    scrivi_due_tasti(config, "cambio", CAMBIO[0], CAMBIO[1]);
    config["blocco_sinistra"]      = std::string(BLOCCO_SINISTRA);
    config["blocco_destra"]        = std::string(BLOCCO_DESTRA);
    config["ghost_block_sinistra"] = std::string(BLOCCO_GHOST_SINISTRA);
    config["ghost_block_destra"]   = std::string(BLOCCO_GHOST_DESTRA);
    config["musica"]        = AUDIO_MUSICA;
    config["suoni"]         = AUDIO_SUONI;
    

    ofstream file("config.json");
    file << config.dump(4);
}

void scrivi_due_tasti(ordered_json& cfg, const char* chiave, const char& a, const char& b){
    cfg[chiave] = { std::string(1, a), std::string(1, b) };
}

void carica_due_tasti(const ordered_json& cfg, const char* chiave, char& a, char& b){
    a = cfg.at(chiave)[0].get<std::string>()[0];
    b = cfg.at(chiave)[1].get<std::string>()[0];
}

// ---------------- Terminale/Console (compatibilità Linux) ----------------

void cmd_type(){
    // Imposta la console a UTF-8 (SOLO la code page)
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void disabilita_echo() {
    // Su Windows l'echo è gestito diversamente, ma manteniamo la funzione vuota
    // per compatibilità con il codice Linux
}

void ripristina_echo() {
    // Su Windows l'echo è gestito diversamente, ma manteniamo la funzione vuota
    // per compatibilità con il codice Linux
}

// ---------------- Output e cursore ----------------

void scritta(int dormi, const std::string& testo) {
    for (char c : testo) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(dormi));
        if (_kbhit()) { _getch(); dormi = 0; }
    }
}

void pulisci() { system("cls"); }

void cursore_manuale(short x, short y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord_posizione = {x, y};
    SetConsoleCursorPosition(hConsole, coord_posizione);
}

void posizione_cursore(COORD c) { cursore_manuale(c.X, c.Y); }

void cursore_alto(COORD* c, short d) { c->Y -= d; posizione_cursore(*c); }
void cursore_basso(COORD* c, short d) { c->Y += d; posizione_cursore(*c); }
void cursore_sinistra(COORD* c, short d) { c->X -= d; posizione_cursore(*c); }
void cursore_destra(COORD* c, short d) { c->X += d; posizione_cursore(*c); }

COORD posizione_attuale() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    return csbi.dwCursorPosition;
}

void nascondi_cursore() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void mostra_cursore() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void cmd_grande() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleDisplayMode(hOut, CONSOLE_FULLSCREEN_MODE, NULL);
}

// ---------------- Input ----------------
/*
int _getch() {
    return ::_getch();  // chiama la versione di conio.h
}

bool kbhit() {
    return ::_kbhit() != 0;  // chiama la versione di conio.h
}
*/
void countdown_input(int tempo) {
    this_thread::sleep_for(milliseconds(tempo));
    timer_input = 0;
}

void countdown_caduta(int tempo) {
    this_thread::sleep_for(milliseconds(tempo));
    timer_caduta = 0;
}

// ---------------- Random ----------------

int numero_casuale(int min, int max) {
    // Controllo per evitare intervallo non valido
    if (min > max) {
        std::swap(min, max);
    }
    
    // Usa l'orologio di sistema come seed
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    std::uniform_int_distribution<int> distrib(min, max);
    
    return distrib(gen);
}

#endif