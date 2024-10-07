#include <cstdint>
#include "slp.h"

SLPToNP::SLPException::SLPException(const char * msg) : message(msg) {}

const char * SLPToNP::SLPException::what() const throw () {
  return message.c_str();
}

SLPToNP::SLP::SLP() {
  payloads = std::make_unique<SLPToNP::Payloads>();
  gameStart = std::make_unique<SLPToNP::GameStart>();
}

SLPToNP::SLP::~SLP() {
}

void SLPToNP::SLP::_verifyAndSetPayloadSizes() {
  std::string errString{};
  uint16_t payloadSize{};

  payloadSize = payloads->getGameStartSize();
  if (payloadSize > sizeof(SLPToNP::GameStartStruct)) {
    errString += "GameStart, ";
  }
  // To read the extra byte
  gameStart->setPayloadSize(payloadSize+1);

  if (errString.size()) {
    std::string errMessage("Size specified in binary for payload(s) " + errString + " was/were larger than internal struct(s).");
    throw SLPToNP::SLPException(errMessage.c_str());
  }
}

uint16_t SLPToNP::SLP::getPayloadSize(SLPToNP::PayloadByte payloadByte) {
  return payloads->getPayloadSize(payloadByte);
}

void SLPToNP::SLP::readGameStart(std::ifstream &fin) {
  gameStart->read(fin);
}

void SLPToNP::SLP::readPayload(std::ifstream &fin) {
  payloads->read(fin);

  _verifyAndSetPayloadSizes();

}
