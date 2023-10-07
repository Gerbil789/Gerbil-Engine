#include "ModelManager.h"

glm::vec4 getRandomColor() {
	float r = static_cast<float>(rand()) / RAND_MAX;
	float g = static_cast<float>(rand()) / RAND_MAX;
	float b = static_cast<float>(rand()) / RAND_MAX;
	return glm::vec4(r, g, b, 1.0f); // Alpha is set to 1.0f
}

ModelManager::ModelManager()
{
	//SQUARE
	Vertex square_vertices[] = {
		{ { -.5f, -.5f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } }, // Bottom left
		{ { -.5f, .5f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },  // Top left
		{ {  .5f, .5f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },   // Top right
		{ {  .5f, -.5f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } }   // Bottom right
	};

	//TRIANGLE
	Vertex triangle_vertices[] = {
		{ { -.5f, -.5f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
		{ { -.5f, .5f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ {  .5f, .5f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
	};

	//CUBE
	Vertex cube_vertices[] = {
        // Back face
        { { -0.5f, -0.5f, -0.5f, 1.0f }, {1.0f, 0.0f, 0.0f, 1.0f} },
        { { -0.5f, 0.5f, -0.5f, 1.0f }, {1.0f, 0.0f, 0.0f, 1.0f} },
        { { 0.5f, 0.5f, -0.5f, 1.0f }, {1.0f, 0.0f, 0.0f, 1.0f} },
        { { 0.5f, 0.5f, -0.5f, 1.0f }, {1.0f, 0.0f, 0.0f, 1.0f} },
        { { 0.5f, -0.5f, -0.5f, 1.0f }, {1.0f, 0.0f, 0.0f, 1.0f} },
        { { -0.5f, -0.5f, -0.5f, 1.0f }, {1.0f, 0.0f, 0.0f, 1.0f} },

        // Front face
        { { -0.5f, -0.5f, 0.5f, 1.0f }, {1.0f, 0.0f, 0.0f, 1.0f} },
        { { 0.5f, -0.5f, 0.5f, 1.0f }, {1.0f, 0.0f, 0.0f, 1.0f} },
        { { 0.5f, 0.5f, 0.5f, 1.0f }, {1.0f, 0.0f, 0.0f, 1.0f} },
        { { 0.5f, 0.5f, 0.5f, 1.0f }, {1.0f, 0.0f, 0.0f, 1.0f} },
        { { -0.5f, 0.5f, 0.5f, 1.0f }, {1.0f, 0.0f, 0.0f, 1.0f} },
        { { -0.5f, -0.5f, 0.5f, 1.0f }, {1.0f, 0.0f, 0.0f, 1.0f} },

        // Left face
        { { -0.5f, 0.5f, 0.5f, 1.0f }, {0.0f, 1.0f, 0.0f, 1.0f} },
        { { -0.5f, 0.5f, -0.5f, 1.0f }, {0.0f, 1.0f, 0.0f, 1.0f} },
        { { -0.5f, -0.5f, -0.5f, 1.0f }, {0.0f, 1.0f, 0.0f, 1.0f} },
        { { -0.5f, -0.5f, -0.5f, 1.0f }, {0.0f, 1.0f, 0.0f, 1.0f} },
        { { -0.5f, -0.5f, 0.5f, 1.0f }, {0.0f, 1.0f, 0.0f, 1.0f} },
        { { -0.5f, 0.5f, 0.5f, 1.0f }, {0.0f, 1.0f, 0.0f, 1.0f} },

        // Right face
        { { 0.5f, 0.5f, 0.5f, 1.0f }, {0.0f, 1.0f, 0.0f, 1.0f} },
        { { 0.5f, -0.5f, 0.5f, 1.0f }, {0.0f, 1.0f, 0.0f, 1.0f} },
        { { 0.5f, -0.5f, -0.5f, 1.0f }, {0.0f, 1.0f, 0.0f, 1.0f} },
        { { 0.5f, -0.5f, -0.5f, 1.0f }, {0.0f, 1.0f, 0.0f, 1.0f} },
        { { 0.5f, 0.5f, -0.5f, 1.0f }, {0.0f, 1.0f, 0.0f, 1.0f} },
        { { 0.5f, 0.5f, 0.5f, 1.0f }, {0.0f, 1.0f, 0.0f, 1.0f} },

        // Bottom face
        { { -0.5f, -0.5f, -0.5f, 1.0f }, {0.0f, 0.0f, 2.0f, 1.0f} },
        { { 0.5f, -0.5f, -0.5f, 1.0f },  {0.0f, 0.0f, 2.0f, 1.0f} },
        { { 0.5f, -0.5f, 0.5f, 1.0f },  {0.0f, 0.0f, 2.0f, 1.0f} },
        { { 0.5f, -0.5f, 0.5f, 1.0f },  {0.0f, 0.0f, 2.0f, 1.0f} },
        { { -0.5f, -0.5f, 0.5f, 1.0f },  {0.0f, 0.0f, 2.0f, 1.0f} },
        { { -0.5f, -0.5f, -0.5f, 1.0f },  {0.0f, 0.0f, 2.0f, 1.0f} },

        // Top face
        { { -0.5f, 0.5f, -0.5f, 1.0f },  {0.0f, 0.0f, 2.0f, 1.0f} },
        { { -0.5f, 0.5f, 0.5f, 1.0f },  {0.0f, 0.0f, 2.0f, 1.0f} },
        { { 0.5f, 0.5f, 0.5f, 1.0f },  {0.0f, 0.0f, 2.0f, 1.0f} },
        { { 0.5f, 0.5f, 0.5f, 1.0f },  {0.0f, 0.0f, 2.0f, 1.0f} },
        { { 0.5f, 0.5f, -0.5f, 1.0f },  {0.0f, 0.0f, 2.0f, 1.0f} },
        { { -0.5f, 0.5f, -0.5f, 1.0f },  {0.0f, 0.0f, 2.0f, 1.0f} }
    };

	Model* square = new Model("square", square_vertices, sizeof(square_vertices) / sizeof(Vertex));
	Model* triangle = new Model("triangle", triangle_vertices, sizeof(triangle_vertices) / sizeof(Vertex));
	Model* cube = new Model("cube", cube_vertices, sizeof(cube_vertices) / sizeof(Vertex));

	this->models.push_back(square);
	this->models.push_back(triangle);
	this->models.push_back(cube);

}

Model* ModelManager::GetModel(std::string _name)
{
	for (int i = 0; i < models.size(); i++) {
		if (models[i]->name == _name) {
			return models[i];
		}
	}
	std::cerr << "ERROR: could not find model with name [" << _name << "]\n";
	return nullptr;
}
