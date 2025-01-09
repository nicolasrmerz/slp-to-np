#include "numpy/numpy_writer.h"
#include "readers/bin_reader.h"

#include <xtensor/xarray.hpp>
#include <xtensor/xnpy.hpp>

int main()
{
  // SLPToNP::NumpyWriter npWriter;
  //
  // npWriter.writeHeader("test.npy", SLPToNP::U8);

  //SLPToNP::Reader reader("/home/nicolasmerz/Documents/slp-to-np/samples/offline_2.slp");
  SLPToNP::BinReader reader("/home/nicolasmerz/Documents/slp-to-np/samples/netplay.slp");
  try {
    // std::unique_ptr<SLPToNP::SLP> slp = reader.read(725, 750);
    std::unique_ptr<SLPToNP::SLP> slp = reader.read();
  } catch (const SLPToNP::BinReaderException &e) {
    std::cerr << e.what() << "\n";
  }
  // SLPToNP::Reader reader;
  return 0;
}
