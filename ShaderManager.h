#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class ShaderManager
{
public:
	static ShaderManager& getInstance() {
		static ShaderManager instance; 
		return instance;
	}
	
	void Init();
	void UseShader(int shaderID);
	std::vector<std::pair<std::string, GLuint>> shaderPrograms;

private:
	ShaderManager() {};
	void CheckShaderCompilation(GLuint shader, const std::string& shaderType);
	void CheckProgramLinking(GLuint program);
	int currentShader = -1;
	bool initialized = false;
	std::string ReadShaderSource(const std::string& filePath);
	GLuint CreateShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath);
};


