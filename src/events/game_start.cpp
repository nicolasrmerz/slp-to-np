#include "events/common.h"
#include "events/game_start.h"

void SLPToNP::GameStart::read(std::ifstream &fin) {
  fin.read(reinterpret_cast<char*>(&gameStartStruct), payloadSize);
}

std::size_t SLPToNP::GameStart::getInternalStructSize() {
  return sizeof(GameStartStruct);
}

SLPToNP::PayloadByte SLPToNP::GameStart::getPayloadByte() {
  return static_cast<SLPToNP::PayloadByte>(gameStartStruct.command_byte);
}

std::string_view SLPToNP::GameStart::getEventName() {
  return "Game Start";
}