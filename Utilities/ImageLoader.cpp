#include "ImageLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

unsigned char* ImageLoader::LoadImage(const std::string& filePath, int& width, int& height, int& channels)
{
  unsigned char* image = stbi_load(filePath.c_str(), &width, &height, &channels, 0);

  // Allocate memory for the flipped image
  unsigned char* flippedImage = new unsigned char[width * height * channels];

  // Flip the image horizontally
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      for (int c = 0; c < channels; c++) {
        flippedImage[((height - 1 - y) * width + x) * channels + c] = image[(y * width + x) * channels + c];
      }
    }
  }

  


  return flippedImage;
}

void ImageLoader::FreeImage(unsigned char* image)
{
	stbi_image_free(image);
}
