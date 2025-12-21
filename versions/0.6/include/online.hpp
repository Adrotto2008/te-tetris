#ifndef ONLINE_HPP
#define ONLINE_HPP

#include "utilita.hpp"

using json = nlohmann::json;

class Online {
public:
    Online(const std::string& serverIp, int port);
    ~Online();

    // --- Gestione Connessione ---
    void login(const std::string& username);
    void disconnect();

    // --- Chiamate HTTP (Sincrone) ---
    std::vector<RoomDTO> getAvailableRooms();
    bool createRoom(const std::string& roomName);
    bool joinRoom(int roomId);

    // --- WebSocket / STOMP (Asincrone) ---
    // Callback: riceve il body del messaggio come stringa JSON
    using MessageCallback = std::function<void(const std::string&)>;

    void subscribe(const std::string& topic, MessageCallback callback);
    void sendGameUpdate(int roomId, const MessageDTO& message);

private:
    std::string _serverIp;
    int _port;
    std::string _username;
    ix::WebSocket _ws;

    // Mappa per gestire le callback dei vari canali sottoscritti
    std::map<std::string, MessageCallback> _callbacks;

    // Helper interni per il protocollo STOMP
    std::string _buildStompFrame(const std::string& cmd, const std::map<std::string, std::string>& headers, const std::string& body);
    void _handleIncomingMessage(const ix::WebSocketMessagePtr& msg);
    void _sendStompConnect();
};

#endif