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
		COLOR = 1 << 0,  // 1
		NORMAL = 1 << 1,  // 2
		CAMERA = 1 << 2   // 4
	};

	Shader(GLuint _id, std::string _name);
	void UseShader();
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
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	glm::mat4 projectionMatrix = glm::mat4(1.0f);

	void SetUniforms();
};

