#include "../Components/MeshRenderer.h"
#include <algorithm>
#include <glm/glm.hpp>
#include "Spline.h"


Spline::Spline(const std::vector<glm::vec3>& _controlPoints, bool _closedLoop)
{
    controlPoints = _controlPoints;
    closedLoop = _closedLoop;
}

glm::vec3 Spline::GetPosition(float t)
{
    t = std::clamp(t, 0.0f, 1.0f);

    int n = controlPoints.size() - 1;
   
    glm::mat4 A = glm::mat4(glm::vec4(
        -1.0, 3.0, -3.0, 1.0),
        glm::vec4(3.0, -6.0, 3.0, 0),
        glm::vec4(-3.0, 3.0, 0, 0),
        glm::vec4(1, 0, 0, 0)
    );

    glm::mat4x3 B;  // Matrix for control points
    for (int i = 0; i <= n; ++i) {
        B[i] = glm::vec3(controlPoints[i]);
    }


    glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);


    glm::vec3 p = parameters * A * glm::transpose(B);
    return p;
}

void Spline::Draw()
{
    for (glm::vec3 pos : controlPoints) {
        GameObject* go = new GameObject("control_point");
        go->AddComponent<MeshRenderer>("sphere", "constant", Color::Blue);
        go->transform->SetScale(glm::vec3(0.2f));
        go->transform->SetPosition(pos);
        this->gameObject->AddChildren(go);

        SceneManager::GetInstance().GetActiveScene()->Add(go);
    }

    for (float t = 0.0f; t <= 1.0f; t += 0.05f) {
        GameObject* go = new GameObject("spline_point");
        go->AddComponent<MeshRenderer>("sphere", "constant", Color::Red);
        go->transform->SetScale(glm::vec3(0.1f));
        go->transform->SetPosition(GetPosition(t));
        this->gameObject->AddChildren(go);

        SceneManager::GetInstance().GetActiveScene()->Add(go);
    }
}
