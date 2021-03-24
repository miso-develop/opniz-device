#ifndef BASE_DEVICE_H
#define BASE_DEVICE_H

#include <unordered_map>

#include "devices/base/lib/TcpManager.h"
#include "devices/base/BaseHandler.h"
#include "devices/base/BaseEmitter.h"
#include "lib/Utils.h"

class BaseDevice : public TcpManager {
private:
    std::unordered_map<std::string, BaseHandler*> _handlers;
    std::vector<BaseEmitter*> _emitters;
    
    JsonParser _jsonParser;
    DynamicJsonDocument _responseJsonDoc;
    
    String _messageHandler(String message);
    std::function<String(String)> _messageHandlerFunction = [this](String message) -> String { return _messageHandler(message); };
    
public:
    BaseDevice(const char* address, uint16_t port);
    virtual ~BaseDevice() = default;
    
    String name;
    void handleMessage();
    void emitMessage();
    void addHandler(std::vector<BaseHandler*> handlers);
    void addEmitter(std::vector<BaseEmitter*> emitters);
};

#endif
