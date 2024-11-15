#ifndef EVENTFRAMESPOSTFRAME_H_
#define EVENTFRAMESPOSTFRAME_H_
#include "events/common.h"

namespace SLPToNP {
  class PostFrame : public SLPToNP::Event {
    void read(std::ifstream &fin) {};
  };
}

#endif