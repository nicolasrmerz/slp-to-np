#include <cstdint>
#include "slp.h"
#include "events/payloads.h"
#include <vector>

SLPToNP::SLPException::SLPException(const char * msg) : message(msg) {}

const char * SLPToNP::SLPException::what() const throw () {
  return message.c_str();
}

SLPToNP::SLP::SLP() {
  gameStart = std::make_unique<SLPToNP::GameStart>();
  gameEnd = std::make_unique<SLPToNP::GameEnd>();
  payloads = std::make_unique<SLPToNP::Payloads>();
  frames = std::make_unique<SLPToNP::FrameWrapper>();
}

SLPToNP::SLP::SLP(int32_t startFrame, int32_t endFrame) {
  gameStart = std::make_unique<SLPToNP::GameStart>();
  gameEnd = std::make_unique<SLPToNP::GameEnd>();
  payloads = std::make_unique<SLPToNP::Payloads>();
  if (startFrame < minFrame && endFrame < minFrame) {
    frames = std::make_unique<SLPToNP::FrameWrapper>();
  } else {
    frames = std::make_unique<SLPToNP::FrameWrapper>(startFrame, endFrame);
  }
}

SLPToNP::SLP::~SLP() {
}

void SLPToNP::SLP::_verifyAndSetPayloadSizes() {
  gameStart->setPayloadSize(payloads);

  gameEnd->setPayloadSize(payloads);
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
  uint32_t frameEstimate{};
  // If frames has been initialized with a start and end frame, we only need a vector of that length
  if (frames->getFrameSubsetLength() > -1) {
    frameEstimate = static_cast<uint32_t>(frames->getFrameSubsetLength());
  } else {
    frameEstimate = estimateFrameAllocation(binarySize);
  }

  frames->allocateVectors(frameEstimate);
}

uint16_t SLPToNP::SLP::getPayloadSize(SLPToNP::PayloadByte payloadByte) {
  return payloads->getPayloadSize(payloadByte);
}

void SLPToNP::SLP::readGameStart(std::ifstream &fin) {
  gameStart->read(fin);
}

void SLPToNP::SLP::readGameEnd(std::ifstream &fin) {
  gameEnd->read(fin);
}

void SLPToNP::SLP::readPayload(std::ifstream &fin) {
  payloads->read(fin);

  _verifyAndSetPayloadSizes();

}

bool SLPToNP::SLP::readFrameData(std::ifstream &fin) {
  return frames->read(fin, payloads);
}

void SLPToNP::SLP::readMetadata(std::ifstream &fin) {
  auto curr_location = fin.tellg();
  fin.seekg(0, fin.end);
  auto end_location = fin.tellg();
  // there is a final closing bracket matching the one at the start of the binary
  // if not ignored, from_ubjson throws an error
  int ubjson_len = end_location - curr_location - 1;
  fin.seekg(curr_location, std::ios::beg);

  std::vector<std::byte> ubjson_bytes (ubjson_len); // Use parentheses so that we construct a vector of a certain size
  fin.read( reinterpret_cast<char*>(ubjson_bytes.data()), static_cast<long>(ubjson_len) );

  metadata = nlohmann::json::from_ubjson(ubjson_bytes);
}