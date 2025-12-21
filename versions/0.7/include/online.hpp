#ifndef ONLINE_HPP
#define ONLINE_HPP

#include "utilita.hpp"

#include <ixwebsocket/IXWebSocket.h>
#include <httplib.h>
#include <nlohmann/json.hpp>

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>

class Online {
public:
    Online(const std::string& serverIp, int port);
    ~Online();

    void login(const std::string& username);
    void disconnect();

    std::vector<RoomDTO> getAvailableRooms();
    RoomDTO createRoom(const std::string& roomName);
    bool joinRoom(int roomId);

    // ===== SUBSCRIBE TIPIZZATO =====
    template<typename T>
    void subscribe(const std::string& topic,
                   std::function<void(const T&)> callback);

    void sendGameUpdate(int roomId, const MessageDTO& message);

private:
    std::string _serverIp;
    int _port;
    std::string _username;

    ix::WebSocket _ws;
    httplib::Headers headers;

    // callback "raw" interna (JSON)
    using RawCallback = std::function<void(const nlohmann::json&)>;
    std::unordered_map<std::string, RawCallback> _callbacks;

    std::string _buildStompFrame(const std::string& cmd,
                                 const std::map<std::string, std::string>& headers,
                                 const std::string& body);

    void _handleIncomingMessage(const ix::WebSocketMessagePtr& msg);
    void _sendStompConnect();
};

/* ================= TEMPLATE IMPLEMENTATION ================= */

template<typename T>
void Online::subscribe(const std::string& topic,
                       std::function<void(const T&)> callback)
{
    _callbacks[topic] = [callback](const nlohmann::json& j) {
        callback(j.get<T>()); // JSON → DTO
    };

    std::map<std::string, std::string> h = {
        {"id", "sub-" + topic},
        {"destination", topic}
    };

    _ws.send(_buildStompFrame("SUBSCRIBE", h, ""));
}

#endif