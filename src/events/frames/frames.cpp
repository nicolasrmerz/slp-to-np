#include "events/frames/frames.h"
#include "events/payloads.h"
#include <string>

SLPToNP::FrameWrapperException::FrameWrapperException(const char * msg) : message(msg) {}

const char * SLPToNP::FrameWrapperException::what() const throw () {
  return message.c_str();
}

SLPToNP::FrameWrapper::FrameWrapper(std::shared_ptr<SLPToNP::Payloads> payloads) {
  this->payloads = payloads;
}

void SLPToNP::FrameWrapper::allocateVectors(uint32_t allocateSize) {
  for(int i = 0; i < 4; i++) {
    preFrames[i].reserve(allocateSize);
    postFrames[i].reserve(allocateSize);
  }
  frameStarts.reserve(allocateSize);
  itemUpdates.reserve(allocateSize);
  frameBookends.reserve(allocateSize);
      
}

void SLPToNP::FrameWrapper::read(std::ifstream &fin) {
  SLPToNP::PayloadByte payloadByte{};
  uint16_t payloadSize;
  payloadByte = static_cast<SLPToNP::PayloadByte>(fin.peek());
  payloadSize = payloads->getPayloadSize(payloadByte)+1;
  switch(payloadByte)
    {
    case SLPToNP::PREFRAME: {
      std::shared_ptr<SLPToNP::PreFrame> preFrame = std::make_shared<SLPToNP::PreFrame>(fin, payloadSize);
      uint8_t playerIndex{preFrame->getPlayerIndex()};
      if (playerIndex >= 4) {
        std::string errMessage = "PreFrame player_index must be between 0 and 3 (inclusive). PreFrame ";
        errMessage += std::to_string(preFrame->getFrameNumber());
        errMessage += " had player_index of ";
        errMessage += std::to_string(playerIndex);
        errMessage += ".\n";

        throw SLPToNP::FrameWrapperException(errMessage.c_str());

      }
      _addFrame(preFrame, preFrames[playerIndex]);
    }
    break;

    case SLPToNP::POSTFRAME:
    case SLPToNP::FRAMESTART:
    case SLPToNP::ITEMUPDATE:
    case SLPToNP::FRAMEBOOKEND:
      // slp->readFrameData(fin);
      fin.ignore(payloadSize);
      break;
    default:
      return;
  }

}