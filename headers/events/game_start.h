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

  struct __attribute__((__packed__)) GameStartVersionStruct {
    uint8_t major{0};
    uint8_t minor{0};
    uint8_t build{0};
    uint8_t unused{0};
  };

  struct __attribute__((__packed__)) GameStartStruct {
    uint8_t command_byte{0x36};
    struct GameStartVersionStruct game_start_version;
    uint8_t game_info_block[312] = {0};
    uint32_t random_seed{0};
    struct DashbackShieldDropFixesStruct dashback_fix[4] = {};
    uint16_t nametag[4*8] = {0};
    uint8_t pal{0};
    uint8_t frozen_ps{0};
    uint8_t minor_scene{0};
    uint8_t major_scene{0};
    uint8_t display_name[4*31] = {0};
    uint8_t connect_code[4*10] = {0};
    uint8_t slippi_uid[4*29] = {0};
    uint8_t language_option{1};
    uint8_t match_id[51] = {0};
    uint32_t game_number{1};
    uint32_t tiebreaker_number{0};
  };

  class GameStart : public SLPToNP::Event {
    public:
      void read(std::ifstream &fin);

    protected:
      GameStartStruct gameStartStruct{};
  };
}

#endif
