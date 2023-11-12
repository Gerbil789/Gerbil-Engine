#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include "../ImageLoader.h"

class Material
{
public:
	Material(std::string path = "Textures/test_grid.png", std::string _name = "material");
	std::string name;
	glm::vec3 ambient = glm::vec3(0.05f);
	glm::vec3 diffuse = glm::vec3(1.0f);
	glm::vec3 specular = glm::vec3(1.0f);
	float shininess = 16.0f;

	GLuint textureID = 0;


	void LoadTexture(std::string path);
};

