#include "Shader.h"
#include "../Components/Camera.h"


Shader::Shader(GLuint _id, std::string _name)
{
	id = _id;
    name = _name;
}



void Shader::UpdateObserver(ISubject* _subject)
{
    if (Camera* cam = dynamic_cast<Camera*>(_subject)) {
        camPosition = cam->transform->GetPosition();
        projectionMatrix = cam->GetProjectionMatrix();
        viewMatrix = cam->GetViewMatrix();
    }
    else {
        std::cout << "[Shader.cpp] ERROR: dynamic cast failed\n";
    }
}






