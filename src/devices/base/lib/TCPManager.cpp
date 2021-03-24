#include "devices/base/lib/TcpManager.h"

TcpManager::TcpManager(const char* address, const uint16_t port) : _address(address), _port(port) {}

void TcpManager::connect() {
    connect(_timeoutCallback, _connectingSignal);
}
void TcpManager::connect(std::function<void()> timeoutCallback) {
    connect(timeoutCallback, _connectingSignal);
}
void TcpManager::connect(std::function<void(boolean)> connectingSignal) {
    connect(_timeoutCallback, connectingSignal);
}
void TcpManager::connect(std::function<void()> timeoutCallback, std::function<void(boolean)> connectingSignal) {
    if (_server.operator bool() && _client.connected()) return;
    
    // connecting
    _startTime = millis();
    while (!_server.operator bool() || !_client.connected()) {
        if (!_server.operator bool()) _server.begin(_port);
        if (!_client.connected()) _client.connect(_address, _port);
        
        // Serial.println(errno);
        // MEMO: errno: 104, "Connection reset by peer" -> 119
        // MEMO: errno: 113, "Software caused connection abort" -> 119
        // MEMO: errno: 118, "Host is unreachable" -> 118
        
        if((millis() - _startTime) > _timeout) {
            _startTime = millis();
            timeoutCallback();
            return;
        }
        
        _connectingSignalState = !_connectingSignalState;
        connectingSignal(_connectingSignalState);
        
        delay(250);
    }
    
    connectingSignal(false); // 接続中表示関数実行
}

boolean TcpManager::send(const String message) {
    if (!_client.connected()) return false;
    
    jdlog("send", message); // DEBUG:
    _client.print(message);
    
    // レスポンスのタイムアウト
    uint32_t _startTime = millis();
    uint16_t _timeout = 5 * 1000;
    while (_client.available() == 0) {
        if (millis() - _startTime > _timeout) {
            _client.stop();
            return false;
        }
        delay(10);
    }
    
    return true;
    
    // MEMO: とりあえずの実装としてレスポンスの値自体は特に見ない
    // while(_client.available()) {
    //     Serial.println(_client.readStringUntil('\r'));
    // }
}

void TcpManager::receive(std::function<String(String)> messageHandler) {
    if (!_socket.connected()) {
        _socket.stop();
        _socket = _server.available();
        
    } else {
        _socket.setTimeout(0);
        String request = _socket.readString();
        if (request == "") return;
        
        jdlog("request", request); // DEBUG:
        String response = messageHandler(request);
        jdlog("response", response); // DEBUG:
        if (response == "[\0]") return;
        
        _socket.print(response);
        
        dlog(esp_get_minimum_free_heap_size()); // DEBUG:
        dlog(uxTaskGetStackHighWaterMark(NULL)); // DEBUG:
        dlog(temperatureRead()); // DEBUG:
    }
}

void TcpManager::close() {
    _server.close();
    _socket.stop();
    _client.stop();
}

TcpManager::~TcpManager() {
    close();
};
