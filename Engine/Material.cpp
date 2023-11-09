#include "Material.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

Material::Material()
{
	LoadTexture();
}

void Material::LoadTexture(std::string path)
{

	glGenTextures(1, &this->textureID);
	glBindTexture(GL_TEXTURE_2D, this->textureID);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	int width, height, channels;
	unsigned char* image_data = stbi_load(path.c_str(), &width, &height, &channels, 4);
	if (!image_data) {
		std::cerr << "Failed to load texture\n";
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	//free memory
	stbi_image_free(image_data);
}
