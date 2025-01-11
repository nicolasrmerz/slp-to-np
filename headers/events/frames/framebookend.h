#ifndef EVENTFRAMESFRAMEBOOKEND_H_
#define EVENTFRAMESFRAMEBOOKEND_H_
#include "events/common.h"

namespace SLPToNP {
  struct __attribute__((__packed__)) FrameBookendStruct {
    uint8_t command_byte{0x3C};
    int32_t frame_number{};
    int32_t latest_finalized_frame{};
  };

  class FrameBookend : public SLPToNP::Event {
    public:
      FrameBookend(std::ifstream &fin, uint16_t payloadSize);
      void read(std::ifstream &fin) {};
      std::size_t getInternalStructSize();
      std::string_view getEventName();
      SLPToNP::PayloadByte getPayloadByte();
    private:
      FrameBookendStruct frameBookendStruct{};
  };
}

#endif