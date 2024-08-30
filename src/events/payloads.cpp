#include <fstream>
#include "events/payloads.h"
#include "utils/endian.h"
#include "reader.h"

void SLPToNP::Payloads::_readSizeMap(std::ifstream &fin, uint16_t payloadSize) {
  if((payloadSize % 3) != 0)
    throw SLPToNP::ReaderException("Read payload size is not divisible by 3.");

  for(unsigned int i{0}; i < payloadSize/3; i++) {
    uint8_t payload_byte{};
    uint16_t payload_size{};
    fin.read(reinterpret_cast<char*>(&payload_byte), sizeof(uint8_t));
    fin.read(reinterpret_cast<char*>(&payload_size), sizeof(uint16_t));
    payload_size = endian_swap_16(payload_size);

    sizeMap[static_cast<SLPToNP::PayloadByte>(payload_byte)] = payload_size;
  }
}

void SLPToNP::Payloads::read(std::ifstream &fin) {
  uint8_t payloadByte{};
  uint16_t remainingPayloadSize{};

  fin.read(reinterpret_cast<char*>(&payloadByte), sizeof(uint8_t));
  if(payloadByte != SLPToNP::PAYLOADS)
    throw SLPToNP::ReaderException("Did not find expected payload byte (0x35) at start of payloads payload.");

  fin.read(reinterpret_cast<char*>(&remainingPayloadSize), sizeof(uint8_t));

  // The payload size includes the one byte that we just read - read the reamining n-1 bytes
  _readSizeMap(fin, remainingPayloadSize - 1);
}

