#include "numpy/numpy_writer.h"
#include "reader.h"

#include <xtensor/xarray.hpp>
#include <xtensor/xnpy.hpp>

int main()
{
  // SLPToNP::NumpyWriter npWriter;
  //
  // npWriter.writeHeader("test.npy", SLPToNP::U8);

  SLPToNP::Reader reader("/home/nicolasmerz/Documents/slp-to-np/samples/offline.slp");
  reader.read();
  // SLPToNP::Reader reader;
  return 0;
}
