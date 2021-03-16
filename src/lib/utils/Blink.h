#ifndef BLINK_H
#define BLINK_H

#include <M5Atom.h>

auto blink = [](boolean state, long color) { M5.dis.drawpix(0, state ? color : 0x000000); };
auto blinkRed = [](boolean state) { blink(state, 0x00ff00); };
auto blinkGreen = [](boolean state) { blink(state, 0xff0000); };
auto blinkBlue = [](boolean state) { blink(state, 0x0000ff); };
auto blinkYellow = [](boolean state) { blink(state, 0xffff00); };

#endif
