#include "Material.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

Material::Material(std::string path, bool skybox)
{
	if (skybox) 
	{
		std::vector<std::string> faces
		{
				"Textures/cubemap/negx.jpg",
				"Textures/cubemap/negy.jpg",
				"Textures/cubemap/negz.jpg",
				"Textures/cubemap/posx.jpg",
				"Textures/cubemap/posy.jpg",
				"Textures/cubemap/posz.jpg"
		};
		LoadSkyboxTexture(faces);
	}
	else 
	{
		LoadTexture(path);
	}
	
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

void Material::LoadSkyboxTexture(std::vector<std::string> faces)
{
	glGenTextures(1, &this->textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureID);

	int width, height, channels;
	
	for (GLuint i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &channels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cerr << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	/*glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);*/
}
