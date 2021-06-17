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
            String name() override { return "getFreeHeap"; };
            String handle(JsonArray parameters) override;
        };
        
        class TemperatureReadHandler : public BaseHandler {
        public:
            String name() override { return "temperatureRead"; };
            String handle(JsonArray parameters) override;
        };
        
        class RestartHandler : public BaseHandler {
        public:
            String name() override { return "restart"; };
            String handle(JsonArray parameters) override;
        };
        
        class DelayHandler : public BaseHandler {
        public:
            String name() override { return "delay"; };
            String handle(JsonArray parameters) override;
        };
        
        class AnalogReadHandler : public BaseHandler {
        public:
            String name() override { return "analogRead"; };
            String handle(JsonArray parameters) override;
        };
        
        class DacWriteHandler : public BaseHandler {
        public:
            String name() override { return "dacWrite"; };
            String handle(JsonArray parameters) override;
        };
        
        class DigitalReadHandler : public BaseHandler {
        public:
            String name() override { return "digitalRead"; };
            String handle(JsonArray parameters) override;
        };
        
        class DigitalWriteHandler : public BaseHandler {
        public:
            String name() override { return "digitalWrite"; };
            String handle(JsonArray parameters) override;
        };
        
        class LedcWriteHandler : public BaseHandler {
        public:
            String name() override { return "ledcWrite"; };
            String handle(JsonArray parameters) override;
        };
    };
}

#endif
