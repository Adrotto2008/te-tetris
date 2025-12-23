#include "utilita_linux.hpp"

using namespace std;
using namespace chrono;

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

int timer_input;
int timer_caduta;
ordered_json config;
termios term_originale;


// ---------------- DTO ----------------

json casellaToJson(const CasellaDTO& c) {
    return json{{"id", c.id}, {"colore", string(1, c.colore)}, {"blocco", string(1, c.blocco)}};
}

CasellaDTO casellaFromJson(const json& j) {
    CasellaDTO c;
    c.id = j.at("id").get<int>();
    c.colore = j.at("colore").get<string>()[0];
    c.blocco = j.at("blocco").get<string>()[0];
    return c;
}

json messageToJson(const MessageDTO& m) {
    json grid = json::array();
    for (int r = 0; r < GRID_ROWS; r++) {
        json row = json::array();
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

MessageDTO messageFromJson(const json& j) {
    MessageDTO m{};
    strncpy(m.from, j.at("from").get<string>().c_str(), MAX_STR_LEN - 1);
    strncpy(m.to, j.at("to").get<string>().c_str(), MAX_STR_LEN - 1);
    m.seed = j.at("seed").get<int>();
    m.GameOver = j.at("GameOver").get<bool>();
    m.score = j.at("score").get<int>();

    auto grid = j.at("caselle");
    for (int r = 0; r < GRID_ROWS; r++)
        for (int c = 0; c < GRID_COLS; c++)
            m.caselle[r][c] = casellaFromJson(grid[r][c]);

    return m;
}

RoomDTO roomFromJson(const json& j) {
    RoomDTO r{};
    r.id = j.at("id").get<int>();

    auto mems = j.at("members");
    r.memberCount = min((int)mems.size(), MAX_PLAYERS);

    for (int i = 0; i < r.memberCount; i++) {
        if (!mems[i].is_null())
            strncpy(r.members[i], mems[i].get<string>().c_str(), MAX_STR_LEN - 1);
    }

    return r;
}

GameStartedDTO gameStartedFromJson(const json& j) {
    GameStartedDTO g{};
    g.roomId = j.at("roomId").get<int>();
    auto pls = j.at("players");
    g.playerCount = min((int)pls.size(), MAX_PLAYERS);
    for (int i = 0; i < g.playerCount; i++)
        strncpy(g.players[i], pls[i].get<string>().c_str(), MAX_STR_LEN - 1);
    return g;
}

// ---- Conversioni automatiche JSON ----

void to_json(json& j, const MessageDTO& m) { j = messageToJson(m); }
void from_json(const json& j, MessageDTO& m) { m = messageFromJson(j); }

void to_json(json& j, const RoomDTO& r) {
    j = {{"id", r.id}, {"owner", string(r.owner)}, {"name", string(r.name)}, {"members", json::array()}};
    for(int i = 0; i < r.memberCount; i++)
        j["members"].push_back(string(r.members[i]));
}

void from_json(const json& j, RoomDTO& r) {
    r.id = j.at("id").get<int>();
    strncpy(r.owner, j.at("owner").get<string>().c_str(), MAX_STR_LEN-1);
    strncpy(r.name, j.at("name").get<string>().c_str(), MAX_STR_LEN-1);
    auto mems = j.at("members");
    r.memberCount = min((int)mems.size(), MAX_PLAYERS);
    for(int i = 0; i < r.memberCount; i++)
        strncpy(r.members[i], mems[i].get<string>().c_str(), MAX_STR_LEN-1);
}

void to_json(json& j, const GameStartedDTO& g) {
    j = {{"roomId", g.roomId}, {"players", json::array()}};
    for(int i = 0; i < g.playerCount; i++)
        j["players"].push_back(string(g.players[i]));
}

void from_json(const json& j, GameStartedDTO& g) {
    g.roomId = j.at("roomId").get<int>();
    auto pls = j.at("players");
    g.playerCount = min((int)pls.size(), MAX_PLAYERS);
    for(int i = 0; i < g.playerCount; i++)
        strncpy(g.players[i], pls[i].get<string>().c_str(), MAX_STR_LEN-1);
}

// ---------------- Timer ----------------

void countdown_input(int ms) { this_thread::sleep_for(milliseconds(ms)); timer_input = 0; }
void countdown_caduta(int ms) { this_thread::sleep_for(milliseconds(ms)); timer_caduta = 0; }

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
    strcpy(BLOCCO_SINISTRA, config.at("blocco_sinistra").get<std::string>().c_str());
    strcpy(BLOCCO_DESTRA, config.at("blocco_destra").get<std::string>().c_str());
    strcpy(BLOCCO_GHOST_SINISTRA, config.at("ghost_block_sinistra").get<std::string>().c_str());
    strcpy(BLOCCO_GHOST_DESTRA, config.at("ghost_block_destra").get<std::string>().c_str());

    std::string nome = config["nome"];
    file.close();
    return nome;
}

string inizializza_config() {
    string nome;

    scritta(50, "hey player, come ti chiami?");
    getline(cin, nome);
    
    salva_config(nome);

    disabilita_echo();
    setlocale(LC_ALL, "");

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
    config["blocco_sinistra"]       = std::string(BLOCCO_SINISTRA);
    config["blocco_destra"]        = std::string(BLOCCO_DESTRA);
    config["ghost_block_sinistra"] = std::string(BLOCCO_GHOST_SINISTRA);
    config["ghost_block_destra"]   = std::string(BLOCCO_GHOST_DESTRA);
    

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

// ---------------- Console ----------------

void disabilita_echo() {
    tcgetattr(STDIN_FILENO, &term_originale); // salva lo stato originale
    termios nuovo = term_originale;
    nuovo.c_lflag &= ~(ICANON | ECHO); // disabilita canonica e echo
    tcsetattr(STDIN_FILENO, TCSANOW, &nuovo);
}

void ripristina_echo() {
    termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void scritta(int dormi, const std::string& testo) {
    for (char c : testo) {
        cout << c << flush;
        disabilita_echo();
        std::this_thread::sleep_for(std::chrono::milliseconds(dormi));
        if (kbhit()) { _getch(); dormi = 0; }//getch
    }
}

void pulisci() { cout << "\033[2J\033[H" << flush; }
void cursore_manuale(short x, short y) { cout << "\033[" << y+1 << ";" << x+1 << "H" << flush; }
void posizione_cursore(COORD c) { cursore_manuale(c.X, c.Y); }
void cursore_alto(COORD* c, short d) { c->Y -= d; posizione_cursore(*c); }
void cursore_basso(COORD* c, short d) { c->Y += d; posizione_cursore(*c); }
void cursore_sinistra(COORD* c, short d) { c->X -= d; posizione_cursore(*c); }
void cursore_destra(COORD* c, short d) { c->X += d; posizione_cursore(*c); }
COORD posizione_attuale() { 

    COORD posizione;

//    posizione.X = ;
//    posizione.Y = ;

    return posizione; 

}
void nascondi_cursore() { cout << "\033[?25l" << flush; }
void mostra_cursore()   { cout << "\033[?25h" << flush; }
void cmd_grande() { /* non esiste su Linux → no-op */ }

// ---------------- Input ----------------

int _getch() {
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

bool kbhit() {
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int oldf = fcntl(STDIN_FILENO, F_GETFL);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    int ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return true;
    }
    return false;
}
