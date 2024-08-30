#ifndef EVENTPAYLOADS_H_
#define EVENTPAYLOADS_H_
#include <fstream>
#include <memory>
#include <unordered_map>
#include <cstdint>
#include "events/common.h"
#include "events/game_start.h"
namespace SLPToNP {
  enum PayloadByte {
    PAYLOADS = 0x35,
    GAMESTART = 0x36,
    PREFRAME = 0x37,
    POSTFRAME = 0x38,
    GAMEEND = 0x39,
    FRAMESTART = 0x3A,
    ITEMUPDATE = 0x3B,
    FRAMEBOOKEND = 0x3C,
    GECKOLIST = 0x3D,
    MESSAGESPLITTER = 0x10
  };

  class Payloads : public SLPToNP::Event {
    public:
      void read(std::ifstream &fin);
    private:
      void _readSizeMap(std::ifstream &fin, uint16_t payload_size);
      std::unordered_map<PayloadByte, uint16_t> sizeMap;

  };
}

#endif
