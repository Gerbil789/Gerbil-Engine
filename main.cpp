/**
 * @file main.cpp
 *
 * @brief Main function
 * 
 *
 * @author Vojta Rubeš
	**/

//USE C++ 17 or newer !!!
//It wont compile otherwise

#include "Application.h"


int main(void)
{
	Application* app = new Application();
	app->Init();

}