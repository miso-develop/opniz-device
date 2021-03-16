#ifndef BASE_HANDLER_H
#define BASE_HANDLER_H

#include <ArduinoJson.h>

extern DynamicJsonDocument jsonDoc;

class BaseHandler {
protected:
    static boolean isMessageName(JsonObject json, String name) {
        String messageName = json["name"];
        return messageName.indexOf(name) == 0;
    }
    
public:
    virtual boolean canHandle(JsonObject json) = 0;
    virtual String handle(JsonObject json) = 0;
    virtual ~BaseHandler() = default;
};

#endif
