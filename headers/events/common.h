#ifndef EVENTCOMMON_H_
#define EVENTCOMMON_H_
#include <map>
#include <cstdint>
#include <fstream>
#include <memory>
#include "events/payloads.h"

namespace SLPToNP {
  class EventException : public std::exception {
    public:
      EventException(const char * msg);
      const char * what() const throw ();
    private:
      std::string message;
  };

  class Event {
    public:
      virtual void read(std::ifstream &fin) = 0;
      virtual std::size_t getInternalStructSize() = 0;
      virtual SLPToNP::PayloadByte getPayloadByte() = 0;
      virtual std::string_view getEventName() = 0;
      void setPayloadSize(const std::unique_ptr<SLPToNP::Payloads> & payloads);
      void setPayloadSize(uint16_t size);
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
