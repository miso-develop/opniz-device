#include "devices/base/BaseDevice.h"

BaseDevice::BaseDevice(const char* address, uint16_t port) : TcpManager(address, port), _responseJsonDoc(1024) {}

String BaseDevice::_messageHandler(String message) {
    const JsonArray jsonArray = _jsonParser.parseArray(message);
    JsonArray responseJsonArray = _responseJsonDoc.to<JsonArray>();
    for (JsonObject json : jsonArray) {
        String response = "notmatch";
        for (BaseHandler* handler : _handlerList) {
            if (handler->canHandle(json)) {
                response = handler->handle(json);
                break;
            }
        }
        responseJsonArray.add(response);
    }
    return _jsonParser.stringify(_responseJsonDoc);
};

void BaseDevice::handleMessage() {
    receive(_messageHandlerFunction);
}

void BaseDevice::emitMessage() {
    for (BaseEmitter* emitter : _emitterList) {
        if (emitter->canEmit()) {
            // MEMO: デバイスからのイベントを瞬間的に同時に受け取ることがあり、その場合`{...}{...}`のようなメッセージとなりJSON.parseでエラーとなる。
            // MEMO: それを回避するため必ずオブジェクト末尾に`,`を付与し`{...},`の形でデバイスからメッセージを送り、Server側にて`[]`で括り配列にする。
            send(emitter->emit() + ",");
        }
    }
}

void BaseDevice::addHandlerList(std::vector<BaseHandler*> handlerList) {
    copy(handlerList.begin(), handlerList.end(), back_inserter(_handlerList));
}

void BaseDevice::addEmitterList(std::vector<BaseEmitter*> emitterList) {
    copy(emitterList.begin(), emitterList.end(), back_inserter(_emitterList));
}
