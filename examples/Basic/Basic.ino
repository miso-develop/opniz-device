#include <Opniz.h>

// WiFi
const char* ssid = "<SSID>";
const char* password = "<PASSWORD>";

// opniz
const char* address = "192.168.0.1";
const uint16_t port = 3000;
Opniz::M5AtomLite* opniz = new Opniz::M5AtomLite(address, port);



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
    
    // opniz connect
    opniz->connect();
}

void loop() {
    opniz->handleMessage();
    opniz->emitMessage();
}
