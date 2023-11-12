/**
 * @file main.cpp
 *
 * @brief Main function
 * 
 *
 * @author Vojta Rubeš
	**/

//USE C++ 17 or newer !!!

//known issues:
// lights must be definad after all other objects, otherwise it wont work correctly

#include "Application.h"

int main(void)
{
	Application* app = new Application();
	app->Init();
	app->InitScenes();
	app->Run();

}