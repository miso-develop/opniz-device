#include "devices/M5Atom.h"

Opniz::M5Atom::M5Atom(const char* address, uint16_t port) : Esp32(address, port) {
    name = "m5atom";
    
    addHandler({
        new DrawpixHandler
    });
    
    addEmitter({
        new ButtonEmitter
    });
};



String Opniz::M5Atom::DrawpixHandler::handle(JsonObject json) {
    uint8_t number = (uint8_t)json["parameters"][0];
    String color = json["parameters"][1];
    M5.dis.drawpix(number, str2crgb(color));
    return "true";
}



boolean Opniz::M5Atom::ButtonEmitter::canEmit() {
    M5.Btn.read();
    return M5.Btn.wasPressed();
}
String Opniz::M5Atom::ButtonEmitter::emit() {
    std::vector<String> parameters;
    parameters.emplace_back("single-push");
    return createMassageJson("button", parameters);
}
