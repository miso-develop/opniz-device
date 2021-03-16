#ifndef BASE_EMITTER_H
#define BASE_EMITTER_H

#include "lib/JsonParser.h"

class BaseEmitter {
private:
    JsonParser _jsonParser;
    uint16_t _size = 256;
    
protected:
    String createMassageJson(String name) {
        std::vector<String> parameters;
        return createMassageJson(name, parameters);
    }
    String createMassageJson(String name, std::vector<String> parameters) {
        return createMassageJson(name, parameters, _size);
    }
    String createMassageJson(String name, uint16_t size) {
        std::vector<String> parameters;
        return createMassageJson(name, parameters, size);
    }
    String createMassageJson(String name, std::vector<String> parameters, uint16_t size) {
        DynamicJsonDocument jsonDoc(size);
        JsonObject messageJson = jsonDoc.to<JsonObject>();
        messageJson["name"] = name;
        
        if (parameters.size() > 0) {
            JsonArray parametersJson = messageJson.createNestedArray("parameters");
            for (String parameter : parameters) { parametersJson.add(parameter); }
        }
        
        return _jsonParser.stringify(messageJson);
    }
    
    void setSize(uint16_t size) { _size = size; }
    
public:
    virtual boolean canEmit() = 0;
    virtual String emit() = 0;
    virtual ~BaseEmitter() = default;
};

#endif
