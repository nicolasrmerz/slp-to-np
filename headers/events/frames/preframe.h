#ifndef EVENTFRAMESPREFRAME_H_
#define EVENTFRAMESPREFRAME_H_
#include "events/common.h"

namespace SLPToNP {
  class PreFrame : public SLPToNP::Event {
    void read(std::ifstream &fin) {};
  };
}

#endif