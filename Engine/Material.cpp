#include "Material.h"


Material::Material(std::string path, std::string _name)
{
	name = _name;
	textureID = LoadTexture(path);
}

bool endsWith(const std::string& str, const std::string& suffix) {
	if (str.length() >= suffix.length()) {
		return (0 == str.compare(str.length() - suffix.length(), suffix.length(), suffix));
	}
	else {
		return false;
	}
}


GLuint Material::LoadTexture(std::string path)
{
	GLuint id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	int width, height, channels;
	unsigned char* data = ImageLoader::LoadImage(path, width, height, channels);
	if (!data) {
		std::cerr << "Failed to load texture\n";
	}
	if (endsWith(path, ".jpg") || endsWith(path, ".jpeg")) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else if (endsWith(path, ".png") ) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else {
		std::cout << "File does not end with .jpg or .png" << std::endl;
	}

	
	glGenerateMipmap(GL_TEXTURE_2D);

	ImageLoader::FreeImage(data);
	return id;
}

