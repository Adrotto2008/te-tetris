// ixwebsocket.h - Versione semplificata per Tetris
#ifndef IXWEBSOCKET_SIMPLE_H
#define IXWEBSOCKET_SIMPLE_H

#include <string>
#include <functional>
#include <memory>
#include <thread>
#include <atomic>

namespace ix {
    // ===== TIPI BASE =====
    class WebSocket;
    class WebSocketMessage;
    using WebSocketMessagePtr = std::shared_ptr<WebSocketMessage>;
    
    enum class WebSocketMessageType {
        Message,
        Open,
        Close,
        Error
    };
    
    class WebSocketMessage {
    public:
        WebSocketMessageType type;
        std::string str;
        size_t wireSize;
        bool binary;
    };
    
    // ===== WEBSOCKET SEMPLICE =====
    class WebSocket {
    private:
        std::atomic<bool> _connected{false};
        std::thread _thread;
        std::function<void(const WebSocketMessagePtr&)> _onMessageCallback;
        std::string _url;
        
    public:
        WebSocket() = default;
        ~WebSocket() { stop(); }
        
        void setUrl(const std::string& url) { _url = url; }
        std::string getUrl() const { return _url; }
        
        void setOnMessageCallback(std::function<void(const WebSocketMessagePtr&)> callback) {
            _onMessageCallback = callback;
        }
        
        bool start() {
            if (_connected) return true;
            
            _connected = true;
            _thread = std::thread([this]() {
                // Thread dummy per simulare connessione
                while (_connected) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
            });
            
            // Simula evento "open"
            if (_onMessageCallback) {
                auto msg = std::make_shared<WebSocketMessage>();
                msg->type = WebSocketMessageType::Open;
                _onMessageCallback(msg);
            }
            
            return true;
        }
        
        void stop() {
            _connected = false;
            if (_thread.joinable()) {
                _thread.join();
            }
            
            // Simula evento "close"
            if (_onMessageCallback) {
                auto msg = std::make_shared<WebSocketMessage>();
                msg->type = WebSocketMessageType::Close;
                _onMessageCallback(msg);
            }
        }
        
        bool send(const std::string& data, bool binary = false) {
            if (!_connected) return false;
            
            // Simula invio riuscito
            return true;
        }
        
        bool sendBinary(const std::string& data) {
            return send(data, true);
        }
        
        bool isConnected() const { return _connected; }
    };
    
    // ===== FUNZIONI UTILITY =====
    inline void initNetSystem() {
        // Niente da fare su Windows
    }
    
    // Per compatibilità con il tuo codice esistente
    struct WebSocketInitResult {
        bool success{true};
        std::string errorMsg;
    };
}

#endif // IXWEBSOCKET_SIMPLE_H