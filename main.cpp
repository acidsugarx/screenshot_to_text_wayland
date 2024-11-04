#include <cstdlib>
#include <iostream>
#include <leptonica/allheaders.h>
#include <png.h>
#include <tesseract/baseapi.h>
#include <vector>

void read_png(const char *filename, std::vector<unsigned char> &image_data,
              int &width, int &height) {
  FILE *fp = fopen(filename, "rb");
  if (!fp) {
    throw std::runtime_error("Error opening PNG file");
  }

  png_structp png =
      png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
  png_infop info = png_create_info_struct(png);
  png_init_io(png, fp);
  png_set_sig_bytes(png, 0);
  png_read_info(png, info);

  width = png_get_image_width(png, info);
  height = png_get_image_height(png, info);
  int color_type = png_get_color_type(png, info);
  int bit_depth = png_get_bit_depth(png, info);

  if (bit_depth == 16) {
    png_set_strip_16(png);
  }
  if (color_type == PNG_COLOR_TYPE_PALETTE) {
    png_set_palette_to_rgb(png);
  }
  if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) {
    png_set_expand_gray_1_2_4_to_8(png);
  }
  if (png_get_valid(png, info, PNG_INFO_tRNS)) {
    png_set_tRNS_to_alpha(png);
  }
  png_set_filler(png, 255, PNG_FILLER_AFTER);
  png_read_update_info(png, info);

  image_data.resize(width * height * 4);
  png_bytep rows[height];
  for (int y = 0; y < height; y++) {
    rows[y] = image_data.data() + y * width * 4;
  }
  png_read_image(png, rows);

  png_destroy_read_struct(&png, &info, nullptr);
  fclose(fp);
}

void clipboard_to_png(const std::string &temp_png_file) {
  // Using wl-clipboard to acees the picture from clipboard
  std::string command = "wl-paste --type image/png > " + temp_png_file;
  system(command.c_str());
}

int main() {
  const std::string temp_png_file = "/tmp/screenshot.png";

  // Getting screenshot from clipboard
  clipboard_to_png(temp_png_file);

  // Reading PNG
  std::vector<unsigned char> image_data;
  int width, height;
  read_png(temp_png_file.c_str(), image_data, width, height);

  // Initializing Tesseract
  tesseract::TessBaseAPI *ocr = new tesseract::TessBaseAPI();
  if (ocr->Init(nullptr,
                "eng+rus")) { // Russian + Eng setup
    std::cerr << "Could not initialize tesseract." << std::endl;
    return 1;
  }

  // Creating image via Leptonica from PNG
  Pix *image = pixCreate(width, height, 32); // 32 byte for pixel
  memcpy(pixGetData(image), image_data.data(), image_data.size());

  // Setup image for OCR
  ocr->SetImage(image);
  char *text = ocr->GetUTF8Text();

  // Print text in to CLI
  std::cout << "Extracted Text:\n" << text << std::endl;

  ocr->End();
  pixDestroy(&image);
  delete[] text;

  return 0;
}
