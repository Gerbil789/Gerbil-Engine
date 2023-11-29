#include "Application.h"


static void error_callback(int error, const char* description) { fputs(description, stderr); }

static void window_size_callback(GLFWwindow* window, int _width, int _height) {
	
	printf("resize %d, %d \n", _width, _height);
	SceneManager::GetInstance().GetActiveScene()->GetActiveCamera()->SetAspect((float)_width / _height);

	glViewport(0, 0, _width, _height);
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
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

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
	this->activeScene = scene1;

	Material* m_test_grid = new Material("Textures/test_grid.png", "m_test_grid");
	Material* m_gun = new Material("Textures/gun_color.png", "m_gun");

	//player
	GameObject* player_go = new GameObject("player");
	player_go->AddComponent<Camera>();
	Camera* cam = player_go->GetComponent<Camera>();
	player_go->GetComponent<Camera>()->SetAspect(ratio);
	player_go->AddComponent<CameraController>(2.0f, player_go->GetComponent<Camera>());
	player_go->transform->SetPosition(glm::vec3(0.0f, 5.0f, 0.0f));
	scene1->Add(player_go);

	//spline
	std::vector<glm::vec3> controlPoints = {
			 glm::vec3(0.0f, 0.0f, 0.0f),
			 glm::vec3(1.0f, 5.0f, 5.0f),
			 glm::vec3(4.0f, 5.0f, -5.0f),
			 glm::vec3(5.0f, 0.0f, 0.0f)
	};
	
	GameObject* spline = new GameObject("Spline");
	Spline* splineComponent = spline->AddComponent<Spline>(controlPoints, false);
	splineComponent->Draw();
	scene1->Add(spline);

	GameObject* sphere = new GameObject("sphere_on_spline");
	sphere->AddComponent<MeshRenderer>();
	sphere->AddComponent<MoveOnSplineScript>(splineComponent);
	sphere->AddComponent<RotationScript>(100.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	scene1->Add(sphere);

	//ground
	GameObject* ground = new GameObject("ground");
	ground->AddComponent<MeshRenderer>("plane", "phong", Color::White, m_test_grid);
	ground->transform->SetScale(glm::vec3(20.0f));
	scene1->Add(ground);

	//coin
	GameObject* coin = new GameObject("coin_sprite");
	coin->AddComponent<SpriteRenderer>("Textures/coin.png");
	coin->transform->SetPosition(glm::vec3(8.0f, 2.0f, 0.0f));
	coin->transform->SetRotation(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	coin->AddComponent<RotationScript>(100.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	scene1->Add(coin);

	//skulls
	GameObject* skulls = new GameObject("skulls_sprite");
	skulls->AddComponent<SpriteRenderer>("Textures/skulls.png");
	skulls->transform->SetScale(glm::vec3(3.0f * 3, 0.0f, 0.7f * 3));
	skulls->transform->SetPosition(glm::vec3(-10.0f, 3.0f, 0.0f));
	skulls->transform->RotateBy(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	skulls->transform->RotateBy(90.0f, glm::vec3(0.0f, -1.0f, 0.0f));
	scene1->Add(skulls);

	//gun
	GameObject* gun_frame = new GameObject("gun");
	gun_frame->AddComponent<MeshRenderer>("gun_frame", "phong", Color::White, m_gun);
	gun_frame->transform->SetPosition(glm::vec3(0.0f, 5.0f, 0.0f));
	gun_frame->AddComponent<RotationScript>(200.0f, glm::vec3(1.0f));
	scene1->Add(gun_frame);

	GameObject* gun_slide = new GameObject("slider");
	gun_slide->AddComponent<MeshRenderer>("gun_slide", "phong", Color::White, m_gun);
	gun_frame->AddChildren(gun_slide);
	scene1->Add(gun_slide);

	GameObject* gun_trigger = new GameObject("trigger");
	gun_trigger->AddComponent<MeshRenderer>("gun_trigger", "phong", Color::White, m_gun);
	gun_frame->AddChildren(gun_trigger);
	gun_trigger->transform->SetPosition(glm::vec3(0.0f, -0.05f, 0.1f));
	scene1->Add(gun_trigger);

	GameObject* gun_hammer = new GameObject("hammer");
	gun_hammer->AddComponent<MeshRenderer>("gun_hammer", "phong", Color::White, m_gun);
	gun_frame->AddChildren(gun_hammer);
	gun_hammer->transform->SetPosition(glm::vec3(0.0f, -0.035f, -0.13f));
	scene1->Add(gun_hammer);

	GameObject* gun_silencer = new GameObject("silencer");
	gun_silencer->AddComponent<MeshRenderer>("gun_silencer", "phong", Color::White, m_gun);
	gun_frame->AddChildren(gun_silencer);
	scene1->Add(gun_silencer);

	//cats
	std::string cats[] = { "Textures/cat1.jpg", "Textures/cat2.jpg", "Textures/cat3.jpg", "Textures/cat4.jpg", "Textures/cat5.jpg", "Textures/cat6.jpg", "Textures/cat7.jpg", "Textures/cat8.jpg" };
	for (int i = 0; i < 8; i++) {
		GameObject* cat = new GameObject("cat_sprite");
		cat->AddComponent<SpriteRenderer>(cats[i]);
		cat->transform->SetScale(glm::vec3(1.0f * 2, 0.0f, 1.46f * 2));
		cat->transform->SetPosition(glm::vec3(10.0f, 3.0f, -17.5f + i * 5.0f));
		cat->transform->RotateBy(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		cat->transform->RotateBy(90.0f, glm::vec3(0.0f, -1.0f, 0.0f));
		scene1->Add(cat);
	}


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
	Material* m_test_grid = new Material("Textures/test_grid.png", "m_test_grid");

	MoveOnSplineScript* tmp = activeScene->GetObjectManager().GetGameObject("sphere_on_spline")->GetComponent<MoveOnSplineScript>();
	float t = 0;
	float speed = 0.5f;

	GUI gui(window, SceneManager::GetInstance().GetActiveScene());
	while (!glfwWindowShouldClose(window)) {

		if (Input::IsKeyDown(GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		Time::Update();

		//[TMP]spline testing
		if (Input::IsKeyDown(GLFW_KEY_UP)) {
			t += Time::deltaTime * speed;
			t = std::clamp(t, 0.0f, 1.0f);
			tmp->Move(t);
		}

		if (Input::IsKeyDown(GLFW_KEY_DOWN)) {
			t -= Time::deltaTime * speed;
			t = std::clamp(t, 0.0f, 1.0f);
			tmp->Move(t);
		}

		activeScene->Update();

		//todo: make a controller class for flashlight instead of this line
		SceneManager::GetInstance().GetActiveScene()->GetObjectManager().GetGameObject("flash light")->GetComponent<SpotLight>()->SetDirection(SceneManager::GetInstance().GetActiveScene()->GetActiveCamera()->GetFront());

		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);

		GLbyte color[4];
		GLfloat depth;
		GLuint index;

		//center of the screen
		GLint x = viewport[2] / 2;
		GLint y = viewport[3] / 2;

		//GLint x = Input::GetMouseX();
		//GLint y = Input::GetMouseY();

		//int newy = viewport[3] - y; //WHY?
		//glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		//glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		//glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

		glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

		//glm::vec3 screenX = glm::vec3(x, newy, depth);
		glm::vec3 screenCenter = glm::vec3(x, y, depth);
		
		glm::mat4 view = ShaderManager::GetInstance().GetShaderProgram(ShaderManager::GetInstance().GetShaderProgramId("phong"))->viewMatrix;
		glm::mat4 projection = ShaderManager::GetInstance().GetShaderProgram(ShaderManager::GetInstance().GetShaderProgramId("phong"))->projectionMatrix;
		
		
		glm::vec4 viewPort = glm::vec4(0, 0, viewport[2], viewport[3]);
		glm::vec3 pos = glm::unProject(screenCenter, view, projection, viewPort); // mouse position

		if (Input::IsMouseButtonClicked(0) && index > 2) {
			//printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth% f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);
			//printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);
			//printf("Name %s\n", SceneManager::GetInstance().GetActiveScene()->GetObjectManager().GetGameObject(index)->GetName().c_str());

			GameObject* sphere = new GameObject("sphere");
			sphere->AddComponent<MeshRenderer>("sphere", "constant", Color::Random());
			sphere->transform->SetPosition(glm::vec3(pos.x, pos.y, pos.z));
			sphere->AddComponent<RotationScript>(200.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			activeScene->Add(sphere);

			sphere->Destroy(5.0f); //delete sphere after 5 sec
		}		

		glfwPollEvents();
		gui.Update();
		glfwSwapBuffers(window);
	}

	gui.Dispose();
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
