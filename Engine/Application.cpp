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
	Scene* scene1 = new Scene();
	SceneManager::GetInstance().LoadScene(scene1);

	Material* m_test_grid = new Material("Textures/test_grid.png", "m_test_grid");
	Material* m_wood = new Material("Textures/wooden_fence.png", "m_wood");

	//player
	GameObject* player_go = new GameObject("player");
	player_go->AddComponent<Camera>();
	player_go->GetComponent<Camera>()->SetAspect(ratio);
	player_go->AddComponent<CameraController>(2.0f, player_go->GetComponent<Camera>());
	player_go->transform->SetPosition(glm::vec3(0.0f, 5.0f, 0.0f));
	scene1->Add(player_go);


	//ground
	GameObject* ground = new GameObject("ground");
	ground->AddComponent<MeshRenderer>("plane", "phong", Color::White, m_test_grid);
	ground->transform->SetScale(glm::vec3(50.0f));
	scene1->Add(ground);

	//spheres
	std::string models[] = { "sphere", "cube", "oak", "spruce"};
	for (int i = -7; i <= 7; i++) {
		for (int j = -7; j <= 7; j++) {
			std::string model = models[rand() % 4];
			GameObject* sphere = new GameObject("sphere");
			//tmp test multiple textures
			if (rand() % 2 == 1) {
				sphere->AddComponent<MeshRenderer>("sphere", "phong", Color::Random(), m_test_grid);
			}
			else {
				sphere->AddComponent<MeshRenderer>("sphere", "phong", Color::Random(), m_wood);
			}
			sphere->transform->SetPosition(glm::vec3(3.0f * i, 1.0f, 3.0f * j));
			scene1->Add(sphere);
		}
	}


	GameObject* rotator = new GameObject("empty");
	rotator->AddComponent<RotationScript>(150.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	rotator->transform->SetPosition(glm::vec3(0.0f, 6.0f, 0.0f));
	rotator->transform->SetScale(glm::vec3(0.5f));
	scene1->Add(rotator);

	//red light
	GameObject* spot1 = new GameObject("spot light");
	spot1->AddComponent<SpotLight>(Color::Red, 15.0f);
	spot1->transform->SetPosition(glm::vec3(0.0f, 0.0f, -1.0f));
	spot1->transform->SetScale(glm::vec3(0.5f));
	spot1->transform->RotateBy(45.0f, glm::vec3(1.0f, 0.0f, 0.0f)); //set 45 angle
	scene1->Add(spot1);
	rotator->AddChildren(spot1);

	//blue light
	GameObject* spot2 = new GameObject("spot light");
	spot2->AddComponent<SpotLight>(Color::Blue, 15.0f);
	spot2->transform->SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
	spot2->transform->SetScale(glm::vec3(0.5f));
	spot2->transform->RotateBy(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	spot2->transform->RotateBy(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	scene1->Add(spot2);
	rotator->AddChildren(spot2);

	//directional light
	GameObject* dir = new GameObject("directional light");
	dir->AddComponent<DirectionalLight>(Color::White, 0.5f);
	scene1->Add(dir);

	//flash light
	GameObject* flashLight = new GameObject("flash light");
	flashLight->AddComponent<SpotLight>(Color::White, 5.0f);
	scene1->Add(flashLight);
	player_go->AddChildren(flashLight);
}

void Application::Run()
{
	GUI gui(window, SceneManager::GetInstance().GetActiveScene());

	while (!glfwWindowShouldClose(window)) {

		if (Input::IsKeyDown(GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		Time::Update();
		
		SceneManager::GetInstance().GetActiveScene()->Update();
		
		//todo: make a controller class for this
		SceneManager::GetInstance().GetActiveScene()->GetObjectManager().FindByName("flash light")->GetComponent<SpotLight>()->SetDirection(SceneManager::GetInstance().GetActiveScene()->GetActiveCamera()->GetFront());

		glfwPollEvents();
		gui.Update();
		glfwSwapBuffers(window);
	}

	gui.Dispose();
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
