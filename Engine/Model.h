#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

class Model {
public:
  Model(std::string path);
  ~Model();
  void Draw();

  std::string name;
  std::vector< glm::vec3 > vertices;
  std::vector< glm::vec2 > uvs;
  std::vector< glm::vec3 > normals;
  GLuint VBO = 0, VAO = 0, textureID = 0;
private:
  bool LoadOBJ(std::string path, std::vector < glm::vec3 >& out_vertices, std::vector < glm::vec2 >& out_uvs, std::vector < glm::vec3 >& out_normals);
  bool LoadTexture(std::string path);
};