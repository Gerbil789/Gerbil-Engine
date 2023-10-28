#pragma once
#include <string>
#include <glm/glm.hpp>

class Material
{
public:
	std::string name = "material";
	glm::vec3 ambient = glm::vec3(0.1f);
	glm::vec3 diffuse = glm::vec3(1.0f);
	glm::vec3 specular = glm::vec3(1.0f);
	float shininess = 16.0f;
};

