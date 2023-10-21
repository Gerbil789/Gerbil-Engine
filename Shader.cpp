#include "Shader.h"
#include "../Components/Camera.h"

Shader::Shader(GLuint _id, std::string _name)
{
	id = _id;
    name = _name;
    flags = 0;
}

void Shader::UseShader(glm::mat4 transformMatrix, glm::vec4 color)
{
	SetUniforms(transformMatrix, color);
	glUseProgram(id);
}

void Shader::SetUniforms(glm::mat4 transformMatrix, glm::vec4 color)
{
	//transformMatrix
	GLint idModelTransform = glGetUniformLocation(id, "modelMatrix");
	if (idModelTransform == -1) {
		std::cout << "ERROR: could not find model transform location\n";
	}
	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, glm::value_ptr(transformMatrix));

	//color
	GLint idColor = glGetUniformLocation(id, "color");
	if (idColor == -1) {
		std::cerr << "Uniform color not found in shader." << std::endl;
	}
	glUniform4fv(idColor, 1, glm::value_ptr(color));
	//viewMatrix
	GLint idView = glGetUniformLocation(id, "viewMatrix");
	if (idView == -1) {
		std::cout << "ERROR: could not find viewMatrix location\n";
	}
	glUniformMatrix4fv(idView, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	//projectionMatrix
	GLint idProjection = glGetUniformLocation(id, "projectionMatrix");
	if (idProjection == -1) {
		std::cout << "ERROR: could not find projectionMatrix location\n";
	}
	glUniformMatrix4fv(idProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	if (IsFlagSet(NORMAL)) {
		//normalMatrix
		GLint idNormal = glGetUniformLocation(id, "normalMatrix");
		if (idNormal == -1) {
			std::cout << "ERROR: could not find normalMatrix location\n";
		}
		glUniformMatrix3fv(idNormal, 1, GL_FALSE, glm::value_ptr(glm::mat3(1.0f)));
	}

	if (IsFlagSet(CAMERA)) {
		//TO DO: optimize this
		GLint idcam = glGetUniformLocation(id, "cameraPosition");
		if (idcam == -1) {
			std::cout << "ERROR: could not find cameraPosition location\n";
		}
		glUniform3fv(idcam, 1, glm::value_ptr(camSubject->transform->GetPosition()));
	}

	if (IsFlagSet(SPECULAR)) {

		GLint idSpec = glGetUniformLocation(id, "specularStrength");
		if (idSpec == -1) {
			std::cout << "ERROR: could not find specularStrength location\n";
		}
		glUniform1f(idSpec, 16.0f);
	}

	if (IsFlagSet(LIGHTS)) {
		GLint idLight = glGetUniformLocation(id, "lightPosition");
		if (idLight == -1) {
			std::cout << "ERROR: could not find lightPosition location\n";
		}
		glUniform3fv(idLight, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, 0.0f)));
	}
}

void Shader::SetCamSubject(Camera* _camSubject)
{
    camSubject = _camSubject;
    camSubject->Attach(this);
}

void Shader::UpdateObserver()
{
    projectionMatrix = camSubject->GetProjectionMatrix();
    viewMatrix = camSubject->GetViewMatrix();
}



void Shader::SetFlag(FLAGS _flag)
{
    flags |= _flag; // bitwise OR
}

void Shader::RemoveFlag(FLAGS _flag)
{
    flags &= ~_flag; //bitwise AND and bitwise NOT
}

bool Shader::IsFlagSet(FLAGS _flag)
{
    return (flags & _flag) != 0;
}
