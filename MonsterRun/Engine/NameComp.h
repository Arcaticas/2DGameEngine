#pragma once
#include "GameObject.h"

class Name : public IObjectComponents
{
public:
	const char* name;

	Name();
	Name(const char*);

	const char* getName() { return name; }

	void PreUpdate(GameObject&) override;
	void Update(GameObject&) override;
};