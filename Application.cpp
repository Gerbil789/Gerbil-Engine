#include "Application.h"

static void error_callback(int error, const char* description) { fputs(description, stderr); }




static void window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	ShaderManager::GetInstance().GetCam()->SetAspect((float)width / height);
	glViewport(0, 0, width, height);
}

static void window_focus_callback(GLFWwindow* window, int focused) {}

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

	window = glfwCreateWindow(1080, 720, "Gerbil Engine", NULL, NULL);
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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	

	glfwSetWindowFocusCallback(window, window_focus_callback);

	glfwSetWindowIconifyCallback(window, window_iconify_callback);

	glfwSetWindowSizeCallback(window, window_size_callback);

	ShaderManager& shaderManager = ShaderManager::GetInstance();
	shaderManager.Init();
	

	ModelManager& modelManager = ModelManager::GetInstance();
	modelManager.Init();

	Scene scene;

	GameObject* grid = new GameObject("grid");
	grid->AddComponent<MeshRenderer>(Color::Gray, "grid");
	scene.Add(grid);

	GameObject* cone = new GameObject("center");
	cone->AddComponent<MeshRenderer>(Color::White, "cone");
	cone->transform->SetScale(glm::vec3(0.2f));
	scene.Add(cone);

	GameObject* center = new GameObject("center");
	scene.Add(center);


	GameObject* sun = new GameObject("sun");
	sun->AddComponent<MeshRenderer>(Color::Yellow, "sphere");
	sun->transform->SetPosition(glm::vec3(4.0f, 0.0f, 0.0f));

	GameObject* go2 = new GameObject("planet");
	go2->AddComponent<MeshRenderer>(Color::Green, "sphere");
	go2->AddComponent<MeshRenderer>(Color::DarkGreen, "torus");
	go2->transform->SetScale(glm::vec3(0.5f));
	go2->transform->SetPosition(glm::vec3(3.0f, 0.0f, 0.0f));
	

	GameObject* go3 = new GameObject("planet");
	go3->AddComponent<MeshRenderer>(Color::Cyan, "cylinder");
	go3->transform->SetScale(glm::vec3(0.5f, 4.0f, 0.5f));
	go3->transform->SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));


	scene.Add(go3);
	scene.Add(go2);
	scene.Add(sun);

	center->AddChildren(sun);
	sun->AddChildren(go2);
	go2->AddChildren(go3);

	GameObject* player_go = new GameObject("player");
	player_go->transform->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	player_go->AddComponent<Camera>();
	player_go->GetComponent<Camera>()->SetTarget(glm::vec3(0.0f, 0.0f, -5.0f));
	player_go->GetComponent<Camera>()->SetAspect(ratio);
	shaderManager.SetCam(player_go->GetComponent<Camera>());
	player_go->AddComponent<CameraController>();

	glfwSetCursorPosCallback(window, player_go->GetComponent<CameraController>()->cursor_callback);
	scene.Add(player_go);

	//main loop
	while (!glfwWindowShouldClose(window)) {

		if (Input::IsKeyDown(GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		Time::Update();

		center->transform->RotateBy(0.4f, glm::vec3(0.0f, 1.0f, 0.0f));
		sun->transform->RotateBy(0.5f, glm::vec3(0.0f, 1.0f, 0.0f));
		go2->transform->RotateBy(1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		go3->transform->RotateBy(-0.5f, glm::vec3(1.0f, 1.0f, 1.0f));


		scene.Update();
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
