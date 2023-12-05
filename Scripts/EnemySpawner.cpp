#include "EnemySpawner.h"
#include "../Components/MeshRenderer.h"
#include "../Scripts/MoveOnSplineScript.h"
#include "../Scripts/Enemy.h"
#include "../Utilities/Time.h"

EnemySpawner::EnemySpawner(Spline* _spline)
{
	spline = _spline;
	m_rat = new Material("Textures/rattex.jpeg", "m_rat");
}

void EnemySpawner::Update()
{
	if (delta == 0.0f) {

		//spawn rat
		GameObject* rat = new GameObject("rat");
		rat->AddComponent<Enemy>();
		rat->AddComponent<MeshRenderer>("rat", "phong", Color::White, m_rat);
		rat->AddComponent<MoveOnSplineScript>(spline);
		rat->transform->SetScale(glm::vec3(0.5f));
		rat->transform->SetRotation(-90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		SceneManager::GetInstance().GetActiveScene()->Add(rat);
	}


	delta += Time::deltaTime * speed;

	if (delta >= 1.0f) {
		delta = 0.0f;
	}
}
