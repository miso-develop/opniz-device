#include "lib/utils/Esp32Util.h"

// ヒープメモリがしきい値を下回ったら再起動
void watchHeap() {
    const int freeHeapThreshold = 51200;
    if (esp_get_minimum_free_heap_size() < freeHeapThreshold) esp_restart();
}
