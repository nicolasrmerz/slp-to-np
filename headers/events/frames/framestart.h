#ifndef EVENTFRAMESFRAMESTART_H_
#define EVENTFRAMESFRAMESTART_H_
#include "events/common.h"

namespace SLPToNP {
  struct __attribute__((__packed__)) FrameStartStruct {
    uint8_t command_byte{0x3A};
    int32_t frame_number{};
    uint32_t random_seed{};
    uint32_t scene_frame_counter{};
  };

  class FrameStart : public SLPToNP::Event {
    public:
      FrameStart(std::ifstream &fin, uint16_t payloadSize);
      void read(std::ifstream &fin) {};
    private:
      FrameStartStruct frameStartStruct{};
  };
}

#endif