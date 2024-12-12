#include "events/frames/itemupdate.h"
#include "utils/endian.h"

SLPToNP::ItemUpdate::ItemUpdate(std::ifstream &fin, uint16_t payloadSize) {
  fin.read(reinterpret_cast<char*>(&itemUpdateStruct), payloadSize);
  frameNumber = endian_swap_32(itemUpdateStruct.frame_number);
}
