#include "Application.h"

static void error_callback(int error, const char* description) { fputs(description, stderr); }

static void button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}


static void cursor_callback(GLFWwindow* window, double x, double y) {/* printf("cursor_callback \n"); */ }

static void window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


static void window_focus_callback(GLFWwindow* window, int focused) {/* printf("window_focus_callback \n");*/ }

static void window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

void Application::Init()
{

	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
		GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(720, 720, "Gerbil Engine", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "ERROR: could not start GLEW\n");
		exit(EXIT_FAILURE);
	}

	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	

	glfwSetKeyCallback(window, key_callback);

	glfwSetCursorPosCallback(window, cursor_callback);

	glfwSetMouseButtonCallback(window, button_callback);

	glfwSetWindowFocusCallback(window, window_focus_callback);

	glfwSetWindowIconifyCallback(window, window_iconify_callback);

	glfwSetWindowSizeCallback(window, window_size_callback);

	ShaderLib& shaderLib = ShaderLib::getInstance();
	shaderLib.Init();

	ModelManager& modelManager = ModelManager::getInstance();
	modelManager.Init();

	Scene scene;

	GameObject* go1 = new GameObject("gopos");
	go1->AddComponent<MeshRenderer>(Color::Red, "cube");
	go1->GetComponent<Transform>()->setScale(glm::vec3(0.2f, 0.2f, 0.2f));
	go1->GetComponent<Transform>()->setPosition(glm::vec3(-0.5f, 0.0f, 0.0f));
	scene.Add(go1);

	GameObject* go2 = new GameObject("gorot");
	go2->AddComponent<MeshRenderer>(Color::Cyan, "cylinder");
	go2->GetComponent<Transform>()->setScale(glm::vec3(0.2f, 0.2f, 0.2f));
	go2->GetComponent<Transform>()->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	scene.Add(go2);

	GameObject* go3 = new GameObject("goscl");
	go3->AddComponent<MeshRenderer>(Color::Blue, "cone");
	go3->GetComponent<Transform>()->setScale(glm::vec3(0.2f, 0.2f, 0.2f));
	go3->GetComponent<Transform>()->setPosition(glm::vec3(0.5f, 0.0f, 0.0f));
	scene.Add(go3);
	
	//main loop
	double angle = 1.0;
	while (!glfwWindowShouldClose(window)) {
		go1->GetComponent<Transform>()->setPosition(glm::vec3(-0.5f, std::sin(angle) * 0.1f, 0.0f));
		go1->GetComponent<Transform>()->rotateBy(0.5f, glm::vec3(1.0f, 1.0f, 0.0f));
		go2->GetComponent<Transform>()->rotateBy(1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		go3->GetComponent<Transform>()->setScale(glm::vec3(0.2f, std::sin(angle) * 0.1 + 0.4, 0.2f));
		go3->GetComponent<Transform>()->rotateBy(-0.5f, glm::vec3(1.0f, 0.0f, 0.0f));
		angle += 0.05;
		scene.Draw();
		glfwPollEvents();
		glfwSwapBuffers(window);
		
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}