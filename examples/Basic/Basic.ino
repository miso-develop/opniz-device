#include <Opniz.h>

// Static IP address
IPAddress ip(192, 168, 0, 2);
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(192,168, 0, 1);
IPAddress DNS(1, 1, 1, 1);

// WiFi
const char* ssid = "<SSID>";
const char* password = "<PASSWORD>";

// opniz
const char* address = "192.168.0.3";
const uint16_t port = 3000;
Opniz::M5Atom* opniz = new Opniz::M5Atom(address, port);



void setup() {
    // M5 init
    M5.begin(true, false, true);
    M5.dis.setBrightness(10);
    setCpuFrequencyMhz(160);
    
    // WiFi connect
    WiFi.config(ip, gateway, subnet, DNS);
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
