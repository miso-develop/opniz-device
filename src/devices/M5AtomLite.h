#ifndef M5ATOM_LITE_H
#define M5ATOM_LITE_H

#include <M5Atom.h>

#include "devices/Esp32Pico.h"

class M5AtomLite : public Esp32Pico {
public:
    M5AtomLite(const char* address, uint16_t port);
    ~M5AtomLite() {};
    
    class DrawpixHandler : public BaseHandler {
    public:
        boolean canHandle(JsonObject json) override;
        String handle(JsonObject json) override;
    };
    
    class ButtonEmitter : public BaseEmitter {
    public:
        boolean canEmit() override;
        String emit() override;
    };
};

#endif
