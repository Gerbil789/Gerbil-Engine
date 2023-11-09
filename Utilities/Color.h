#ifndef COLOR_H
#define COLOR_H

#include <glm/glm.hpp>


class Color {
public:
  static const glm::vec3 Red;
  static const glm::vec3 Green;
  static const glm::vec3 Blue;
  static const glm::vec3 Yellow;
  static const glm::vec3 Pink;
  static const glm::vec3 Purple;
  static const glm::vec3 Cyan;
  static const glm::vec3 Black;
  static const glm::vec3 White;
  static const glm::vec3 DarkGreen;
  static const glm::vec3 Gray;

  static glm::vec3 Random(float min = 0.5f);
};

#endif
