#include "reader.h"
#include <cstring>
#include <iostream>
static constexpr uint8_t ubjson_magic_bytes[] = {
  0x7B, 0x55, 0x03, 0x72, 0x61, 0x77, 0x5B, 0x24, 0x55, 0x23, 0x6C, 
};

SLPToNP::ReaderException::ReaderException(const char * msg) : message(msg) {}

const char * SLPToNP::ReaderException::what() {
  return message.c_str();
}

SLPToNP::Reader::Reader(const char* filename) {
  fin.open(filename);
}

SLPToNP::Reader::~Reader() {
  fin.close();
}

void SLPToNP::Reader::_read_ubjson() {
  // [{][U][3][r][a][w][[][$][U][#][l]
  uint8_t buf[std::size(ubjson_magic_bytes)] = {0};
  fin.read((char*) buf, std::size(ubjson_magic_bytes));
  if(memcmp(ubjson_magic_bytes, buf, std::size(ubjson_magic_bytes)) != 0)
    throw SLPToNP::ReaderException("Did not find expected UBJSON bytes at start of file.");
}

void SLPToNP::Reader::read() {
  _read_ubjson();
}
