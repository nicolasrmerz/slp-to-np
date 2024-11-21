#include "events/frames/frames.h"
#include "events/payloads.h"


SLPToNP::FrameWrapper::FrameWrapper(std::shared_ptr<SLPToNP::Payloads> payloads) {
  this->payloads = payloads;
}

void SLPToNP::FrameWrapper::allocateVectors(uint32_t allocateSize) {
  preFrames.reserve(allocateSize);
  postFrames.reserve(allocateSize);
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
      _addFrame(preFrame, preFrames);
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