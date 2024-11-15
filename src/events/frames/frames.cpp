#include "events/frames/frames.h"

void SLPToNP::FrameWrapper::allocateVectors(uint32_t allocateSize) {
  preFrames.reserve(allocateSize);
  postFrames.reserve(allocateSize);
  frameStarts.reserve(allocateSize);
  itemUpdates.reserve(allocateSize);
  frameBookends.reserve(allocateSize);
      
}


void SLPToNP::FrameWrapper::read(std::ifstream &fin) {

}