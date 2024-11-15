#ifndef EVENTFRAMESITEMUPDATE_H_
#define EVENTFRAMESITEMUPDATE_H_
#include "events/common.h"

namespace SLPToNP {
  class ItemUpdate : public SLPToNP::Event {
    void read(std::ifstream &fin) {};
  };
}

#endif