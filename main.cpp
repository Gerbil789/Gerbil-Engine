/**
 * @file main.cpp
 *
 * @brief Main function
 * 
 *
 * @author Vojta Rubeš
	**/

//USE C++ 17 or newer !!!

#include "Application.h"

int main(void)
{
	Application* app = new Application();
	app->Init();
	app->Run();

}