#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "../Utilities/Color.h"
#include "../Utilities/Input.h"
#include "../Utilities/Time.h"
#include "../Utilities/Serializer.h"

#include "../Components/MeshRenderer.h"
#include "../Components/CameraController.h"
#include "../Engine/GameObject.h"
#include "../Managers/ModelManager.h"
#include "../Scripts/RotationScript.h"
#include "../GUI/GUI.h"
#include "../PointLight.h"
#include "../SpotLight.h"
#include "../DirectionalLight.h"


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

