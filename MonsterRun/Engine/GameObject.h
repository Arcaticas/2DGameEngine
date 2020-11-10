#pragma once
#include <vector>
#include "Point2D.h"


class IObjectComponents {
public:
	virtual void PreUpdate(GameObject& obj) = 0;
	virtual void Update(GameObject& obj) = 0;
};

class GameObject {

public:
	GameObject();
	GameObject(int, int);
	~GameObject();
	void Attach(IObjectComponents* );
	virtual void UpdateObject();

	std::vector<IObjectComponents*> components;
	Point2D position;
};