#include "ShaderManager.h"


void ShaderManager::CheckShaderCompilation(GLuint shader, const std::string& shaderType) {
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLint logSize;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
		std::vector<GLchar> errorLog(logSize);
		glGetShaderInfoLog(shader, logSize, NULL, errorLog.data());
		std::cerr << "Error compiling " << shaderType << ":\n" << errorLog.data() << std::endl;
		exit(1);
	}
}

void ShaderManager::CheckProgramLinking(GLuint program) {
	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		GLint logSize;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
		std::vector<GLchar> errorLog(logSize);
		glGetProgramInfoLog(program, logSize, NULL, errorLog.data());
		std::cerr << "Error linking program:\n" << errorLog.data() << std::endl;
		exit(1);
	}
}

GLuint ShaderManager::CreateShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath)
{
	std::string vertex_shader_str = ReadShaderSource(vertexShaderPath);
	std::string fragment_shader_str = ReadShaderSource(fragmentShaderPath);

	const char* vertex_shader = vertex_shader_str.c_str();
	const char* fragment_shader = fragment_shader_str.c_str();

	//vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	glCompileShader(vertexShader);
	CheckShaderCompilation(vertexShader, "Vertex Shader");

	//fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	glCompileShader(fragmentShader);
	CheckShaderCompilation(fragmentShader, "Fragment Shader");

	//shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	CheckProgramLinking(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}


void ShaderManager::Init()
{
	if (initialized) {
		std::cerr << "ShaderLib is already initialized." << std::endl;
		return;
	}
	GLuint shaderProgram;
	shaderProgram = CreateShaderProgram("Shaders/model_vertex.glsl", "Shaders/model_fragment.glsl");
	shaderPrograms.push_back(std::make_pair("ModelShader", shaderProgram));

	initialized = true;
}

void ShaderManager::UseShader(int shaderID)
{
	if (!initialized) {
		std::cerr << "ShaderLib is not initialized. Call init() first." << std::endl;
		return;
	}

	if (shaderID == currentShader) {
		return;
	}

	glUseProgram(shaderID);

	currentShader = shaderID;
}

GLuint ShaderManager::GetShaderProgram(std::string shader_name)
{
	for (const auto& pair : shaderPrograms) {
		if (pair.first == shader_name) {
			return pair.second;
		}
	}
	std::cout << "Shader [" << shader_name << "] does not exist\n";
	return 0;
}


std::string ShaderManager::ReadShaderSource(const std::string& filePath) {
	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::cerr << "Failed to open the shader file: " << filePath << std::endl;
		return "";
	}

	std::string shaderSource((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	return shaderSource;
}