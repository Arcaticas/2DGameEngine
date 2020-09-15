#pragma once
#ifndef OBJECT2D
#define OBJECT2D
#include "Point2D.h"



class Object2D : public Point2D
{
private:
	const char* name;

public:
	Object2D();
	Object2D(char*);
	Object2D(char*, int, int);
	Object2D(char*, int, int, int, int);

	char getName() { return *name; }
};

#endif




