#include "events/frames/framestart.h"
#include "utils/endian.h"

SLPToNP::FrameStart::FrameStart(std::ifstream &fin, uint16_t payloadSize) {
  fin.read(reinterpret_cast<char*>(&frameStartStruct), payloadSize);
  frameNumber = endian_swap_32(frameStartStruct.frame_number);
}

std::size_t SLPToNP::FrameStart::getInternalStructSize() {
  return sizeof(FrameStartStruct);
}

SLPToNP::PayloadByte SLPToNP::FrameStart::getPayloadByte() {
  return static_cast<SLPToNP::PayloadByte>(frameStartStruct.command_byte);
}

std::string_view SLPToNP::FrameStart::getEventName() {
  return "Frame Start";
}