#include "online.hpp"

#include <iostream>

Online::Online(const std::string& serverIp)
    : _serverIp(serverIp)
{
    _ws.setOnMessageCallback([this](const ix::WebSocketMessagePtr& msg) {
        _handleIncomingMessage(msg);
    });
}

Online::~Online() {
    disconnect();
}

void Online::login(const std::string& username) {
    _username = username;

    std::string url =
        "ws://" + _serverIp +
        "/ws?username=" + _username;

    _ws.setUrl(url);
    _ws.start();

    headers = {
        { "username", _username }
    };
}

void Online::disconnect() {
    _ws.stop();
}

std::vector<RoomDTO> Online::getAvailableRooms() {
    httplib::Client cli(_serverIp, 80);
    auto res = cli.Get("/room/getAll", headers);

    std::vector<RoomDTO> rooms;

    if (!res) {
        std::cout << "NO RESPONSE FROM SERVER\n";
        return rooms;
    }

    if (res->status == 200) {
        auto j = nlohmann::json::parse(res->body);
        for (auto& item : j) {
            rooms.push_back(roomFromJson(item));
        }
    }

    return rooms;
}

RoomDTO Online::createRoom(const std::string& roomName) {
    httplib::Client cli(_serverIp, 80);
    auto res = cli.Post(
        ("/room/create/" + roomName).c_str(),
        headers,
        "",
        "text/plain"
    );

    return roomFromJson(nlohmann::json::parse(res->body));
}

bool Online::joinRoom(int roomId) {
    httplib::Client cli(_serverIp, 80);
    auto res = cli.Post(
        ("/room/join/" + std::to_string(roomId)).c_str(),
        headers,
        "",
        "text/plain"
    );
    return res && res->status == 200;
}

void Online::sendGameUpdate(int roomId, const MessageDTO& message) {
    std::string dest = "/app/send_game_data." + std::to_string(roomId);
    std::string body = messageToJson(message).dump();

    std::map<std::string, std::string> h = {
        {"destination", dest},
        {"content-type", "application/json"}
    };

    _ws.send(_buildStompFrame("SEND", h, body));
}

/* ================= STOMP HANDLING ================= */

void Online::_handleIncomingMessage(const ix::WebSocketMessagePtr& msg) {
    if (msg->type == ix::WebSocketMessageType::Open) {
        _sendStompConnect();
        return;
    }

    if (msg->type != ix::WebSocketMessageType::Message) return;

    const std::string& data = msg->str;

    for (auto& [topic, callback] : _callbacks) {
        if (data.find("destination:" + topic) != std::string::npos) {
            size_t bodyPos = data.find("\n\n");
            if (bodyPos == std::string::npos) return;

            std::string body =
                data.substr(bodyPos + 2,
                data.find('\0') - (bodyPos + 2));

            auto json = nlohmann::json::parse(body);
            callback(json);
            return;
        }
    }
}

void Online::_sendStompConnect() {
    std::map<std::string, std::string> h = {
        {"accept-version", "1.2"},
        {"host", "server"}
    };

    _ws.send(_buildStompFrame("CONNECT", h, ""));
}

std::string Online::_buildStompFrame(
    const std::string& cmd,
    const std::map<std::string, std::string>& h,
    const std::string& b)
{
    std::string f = cmd + "\n";
    for (auto& [k, v] : h) {
        f += k + ":" + v + "\n";
    }
    f += "\n" + b + '\0';
    return f;
}