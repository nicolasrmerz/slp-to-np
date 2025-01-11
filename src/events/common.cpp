#include "events/common.h"

SLPToNP::EventException::EventException(const char * msg) : message(msg) {}

const char * SLPToNP::EventException::what() const throw () {
  return message.c_str();
}

void SLPToNP::Event::setPayloadSize(uint16_t size) {
  payloadSize = size;
}

int32_t SLPToNP::Event::getFrameNumber() {
  return frameNumber;
}

void SLPToNP::Event::setPayloadSize(const std::unique_ptr<SLPToNP::Payloads> & payloads) {
  uint16_t payloadSize = payloads->getPayloadSize(getPayloadByte());
  std::size_t structSize = getInternalStructSize();
  if (payloadSize > structSize) {
    throw SLPToNP::EventException(std::string("Size specified in binary for " + std::string(getEventName()) + " payload was larger than internal struct.").c_str());
  }
  // To read the extra byte
  setPayloadSize(payloadSize+1);

}
