#pragma once
#include "GameObject.h"


class PlayerController : public IObjectComponents
{

public:
	char input;

	PlayerController();

	void GetInput(char);
	void Move(Point2D pos);

	void PreUpdate(GameObject&) override;
	void Update(GameObject&) override;

};