#ifndef EVENTFRAMES_H_
#define EVENTFRAMES_H_
#include "payloads.h"
#include "events/common.h"
#include "events/frames/preframe.h"
#include "events/frames/postframe.h"
#include "events/frames/framestart.h"
#include "events/frames/itemupdate.h"
#include "events/frames/framebookend.h"
#include <cstdint>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
namespace SLPToNP {
  class FrameWrapperException : public std::exception {
    public:
      FrameWrapperException(const char * msg);
      const char * what() const throw ();
    private:
      std::string message;
  };

  class FrameWrapper {
    public:
      FrameWrapper();
      FrameWrapper(int32_t startFrame, int32_t endFrame);
      bool read(std::ifstream &fin, const std::unique_ptr<SLPToNP::Payloads> & payloads);
      void allocateVectors(uint32_t allocateSize);
      int32_t getFrameSubsetLength();

    private:
      // 1 vector per potential player
      std::vector<std::shared_ptr<SLPToNP::PreFrame>> preFrames[4];
      std::vector<std::shared_ptr<SLPToNP::PostFrame>> postFrames[4];

      std::vector<std::shared_ptr<SLPToNP::FrameStart>> frameStarts;
      std::vector<std::shared_ptr<SLPToNP::ItemUpdate>> itemUpdates;
      std::vector<std::shared_ptr<SLPToNP::FrameBookend>> frameBookends;
      void _checkFrameStartEnd(int32_t start_frame, int32_t end_frame);
      void _checkPlayerIndex(const char * frameType, int32_t frameNumber, uint8_t playerIndex);
      int32_t startFrame;
      int32_t endFrame;
      bool frameNumberStartExists{};
      bool frameNumberEndExists{};
      template <typename T>
      bool _addFrame(std::shared_ptr<T> event, std::vector<std::shared_ptr<T>> & eventVector, int32_t frameNumber);
  };
}
template <typename T>
bool SLPToNP::FrameWrapper::_addFrame(std::shared_ptr<T> event, std::vector<std::shared_ptr<T>> & eventVector, int32_t frameNumber) {
  if (frameNumberStartExists && frameNumber < startFrame) {
    return true;
  }

  // Max rollback is 7 frames - conservatively, if we're over 8 frames,
  // we've finalized the range we're interested in
  if (frameNumberEndExists && frameNumber >= endFrame + 8) {
    return false;
  }

  // Frames start at -123
  auto zeroIdxFrameNumber{static_cast<typename std::vector<std::shared_ptr<T>>::size_type>(frameNumber + 123)};
  // If we're skipping frames, ensure we start at idx 0
  zeroIdxFrameNumber -= (startFrame * frameNumberStartExists);
  if (zeroIdxFrameNumber < eventVector.size()) {
    eventVector[zeroIdxFrameNumber] = event;
  } else {
    eventVector.push_back(event);
  }

  return true;

}

#endif
