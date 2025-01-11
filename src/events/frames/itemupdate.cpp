#include "events/frames/itemupdate.h"
#include "utils/endian.h"

SLPToNP::ItemUpdate::ItemUpdate(std::ifstream &fin, uint16_t payloadSize) {
  fin.read(reinterpret_cast<char*>(&itemUpdateStruct), payloadSize);
  frameNumber = endian_swap_32(itemUpdateStruct.frame_number);
}

std::size_t SLPToNP::ItemUpdate::getInternalStructSize() {
  return sizeof(ItemUpdateStruct);
}

SLPToNP::PayloadByte SLPToNP::ItemUpdate::getPayloadByte() {
  return static_cast<SLPToNP::PayloadByte>(itemUpdateStruct.command_byte);
}

std::string_view SLPToNP::ItemUpdate::getEventName() {
  return "Item Update";
}