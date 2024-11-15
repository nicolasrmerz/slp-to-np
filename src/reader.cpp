#include "utils/endian.h"
#include "events/game_start.h"
#include "reader.h"
#include "slp.h"
#include <sys/stat.h>
#include <cstring>
static constexpr uint8_t ubjson_magic_bytes[] = {
  0x7B, 0x55, 0x03, 0x72, 0x61, 0x77, 0x5B, 0x24, 0x55, 0x23, 0x6C, 
};

SLPToNP::ReaderException::ReaderException(const char * msg) : message(msg) {}

const char * SLPToNP::ReaderException::what() const throw () {
  return message.c_str();
}

SLPToNP::Reader::Reader(const char* filename) {
  struct stat buffer;   
  if (stat (filename, &buffer) != 0) {
    throw SLPToNP::ReaderException("Filename does not exist.");
  }
  fin.open(filename);
  // payloads = std::make_unique<SLPToNP::Payloads>();
  // gameStart = std::make_unique<SLPToNP::GameStart>();
}

SLPToNP::Reader::~Reader() {
  fin.close();
}

void SLPToNP::Reader::_read_ubjson_header() {
  // [{][U][3][r][a][w][[][$][U][#][l]
  uint8_t buf[std::size(ubjson_magic_bytes)] = {0};
  fin.read(reinterpret_cast<char*>(buf), std::size(ubjson_magic_bytes));
  if(memcmp(ubjson_magic_bytes, buf, std::size(ubjson_magic_bytes)) != 0)
    throw SLPToNP::ReaderException("Did not find expected UBJSON bytes at start of file.");

  fin.read(reinterpret_cast<char*>(&slpLen), sizeof(slpLen));
  slpLen = endian_swap_32(slpLen);
}


void SLPToNP::Reader::_readLoop(std::shared_ptr<SLPToNP::SLP> slp) {
  SLPToNP::PayloadByte payloadByte{};
  while(true) {
    payloadByte = static_cast<SLPToNP::PayloadByte>(fin.peek());

    switch(payloadByte)
    {
    case SLPToNP::GAMESTART:
      // gameStart->read(fin);
      slp->readGameStart(fin);
      break;
    // TODO: These are placeholders while they are not implemented
    case SLPToNP::PREFRAME:
    case SLPToNP::POSTFRAME:
    case SLPToNP::FRAMESTART:
    case SLPToNP::ITEMUPDATE:
    case SLPToNP::FRAMEBOOKEND:
      slp->readFrameData(fin);
      break;
    case SLPToNP::GAMEEND:
    case SLPToNP::GECKOLIST:
    case SLPToNP::MESSAGESPLITTER:
      // fin.ignore(payloads->getPayloadSize(payloadByte)+1);
      fin.ignore(slp->getPayloadSize(payloadByte)+1);
      break;
    default:
      return;
    }
  }
}

void SLPToNP::Reader::read() {
  std::shared_ptr<SLPToNP::SLP> slp = std::make_shared<SLPToNP::SLP>();
  _read_ubjson_header();

  slp->readPayload(fin);
  slp->setFrameAllocationEstimate(slpLen);

  _readLoop(slp);
}
