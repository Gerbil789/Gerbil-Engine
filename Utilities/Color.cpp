#include "Color.h"

const glm::vec3 Color::Red = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 Color::Green = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 Color::Blue = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 Color::Yellow = glm::vec3(1.0f, 1.0f, 0.0f);
const glm::vec3 Color::Pink = glm::vec3(1.0f, 0.0f, 1.0f);
const glm::vec3 Color::Purple = glm::vec3(0.5f, 0.0f, 0.5f);
const glm::vec3 Color::Cyan = glm::vec3(0.0f, 1.0f, 1.0f);
const glm::vec3 Color::Black = glm::vec3(0.0f, 0.0f, 0.0f);
const glm::vec3 Color::White = glm::vec3(1.0f, 1.0f, 1.0f);
const glm::vec3 Color::DarkGreen = glm::vec3(0.0f, 0.5f, 0.0f);
const glm::vec3 Color::Gray = glm::vec3(0.4f, 0.4f, 0.4f);

glm::vec3 Color::Random(float min)
{
    glm::vec3 color;
    color.x = static_cast<float>(std::rand()) / RAND_MAX + min;
    color.y = static_cast<float>(std::rand()) / RAND_MAX + min;
    color.z = static_cast<float>(std::rand()) / RAND_MAX + min;

    return color;
}
