#include "devices/Esp32.h"

Opniz::Esp32::Esp32(const char* address, uint16_t port) : BaseDevice(address, port) {
    name = "esp32";
    
    addHandler({
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
    
    // addEmitter({
    // });
}



String Opniz::Esp32::GetFreeHeapHandler::handle(JsonObject json) {
    // return (String)ESP.getMinFreeHeap(); // MEMO: ←より↓の方が結構値が小さい
    return (String)esp_get_minimum_free_heap_size();
}

String Opniz::Esp32::TemperatureReadHandler::handle(JsonObject json) {
    return (String)temperatureRead();
}

String Opniz::Esp32::RestartHandler::handle(JsonObject json) {
    esp_restart();
    return "true";
}

String Opniz::Esp32::DelayHandler::handle(JsonObject json) {
    uint32_t ms = (uint32_t)json["parameters"][0];
    delay(ms);
    return "true";
}

String Opniz::Esp32::AnalogReadHandler::handle(JsonObject json) {
    uint8_t pin = (uint8_t)json["parameters"][0];
    pinMode(pin, INPUT);
    return (String)analogRead(pin);
}

String Opniz::Esp32::DacWriteHandler::handle(JsonObject json) {
    uint8_t pin = (uint8_t)json["parameters"][0];
    uint8_t value = (uint8_t)json["parameters"][1];
    pinMode(pin, OUTPUT);
    dacWrite(pin, value);
    return "true";
}

String Opniz::Esp32::DigitalReadHandler::handle(JsonObject json) {
    uint8_t pin = (uint8_t)json["parameters"][0];
    pinMode(pin, INPUT);
    return (String)digitalRead(pin);
}

String Opniz::Esp32::DigitalWriteHandler::handle(JsonObject json) {
    uint8_t pin = (uint8_t)json["parameters"][0];
    uint8_t val = (uint8_t)json["parameters"][1];
    pinMode(pin, OUTPUT);
    digitalWrite(pin, val);
    return "true";
}

String Opniz::Esp32::LedcWriteHandler::handle(JsonObject json) {
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
