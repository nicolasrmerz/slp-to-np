#include "events/frames/framebookend.h"
#include "utils/endian.h"

SLPToNP::FrameBookend::FrameBookend(std::ifstream &fin, uint16_t payloadSize) {
  fin.read(reinterpret_cast<char*>(&frameBookendStruct), payloadSize);
  frameNumber = endian_swap_32(frameBookendStruct.frame_number);
}
