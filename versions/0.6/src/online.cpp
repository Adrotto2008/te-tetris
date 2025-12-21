#include "online.hpp"


Online::Online(const std::string& serverIp, int port) 
    : _serverIp(serverIp), _port(port) {
    
    // Inizializzazione rete (necessaria su Windows)
    ix::initNetSystem();

    // Configurazione callback globale del WebSocket
    _ws.setOnMessageCallback([this](const ix::WebSocketMessagePtr& msg) {
        _handleIncomingMessage(msg);
    });
}

Online::~Online() {
    disconnect();
    ix::uninitNetSystem();
}

// --- Gestione Connessione ---

void Online::login(const std::string& username) {
    _username = username;
    std::string url = "ws://" + _serverIp + ":" + std::to_string(_port) + "/ws?username=" + username;
    _ws.setUrl(url);
    _ws.start(); // Avvia il thread in background
}

void Online::disconnect() {
    _ws.stop();
}

// --- Metodi HTTP ---

std::vector<RoomDTO> Online::getAvailableRooms() {
    httplib::Client cli(_serverIp, _port);
    auto res = cli.Get("/room/getAll", {{"username", _username}});

    std::vector<RoomDTO> rooms; 
    // Nota: usiamo vector solo per il ritorno della funzione per comodità, 
    // ma i dati interni a RoomDTO sono array fissi.

    if (res && res->status == 200) {
        auto j = json::parse(res->body);
        for (auto& item : j) {
            RoomDTO r;
            from_json(item, r); // Usa la nostra funzione custom per array statici
            rooms.push_back(r);
        }
    }
    return rooms;
}

bool Online::createRoom(const std::string& roomName) {
    httplib::Client cli(_serverIp, _port);
    auto res = cli.Post(("/room/create/" + roomName).c_str(), {{"username", _username}}, "", "text/plain");
    return res && res->status == 200;
}