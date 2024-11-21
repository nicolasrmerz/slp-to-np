#include "events/frames/preframe.h"

SLPToNP::PreFrame::PreFrame(std::ifstream &fin, uint16_t payloadSize) {
  fin.read(reinterpret_cast<char*>(&preFrameStruct), payloadSize);
}
