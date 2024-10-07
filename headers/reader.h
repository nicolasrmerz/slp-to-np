#ifndef READER_H_
#define READER_H_
#include <map>
#include <cstdint>
#include <fstream>
#include <memory>
#include "events/game_start.h"
#include "events/payloads.h"
#include "slp.h"

namespace SLPToNP {
  class ReaderException : public std::exception {
    public:
      ReaderException(const char * msg);
      const char * what() const throw ();
    private:
      std::string message;
  };

  class Reader {
    public:
      Reader(const char* filename);
      ~Reader();
      void read();
    private:
      uint32_t slpLen;
      std::ifstream fin;
      void _read_ubjson_header();
      void _readLoop(std::shared_ptr<SLPToNP::SLP> slp);
  };
}
#endif
