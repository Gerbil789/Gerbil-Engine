#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <string>
#include <vector>
#include <iostream>

#include "Observer.h"

class Camera;

class Shader : public IObserver
{
public:
	enum FLAGS {
		NORMAL = 1 << 0,	// 1
		CAMERA = 1 << 1,	// 2
		SPECULAR = 1 << 2,  // 4
		LIGHTS = 1 << 3		// 8

	};

	Shader(GLuint _id, std::string _name);
	void UseShader(glm::mat4 transformMatrix, glm::vec4 color, float specular);
	GLuint id;
	std::string name;
	
	void SetCamSubject(Camera* _camSubject);
	void UpdateObserver() override;

	void SetFlag(FLAGS _flag);
	void RemoveFlag(FLAGS _flag);
	bool IsFlagSet(FLAGS _flag);
private:
	int flags;
	Camera* camSubject;
	glm::vec3 camPosition = glm::vec3(1.0f);
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	glm::mat4 projectionMatrix = glm::mat4(1.0f);

	void SetUniforms(glm::mat4 transformMatrix, glm::vec4 color, float specular = 16.0f);
};

