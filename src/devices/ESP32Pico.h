#ifndef ESP32_PICO_H
#define ESP32_PICO_H

#include "devices/base/BaseDevice.h"

class Esp32Pico : public BaseDevice {
public:
    Esp32Pico(const char* address, uint16_t port);
    ~Esp32Pico() {};
    
    class GetFreeHeapHandler : public BaseHandler {
    public:
        boolean canHandle(JsonObject json) override;
        String handle(JsonObject json) override;
    };
    
    class TemperatureReadHandler : public BaseHandler {
    public:
        boolean canHandle(JsonObject json) override;
        String handle(JsonObject json) override;
    };
    
    class RestartHandler : public BaseHandler {
    public:
        boolean canHandle(JsonObject json) override;
        String handle(JsonObject json) override;
    };
    
    class DelayHandler : public BaseHandler {
    public:
        boolean canHandle(JsonObject json) override;
        String handle(JsonObject json) override;
    };
    
    class AnalogReadHandler : public BaseHandler {
    public:
        boolean canHandle(JsonObject json) override;
        String handle(JsonObject json) override;
    };
    
    class DacWriteHandler : public BaseHandler {
    public:
        boolean canHandle(JsonObject json) override;
        String handle(JsonObject json) override;
    };
    
    class DigitalReadHandler : public BaseHandler {
    public:
        boolean canHandle(JsonObject json) override;
        String handle(JsonObject json) override;
    };
    
    class DigitalWriteHandler : public BaseHandler {
    public:
        boolean canHandle(JsonObject json) override;
        String handle(JsonObject json) override;
    };
    
    class LedcWriteHandler : public BaseHandler {
    public:
        boolean canHandle(JsonObject json) override;
        String handle(JsonObject json) override;
    };
};

#endif
