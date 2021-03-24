#ifndef TCP_MANAGER_H
#define TCP_MANAGER_H

#include <WiFi.h>

#include "lib/utils/Log.h" // DEBUG:

class TcpManager {
private:
    const char* _address;
    uint16_t _port;
    
    WiFiServer _server;
    WiFiClient _socket;
    WiFiClient _client;
    
    uint16_t _timeout = 60 * 1000;
    uint32_t _startTime;
    std::function<void()> _timeoutCallback = [this]() { connect(); };
    
    boolean _connectingSignalState = false;
    std::function<void(boolean)> _connectingSignal = [](boolean){};
    
public:
    TcpManager(const char* address, uint16_t port);
    
    void connect();
    void connect(std::function<void()> timeoutCallback);
    void connect(std::function<void(boolean)> connectingSignal);
    void connect(std::function<void()> timeoutCallback, std::function<void(boolean)> connectingSignal);
    
    boolean send(const String message);
    void receive(std::function<String(String)> messageHandler);
    void close();
    
    void setTimeout(uint16_t timeout) { _timeout = timeout; };
    void setTimeoutCallback(std::function<void()> timeoutCallback) { _timeoutCallback = timeoutCallback; };
    void setConnectingSignal(std::function<void(boolean)> connectingSignal) { _connectingSignal = connectingSignal; };
    
    ~TcpManager();
};

#endif
