#include "Model.h"

std::string GetName(std::string input) {
	std::string result = input;

	// Remove "Models/" from the start
	size_t foundStart = result.find("Models/");
	if (foundStart != std::string::npos) {
		result = result.substr(foundStart + 7); // "Models/".length() is 7
	}

	// Remove ".obj" from the end
	size_t foundEnd = result.find(".obj");
	if (foundEnd != std::string::npos) {
		result = result.substr(0, foundEnd);
	}

	return result;
}

Model::Model(std::string path) {
	name = GetName(path);
	
	if (!LoadOBJ(path, vertices, uvs, normals)) {
		std::cerr << "Loading .obj file failed. [" << path << "]\n";
		return;
	}

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	size_t totalDataSize = (vertices.size() * sizeof(glm::vec3)) + (normals.size() * sizeof(glm::vec3)) + (uvs.size() * sizeof(glm::vec2));
	glBufferData(GL_ARRAY_BUFFER, totalDataSize, nullptr, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(glm::vec3), &vertices[0]);
	glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), normals.size() * sizeof(glm::vec3), &normals[0]);
	glBufferSubData(GL_ARRAY_BUFFER, (vertices.size() + normals.size()) * sizeof(glm::vec3), uvs.size() * sizeof(glm::vec2), &uvs[0]);

	// Configure the vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);  // Vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(vertices.size() * sizeof(glm::vec3)));  // Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)((vertices.size() + normals.size()) * sizeof(glm::vec3)));  // UVs
	glEnableVertexAttribArray(2);

	// Unbind VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Model::~Model() {

}


bool Model::LoadOBJ(std::string path, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals)
{
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	std::ifstream file(path);
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << path << std::endl;
		return false;
	}

	std::string line;
	while (std::getline(file, line)) {
		if (line.find("vt ") == 0) { 
			glm::vec2 uv;
			std::istringstream ss(line.substr(2));
			ss >> uv.x >> uv.y;
			temp_uvs.push_back(uv);
		}
		else if (line.find("vn ") == 0) { 
			glm::vec3 normal;
			std::istringstream ss(line.substr(2));
			ss >> normal.x >> normal.y >> normal.z;
			temp_normals.push_back(normal);
		}
		else if (line.find("v ") == 0) {
			glm::vec3 vertex;
			std::istringstream ss(line.substr(1));
			ss >> vertex.x >> vertex.y >> vertex.z;
			temp_vertices.push_back(vertex);
		}
		else if (line.find("f ") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			std::istringstream ss(line.substr(1));
			char slash;

			ss >> vertexIndex[0] >> slash >> uvIndex[0] >> slash >> normalIndex[0];
			ss >> vertexIndex[1] >> slash >> uvIndex[1] >> slash >> normalIndex[1];
			ss >> vertexIndex[2] >> slash >> uvIndex[2] >> slash >> normalIndex[2];

			// OBJ file indices start from 1, so subtract 1 to get the correct index.
			vertexIndices.push_back(vertexIndex[0] - 1);
			vertexIndices.push_back(vertexIndex[1] - 1);
			vertexIndices.push_back(vertexIndex[2] - 1);
			uvIndices.push_back(uvIndex[0] - 1);
			uvIndices.push_back(uvIndex[1] - 1);
			uvIndices.push_back(uvIndex[2] - 1);
			normalIndices.push_back(normalIndex[0] - 1);
			normalIndices.push_back(normalIndex[1] - 1);
			normalIndices.push_back(normalIndex[2] - 1);
		}
	}
	file.close();

	// Now, populate the output vectors with the correct data using the indices.
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertexIndex];
		out_vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 uv = temp_uvs[uvIndex];
		out_uvs.push_back(uv);
	}

	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_normals[normalIndex];
		out_normals.push_back(normal);
	}

	return true;
}






void Model::Draw()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glBindVertexArray(0);
}

