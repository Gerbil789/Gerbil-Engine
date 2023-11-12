#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "../Components/Camera.h"
#include "../Engine/Shader.h"

class ShaderManager
{
public:
	static ShaderManager& GetInstance() {
		static ShaderManager instance; 
		return instance;
	}
	
	void Init();
	void UseShader(GLuint _id);
	GLuint GetShaderProgramId(std::string shader_name);
	Shader* GetShaderProgram(GLuint _id);
	std::vector<Shader*> GetShaderPrograms();

	void SetUniform(const char* _uniform, const glm::mat3& _value);
	void SetUniform(const char* _uniform, const glm::mat4& _value);
	void SetUniform(const char* _uniform, const glm::vec3& _value);
	void SetUniform(const char* _uniform, const int& _value);
	void SetUniform(const char* _uniform, const GLuint& _value);
	void SetUniform(const char* _uniform, const float& _value);
private:
	int currentShaderId = -1;
	bool initialized = false;
	

	ShaderManager() {};
	void CheckShaderCompilation(GLuint shader, const std::string& shaderType);
	void CheckProgramLinking(GLuint program);
	std::vector<Shader*> shaderPrograms;
	std::string ReadShaderSource(const std::string& filePath);
	Shader* CreateShader(std::string _name, std::string vertexShaderPath, std::string fragmentShaderPath);

};



