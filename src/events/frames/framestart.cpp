#include "events/frames/framestart.h"
#include "utils/endian.h"

SLPToNP::FrameStart::FrameStart(std::ifstream &fin, uint16_t payloadSize) {
  fin.read(reinterpret_cast<char*>(&frameStartStruct), payloadSize);
  frameNumber = endian_swap_32(frameStartStruct.frame_number);
}
