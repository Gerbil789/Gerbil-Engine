#pragma once
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <GL/glew.h>

class ImageLoader
{
public:
	static ImageLoader& GetInstance() {
		static ImageLoader instance;
		return instance;
	}
	static GLuint LoadTexture(std::string path);
	static unsigned char* LoadImage(const std::string& filePath, int& width, int& height, int& channels);
	static void FreeImage(unsigned char* image);
private:
	ImageLoader() {}
};

