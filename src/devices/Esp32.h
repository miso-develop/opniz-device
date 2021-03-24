#ifndef ESP32_H
#define ESP32_H

#include <Arduino.h>

#include "devices/base/BaseDevice.h"

namespace Opniz {
    class Esp32 : public BaseDevice {
    public:
        Esp32(const char* address, uint16_t port);
        ~Esp32() {};
        
        class GetFreeHeapHandler : public BaseHandler {
        public:
            String getName() override { return "getFreeHeap"; };
            String handle(JsonObject json) override;
        };
        
        class TemperatureReadHandler : public BaseHandler {
        public:
            String getName() override { return "temperatureRead"; };
            String handle(JsonObject json) override;
        };
        
        class RestartHandler : public BaseHandler {
        public:
            String getName() override { return "restart"; };
            String handle(JsonObject json) override;
        };
        
        class DelayHandler : public BaseHandler {
        public:
            String getName() override { return "delay"; };
            String handle(JsonObject json) override;
        };
        
        class AnalogReadHandler : public BaseHandler {
        public:
            String getName() override { return "analogRead"; };
            String handle(JsonObject json) override;
        };
        
        class DacWriteHandler : public BaseHandler {
        public:
            String getName() override { return "dacWrite"; };
            String handle(JsonObject json) override;
        };
        
        class DigitalReadHandler : public BaseHandler {
        public:
            String getName() override { return "digitalRead"; };
            String handle(JsonObject json) override;
        };
        
        class DigitalWriteHandler : public BaseHandler {
        public:
            String getName() override { return "digitalWrite"; };
            String handle(JsonObject json) override;
        };
        
        class LedcWriteHandler : public BaseHandler {
        public:
            String getName() override { return "ledcWrite"; };
            String handle(JsonObject json) override;
        };
    };
}

#endif
