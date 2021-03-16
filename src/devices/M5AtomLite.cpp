#include "devices/M5AtomLite.h"

M5AtomLite::M5AtomLite(const char* address, uint16_t port) : Esp32Pico(address, port) {
    name = "m5atom-lite";
    
    addHandlerList({
        new DrawpixHandler
    });
    
    addEmitterList({
        new ButtonEmitter
    });
};



boolean M5AtomLite::DrawpixHandler::canHandle(JsonObject json) { return isMessageName(json, "drawpix"); }
String M5AtomLite::DrawpixHandler::handle(JsonObject json) {
    uint8_t number = (uint8_t)json["parameters"][0];
    String color = json["parameters"][1];
    M5.dis.drawpix(number, str2crgb(color));
    return "true";
}



boolean M5AtomLite::ButtonEmitter::canEmit() {
    M5.Btn.read();
    return M5.Btn.wasPressed();
}
String M5AtomLite::ButtonEmitter::emit() {
    std::vector<String> parameters;
    parameters.emplace_back("single-push");
    return createMassageJson("button", parameters);
}
