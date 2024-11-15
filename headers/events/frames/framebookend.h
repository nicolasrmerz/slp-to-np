#ifndef EVENTFRAMESFRAMEBOOKEND_H_
#define EVENTFRAMESFRAMEBOOKEND_H_
#include "events/common.h"

namespace SLPToNP {
  class FrameBookend : public SLPToNP::Event {
    void read(std::ifstream &fin) {};
  };
}

#endif