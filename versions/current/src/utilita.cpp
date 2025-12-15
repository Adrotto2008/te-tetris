#include "utilita.hpp"
#include "input.hpp"


using namespace std;
using namespace chrono;
using namespace chrono_literals;

int timer_input;
int timer_caduta;


void countdown_input(int tempo){

    this_thread::sleep_for(milliseconds(tempo));
    timer_input = 0;

}

void countdown_caduta(int tempo){

    this_thread::sleep_for(milliseconds(tempo));
    timer_caduta = 0;

}

CasellaDTO casellaFromJson(const nlohmann::json& j) {
    CasellaDTO c;
    c.id = j.at("id").get<int>();
    c.colore = j.at("colore").get<char>();
    c.blocco = j.at("blocco").get<char>();
    return c;
}

MessageDTO messageFromJson(const nlohmann::json& j) {
    MessageDTO m;

    m.from = j.at("from").get<std::string>();
    m.seed = j.at("seed").get<int>();
    m.GameOver = j.at("GameOver").get<bool>();
    m.score = j.at("score").get<int>();
    m.to = j.at("to").get<std::string>();

    // parsing array 2D

    const auto& jCaselle = j.at("caselle");

    for (size_t i = 0; i < CAMPO_ALTEZZA - 2; ++i) {
        const auto& riga = jCaselle[i];
        for (size_t j = 0; j < CAMPO_LUNGHEZZA - 2; ++j) {
            m.caselle[i][j] = casellaFromJson(riga[j]);
        }
    }

    return m;
}

nlohmann::json casellaToJson(const CasellaDTO& c) {
    nlohmann::json j;
    j["id"] = c.id;
    j["colore"] = c.colore;
    j["blocco"] = c.blocco;
    return j;
}

nlohmann::json messageToJson(const MessageDTO& m) {
    nlohmann::json j;
    j["from"] = m.from;
    j["GameOver"] = m.GameOver;
    j["score"] = m.score;
    j["to"] = m.to;

    nlohmann::json jCaselle = nlohmann::json::array();

    for (size_t i = 0; i < CAMPO_ALTEZZA - 2; ++i) {
        nlohmann::json jRiga = nlohmann::json::array();
        for (size_t j = 0; j < CAMPO_LUNGHEZZA - 2; ++j) {
            jRiga.push_back(casellaToJson(m.caselle[i][j]));
        }
        jCaselle.push_back(jRiga);
    }

    j["caselle"] = jCaselle;
    return j;
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
