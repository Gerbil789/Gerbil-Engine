#include "Application.h"

static void error_callback(int error, const char* description) { fputs(description, stderr); }

static void window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	SceneManager::GetInstance().GetActiveScene()->GetActiveCamera()->SetAspect((float)width / height);
	glViewport(0, 0, width, height);
}

static void window_focus_callback(GLFWwindow* window, int focused) {}

static void window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

void Application::Init()
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;
	glViewport(0, 0, width, height);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);

	glfwSetWindowFocusCallback(window, window_focus_callback);

	glfwSetWindowIconifyCallback(window, window_iconify_callback);

	glfwSetWindowSizeCallback(window, window_size_callback);

	ShaderManager::GetInstance().Init();

	ModelManager::GetInstance().Init();
}

void Application::InitScenes()
{
	Scene* scene1 = new Scene("PhongTest");
	SceneManager::GetInstance().LoadScene(scene1);

	GameObject* player_go = new GameObject("player");
	player_go->transform->SetPosition(glm::vec3(0.0f, 0.0f, 5.0f));
	player_go->AddComponent<Camera>();
	player_go->GetComponent<Camera>()->SetTarget(glm::vec3(0.0f, 0.0f, -5.0f));
	player_go->GetComponent<Camera>()->SetAspect(ratio);
	player_go->AddComponent<CameraController>(2.0f, player_go->GetComponent<Camera>());
	player_go->transform->SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));
	scene1->Add(player_go);

	GameObject* ground = new GameObject("ground");
	ground->AddComponent<MeshRenderer>("plane");
	ground->transform->SetScale(glm::vec3(100.0f));
	scene1->Add(ground);


	for (int i = -7; i <= 7; i++) {
		for (int j = -7; j <= 7; j++) {
			GameObject* sphere = new GameObject("sphere");
			sphere->AddComponent<MeshRenderer>("sphere", "phong", Color::Random());
			sphere->transform->SetPosition(glm::vec3(3.0f * i, 1.0f, 3.0f * j));
			scene1->Add(sphere);
		}
	}



	GameObject* empty = new GameObject("empty");
	empty->AddComponent<RotationScript>(150.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	scene1->Add(empty);

	GameObject* spot1 = new GameObject("spot light");
	spot1->AddComponent<SpotLight>(Color::Red, 5.0f);
	spot1->transform->SetPosition(glm::vec3(0.0f, 5.0f, 0.0f));
	spot1->transform->SetScale(glm::vec3(0.1f));
	spot1->transform->RotateBy(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	spot1->AddComponent<RotationScript>(150.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	scene1->Add(spot1);
	empty->AddChildren(spot1);

	GameObject* spot2 = new GameObject("spot light");
	spot2->AddComponent<SpotLight>(Color::Blue, 5.0f);
	spot2->transform->SetPosition(glm::vec3(0.0f, 5.0f, 0.0f));
	spot2->transform->SetScale(glm::vec3(0.1f));
	spot2->transform->RotateBy(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	spot2->transform->RotateBy(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	spot2->AddComponent<RotationScript>(150.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	scene1->Add(spot2);
	empty->AddChildren(spot2);

	//GameObject* dir = new GameObject("directional light");
	//dir->AddComponent<DirectionalLight>(Color::White, 0.1f);
	//scene1->Add(dir);

	/*for(int i = 0; i < 5; i++) {
		GameObject* point = new GameObject("point light");
		glm::vec3 color = Color::Random();
		point->AddComponent<PointLight>(color);
		point->AddComponent<MeshRenderer>("sphere", "constant", color);
		point->transform->SetScale(glm::vec3(0.1f));
		point->transform->SetPosition(glm::vec3(5.0f * i, 1.0f, 0.0f));
		scene1->Add(point);
	}*/


	//SceneManager::GetInstance().SaveScene();
}



void Application::Run()
{
	GUI gui(window, SceneManager::GetInstance().GetActiveScene());

	while (!glfwWindowShouldClose(window)) {

		if (Input::IsKeyDown(GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		Time::Update();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		SceneManager::GetInstance().GetActiveScene()->Update();

		glfwPollEvents();
		gui.Update();
		glfwSwapBuffers(window);
	}

	gui.Dispose();
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
