#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>

#include "../Scene.h"
#include "../GameObject/GameObject.h"
#include "../Managers/ModelManager.h"
#include "../Utilities/Color.h"
#include "../Utilities/Input.h"
#include "../Utilities/Time.h"
#include "../Components/CameraController.h"
#include "../Components/SpriteRenderer.h"
#include "../Components/MeshRenderer.h"
#include "../Components/Camera.h"
#include "../GUI.h"
#include "../Components/PointLight.h"


class Application
{
public:
	void Init();
	void Run();
private:
	GLFWwindow* window;
	int width, height;
	float ratio;
	

};

