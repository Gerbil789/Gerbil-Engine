#include "Shader.h"
#include "../Components/Camera.h"


Shader::Shader(GLuint _id, std::string _name)
{
	id = _id;
    name = _name;
}

void Shader::SetCamSubject(Camera* _camSubject)
{
    camSubject = _camSubject;
    camSubject->Attach(this);
}

void Shader::UpdateObserver()
{
	camPosition = camSubject->transform->GetPosition();
    projectionMatrix = camSubject->GetProjectionMatrix();
    viewMatrix = camSubject->GetViewMatrix();
}





