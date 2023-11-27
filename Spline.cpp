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

    

    if (closedLoop) {
      controlPoints.push_back(controlPoints[0]);
    }

    int n = static_cast<int>(controlPoints.size()) - 1;
   

    glm::vec3 p(0.0f);

    for (int i = 0; i <= n; ++i) {
        float coeff = factorial(n) / (factorial(i) * factorial(n - i));
        float term = coeff * glm::pow(t, i) * glm::pow(1.0f - t, n - i);
        p += term * controlPoints[i];
    }

    if (closedLoop) {
      controlPoints.pop_back();
    }

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
