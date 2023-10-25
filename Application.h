#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
//#include <cmath>

#include "../Utilities/Color.h"
#include "../Utilities/Input.h"
#include "../Utilities/Time.h"

#include "../Components/MeshRenderer.h"
#include "../Components/CameraController.h"
#include "../GameObject/GameObject.h"
#include "../Managers/ModelManager.h"
#include "../RotationScript.h"
#include "../GUI.h"


class Application
{
public:
	void Init();
	void InitScenes();
	void Run();
private:
	GLFWwindow* window;
	int width, height;
	float ratio;
	

};

