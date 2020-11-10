#include "AiControllerComp.h"


AiController::AiController(GameObject* target)
{
	player = target;
}

void AiController::Move(Point2D& pos)
{
	if (player->position.getXPosition() > pos.getXPosition())
	{
		pos.setXPosition(pos.getXPosition() + 1);
		if (player->position.getYPosition() > pos.getYPosition())
		{
			pos.setYPosition(pos.getYPosition() + 1);
		}
		else if (player->position.getYPosition() < pos.getYPosition())
		{
			pos.setYPosition(pos.getYPosition() - 1);
		}
		else
		{
			pos.setXPosition(pos.getXPosition() + 1);
		}

	}
	else if (player->position.getXPosition() < pos.getXPosition())
	{
		pos.setXPosition(pos.getXPosition() - 1);
		if (player->position.getYPosition() > pos.getYPosition())
		{
			pos.setYPosition(pos.getYPosition() + 1);
		}
		else if (player->position.getYPosition() < pos.getYPosition())
		{
			pos.setYPosition(pos.getYPosition() - 1);
		}
		else
		{
			pos.setXPosition(pos.getXPosition() - 1);
		}

	}
	else
	{
		pos.setYPosition(pos.getYPosition() + 2);
	}
}

void AiController::Update(GameObject& obj)
{
	Move(obj.position);
}
