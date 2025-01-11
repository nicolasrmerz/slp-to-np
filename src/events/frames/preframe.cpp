#include "events/frames/preframe.h"
#include "utils/endian.h"

SLPToNP::PreFrame::PreFrame(std::ifstream &fin, uint16_t payloadSize) {
  fin.read(reinterpret_cast<char*>(&preFrameStruct), payloadSize);
  frameNumber = endian_swap_32(preFrameStruct.frame_number);
  playerIndex = preFrameStruct.player_index;
}

uint8_t SLPToNP::PreFrame::getPlayerIndex() {
  return playerIndex;
}

std::size_t SLPToNP::PreFrame::getInternalStructSize() {
  return sizeof(PreFrameStruct);
}

SLPToNP::PayloadByte SLPToNP::PreFrame::getPayloadByte() {
  return static_cast<SLPToNP::PayloadByte>(preFrameStruct.command_byte);
}

std::string_view SLPToNP::PreFrame::getEventName() {
  return "Pre Frame";
}