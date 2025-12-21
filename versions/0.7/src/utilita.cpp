#include "utilita.hpp"

using namespace std;
using namespace chrono;
using ordered_json = nlohmann::ordered_json;

int timer_input;
int timer_caduta;
ordered_json config;

// --- Conversioni DTO ---

json casellaToJson(const CasellaDTO& c) {
    return json{{"id", c.id}, {"colore", string(1, c.colore)}, {"blocco", string(1, c.blocco)}};
}

CasellaDTO casellaFromJson(const json& j) {
    CasellaDTO c;
    c.id = j.at("id").get<int>();
    string col = j.at("colore").get<string>();
    string blo = j.at("blocco").get<string>();
    c.colore = col.empty() ? ' ' : col[0];
    c.blocco = blo.empty() ? ' ' : blo[0];
    return c;
}

json messageToJson(const MessageDTO& m) {
    json grid = json::array();
    for (int r = 0; r < GRID_ROWS; r++) {
        json row = json::array();
        for (int c = 0; c < GRID_COLS; c++) {
            row.push_back(casellaToJson(m.caselle[r][c]));
        }
        grid.push_back(row);
    }
    return json{
        {"from", string(m.from)},
        {"caselle", grid},
        {"seed", m.seed},
        {"GameOver", m.GameOver},
        {"score", m.score},
        {"to", string(m.to)}
    };
}

MessageDTO messageFromJson(const json& j) {
    MessageDTO m;
    strncpy(m.from, j.at("from").get<string>().c_str(), MAX_STR_LEN - 1);
    m.from[MAX_STR_LEN - 1] = '\0';
    strncpy(m.to, j.at("to").get<string>().c_str(), MAX_STR_LEN - 1);
    m.to[MAX_STR_LEN - 1] = '\0';
    m.seed = j.at("seed").get<int>();
    m.GameOver = j.at("GameOver").get<bool>();
    m.score = j.at("score").get<int>();

    auto grid = j.at("caselle");
    for (int r = 0; r < GRID_ROWS && r < (int)grid.size(); r++) {
        auto row = grid[r];
        for (int c = 0; c < GRID_COLS && c < (int)row.size(); c++) {
            m.caselle[r][c] = casellaFromJson(row[c]);
        }
    }
    return m;
}

RoomDTO roomFromJson(const json& j) {
    RoomDTO r;
    r.id = j.at("id").get<int>();

    // owner
    if (!j.at("owner").is_null()) {
        strncpy(r.owner, j.at("owner").get<std::string>().c_str(), MAX_STR_LEN - 1);
    } else {
        r.owner[0] = '\0';
    }
    r.owner[MAX_STR_LEN - 1] = '\0';

    // name
    if (!j.at("name").is_null()) {
        strncpy(r.name, j.at("name").get<std::string>().c_str(), MAX_STR_LEN - 1);
    } else {
        r.name[0] = '\0';
    }
    r.name[MAX_STR_LEN - 1] = '\0';

    // members
    auto mems = j.at("members");
    r.memberCount = std::min((int)mems.size(), MAX_PLAYERS);

    for (int i = 0; i < r.memberCount; i++) {
        if (mems[i].is_null()) {
            r.members[i][0] = '\0';
        } else {
            strncpy(r.members[i], mems[i].get<std::string>().c_str(), MAX_STR_LEN - 1);
            r.members[i][MAX_STR_LEN - 1] = '\0';
        }
    }

    return r;
}


GameStartedDTO gameStartedFromJson(const json& j) {
    GameStartedDTO g;
    g.roomId = j.at("roomId").get<int>();
    auto pls = j.at("players");
    g.playerCount = min((int)pls.size(), MAX_PLAYERS);
    for (int i = 0; i < g.playerCount; i++) {
        strncpy(g.players[i], pls[i].get<string>().c_str(), MAX_STR_LEN - 1);
        g.players[i][MAX_STR_LEN - 1] = '\0';
    }
    return g;
}

// --- Funzioni Thread ---

void countdown_input(int tempo) {
    this_thread::sleep_for(milliseconds(tempo));
    timer_input = 0;
}

void countdown_caduta(int tempo) {
    this_thread::sleep_for(milliseconds(tempo));
    timer_caduta = 0;
}

// --- Configurazione ---

string apri_config() {
    ifstream file("config.json");
    if (!file) return inizializza_config(false);
    stringstream buffer;
    buffer << file.rdbuf();
    config = ordered_json::parse(buffer.str());
    return config["nome"].get<string>();
}

string inizializza_config(bool esiste) {
    string nome = "Player";
    if (!esiste) {
        scritta(5, "hey player, come ti chiami?");
        getline(cin, nome);
        string _nome = nome;
        config["nome"] = _nome;
    }
    config["rotazione"] = {"W", "w"};
    config["sinistra"] = {"A", "a"};
    config["destra"] = {"D", "d"};
    config["caduta_veloce"] = {"S", "s"};
    ofstream file("config.json");
    file << config.dump(4);
    return nome;
}

void salva_config() {
    ofstream file("config.json");
    file << config.dump(4);
}

void scrivi_due_tasti(ordered_json& c, const char* chiave, const char& a, const char& b) {
    c[chiave] = {string(1, a), string(1, b)};
}

void carica_due_tasti(const ordered_json& c, const char* chiave, char& a, char& b) {
    a = c.at(chiave)[0].get<string>()[0];
    b = c.at(chiave)[1].get<string>()[0];
}

// --- Utility Console ---

void scritta(int dormi, string s) {
    for (char c : s) {
        cout << c << flush;
        if (dormi > 0) Sleep(dormi);
        if (_kbhit()) { _getch(); dormi = 0; }
    }
}

void cursore_manuale(short x, short y) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {x, y});
}

void posizione_cursore(COORD c) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void cursore_alto(COORD* c, short d) { c->Y -= d; posizione_cursore(*c); }
void cursore_basso(COORD* c, short d) { c->Y += d; posizione_cursore(*c); }
void cursore_sinistra(COORD* c, short d) { c->X -= d; posizione_cursore(*c); }
void cursore_destra(COORD* c, short d) { c->X += d; posizione_cursore(*c); }

COORD posizione_attuale() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition;
}

void nascondi_cursore() {
    CONSOLE_CURSOR_INFO info = {1, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void mostra_cursore() {
    CONSOLE_CURSOR_INFO info = {1, TRUE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void pulisci() { system("cls"); }

void cmd_grande() {
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
}