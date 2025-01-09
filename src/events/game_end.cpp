#include "events/common.h"
#include "events/game_end.h"

void SLPToNP::GameEnd::read(std::ifstream &fin) {
  fin.read(reinterpret_cast<char*>(&gameEndStruct), payloadSize);
}
