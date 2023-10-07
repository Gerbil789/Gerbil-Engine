#include "Model.h"

Model::Model(std::string _name, const Vertex _vertices[], int _numVertices){
  name = _name;
  numVertices = _numVertices;
  if (numVertices < 0) {
    std::cerr << "Invalid number of vertices!" << std::endl;
    numVertices = 0;
  }
  
  vertices = new Vertex[numVertices];
  for (int i = 0; i < numVertices; ++i) {
    vertices[i] = _vertices[i];
  }


  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex), vertices, GL_STATIC_DRAW);

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);


  //TO DO: make this better (more modular)
  // Configure the vertex attributes
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(4 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Unbind VBO and VAO
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

Model::~Model() {
  delete[] vertices;
}

