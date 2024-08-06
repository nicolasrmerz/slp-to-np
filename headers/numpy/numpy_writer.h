#ifndef NUMPYWRITER_H_
#define NUMPYWRITER_H_

namespace SLPToNP {
  enum NumpyType {U8, U16, U32, I8, I16, I32, F32, F64};
  enum NumpyEndian {BIG_ENDIAN, LITTLE_ENDIAN};

  class NumpyWriter {
    public:
      void writeHeader(const char* filename, NumpyType numpyType);
  };
}
#endif
