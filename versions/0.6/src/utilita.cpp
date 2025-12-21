#include "utilita.hpp"



using namespace std;
using namespace chrono;
using namespace chrono_literals;
using ordered_json = nlohmann::ordered_json;

int timer_input;
int timer_caduta;

nlohmann::json_abi_v3_11_3::ordered_json config;


void countdown_input(int tempo){

    this_thread::sleep_for(milliseconds(tempo));
    timer_input = 0;

}

void countdown_caduta(int tempo){

    this_thread::sleep_for(milliseconds(tempo));
    timer_caduta = 0;

}




// --- CASELLA ---

nlohmann::json_abi_v3_11_3::ordered_json casellaToJson(const CasellaDTO& c) {
    return json{
        {"id", c.id}, 
        {"colore", std::string(1, c.colore)}, 
        {"blocco", std::string(1, c.blocco)}
    };
}

CasellaDTO casellaFromJson(const nlohmann::json_abi_v3_11_3::ordered_json& j) {
    CasellaDTO c;
    c.id = j.at("id").get<int>();
    std::string col = j.at("colore").get<std::string>();
    std::string blo = j.at("blocco").get<std::string>();
    c.colore = col.empty() ? ' ' : col[0];
    c.blocco = blo.empty() ? ' ' : blo[0];
    return c;
}

// --- MESSAGE ---

nlohmann::json_abi_v3_11_3::ordered_json messageToJson(const MessageDTO& m) {
    json grid = json::array();
    for (int r = 0; r < GRID_ROWS; r++) {
        json row = json::array();
        for (int c = 0; c < GRID_COLS; c++) {
            row.push_back(casellaToJson(m.caselle[r][c]));
        }
        grid.push_back(row);
    }
    return json{
        {"from", std::string(m.from)},
        {"caselle", grid},
        {"seed", m.seed},
        {"GameOver", m.GameOver},
        {"score", m.score},
        {"to", std::string(m.to)}
    };
}

MessageDTO messageFromJson(const nlohmann::json_abi_v3_11_3::ordered_json& j) {
    MessageDTO m;
    
    // Stringhe
    std::string f = j.at("from").get<std::string>();
    strncpy(m.from, f.c_str(), MAX_STR_LEN - 1);
    m.from[MAX_STR_LEN - 1] = '\0';

    std::string t = j.at("to").get<std::string>();
    strncpy(m.to, t.c_str(), MAX_STR_LEN - 1);
    m.to[MAX_STR_LEN - 1] = '\0';

    // Primitivi
    m.seed = j.at("seed").get<int>();
    m.GameOver = j.at("GameOver").get<bool>();
    m.score = j.at("score").get<int>();

    // Griglia
    auto grid = j.at("caselle");
    for (int r = 0; r < GRID_ROWS; r++) {
        if (r < (int)grid.size()) {
            auto row = grid[r];
            for (int c = 0; c < GRID_COLS; c++) {
                if (c < (int)row.size()) {
                    m.caselle[r][c] = casellaFromJson(row[c]);
                }
            }
        }
    }
    return m;
}

// --- ROOM ---

RoomDTO roomFromJson(const nlohmann::json_abi_v3_11_3::ordered_json& j) {
    RoomDTO r;
    r.id = j.at("id").get<int>();
    
    std::string o = j.at("owner").get<std::string>();
    strncpy(r.owner, o.c_str(), MAX_STR_LEN - 1);
    r.owner[MAX_STR_LEN - 1] = '\0';

    std::string n = j.at("name").get<std::string>();
    strncpy(r.name, n.c_str(), MAX_STR_LEN - 1);
    r.name[MAX_STR_LEN - 1] = '\0';
    
    auto mems = j.at("members");
    r.memberCount = std::min((int)mems.size(), MAX_PLAYERS);
    for (int i = 0; i < r.memberCount; i++) {
        std::string m = mems[i].get<std::string>();
        strncpy(r.members[i], m.c_str(), MAX_STR_LEN - 1);
        r.members[i][MAX_STR_LEN - 1] = '\0';
    }
    return r;
}

// --- GAME STARTED ---

GameStartedDTO gameStartedFromJson(const nlohmann::json_abi_v3_11_3::ordered_json& j) {
    GameStartedDTO g;
    g.roomId = j.at("roomId").get<int>();
    auto pls = j.at("players");
    g.playerCount = std::min((int)pls.size(), MAX_PLAYERS);
    for (int i = 0; i < g.playerCount; i++) {
        std::string p = pls[i].get<std::string>();
        strncpy(g.players[i], p.c_str(), MAX_STR_LEN - 1);
        g.players[i][MAX_STR_LEN - 1] = '\0';
    }
    return g;
}






std::string apri_config() {
    std::ifstream file("config.json");
    if (!file) {
        
        return inizializza_config(false);  
    }

    // Il file esiste → leggilo
    std::stringstream buffer;
    buffer << file.rdbuf();
    config = ordered_json::parse(buffer.str());

    // Assegna valori dagli array
    carica_due_tasti(config, "rotazione", ROTAZIONE[0], ROTAZIONE[1]);
    carica_due_tasti(config, "rotazione_doppia", ROTAZIONE_DOPPIA[0], ROTAZIONE_DOPPIA[1]);
    carica_due_tasti(config, "rotazione_antioraria", ROTAZIONE_ANTIORARIA[0], ROTAZIONE_ANTIORARIA[1]);
    carica_due_tasti(config, "sinistra", SINISTRA[0], SINISTRA[1]);
    carica_due_tasti(config, "destra", DESTRA[0], DESTRA[1]);
    carica_due_tasti(config, "caduta_veloce", CADUTA_VELOCE[0], CADUTA_VELOCE[1]);
    carica_due_tasti(config, "caduta_istantanea", CADUTA_ISTANTANEA[0], CADUTA_ISTANTANEA[1]);
    carica_due_tasti(config, "cambio", CAMBIO[0], CAMBIO[1]);

    return config["nome"].get<std::string>();

}

std::string inizializza_config(bool esiste){

    std::string nome;

    if(!esiste){
        scritta(100, "hey player, come ti chiami?\n");
        std::getline(std::cin, nome);           
        config["nome"] = nome;
    }
    config["rotazione"] = { "W", "w" };
    config["rotazione_doppia"] = { "Z", "z" };
    config["rotazione_antioraria"] = { "R", "r" };
    config["sinistra"] = { "A", "a" };
    config["destra"] = { "D", "d" };
    config["caduta_veloce"] = { "S", "s" };
    config["caduta_istantanea"] = { "Q", "q" };
    config["cambio"] = { "C", "c" };

    std::ofstream file("config.json");
    file << config.dump(4); // indentazione per leggibilità

    return nome;
}

void salva_config() {
    // aggiorna il JSON con valori attuali delle variabili
    scrivi_due_tasti(config, "rotazione", ROTAZIONE[0], ROTAZIONE[1]);
    scrivi_due_tasti(config, "rotazione_doppia", ROTAZIONE_DOPPIA[0], ROTAZIONE_DOPPIA[1]);
    scrivi_due_tasti(config, "rotazione_antioraria", ROTAZIONE_ANTIORARIA[0], ROTAZIONE_ANTIORARIA[1]);
    scrivi_due_tasti(config, "sinistra", SINISTRA[0], SINISTRA[1]);
    scrivi_due_tasti(config, "destra", DESTRA[0], DESTRA[1]);
    scrivi_due_tasti(config, "caduta_veloce", CADUTA_VELOCE[0], CADUTA_VELOCE[1]);
    scrivi_due_tasti(config, "caduta_istantanea", CADUTA_ISTANTANEA[0], CADUTA_ISTANTANEA[1]);
    scrivi_due_tasti(config, "cambio", CAMBIO[0], CAMBIO[1]);

    std::ofstream file("config.json");
    file << config.dump(4); // indentazione per leggibilità
}

void scrivi_due_tasti(nlohmann::json_abi_v3_11_3::ordered_json& config, const char* chiave, const char& a, const char& b){
    config[chiave] = { std::string(1, a), std::string(1, b) };
}

void carica_due_tasti(const nlohmann::json_abi_v3_11_3::ordered_json& config, const char* chiave, char& a, char& b){
    a = config.at(chiave)[0].get<std::string>()[0];
    b = config.at(chiave)[1].get<std::string>()[0];
}

void scritta(int dormi, std::string stringa){

    Input input;

    for(short i = 0; i < stringa.length(); i++){
        putchar(stringa[i]);
        Sleep(dormi);
        if(kbhit()){
            input.scan();
            if(input.azione() == TipoInput::CADUTAISTANTANEA){
                dormi = 0;
            }
        }
        
    }

}

void cursore_manuale(short x, short y){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord_posizione = {x, y};
    posizione_cursore(coord_posizione);
}

void pulisci(){
    system("cls");
}

COORD posizione_attuale() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    return csbi.dwCursorPosition;
}

void cursore_alto(COORD* coord_posizione, short delta){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    coord_posizione->Y -= delta;
    posizione_cursore(*coord_posizione);
}

void cursore_basso(COORD* coord_posizione, short delta){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    coord_posizione->Y += delta;
    posizione_cursore(*coord_posizione);
}

void cursore_sinistra(COORD* coord_posizione, short delta){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    coord_posizione->X -= delta;
    posizione_cursore(*coord_posizione);
}

void cursore_destra(COORD* coord_posizione, short delta){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    coord_posizione->X += delta;
    posizione_cursore(*coord_posizione);
}

void posizione_cursore(COORD coord_posizione){
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, coord_posizione);
}

void nascondi_cursore(){

    printf(CURSORE_INVISIBILE);

}

void mostra_cursore(){

    printf(CURSORE_VISIBILE);

}

void cmd_grande(){

    HWND hwnd = GetConsoleWindow(); // Ottieni il manico della finestra del terminale
    ShowWindow(hwnd, SW_MAXIMIZE);

}
