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
      FrameWrapper(std::shared_ptr<SLPToNP::Payloads> payloads);
      // FrameWrapper(const std::shared_ptr<SLPToNP::Payloads> & payloads);
      //~FrameWrapper();
      void read(std::ifstream &fin);
      void allocateVectors(uint32_t allocateSize);

    private:
      // 1 vector per potential player
      std::vector<std::shared_ptr<SLPToNP::PreFrame>> preFrames[4];
      std::vector<std::shared_ptr<SLPToNP::PostFrame>> postFrames[4];

      std::vector<std::shared_ptr<SLPToNP::FrameStart>> frameStarts;
      std::vector<std::shared_ptr<SLPToNP::ItemUpdate>> itemUpdates;
      std::vector<std::shared_ptr<SLPToNP::FrameBookend>> frameBookends;
      std::shared_ptr<SLPToNP::Payloads> payloads;
      void _checkPlayerIndex(const char * frameType, int32_t frameNumber, uint8_t playerIndex);
      template <typename T>
      void _addFrame(std::shared_ptr<T> event, std::vector<std::shared_ptr<T>> & eventVector);
  };
}
template <typename T>
void SLPToNP::FrameWrapper::_addFrame(std::shared_ptr<T> event, std::vector<std::shared_ptr<T>> & eventVector) {
  // Frames start at -123
  auto zeroIdxFrameNumber{static_cast<typename std::vector<std::shared_ptr<T>>::size_type>(event->getFrameNumber() + 123)};
  if (zeroIdxFrameNumber < eventVector.size()) {
    eventVector[zeroIdxFrameNumber] = event;
  } else {
    eventVector.push_back(event);
  }

}

#endif
