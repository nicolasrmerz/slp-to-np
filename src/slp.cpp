#include <cstdint>
#include "slp.h"
#include "events/payloads.h"
#include <iostream>
#include <vector>

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

uint32_t SLPToNP::SLP::estimateFrameAllocation(uint32_t binarySize) {
  uint32_t singleFrameSize{0};
  uint32_t repeatFrameSize{0};
  std::vector<SLPToNP::PayloadByte> singleFrames = {SLPToNP::PAYLOADS, SLPToNP::GAMESTART, SLPToNP::GAMEEND};
  std::vector<SLPToNP::PayloadByte> repeatFrames = {SLPToNP::PREFRAME, SLPToNP::POSTFRAME, SLPToNP::FRAMESTART, SLPToNP::ITEMUPDATE, SLPToNP::FRAMEBOOKEND};

  for (auto & singleFrameByte : singleFrames) {
    singleFrameSize += payloads->getPayloadSize(singleFrameByte);
  }

  for (auto & repeatFrameByte : repeatFrames) {
    repeatFrameSize += payloads->getPayloadSize(repeatFrameByte);
  }

  return (binarySize - singleFrameSize) / repeatFrameSize;
}

void SLPToNP::SLP::setFrameAllocationEstimate(uint32_t binarySize) {
  uint32_t frameEstimate = estimateFrameAllocation(binarySize);

  frames->allocateVectors(frameEstimate);
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

void SLPToNP::SLP::readFrameData(std::ifstream &fin) {
  frames->read(fin);
}