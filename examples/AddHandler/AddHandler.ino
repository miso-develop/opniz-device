#include <Opniz.h>

// WiFi
const char* ssid = "<SSID>";
const char* password = "<PASSWORD>";

// opniz
const char* address = "192.168.0.1";
const uint16_t port = 3000;
Opniz::Esp32* opniz = new Opniz::Esp32(address, port);



// Custom Handler
class DrawpixHandler : public BaseHandler {
public:
    String name() override { return "drawpix"; };
    String handle(JsonArray parameters) override {
        uint8_t number = (uint8_t)parameters[0];
        String color = parameters[1];
        M5.dis.drawpix(number, str2crgb(color));
        return "true";
    }
};

// Custom Emitter
class ButtonEmitter : public BaseEmitter {
public:
    boolean canEmit() override {
        M5.Btn.read();
        return M5.Btn.wasPressed();
    };
    String emit() override {
        std::vector<String> parameters;
        parameters.emplace_back("single-push");
        return createMassageJson("button", parameters);
    };
};



void setup() {
    // M5 init
    M5.begin(true, false, true);
    M5.dis.setBrightness(10);
    setCpuFrequencyMhz(160);
    
    // WiFi connect
    WiFi.begin(ssid, password);
    Serial.print("WiFi connecting");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(250);
    }
    Serial.print("\nWiFi connected: ");
    Serial.println(WiFi.localIP());
    
    // Add custom handler/emitter
    opniz->addHandler({ new DrawpixHandler });
    opniz->addEmitter({ new ButtonEmitter });
    
    // opniz connect
    opniz->connect();
}

void loop() {
    opniz->handleMessage();
    opniz->emitMessage();
}
