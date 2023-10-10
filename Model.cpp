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

	textureID = LoadTexture("Textures/test.bmp");

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Configure the vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
	glEnableVertexAttribArray(0);
 	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (GLvoid*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);

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
		if (line.find("vt") == 0) {
			glm::vec2 uv;
			std::istringstream ss(line.substr(1));
			ss >> uv.x >> uv.y;
			temp_uvs.push_back(uv);
		}
		else if (line.find("vn") == 0) {
			glm::vec3 normal;
			std::istringstream ss(line.substr(1));
			ss >> normal.x >> normal.y >> normal.z;
			temp_normals.push_back(normal);
		}
		else if (line.find("v") == 0) {
		glm::vec3 vertex;
		std::istringstream ss(line.substr(1));
		ss >> vertex.x >> vertex.y >> vertex.z;
		temp_vertices.push_back(vertex);
		}
		else if (line.find("f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			std::istringstream ss(line.substr(1));
			char slash;

			ss >> vertexIndex[0] >> slash >> uvIndex[0] >> slash >> normalIndex[0];
			ss >> vertexIndex[1] >> slash >> uvIndex[1] >> slash >> normalIndex[1];
			ss >> vertexIndex[2] >> slash >> uvIndex[2] >> slash >> normalIndex[2];
			
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		
	}
	file.close();

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		out_vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 vertex = temp_uvs[uvIndex - 1];
		out_uvs.push_back(vertex);
	}

	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 vertex = temp_normals[normalIndex - 1];
		out_normals.push_back(vertex);
	}
	return true;
}

bool Model::LoadTexture(std::string path) {
	// Use C++ file streams instead of C-style file operations
	std::ifstream file(path, std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Image could not be opened" << std::endl;
		return false;
	}

	// Use C++ standard vectors for dynamic memory allocation
	std::vector<uint8_t> header(54); // Each BMP file begins with a 54-byte header
	uint32_t dataPos;
	uint32_t width, height;
	uint32_t imageSize;

	// Read the header and handle errors
	if (!file.read(reinterpret_cast<char*>(header.data()), 54)) {
		std::cerr << "Not a correct BMP file" << std::endl;
		return false;
	}

	if (header[0] != 'B' || header[1] != 'M') {
		std::cerr << "Not a correct BMP file" << std::endl;
		return false;
	}

	dataPos = *reinterpret_cast<uint32_t*>(&header[0x0A]);
	imageSize = *reinterpret_cast<uint32_t*>(&header[0x22]);
	width = *reinterpret_cast<uint32_t*>(&header[0x12]);
	height = *reinterpret_cast<uint32_t*>(&header[0x16]);

	if (imageSize == 0)
		imageSize = width * height * 3;
	if (dataPos == 0)
		dataPos = 54;

	std::vector<uint8_t> data(imageSize);

	// Read the image data
	if (!file.read(reinterpret_cast<char*>(data.data()), imageSize)) {
		std::cerr << "Error while reading image data" << std::endl;
		return false;
	}

	// Close the file using C++ RAII
	file.close();

	// Use smart pointers for resource management
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Use C++ constants for OpenGL parameters
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return true;
}



void Model::Draw()
{
	//glBindTexture(GL_TEXTURE_2D, textureID);
	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glBindVertexArray(0);
}

