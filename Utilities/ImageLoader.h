#pragma once
#include <string>

class ImageLoader
{
public:
	static ImageLoader& GetInstance() {
		static ImageLoader instance;
		return instance;
	}

	static unsigned char* LoadImage(const std::string& filePath, int& width, int& height, int& channels);
	static void FreeImage(unsigned char* image);
private:
	ImageLoader() {}
};

