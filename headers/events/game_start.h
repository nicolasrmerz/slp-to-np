#ifndef EVENTGAMESTART_H_
#define EVENTGAMESTART_H_
#include "events/common.h"
#include <cstdint>
#include <fstream>

namespace SLPToNP {
  struct __attribute__((__packed__)) DashbackShieldDropFixesStruct {
    uint32_t dashback_fix{};
    uint32_t shield_drop_fix{};
  };

  struct __attribute__((__packed__)) GameStartStruct {
    uint8_t command_byte{0x36};
    uint8_t version[4] = {0,0,0,0};
    uint8_t game_info_block[312] = {0};
    uint32_t random_seed{0};
    struct DashbackShieldDropFixesStruct dashback_fix[4] = {};
    uint16_t nametag[4*8] = {0};
    uint8_t pal{0};
    uint8_t frozen_ps{0};

  };

  class GameStart : public SLPToNP::Event {
    public:
      void read(std::ifstream &fin);

    protected:
      GameStartStruct gameStartStruct{};
  };
}

#endif
