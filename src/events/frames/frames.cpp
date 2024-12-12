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

void SLPToNP::FrameWrapper::_checkPlayerIndex(const char * frameType, int32_t frameNumber, uint8_t playerIndex) {
  if (playerIndex >= 4) {
    std::string errMessage{};
    errMessage += frameType;
    errMessage += " player_index must be between 0 and 3 (inclusive). " ;
    errMessage += frameType;
    errMessage += " ";
    errMessage += std::to_string(frameNumber);
    errMessage += " had player_index of ";
    errMessage += std::to_string(playerIndex);
    errMessage += ".\n";

    throw SLPToNP::FrameWrapperException(errMessage.c_str());

  }
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
      int32_t frameNumber{preFrame->getFrameNumber()};
      _checkPlayerIndex("PreFrame", frameNumber, playerIndex);
      _addFrame(preFrame, preFrames[playerIndex]);
    }
    break;

    case SLPToNP::POSTFRAME:
    {
      std::shared_ptr<SLPToNP::PostFrame> postFrame = std::make_shared<SLPToNP::PostFrame>(fin, payloadSize);
      uint8_t playerIndex{postFrame->getPlayerIndex()};
      int32_t frameNumber{postFrame->getFrameNumber()};
      _checkPlayerIndex("PostFrame", frameNumber, playerIndex);
      _addFrame(postFrame, postFrames[playerIndex]);
    }
    break;

    case SLPToNP::FRAMESTART:
    {
      std::shared_ptr<SLPToNP::FrameStart> frameStart = std::make_shared<SLPToNP::FrameStart>(fin, payloadSize);
      _addFrame(frameStart, frameStarts);
    }
    break;
    case SLPToNP::ITEMUPDATE:
    {
      std::shared_ptr<SLPToNP::ItemUpdate> itemUpdate = std::make_shared<SLPToNP::ItemUpdate>(fin, payloadSize);
      _addFrame(itemUpdate, itemUpdates);
    }
    break;
    case SLPToNP::FRAMEBOOKEND:
    {
      std::shared_ptr<SLPToNP::FrameBookend> frameBookend = std::make_shared<SLPToNP::FrameBookend>(fin, payloadSize);
      _addFrame(frameBookend, frameBookends);
    }
    break;
    default:
      return;
  }

}