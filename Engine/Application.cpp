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

	GameObject* ground = new GameObject("ground");
	ground->AddComponent<MeshRenderer>("plane");
	ground->transform->SetScale(glm::vec3(100.0f));

	scene1->Add(player_go);
	scene1->Add(ground);


	SceneManager::GetInstance().SaveScene();
	//Serializer::SerializeToJson(scene1);
	//Serializer::DeserializeFromJson("Scenes/newScene1.json");
	*/
	//------------Scene 2-------------- TRANSFORM TEST
	/*
	Scene* scene = new Scene("TransformTest");
	SceneManager::GetInstance().LoadScene(scene);

	GameObject* player_go = new GameObject("player");
	player_go->transform->SetPosition(glm::vec3(0.0f, 0.0f, 5.0f));
	player_go->AddComponent<Camera>();
	player_go->GetComponent<Camera>()->SetTarget(glm::vec3(0.0f, 0.0f, -5.0f));
	player_go->GetComponent<Camera>()->SetAspect(ratio);
	player_go->AddComponent<CameraController>(2.0f, player_go->GetComponent<Camera>());
	scene->SetActiveCamera(player_go->GetComponent<Camera>());

	GameObject* empty = new GameObject("empty");
	empty->AddComponent<RotationScript>(-100);

	GameObject* sun = new GameObject("sun");
	sun->AddComponent<MeshRenderer>("sphere");
	sun->transform->SetScale(glm::vec3(3.0f));
	sun->AddComponent<RotationScript>();

	GameObject* earth = new GameObject("earth");
	earth->AddComponent<MeshRenderer>("sphere");
	earth->transform->SetPosition(glm::vec3(-9.0f, 0.0f, 0.0f));
	earth->transform->SetScale(glm::vec3(1.2));
	earth->AddComponent<RotationScript>(500.0f);

	GameObject* moon = new GameObject("moon");
	moon->AddComponent<MeshRenderer>("sphere");
	moon->transform->SetPosition(glm::vec3(-4.0f, 0.0f, 0.0f));
	moon->transform->SetScale(glm::vec3(0.4f));
	moon->AddComponent<RotationScript>(150.0f);

	GameObject* mars = new GameObject("mars");
	mars->AddComponent<MeshRenderer>("sphere");
	mars->transform->SetPosition(glm::vec3(-5.0f, 0.0f, 0.0f));
	mars->transform->SetScale(glm::vec3(0.5f));
	mars->AddComponent<RotationScript>(-350.0f);

	GameObject* pointLight = new GameObject("point light");
	pointLight->AddComponent<Light>(Light::POINT, Color::White);
	pointLight->transform->SetPosition(glm::vec3(0.0f, 5.0f, 0.0f));

	empty->AddChildren(earth);
	earth->AddChildren(moon);
	sun->AddChildren(mars);


	scene->Add(player_go);
	scene->Add(empty);
	scene->Add(sun);
	scene->Add(earth);
	scene->Add(moon);
	scene->Add(mars);
	scene->Add(pointLight);

	Serializer::SerializeToJson(scene);
	*/
	//------------Scene 3-------------- LIGHT TEST
/*
	Scene* scene = new Scene("LightTest1");
	SceneManager::GetInstance().LoadScene(scene);




	

	scene1->SetActiveCamera(player_go->GetComponent<Camera>());
	
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
