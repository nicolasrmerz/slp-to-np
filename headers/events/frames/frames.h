#ifndef EVENTFRAMES_H_
#define EVENTFRAMES_H_
#include "events/common.h"
#include "events/frames/preframe.h"
#include "events/frames/postframe.h"
#include "events/frames/framestart.h"
#include "events/frames/itemupdate.h"
#include "events/frames/framebookend.h"
#include <cstdint>
#include <fstream>
#include <vector>
namespace SLPToNP {
  class FrameWrapper {
    public:
      void read(std::ifstream &fin);
      void allocateVectors(uint32_t allocateSize);

    protected:
      std::vector<SLPToNP::PreFrame> preFrames;
      std::vector<SLPToNP::PostFrame> postFrames;
      std::vector<SLPToNP::FrameStart> frameStarts;
      std::vector<SLPToNP::ItemUpdate> itemUpdates;
      std::vector<SLPToNP::FrameBookend> frameBookends;
  };
}

#endif
