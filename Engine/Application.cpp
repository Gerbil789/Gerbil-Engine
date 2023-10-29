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
	//Scene* scene = SceneManager::GetInstance().LoadScene("Forest");
	//scene->GetActiveCamera()->SetAspect(ratio);

	//------------Scene 1-------------- PHONG TEST
	/*
	Scene* scene1 = new Scene("PhongTest");
	SceneManager::GetInstance().LoadScene(scene1);


	GameObject* player_go = new GameObject("player");
	player_go->transform->SetPosition(glm::vec3(0.0f, 0.0f, 5.0f));
	player_go->AddComponent<Camera>();
	player_go->GetComponent<Camera>()->SetTarget(glm::vec3(0.0f, 0.0f, -5.0f));
	player_go->GetComponent<Camera>()->SetAspect(ratio);
	player_go->AddComponent<CameraController>(2.0f, player_go->GetComponent<Camera>());

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

	GameObject* player_go = new GameObject("player");
	player_go->transform->SetPosition(glm::vec3(0.0f, 0.0f, 5.0f));
	player_go->AddComponent<Camera>();
	player_go->GetComponent<Camera>()->SetTarget(glm::vec3(0.0f, 0.0f, -5.0f));
	player_go->GetComponent<Camera>()->SetAspect(ratio);
	player_go->AddComponent<CameraController>(2.0f, player_go->GetComponent<Camera>());
	scene->SetActiveCamera(player_go->GetComponent<Camera>());

	GameObject* sphere1 = new GameObject("sphere1");
	sphere1->AddComponent<MeshRenderer>("sphere");

	GameObject* pointLight = new GameObject("point light");
	pointLight->AddComponent<Light>(Light::POINT, Color::White);
	pointLight->transform->SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));


	scene->Add(player_go);
	scene->Add(sphere1);
	scene->Add(pointLight);

	SceneManager::GetInstance().SaveScene();
	*/
	//------------Scene 4-------------- RESIZE TEST
/*
	Scene* scene = new Scene("ResizeTest");
	SceneManager::GetInstance().LoadScene(scene);

	GameObject* player_go = new GameObject("player");
	player_go->transform->SetPosition(glm::vec3(0.0f, 0.0f, 5.0f));
	player_go->AddComponent<Camera>();
	player_go->GetComponent<Camera>()->SetTarget(glm::vec3(0.0f, 0.0f, -5.0f));
	player_go->GetComponent<Camera>()->SetAspect(ratio);
	player_go->AddComponent<CameraController>(2.0f, player_go->GetComponent<Camera>());
	scene->SetActiveCamera(player_go->GetComponent<Camera>());

	GameObject* sphere = new GameObject("sphere");
	sphere->AddComponent<MeshRenderer>("sphere");
	sphere->transform->SetPosition(glm::vec3(-6.0f, 0.0f, 0.0f));

	GameObject* torus = new GameObject("torus");
	torus->AddComponent<MeshRenderer>("torus");
	torus->transform->SetPosition(glm::vec3(-2.0f, 0.0f, 0.0f));

	GameObject* cube = new GameObject("cube");
	cube->AddComponent<MeshRenderer>("cube");
	cube->transform->SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));

	GameObject* cone = new GameObject("cone");
	cone->AddComponent<MeshRenderer>("cone");
	cone->transform->SetPosition(glm::vec3(6.0f, 0.0f, 0.0f));

	GameObject* pointLight = new GameObject("point light");
	pointLight->AddComponent<Light>(Light::POINT, Color::White);
	pointLight->transform->SetPosition(glm::vec3(0.0f, 3.0f, 5.0f));


	scene->Add(player_go);
	scene->Add(pointLight);

	scene->Add(sphere);
	scene->Add(torus);
	scene->Add(cube);
	scene->Add(cone);
	

	SceneManager::GetInstance().SaveScene();
	*/
	//------------Scene 5--------------

	Scene* scene = new Scene("Forest");
	SceneManager::GetInstance().LoadScene(scene);

	GameObject* player_go = new GameObject("player");
	player_go->transform->SetPosition(glm::vec3(0.0f, 0.0f, 5.0f));
	player_go->AddComponent<Camera>();
	player_go->GetComponent<Camera>()->SetTarget(glm::vec3(0.0f, 0.0f, -5.0f));
	player_go->GetComponent<Camera>()->SetAspect(ratio);
	player_go->AddComponent<CameraController>(2.0f, player_go->GetComponent<Camera>());
	scene->SetActiveCamera(player_go->GetComponent<Camera>());

	GameObject* plane = new GameObject("plane");
	plane->AddComponent<MeshRenderer>("plane");
	plane->transform->SetScale(glm::vec3(10.0f));

	
	scene->Add(player_go);
	
	scene->Add(plane);

	//random scatter 
	std::string types[] = { "spruce", "oak", "stump", "rock1", "rock2", "rock3"};
	std::string shaders[] = { "constant", "lambert", "phong" };
	
	for (int i = 0; i < 120; i++) {
		std::string type = types[std::rand() % 6];
		std::string shader = shaders[std::rand() % 3];
		//std::string shader = "phong";


		GameObject* go = new GameObject(type);
		MeshRenderer* meshRenderer = go->AddComponent<MeshRenderer>(type, shader, Color::Random());
		float scale = 0.3 + static_cast<float>(std::rand()) / RAND_MAX * (0.5 - 0.3);
		go->transform->SetScale(glm::vec3(scale));

		float rot = std::rand() % 360;
		go->transform->RotateBy(rot, glm::vec3(0.0f, 1.0f, 0.0f));

		float x = -10.0 + static_cast<float>(std::rand()) / RAND_MAX * (10.0 - (-10.0));
		float z = -10.0 + static_cast<float>(std::rand()) / RAND_MAX * (10.0 - (-10.0));
		go->transform->SetPosition(glm::vec3(x,0,z));
		scene->Add(go);
	}

	for (int i = 0; i < 5; i++) {
		GameObject* pointLight = new GameObject("point light");
		pointLight->AddComponent<Light>(Light::POINT, Color::White);
		float x = -10.0 + static_cast<float>(std::rand()) / RAND_MAX * (10.0 - (-10.0));
		float z = -10.0 + static_cast<float>(std::rand()) / RAND_MAX * (10.0 - (-10.0));
		pointLight->transform->SetPosition(glm::vec3(x, 2.0f, z));

		scene->Add(pointLight);
	}

	




	SceneManager::GetInstance().SaveScene();

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
