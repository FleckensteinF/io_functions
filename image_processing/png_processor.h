#ifndef _PNG_PROCESSOR_H_
#define _PNG_PROCESSOR_H_

#include <png.h>
#include <iostream>
#include <fstream>
#include <vector>

using std::vector;

//class PngProcessor{
// public:
  struct PngWithInfo{
    int width, height;
    png_byte color_type;
    png_byte bit_depth;

    int number_of_passes;
    //png_bytep * row_pointers;
    unsigned char header[8];    // 8 is the maximum size that can be checked
    vector<float> data;
    bool error;
  };
//
//  PngProcessor();

  PngWithInfo readPngFile(const char* file_name);
  void writePngFile(const char* file_name, const PngWithInfo& png);

//};

#endif // _PNG_PROCESSOR_H_
