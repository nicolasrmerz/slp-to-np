#ifndef EVENTCOMMON_H_
#define EVENTCOMMON_H_
#include <map>
#include <cstdint>
#include <fstream>

namespace SLPToNP {
  class Event {
    public:
      void read(std::ifstream stream);
      void writeNPFloats(std::ofstream stream);
      // virtual void read(std::ifstream stream) = 0;
      // virtual void writeNPFloats(std::ofstream stream) = 0;
    protected:
      std::map<int32_t, long> writeOffsets;
  };
}
#endif
