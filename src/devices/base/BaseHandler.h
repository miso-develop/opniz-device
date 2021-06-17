#ifndef BASE_HANDLER_H
#define BASE_HANDLER_H

#include <ArduinoJson.h>

extern DynamicJsonDocument jsonDoc;

class BaseHandler {
public:
    virtual String name() = 0;
    virtual String handle(JsonArray parameters) = 0;
    virtual ~BaseHandler() = default;
};

#endif
