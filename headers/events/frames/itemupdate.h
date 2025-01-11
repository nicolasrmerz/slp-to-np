#ifndef EVENTFRAMESITEMUPDATE_H_
#define EVENTFRAMESITEMUPDATE_H_
#include "events/common.h"

namespace SLPToNP {
  struct __attribute__((__packed__)) ItemUpdateStruct {
    uint8_t command_byte{0x3A};
    int32_t frame_number{};
    uint16_t type_id{};
    uint8_t state{};
    float facing_direction{};
    float x_velocity{};
    float y_velocity{};
    float x_position{};
    float y_position{};
    uint16_t damage_taken{};
    float expiration_timer{};
    uint32_t spawn_id{};
    uint8_t misc_1{};
    uint8_t misc_2{};
    uint8_t misc_3{};
    uint8_t misc_4{};
    int8_t owner{};
    uint16_t instance_id{};
  };

  class ItemUpdate : public SLPToNP::Event {
    public:
      ItemUpdate(std::ifstream &fin, uint16_t payloadSize);
      void read(std::ifstream &fin) {};
      std::size_t getInternalStructSize();
      std::string_view getEventName();
      SLPToNP::PayloadByte getPayloadByte();
    private:
      ItemUpdateStruct itemUpdateStruct{};
  };
}

#endif