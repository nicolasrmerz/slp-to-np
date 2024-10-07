#ifndef SLP_H_
#define SLP_H_
#include <map>
#include <cstdint>
#include <fstream>
#include <memory>
#include "events/game_start.h"
#include "events/payloads.h"

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
      uint16_t getPayloadSize(SLPToNP::PayloadByte payloadByte);
    private:
      std::unique_ptr<SLPToNP::Payloads> payloads;
      std::unique_ptr<SLPToNP::GameStart> gameStart;
      void _verifyAndSetPayloadSizes();
      void _readLoop();
  };
}
#endif
