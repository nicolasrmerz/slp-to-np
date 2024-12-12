#include "events/frames/postframe.h"
#include "utils/endian.h"

SLPToNP::PostFrame::PostFrame(std::ifstream &fin, uint16_t payloadSize) {
  fin.read(reinterpret_cast<char*>(&postFrameStruct), payloadSize);
  frameNumber = endian_swap_32(postFrameStruct.frame_number);
  playerIndex = postFrameStruct.player_index;
}

uint8_t SLPToNP::PostFrame::getPlayerIndex() {
  return playerIndex;
}