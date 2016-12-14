#include <png.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "png_processor.h"

using std::vector;

/*PngProcessor::PngProcessor():
  error(false)
{

}*/

//PngProcessor::PngWithInfo PngProcessor::readPngFile(const char* file_name){
PngWithInfo readPngFile(const char* file_name){
  PngWithInfo png;

  /* open file and test for it being a png */
  FILE *fp = fopen(file_name, "rb");
  if (!fp){
    std::cerr << "file " << file_name  << " could not be opened" << std::endl;
    png.error = true;
    return png;
  }
  fread(png.header, 1, 8, fp);
  if (png_sig_cmp(png.header, 0, 8)){
    //abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);
    std::cerr << "could not parse header" << std::endl;
    png.error = true;
    return png;
  }

  /* initialize stuff */
  png_structp png_ptr;
  png_infop info_ptr;
  png_bytep* row_pointers;

  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr){
    std::cerr << "png_create_read_struct failed" << std::endl;
    png.error = true;
    return png;
  }
  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr){
    std::cerr <<  "png_create_info_struct failed" << std::endl;
    png.error = true;
    return png;
  }
  if (setjmp(png_jmpbuf(png_ptr))){
    std::cerr << "Error during init_io" << std::endl;
    png.error = true;
    return png;
  }
  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, 8);

  png_read_info(png_ptr, info_ptr);

  png.width = png_get_image_width(png_ptr, info_ptr);
  png.height = png_get_image_height(png_ptr, info_ptr);
  png.color_type = png_get_color_type(png_ptr, info_ptr);
  png.bit_depth = png_get_bit_depth(png_ptr, info_ptr);

  png.number_of_passes = png_set_interlace_handling(png_ptr);
  png_read_update_info(png_ptr, info_ptr);

  if(png.bit_depth != 16){
    std::cerr << "error parsing" << file_name << ": wrong bit_depth of " << png.bit_depth << std::endl;
    png.error = true;
    return png;
  }

  /* read file */
  if (setjmp(png_jmpbuf(png_ptr))){
    //abort_("[read_png_file] Error during read_image");
    std::cerr << "Error during read_image" << std::endl;
    png.error = true;
    return png;
  }
  row_pointers = new png_bytep[png.height];
  for (int y = 0; y < png.height; y++){
    row_pointers[y] = new png_byte[png_get_rowbytes(png_ptr, info_ptr)];
  }
  png_read_image(png_ptr, row_pointers);

  fclose(fp);
  int number_of_bytes = png.bit_depth/8;
  png.data.resize(png.width * png.height);

  for (int y = 0; y < png.height; y++) {
    png_byte* row = row_pointers[y];
    for (int x = 0; x < png.width; x++) {
      png_byte* ptr = &(row[x * number_of_bytes]);
      uint16_t pixel = ptr[1];
      pixel <<= 8;
      pixel += ptr[0];
      png.data[y * png.width + x] = (float)pixel;
    }
  }

  for (int y = 0; y < png.height; y++){
    delete row_pointers[y];
  }
  delete row_pointers;
  return png;
}


inline void setRGB(png_byte *ptr, float val)
{
  int v = (int)(val * 767);
  if (v < 0) v = 0;
  if (v > 767) v = 767;
  int offset = v % 256;

  if (v<256) {
    ptr[0] = 0; ptr[1] = 0; ptr[2] = offset;
  }
  else if (v<512) {
    ptr[0] = 0; ptr[1] = offset; ptr[2] = 255-offset;
  }
  else {
    ptr[0] = offset; ptr[1] = 255-offset; ptr[2] = 0;
  }
}


//int writePngFile(char* filename, const PngProcessor::PngWithInfo& png){
int writePngFile(char* filename, const PngWithInfo& png){
  int code = 0;
  FILE *fp = NULL;
  png_structp png_ptr = NULL;
  png_infop info_ptr = NULL;
  png_bytep row = NULL;
  // Open file for writing (binary mode)
  fp = fopen(filename, "wb");
  if (fp == NULL) {
    fprintf(stderr, "Could not open file %s for writing\n", filename);
    code = 1;
    goto finalise;
  }
  // Initialize write structure
  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (png_ptr == NULL) {
    fprintf(stderr, "Could not allocate write struct\n");
    code = 1;
    goto finalise;
  }

  // Initialize info structure
  info_ptr = png_create_info_struct(png_ptr);
  if (info_ptr == NULL) {
    fprintf(stderr, "Could not allocate info struct\n");
    code = 1;
    goto finalise;
  }
  // Setup Exception handling
  if (setjmp(png_jmpbuf(png_ptr))) {
    fprintf(stderr, "Error during png creation\n");
    code = 1;
    goto finalise;
  }
  png_init_io(png_ptr, fp);

  // Write header (8 bit colour depth)
  png_set_IHDR(png_ptr, info_ptr, png.width, png.height,
	       8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
	       PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  // Set title
  //if (title != NULL) {
  //  png_text title_text;
  //  title_text.compression = PNG_TEXT_COMPRESSION_NONE;
  //  title_text.key = "Title";
  //  title_text.text = title;
  //  png_set_text(png_ptr, info_ptr, &title_text, 1);
  //}

  png_write_info(png_ptr, info_ptr);

  // Allocate memory for one row (3 bytes per pixel - RGB)
  row = (png_bytep) malloc(3 * png.width * sizeof(png_byte));

  // Write image data
  int x, y;
  for (y = 0 ; y < png.height ; y++) {
    for (x = 0 ; x < png.width ; x++) {
      setRGB(&(row[x * 3]), png.data[y * png.width + x]);
    }
    png_write_row(png_ptr, row);
  }

  // End write
  png_write_end(png_ptr, NULL);

 finalise:
  if (fp != NULL) fclose(fp);
  if (info_ptr != NULL) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
  if (png_ptr != NULL) png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
  if (row != NULL) free(row);

  return code;
}
