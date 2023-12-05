#include "Enemy.h"
#include "../Managers/SceneManager.h"
#include "../Engine/GameObject.h"


void Enemy::Kill()
{
	//coin
	GameObject* coin = new GameObject("coin_sprite");
	coin->AddComponent<SpriteRenderer>("Textures/coin.png");
	coin->transform->SetPosition(this->transform->GetPosition() + glm::vec3(0.0f, 1.0f, 0.0f));
	coin->transform->SetRotation(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	coin->AddComponent<RotationScript>(200.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	SceneManager::GetInstance().GetActiveScene()->Add(coin);




	//destroy itself
	this->gameObject->Destroy();
}
