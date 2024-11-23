#ifndef EVENTCOMMON_H_
#define EVENTCOMMON_H_
#include <map>
#include <cstdint>
#include <fstream>

namespace SLPToNP {
  class Event {
    public:
      virtual void read(std::ifstream &fin) = 0;
      void setPayloadSize(uint16_t size);
      void writeNPFloats(std::ofstream &fout);
      int32_t getFrameNumber();
      // virtual void read(std::ifstream stream) = 0;
      // virtual void writeNPFloats(std::ofstream stream) = 0;
    protected:
      std::map<int32_t, long> writeOffsets;
      uint16_t payloadSize{0};
      int32_t frameNumber{0};
  };
}
#endif
