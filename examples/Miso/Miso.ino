#include <Opniz.h>
#include <lib/WiFiConnector.h>
#include <lib/Utils.h>

// WiFi
const char* ssid = "<SSID>";         // WiFiのSSIDに書き換え
const char* password = "<PASSWORD>"; // WiFiのパスワードに書き換え
WiFiConnector wifi(ssid, password);

// opniz
const char* address = "192.168.0.1"; // Node.js SDKを実行する端末のIPアドレスを指定
const uint16_t port = 3000;          // 任意のポート番号を指定（opniz Node.js SDKでの指定と合わせる）
Opniz::M5Atom* opniz = new Opniz::M5Atom(address, port); // opnizインスタンス生成



void keepAlive() {
    rebootWhenHeap(); // ヒープメモリがしきい値を下回ったら再起動
    wifi.connect();   // WiFi接続チェック
    opniz->connect(); // Node.js SDK実行端末との接続チェック
}



void setup() {
    // M5初期化、M5ATOM推奨設定
    M5.begin(true, false, true);
    M5.dis.setBrightness(10);
    setCpuFrequencyMhz(160);
    
    // WiFi接続
    wifi.setTimeoutCallback([]() { esp_restart(); });
    wifi.setConnectingSignal(blinkBlue);
    wifi.connect();
    
    // Node.js SDK実行端末へ接続
    opniz->setTimeoutCallback([]() { wifi.reconnect(); });
    opniz->setConnectingSignal(blinkYellow);
    opniz->connect();
}

void loop() {
    opniz->handleMessage(); // opnizハンドラー
    opniz->emitMessage();   // opnizエミッター
    
    keepAlive(); // ヒープメモリ、WiFi接続、opniz接続を監視
    
    delay(1);
}
