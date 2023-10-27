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

	SceneManager::GetInstance().Init();
}

void Application::InitScenes()
{
	//------------Scene 1--------------
	Scene* scene1 = new Scene();
	SceneManager::GetInstance().AddScene(scene1);


	GameObject* player_go = new GameObject("player");
	player_go->transform->SetPosition(glm::vec3(0.0f, 0.0f, 5.0f));
	player_go->AddComponent<Camera>();
	player_go->GetComponent<Camera>()->SetTarget(glm::vec3(0.0f, 0.0f, -5.0f));
	player_go->GetComponent<Camera>()->SetAspect(ratio);
	player_go->AddComponent<CameraController>(player_go->GetComponent<Camera>());
	glfwSetCursorPosCallback(window, player_go->GetComponent<CameraController>()->cursor_callback);

	GameObject* sphere1 = new GameObject("sphere1");
	sphere1->AddComponent<MeshRenderer>("sphere");
	sphere1->transform->SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));

	GameObject* sphere2 = new GameObject("sphere2");
	sphere2->AddComponent<MeshRenderer>("sphere");
	sphere2->transform->SetPosition(glm::vec3(-2.0f, 0.0f, 0.0f));

	GameObject* sphere3 = new GameObject("sphere3");
	sphere3->AddComponent<MeshRenderer>("sphere");
	sphere3->transform->SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));

	GameObject* sphere4 = new GameObject("sphere4");
	sphere4->AddComponent<MeshRenderer>("sphere");
	sphere4->transform->SetPosition(glm::vec3(0.0f, -2.0f, 0.0f));

	GameObject* pointLight = new GameObject("point light");
	pointLight->AddComponent<Light>(Light::POINT, Color::White);


	scene1->Add(player_go);
	scene1->Add(sphere1);
	scene1->Add(sphere2);
	scene1->Add(sphere3);
	scene1->Add(sphere4);
	scene1->Add(pointLight);

	scene1->SetActiveCamera(player_go->GetComponent<Camera>());
	
	Serializer::SerializeToJson(scene1);

	//------------Scene 2--------------
	/*GameObject* empty = new GameObject("empty");
	empty->AddComponent<RotationScript>(-100);

	GameObject* sun = new GameObject("sun");
	sun->AddComponent<MeshRenderer>("sphere", Color::Yellow);
	sun->transform->SetScale(glm::vec3(3.0f));
	sun->AddComponent<RotationScript>();

	GameObject* earth = new GameObject("earth");
	earth->AddComponent<MeshRenderer>("sphere", Color::Blue, "phong", 4.0f);
	earth->transform->SetPosition(glm::vec3(-9.0f, 0.0f, 0.0f));
	earth->transform->SetScale(glm::vec3(1.2));
	earth->AddComponent<RotationScript>(500.0f);

	GameObject* moon = new GameObject("moon");
	moon->AddComponent<MeshRenderer>("sphere", Color::Gray);
	moon->transform->SetPosition(glm::vec3(-4.0f, 0.0f, 0.0f));
	moon->transform->SetScale(glm::vec3(0.4f));
	moon->AddComponent<RotationScript>(150.0f);

	GameObject* mars = new GameObject("mars");
	mars->AddComponent<MeshRenderer>("sphere", Color::Red);
	mars->transform->SetPosition(glm::vec3(-5.0f, 0.0f, 0.0f));
	mars->transform->SetScale(glm::vec3(0.5f));
	mars->AddComponent<RotationScript>(-350.0f);

	GameObject* pointLight1 = new GameObject("point light");
	pointLight1->AddComponent<Light>(Light::POINT, Color::White);
	pointLight1->transform->SetPosition(glm::vec3(20.0f, 5.0f, 0.0f));

	GameObject* pointLight2 = new GameObject("point light");
	pointLight2->AddComponent<Light>(Light::POINT, Color::White);
	pointLight2->transform->SetPosition(glm::vec3(-20.0f, 5.0f, 0.0f));

	GameObject* pointLight3 = new GameObject("point light");
	pointLight3->AddComponent<Light>(Light::POINT, Color::White);
	pointLight3->transform->SetPosition(glm::vec3(0.0f, 5.0f, 20.0f));

	GameObject* pointLight4 = new GameObject("point light");
	pointLight4->AddComponent<Light>(Light::POINT, Color::White);
	pointLight4->transform->SetPosition(glm::vec3(0.0f, 5.0f, -20.0f));


	empty->AddChildren(earth);
	earth->AddChildren(moon);
	sun->AddChildren(mars);

	Scene* scene2 = new Scene();
	scene2->Add(player_go);
	scene2->Add(empty);
	scene2->Add(sun);
	scene2->Add(earth);
	scene2->Add(moon);
	scene2->Add(mars);
	scene2->Add(pointLight1);
	scene2->Add(pointLight2);
	scene2->Add(pointLight3);
	scene2->Add(pointLight4);

	scene2->SetActiveCamera(player_go->GetComponent<Camera>());

	SceneManager::GetInstance().AddScene(scene2);
	SceneManager::GetInstance().SetActiveScene(scene2);*/

	//------------Scene 3--------------
	//------------Scene 4--------------
	//------------Scene 5--------------

}

void Application::Run()
{
	//GUI gui(window, scene);

	while (!glfwWindowShouldClose(window)) {

		if (Input::IsKeyDown(GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}


		Time::Update();

		//sphere1->transform->RotateBy(-50.0f * Time::deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
		//sphere2->transform->RotateBy(50.0f * Time::deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
		//sphere3->transform->RotateBy(-50.0f * Time::deltaTime, glm::vec3(1.0f, 0.0f, 0.0f));
		//sphere4->transform->RotateBy(50.0f * Time::deltaTime, glm::vec3(1.0f, 0.0f, 0.0f));


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		SceneManager::GetInstance().GetActiveScene()->Update();
		
		glfwPollEvents();
		//gui.Update();
		glfwSwapBuffers(window);
	}

	//gui.Dispose();
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
