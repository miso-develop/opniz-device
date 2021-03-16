#include "devices/Esp32Pico.h"

Esp32Pico::Esp32Pico(const char* address, uint16_t port) : BaseDevice(address, port) {
    name = "esp32-pico";
    
    addHandlerList({
        new GetFreeHeapHandler,
        new TemperatureReadHandler,
        new RestartHandler,
        new DelayHandler,
        new AnalogReadHandler,
        new DacWriteHandler,
        new DigitalReadHandler,
        new DigitalWriteHandler,
        new LedcWriteHandler
    });
    
    // addEmitterList({
    // });
}



boolean Esp32Pico::GetFreeHeapHandler::canHandle(JsonObject json) { return isMessageName(json, "getFreeHeap"); }
String Esp32Pico::GetFreeHeapHandler::handle(JsonObject json) {
    // return (String)ESP.getMinFreeHeap(); // MEMO: ←より↓の方が結構値が小さい
    return (String)esp_get_minimum_free_heap_size();
}

boolean Esp32Pico::TemperatureReadHandler::canHandle(JsonObject json) { return isMessageName(json, "temperatureRead"); }
String Esp32Pico::TemperatureReadHandler::handle(JsonObject json) {
    return (String)temperatureRead();
}

boolean Esp32Pico::RestartHandler::canHandle(JsonObject json) { return isMessageName(json, "restart"); }
String Esp32Pico::RestartHandler::handle(JsonObject json) {
    esp_restart();
    return "true";
}

boolean Esp32Pico::DelayHandler::canHandle(JsonObject json) { return isMessageName(json, "delay"); }
String Esp32Pico::DelayHandler::handle(JsonObject json) {
    uint32_t ms = (uint32_t)json["parameters"][0];
    delay(ms);
    return "true";
}

boolean Esp32Pico::AnalogReadHandler::canHandle(JsonObject json) { return isMessageName(json, "analogRead"); }
String Esp32Pico::AnalogReadHandler::handle(JsonObject json) {
    uint8_t pin = (uint8_t)json["parameters"][0];
    pinMode(pin, INPUT);
    return (String)analogRead(pin);
}

boolean Esp32Pico::DacWriteHandler::canHandle(JsonObject json) { return isMessageName(json, "dacWrite"); }
String Esp32Pico::DacWriteHandler::handle(JsonObject json) {
    uint8_t pin = (uint8_t)json["parameters"][0];
    uint8_t value = (uint8_t)json["parameters"][1];
    pinMode(pin, OUTPUT);
    dacWrite(pin, value);
    return "true";
}

boolean Esp32Pico::DigitalReadHandler::canHandle(JsonObject json) { return isMessageName(json, "digitalRead"); }
String Esp32Pico::DigitalReadHandler::handle(JsonObject json) {
    uint8_t pin = (uint8_t)json["parameters"][0];
    pinMode(pin, INPUT);
    return (String)digitalRead(pin);
}

boolean Esp32Pico::DigitalWriteHandler::canHandle(JsonObject json) { return isMessageName(json, "digitalWrite"); }
String Esp32Pico::DigitalWriteHandler::handle(JsonObject json) {
    uint8_t pin = (uint8_t)json["parameters"][0];
    uint8_t val = (uint8_t)json["parameters"][1];
    pinMode(pin, OUTPUT);
    digitalWrite(pin, val);
    return "true";
}

boolean Esp32Pico::LedcWriteHandler::canHandle(JsonObject json) { return isMessageName(json, "ledcWrite"); }
String Esp32Pico::LedcWriteHandler::handle(JsonObject json) {
    uint8_t pin = (uint8_t)json["parameters"][0];
    uint32_t duty = (uint32_t)json["parameters"][1];
    uint8_t channel = (uint8_t)json["parameters"][2];
    double freq = (double)json["parameters"][3];
    uint8_t resolution_bits = (uint8_t)json["parameters"][4];
    ledcSetup(channel, freq, resolution_bits);
    ledcAttachPin(pin, channel);
    ledcWrite(channel, duty);
    return "true";
}
