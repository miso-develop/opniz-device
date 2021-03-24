#ifndef M5ATOM_H
#define M5ATOM_H

#include <M5Atom.h>

#include "devices/Esp32.h"

namespace Opniz { // MEMO: 本家M5Atomと名前衝突してしまったのでnamespaceで回避
    class M5Atom : public Esp32 {
    public:
        M5Atom(const char* address, uint16_t port);
        ~M5Atom() {};
        
        class DrawpixHandler : public BaseHandler {
        public:
            String getName() override { return "drawpix"; };
            String handle(JsonObject json) override;
        };
        
        class ButtonEmitter : public BaseEmitter {
        public:
            boolean canEmit() override;
            String emit() override;
        };
    };
}

#endif
