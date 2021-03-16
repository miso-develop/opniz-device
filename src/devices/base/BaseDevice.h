#ifndef BASE_DEVICE_H
#define BASE_DEVICE_H

#include "devices/base/lib/TcpManager.h"
#include "devices/base/BaseHandler.h"
#include "devices/base/BaseEmitter.h"
#include "lib/Utils.h"

class BaseDevice : public TcpManager {
private:
    std::vector<BaseHandler*> _handlerList;
    std::vector<BaseEmitter*> _emitterList;
    
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
    void addHandlerList(std::vector<BaseHandler*> handlerList);
    void addEmitterList(std::vector<BaseEmitter*> emitterList);
};

#endif
