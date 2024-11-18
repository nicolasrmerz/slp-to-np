#ifndef EVENTFRAMESPREFRAME_H_
#define EVENTFRAMESPREFRAME_H_
#include "events/common.h"

namespace SLPToNP {
  struct __attribute__((__packed__)) PreFrameStruct {
    uint8_t command_byte{0x38};
    int32_t frame_number{};
    uint8_t player_index{};
    uint8_t is_follower{};
    uint32_t random_seed{};
    uint16_t action_state_id{};
    float x_position{};
    float y_position{};
    float facing_direction{};
    float joystick_x{};
    float joystick_y{};
    float c_stick_x{};
    float c_stick_y{};
    float trigger{};
    uint32_t processed_buttons{};
    uint16_t physical_buttons{};
    float physical_l_trigger{};
    float physical_r_trigger{};
    float x_analog_for_ucf{};
    float percent{};
    float y_analog_for_ucf{};
  };

  class PreFrame : public SLPToNP::Event {
    public:
      void read(std::ifstream &fin) {};
    private:
      PreFrameStruct preFrameStruct{};
  };
}

#endif