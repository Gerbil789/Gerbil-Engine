#include "Application.h"

static void error_callback(int error, const char* description) { fputs(description, stderr); }

static void button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}


static void cursor_callback(GLFWwindow* window, double x, double y) {/* printf("cursor_callback \n"); */ }

static void window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	ShaderManager::getInstance().GetCam()->SetAspect((float)width / height);
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

	ShaderManager& shaderManager = ShaderManager::getInstance();
	shaderManager.Init();
	

	ModelManager& modelManager = ModelManager::getInstance();
	modelManager.Init();

	Scene scene;

	GameObject* grid = new GameObject("grid");
	grid->AddComponent<MeshRenderer>(Color::Gray, "grid");
	scene.Add(grid);

	GameObject* go1 = new GameObject("gopos");
	go1->AddComponent<MeshRenderer>(Color::Red, "torus");
	go1->transform->SetScale(glm::vec3(1.0f));
	go1->transform->SetPosition(glm::vec3(-0.5f, 0.0f, -2.0f));
	scene.Add(go1);

	GameObject* go2 = new GameObject("gorot");
	go2->AddComponent<MeshRenderer>(Color::Cyan, "torus");
	go2->transform->SetScale(glm::vec3(0.5f));
	go2->transform->SetPosition(glm::vec3(0.0f, 0.0f, -2.0f));
	scene.Add(go2);

	GameObject* go3 = new GameObject("goscl");
	go3->AddComponent<MeshRenderer>(Color::Blue, "torus");
	go3->transform->SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
	go3->transform->SetPosition(glm::vec3(0.5f, 0.0f, -2.0f));
	scene.Add(go3);

	go1->AddChildren(go2);
	go2->AddChildren(go3);

	GameObject* player_go = new GameObject("player");
	player_go->transform->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	player_go->AddComponent<Camera>();
	player_go->GetComponent<Camera>()->SetTarget(glm::vec3(0.0f, 0.0f, -5.0f));
	player_go->GetComponent<Camera>()->SetAspect(ratio);
	shaderManager.SetCam(player_go->GetComponent<Camera>());
	
	scene.Add(player_go);

	//main loop
	double previousTime = glfwGetTime();
	float deltaTime = 0.0;
	

	float a = 0.0f;
	float playerSpeed = 1.0f;
	while (!glfwWindowShouldClose(window)) {
		double currentTime = glfwGetTime();
		deltaTime = currentTime - previousTime;
		previousTime = currentTime;


		go1->transform->RotateBy(0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
		go2->transform->RotateBy(1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		go3->transform->RotateBy(-0.5f, glm::vec3(1.0f, 1.0f, 1.0f));

		//player_go->transform->RotateBy(0.1, glm::vec3(1.0f, 0.0f, 0.0f));

		if (Input::IsKeyDown(GLFW_KEY_W)) {
			player_go->transform->MoveBy(glm::vec3(0.0f, 0.0f, -1.0f) * playerSpeed * deltaTime);
		}

		if (Input::IsKeyDown(GLFW_KEY_S)) {
			player_go->transform->MoveBy(glm::vec3(0.0f, 0.0f, 1.0f) * playerSpeed * deltaTime);
		}

		if (Input::IsKeyDown(GLFW_KEY_A)) {
			player_go->transform->MoveBy(glm::vec3(-1.0f, 0.0f, 0.0f) * playerSpeed* deltaTime);
		}

		if (Input::IsKeyDown(GLFW_KEY_D)) {
			player_go->transform->MoveBy(glm::vec3(1.0f, 0.0f, 0.0f) * playerSpeed * deltaTime);
		}

		if (Input::IsMouseButtonClicked(GLFW_MOUSE_BUTTON_LEFT)) {
			std::cout << "X:" << Input::GetMouseX() << " Y:" << Input::GetMouseY() << "\n";
		}



		a += 0.01f;
		scene.Draw();
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
