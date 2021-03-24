#include "devices/base/BaseDevice.h"

BaseDevice::BaseDevice(const char* address, uint16_t port) : TcpManager(address, port), _responseJsonDoc(1024) {}

String BaseDevice::_messageHandler(String message) {
    const JsonArray jsonArray = _jsonParser.parseArray(message);
    JsonArray responseJsonArray = _responseJsonDoc.to<JsonArray>();
    for (JsonObject json : jsonArray) {
        BaseHandler* handler = _handlers[json["name"]];
        String response = (boolean)handler ? handler->handle(json) : "notmatch";
        responseJsonArray.add(response);
    }
    return _jsonParser.stringify(_responseJsonDoc);
};

void BaseDevice::handleMessage() {
    receive(_messageHandlerFunction);
}

void BaseDevice::emitMessage() {
    for (BaseEmitter* emitter : _emitters) {
        if (emitter->canEmit()) {
            // MEMO: デバイスからのイベントを瞬間的に同時に受け取ることがあり、その場合`{...}{...}`のようなメッセージとなりJSON.parseでエラーとなる。
            // MEMO: それを回避するため必ずオブジェクト末尾に`,`を付与し`{...},`の形でデバイスからメッセージを送り、Server側にて`[]`で括り配列にする。
            send(emitter->emit() + ",");
        }
    }
}

void BaseDevice::addHandler(std::vector<BaseHandler*> handlers) {
    for (BaseHandler* handler : handlers) _handlers[handler->getName().c_str()] = handler;
}

void BaseDevice::addEmitter(std::vector<BaseEmitter*> emitters) {
    copy(emitters.begin(), emitters.end(), back_inserter(_emitters));
}
