#ifndef EVENTFRAMESFRAMESTART_H_
#define EVENTFRAMESFRAMESTART_H_
#include "events/common.h"

namespace SLPToNP {
  class FrameStart : public SLPToNP::Event {
    void read(std::ifstream &fin) {};
  };
}

#endif