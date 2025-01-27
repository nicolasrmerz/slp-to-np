#include "numpy/numpy_writer.h"
#include "readers/bin_reader.h"
#include <ctime>
#include <iostream>

#include <xtensor/xarray.hpp>
#include <xtensor/xnpy.hpp>

int main()
{
  // SLPToNP::NumpyWriter npWriter;
  //
  // npWriter.writeHeader("test.npy", SLPToNP::U8);

  //SLPToNP::Reader reader("/home/nicolasmerz/Documents/slp-to-np/samples/offline_2.slp");
  std::ifstream file("file_list.txt");
  std::string str;
  auto start = std::time(nullptr);
  while (std::getline(file, str))
  {
    try {
      SLPToNP::BinReader reader(str.c_str());
      // std::unique_ptr<SLPToNP::SLP> slp = reader.read(250, 550);
      std::unique_ptr<SLPToNP::SLP> slp = reader.read();
    } catch (const SLPToNP::BinReaderException &e) {
      std::cerr << e.what() << "\n";
    }
  }
  auto end = std::time(nullptr);
  // SLPToNP::Reader reader;
  std::cout << end - start << " seconds elapsed.\n";
  return 0;
}
