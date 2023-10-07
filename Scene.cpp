#include "Scene.h"
#include "ShaderLib.h"

Scene::Scene()
{

	
}

void Scene::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	


	objectManager.DrawObjects();
}


void Scene::Dispose()
{
	this->objectManager.Dispose();
}

void Scene::Add(GameObject* object)
{
	this->objectManager.Add(object);
}

ObjectManager& Scene::GetObjectManager()
{
	return this->objectManager;
}