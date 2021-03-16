#include "lib/utils/M5AtomUtil.h"

// M5Atom初期化
void initM5Atom() {
    M5.begin(true, false, true);
    M5.dis.setBrightness(10);
    setCpuFrequencyMhz(80);
    
    Serial.println();
    delay(100);
}
