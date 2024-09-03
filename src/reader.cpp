#include "utils/endian.h"
#include "events/game_start.h"
#include "reader.h"
#include <cstring>
static constexpr uint8_t ubjson_magic_bytes[] = {
  0x7B, 0x55, 0x03, 0x72, 0x61, 0x77, 0x5B, 0x24, 0x55, 0x23, 0x6C, 
};

SLPToNP::ReaderException::ReaderException(const char * msg) : message(msg) {}

const char * SLPToNP::ReaderException::what() {
  return message.c_str();
}

SLPToNP::Reader::Reader(const char* filename) {
  fin.open(filename);
  payloads = std::make_unique<SLPToNP::Payloads>();
  gameStart = std::make_unique<SLPToNP::GameStart>();
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

void SLPToNP::Reader::_verifyAndSetPayloadSizes() {
  std::string errString{};
  uint16_t payloadSize{};

  payloadSize = payloads->getGameStartSize();
  if (payloadSize > sizeof(SLPToNP::GameStartStruct)) {
    errString += "GameStart, ";
  }
  // To read the extra byte
  gameStart->setPayloadSize(payloadSize+1);

  if (errString.size()) {
    std::string errMessage("Size specified in binary for payload(s) " + errString + " was/were larger than internal struct(s).");
    throw SLPToNP::ReaderException(errMessage.c_str());
  }
}

void SLPToNP::Reader::_readLoop() {
  SLPToNP::PayloadByte payloadByte{};
  while(true) {
    payloadByte = static_cast<SLPToNP::PayloadByte>(fin.peek());

    switch(payloadByte)
    {
    case SLPToNP::GAMESTART:
      gameStart->read(fin);
      break;
    // TODO: These are placeholders while they are not implemented
    case SLPToNP::PREFRAME:
    case SLPToNP::POSTFRAME:
    case SLPToNP::GAMEEND:
    case SLPToNP::FRAMESTART:
    case SLPToNP::ITEMUPDATE:
    case SLPToNP::FRAMEBOOKEND:
    case SLPToNP::GECKOLIST:
    case SLPToNP::MESSAGESPLITTER:
      fin.ignore(payloads->getPayloadSize(payloadByte)+1);
      break;
    default:
      return;
    }
  }
}

void SLPToNP::Reader::read() {
  _read_ubjson_header();
  payloads->read(fin);

  _verifyAndSetPayloadSizes();

  _readLoop();
}
