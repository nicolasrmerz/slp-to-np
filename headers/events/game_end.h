#ifndef EVENTGAMEEND_H_
#define EVENTGAMEEND_H_
#include "events/common.h"
#include <cstdint>
#include <fstream>

namespace SLPToNP {
  struct __attribute__((__packed__)) GameEndStruct {
    uint8_t command_byte{0x39};
    uint8_t game_end_method{};
    int8_t lras_initiator{};
    int8_t player_placements[4] = {0};
  };

  class GameEnd : public SLPToNP::Event {
    public:
      void read(std::ifstream &fin);

    protected:
      GameEndStruct gameEndStruct{};
  };
}

#endif
