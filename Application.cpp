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
	//GameObject* grid = new GameObject("grid");
	//grid->AddComponent<MeshRenderer>(Color::Gray, "grid");

	GameObject* sun = new GameObject("sun");
	sun->AddComponent<MeshRenderer>(Color::Yellow, "sphere");
	sun->transform->SetPosition(glm::vec3(0.0f, 0.0f, -10.0f));

	GameObject* planet = new GameObject("planet");
	planet->AddComponent<MeshRenderer>(Color::Green, "sphere");
	planet->transform->SetScale(glm::vec3(0.5f));
	planet->transform->SetPosition(glm::vec3(3.0f, 0.0f, 0.0f));

	GameObject* moon = new GameObject("moon");
	moon->AddComponent<MeshRenderer>(Color::Gray, "sphere");
	moon->transform->SetScale(glm::vec3(0.5f));
	moon->transform->SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));

	sun->AddChildren(planet);
	planet->AddChildren(moon);

	GameObject* player_go = new GameObject("player");
	player_go->transform->SetPosition(glm::vec3(0.0f, 0.0f, 5.0f));
	player_go->AddComponent<Camera>();
	player_go->GetComponent<Camera>()->SetTarget(glm::vec3(0.0f, 0.0f, -5.0f));
	player_go->GetComponent<Camera>()->SetAspect(ratio);
	ShaderManager::GetInstance().SetCam(player_go->GetComponent<Camera>());
	player_go->AddComponent<CameraController>();
	glfwSetCursorPosCallback(window, player_go->GetComponent<CameraController>()->cursor_callback);


	GameObject* sphere1 = new GameObject("sphere1");
	sphere1->AddComponent<MeshRenderer>(Color::Red, "sphere");
	sphere1->transform->SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));

	GameObject* sphere2 = new GameObject("sphere2");
	sphere2->AddComponent<MeshRenderer>(Color::Green, "sphere");
	sphere2->transform->SetPosition(glm::vec3(-2.0f, 0.0f, 0.0f));

	GameObject* sphere3 = new GameObject("sphere3");
	sphere3->AddComponent<MeshRenderer>(Color::Blue, "sphere");
	sphere3->transform->SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));

	GameObject* sphere4 = new GameObject("sphere4");
	sphere4->AddComponent<MeshRenderer>(Color::Cyan, "sphere");
	sphere4->transform->SetPosition(glm::vec3(0.0f, -2.0f, 0.0f));




	Scene* scene = new Scene();
	//scene->Add(grid);
	scene->Add(moon);
	scene->Add(planet);
	scene->Add(sun);
	scene->Add(player_go);

	scene->Add(sphere1);
	scene->Add(sphere2);
	scene->Add(sphere3);
	scene->Add(sphere4);

	GUI gui(window, scene);

	bool showCursor = false;
	//main loop
	while (!glfwWindowShouldClose(window)) {

		if (Input::IsKeyDown(GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

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

		sun->transform->RotateBy(100.0f * Time::deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
		planet->transform->RotateBy(-450.0f * Time::deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
		moon->transform->RotateBy(-0.5f * Time::deltaTime, glm::vec3(1.0f, 1.0f, 0.0f));

		sphere1->transform->RotateBy(-50.0f * Time::deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
		sphere2->transform->RotateBy(50.0f * Time::deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
		sphere3->transform->RotateBy(-50.0f * Time::deltaTime, glm::vec3(1.0f, 0.0f, 0.0f));
		sphere4->transform->RotateBy(50.0f * Time::deltaTime, glm::vec3(1.0f, 0.0f, 0.0f));

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
