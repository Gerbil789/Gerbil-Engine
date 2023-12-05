#pragma once
#include "../Components/Spline.h"
#include "../Engine/Material.h"
#include "../Components/Component.h"


class EnemySpawner : public IComponent
{
public:
	EnemySpawner(Spline* _spline);
	void Update() override;
private:
	Spline* spline;
	float delta = 0.0f;
	float speed = 0.25f;
	Material* m_rat;
};

