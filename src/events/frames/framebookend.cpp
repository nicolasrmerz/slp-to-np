#include "events/frames/framebookend.h"
#include "utils/endian.h"

SLPToNP::FrameBookend::FrameBookend(std::ifstream &fin, uint16_t payloadSize) {
  fin.read(reinterpret_cast<char*>(&frameBookendStruct), payloadSize);
  frameNumber = endian_swap_32(frameBookendStruct.frame_number);
}

std::size_t SLPToNP::FrameBookend::getInternalStructSize() {
  return sizeof(FrameBookendStruct);
}

SLPToNP::PayloadByte SLPToNP::FrameBookend::getPayloadByte() {
  return static_cast<SLPToNP::PayloadByte>(frameBookendStruct.command_byte);
}

std::string_view SLPToNP::FrameBookend::getEventName() {
  return "Frame Bookend";
}