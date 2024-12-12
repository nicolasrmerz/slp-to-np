#ifndef EVENTFRAMESPOSTFRAME_H_
#define EVENTFRAMESPOSTFRAME_H_
#include "events/common.h"

namespace SLPToNP {
  struct __attribute__((__packed__)) PostFrameStruct {
    uint8_t command_byte{0x38};
    int32_t frame_number{};
    uint8_t player_index{};
    uint8_t is_follower{};
    uint8_t internal_character_id{};
    uint16_t action_state_id{};
    float x_position{};
    float y_position{};
    float facing_direction{};
    float percent{};
    float shield_size{};
    uint8_t last_hitting_attack_id{};
    uint8_t current_combo_count{};
    uint8_t last_hit_by{};
    uint8_t stocks_remaining{};
    float action_state_frame_counter{};
    uint8_t state_bit_flags_1{};
    uint8_t state_bit_flags_2{};
    uint8_t state_bit_flags_3{};
    uint8_t state_bit_flags_4{};
    uint8_t state_bit_flags_5{};
    float misc_as{};
    uint8_t ground_air_state{};
    uint16_t last_ground_id{};
    uint8_t jumps_remaining{};
    uint8_t l_cancel_status{};
    uint8_t hurtbox_collision_state{};
    float self_induced_air_x_speed{};
    float self_induced_air_y_speed{};
    float attack_based_x_speed{};
    float attack_based_y_speed{};
    float self_induced_ground_x_speed{};
    float hitlag_frames_remaining{};
    uint32_t animation_index{};
    uint16_t instance_hit_by{};
    uint16_t instance_id{};
  };

  class PostFrame : public SLPToNP::Event {
    public:
      PostFrame(std::ifstream &fin, uint16_t payloadSize);
      void read(std::ifstream &fin) {};
      uint8_t getPlayerIndex();
    private:
      PostFrameStruct postFrameStruct{};
      uint8_t playerIndex{0};
  };
}

#endif