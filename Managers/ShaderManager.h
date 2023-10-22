#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "../Components/Camera.h"
#include "../Shader.h"

class ShaderManager
{
public:
	static ShaderManager& GetInstance() {
		static ShaderManager instance; 
		return instance;
	}
	
	void Init();
	void UseShader(GLuint _id, glm::mat4 transformMatrix, glm::vec4 color, float specular);
	GLuint GetShaderProgram(std::string shader_name);
	void SetCamForShaders(Camera* _cam);

private:
	ShaderManager() {};
	void CheckShaderCompilation(GLuint shader, const std::string& shaderType);
	void CheckProgramLinking(GLuint program);
	int currentShader = -1;
	bool initialized = false;
	std::vector<Shader*> shaderPrograms;
	std::string ReadShaderSource(const std::string& filePath);
	Shader* CreateShader(std::string _name, std::string vertexShaderPath, std::string fragmentShaderPath);

};



