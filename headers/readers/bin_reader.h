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
  class BinReaderException : public std::exception {
    public:
      BinReaderException(const char * msg);
      const char * what() const throw ();
    private:
      std::string message;
  };

  class BinReader {
    public:
      BinReader(const char* filename);
      std::unique_ptr<SLPToNP::SLP> read();
      std::unique_ptr<SLPToNP::SLP> read(int32_t startFrame, int32_t endFrame);
      uint32_t getNumFrames();
    private:
      std::unique_ptr<SLPToNP::SLP> slp;
      uint32_t slpLen;
      std::ifstream fin;
      void _read_ubjson_header();
      //void _readLoop(std::unique_ptr<SLPToNP::SLP> slp);
      void _readLoop();
      void readMetadata_(const std::unique_ptr<SLPToNP::SLP> &);
  };
}
#endif
