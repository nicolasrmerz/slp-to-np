#include "events/frames/frames.h"
#include "events/payloads.h"
#include <string>

SLPToNP::FrameWrapperException::FrameWrapperException(const char * msg) : message(msg) {}

const char * SLPToNP::FrameWrapperException::what() const throw () {
  return message.c_str();
}

SLPToNP::FrameWrapper::FrameWrapper() {
  frameNumberStartExists = false;
  frameNumberEndExists = false;
  startFrame = -124;
  endFrame = -124;
}

void SLPToNP::FrameWrapper::_checkFrameStartEnd(int32_t start_frame, int32_t end_frame) {

  if (start_frame >= -123 && end_frame >= -123) {
    if (end_frame <= start_frame) {
      std::string errMessage{};
      errMessage += "Starting frame number must be before ending frame number. Starting number was " ;
      errMessage += std::to_string(start_frame);
      errMessage += ", ending number was ";
      errMessage += std::to_string(end_frame);
      errMessage += ".\n";

      throw SLPToNP::FrameWrapperException(errMessage.c_str());

    }
  }
}

SLPToNP::FrameWrapper::FrameWrapper(int32_t start_frame, int32_t end_frame) {
  _checkFrameStartEnd(start_frame, end_frame);

  startFrame = start_frame;
  endFrame = end_frame;
  if (startFrame >= -123) {
    frameNumberStartExists = true;
  }

  if (endFrame >= -123) {
    frameNumberEndExists = true;
  }
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

int32_t SLPToNP::FrameWrapper::getFrameSubsetLength() {
  if (!frameNumberStartExists || !frameNumberEndExists) {
    return -1;
  }

  return endFrame - startFrame;
}

bool SLPToNP::FrameWrapper::read(std::ifstream &fin, const std::unique_ptr<SLPToNP::Payloads> & payloads) {
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
      return _addFrame(preFrame, preFrames[playerIndex], frameNumber);
    }

    case SLPToNP::POSTFRAME:
    {
      std::shared_ptr<SLPToNP::PostFrame> postFrame = std::make_shared<SLPToNP::PostFrame>(fin, payloadSize);
      uint8_t playerIndex{postFrame->getPlayerIndex()};
      int32_t frameNumber{postFrame->getFrameNumber()};
      _checkPlayerIndex("PostFrame", frameNumber, playerIndex);
      return _addFrame(postFrame, postFrames[playerIndex], frameNumber);
    }

    case SLPToNP::FRAMESTART:
    {
      std::shared_ptr<SLPToNP::FrameStart> frameStart = std::make_shared<SLPToNP::FrameStart>(fin, payloadSize);
      int32_t frameNumber{frameStart->getFrameNumber()};
      return _addFrame(frameStart, frameStarts, frameNumber);
    }

    case SLPToNP::ITEMUPDATE:
    {
      std::shared_ptr<SLPToNP::ItemUpdate> itemUpdate = std::make_shared<SLPToNP::ItemUpdate>(fin, payloadSize);
      int32_t frameNumber{itemUpdate->getFrameNumber()};
      return _addFrame(itemUpdate, itemUpdates, frameNumber);
    }

    case SLPToNP::FRAMEBOOKEND:
    {
      std::shared_ptr<SLPToNP::FrameBookend> frameBookend = std::make_shared<SLPToNP::FrameBookend>(fin, payloadSize);
      int32_t frameNumber{frameBookend->getFrameNumber()};
      return _addFrame(frameBookend, frameBookends, frameNumber);
    }

    default:
      return false;
  }

}