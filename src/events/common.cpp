#include "events/common.h"

void SLPToNP::Event::setPayloadSize(uint16_t size) {
  payloadSize = size;
}

int32_t SLPToNP::Event::getFrameNumber() {
  return frameNumber;
}