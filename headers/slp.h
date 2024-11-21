#ifndef SLP_H_
#define SLP_H_
#include <map>
#include <cstdint>
#include <fstream>
#include <memory>
#include "events/game_start.h"
#include "events/payloads.h"
#include "events/frames/frames.h"

namespace SLPToNP {
  class SLPException : public std::exception {
    public:
      SLPException(const char * msg);
      const char * what() const throw ();
    private:
      std::string message;
  };

  class SLP {
    public:
      SLP();
      ~SLP();
      void readPayload(std::ifstream &fin);
      void readGameStart(std::ifstream &fin);
      void readFrameData(std::ifstream &fin);
      uint16_t getPayloadSize(SLPToNP::PayloadByte payloadByte);
      uint32_t estimateFrameAllocation(uint32_t binarySize);
      void setFrameAllocationEstimate(uint32_t binarySize);
    private:
      std::shared_ptr<SLPToNP::Payloads> payloads;
      std::unique_ptr<SLPToNP::GameStart> gameStart;
      std::unique_ptr<SLPToNP::FrameWrapper> frames;
      void _verifyAndSetPayloadSizes();
      void _readLoop();
  };
}
#endif
