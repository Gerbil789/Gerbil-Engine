#include "ImageLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

unsigned char* ImageLoader::LoadImage(const std::string& filePath, int& width, int& height, int& channels)
{
    return stbi_load(filePath.c_str(), &width, &height, &channels, 0);
}

void ImageLoader::FreeImage(unsigned char* image)
{
	stbi_image_free(image);
}
