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

void Application::Run()
{
	GameObject* player_go = new GameObject("player");
	player_go->transform->SetPosition(glm::vec3(0.0f, 0.0f, 5.0f));
	player_go->AddComponent<Camera>();
	player_go->GetComponent<Camera>()->SetTarget(glm::vec3(0.0f, 0.0f, -5.0f));
	player_go->GetComponent<Camera>()->SetAspect(ratio);
	player_go->AddComponent<CameraController>(player_go->GetComponent<Camera>());
	glfwSetCursorPosCallback(window, player_go->GetComponent<CameraController>()->cursor_callback);

	GameObject* grid = new GameObject("grid");
	grid->AddComponent<MeshRenderer>("grid", Color::Gray, "constant");
	grid->transform->SetPosition(glm::vec3(0.0f, -4.0f, 0.0f));

	GameObject* sphere1 = new GameObject("sphere1");
	sphere1->AddComponent<MeshRenderer>("sphere", Color::Red);
	sphere1->transform->SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));

	GameObject* sphere2 = new GameObject("sphere2");
	sphere2->AddComponent<MeshRenderer>("sphere", Color::Green);
	sphere2->transform->SetPosition(glm::vec3(-2.0f, 0.0f, 0.0f));

	GameObject* sphere3 = new GameObject("sphere3");
	sphere3->AddComponent<MeshRenderer>("sphere", Color::Blue);
	sphere3->transform->SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));

	GameObject* sphere4 = new GameObject("sphere4");
	sphere4->AddComponent<MeshRenderer>("sphere", Color::White);
	sphere4->transform->SetPosition(glm::vec3(0.0f, -2.0f, 0.0f));

	GameObject* pointLight = new GameObject("point light");
	pointLight->AddComponent<PointLight>();

	Scene* scene = new Scene();
	
	scene->Add(player_go);
	scene->Add(grid);
	scene->Add(sphere1);
	scene->Add(sphere2);
	scene->Add(sphere3);
	scene->Add(sphere4);
	scene->Add(pointLight);


	scene->SetActiveCamera(player_go->GetComponent<Camera>());
	SceneManager::GetInstance().AddScene(scene);
	SceneManager::GetInstance().SetActiveScene(scene);

	GUI gui(window, scene);

	bool showCursor = false;
	//main loop
	while (!glfwWindowShouldClose(window)) {

		if (Input::IsKeyDown(GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		//TMP
		if (Input::IsKeyDown(GLFW_KEY_C)) {
			showCursor = !showCursor;
			if (showCursor) {
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
			else {
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}
		}

		Time::Update();

		sphere1->transform->RotateBy(-50.0f * Time::deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
		sphere2->transform->RotateBy(50.0f * Time::deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
		sphere3->transform->RotateBy(-50.0f * Time::deltaTime, glm::vec3(1.0f, 0.0f, 0.0f));
		sphere4->transform->RotateBy(50.0f * Time::deltaTime, glm::vec3(1.0f, 0.0f, 0.0f));


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		scene->Update();
		
		glfwPollEvents();
		gui.Update();
		glfwSwapBuffers(window);
	}

	gui.Dispose();
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
