#include "events/common.h"
#include "events/game_end.h"

void SLPToNP::GameEnd::read(std::ifstream &fin) {
  fin.read(reinterpret_cast<char*>(&gameEndStruct), payloadSize);
}

std::size_t SLPToNP::GameEnd::getInternalStructSize() {
  return sizeof(GameEndStruct);
}

SLPToNP::PayloadByte SLPToNP::GameEnd::getPayloadByte() {
  return static_cast<SLPToNP::PayloadByte>(gameEndStruct.command_byte);
}

std::string_view SLPToNP::GameEnd::getEventName() {
  return "Game End";
}