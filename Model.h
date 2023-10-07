#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <iostream>



struct Vertex {
  glm::vec4 pos;
	glm::vec4 color;
};

class Model {
public:
  Model(std::string _name, const Vertex _vertices[], int _numVertices);
  ~Model();

  std::string name;
  Vertex* vertices;
  int numVertices;
  GLuint VBO = 0, VAO = 0;
};