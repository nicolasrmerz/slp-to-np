#ifndef READER_H_
#define READER_H_
#include <map>
#include <cstdint>
#include <fstream>
#include "events/game_start.h"
#include "events/payloads.h"

namespace SLPToNP {
  class ReaderException : public std::exception {
    public:
      ReaderException(const char * msg);
      const char * what();
    private:
      std::string message;
  };

  class Reader {
    public:
      Reader(const char* filename);
      ~Reader();
      void read();
    private:
      std::ifstream fin;
      SLPToNP::Payloads payloads;
      SLPToNP::GameStart gameStart;
      void _read_ubjson();
  };
}
#endif
