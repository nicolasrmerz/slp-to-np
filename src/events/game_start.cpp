#include "events/common.h"
#include "events/game_start.h"

void SLPToNP::GameStart::read(std::ifstream &fin) {
  fin.read(reinterpret_cast<char*>(&gameStartStruct), payloadSize);
}
