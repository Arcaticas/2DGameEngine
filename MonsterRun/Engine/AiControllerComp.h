#pragma once
#include "GameObject.h"


class AiController : public IObjectComponents
{

public:
	GameObject* player;

	AiController(GameObject*);

	void Move(Point2D&);

	void PreUpdate(GameObject&) override;
	void Update(GameObject&) override;

};