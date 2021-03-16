#include "lib/utils/Color.h"

const CRGB str2crgb(String color) {
    return strtoll(&color[1], NULL, 16) & 0xffffff;
}
