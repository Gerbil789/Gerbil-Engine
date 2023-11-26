#include "Spline.h"

Spline::Spline()
{
	controlPoints = { glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 2.0f, 0.0f), glm::vec3(3.0f, 4.0f, 0.0f), glm::vec3(5.0f, 0.0f, 0.0f) };
}

glm::vec3 Spline::GetPosition(float t)
{
    float u = 1 - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    glm::vec3 p = uuu * controlPoints[0]; // (1-t)^3 * P0
    p += 3 * uu * t * controlPoints[1];   // 3t(1-t)^2 * P1
    p += 3 * u * tt * controlPoints[2];   // 3t^2(1-t) * P2
    p += ttt * controlPoints[3];          // t^3 * P3

    return p;
}
