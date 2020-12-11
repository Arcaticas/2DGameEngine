#include <cassert>
#include <vector>
#include<typeinfo>
#include "GameObject.h"

GameObject::GameObject()
{
    position = Point2D();
}

GameObject::GameObject(int x, int y)
{
    position = Point2D(x,y);
}


void GameObject::Attach(IObjectComponents* comp)
{
    if (comp)
    {
        components.push_back(comp);
    }
}

void GameObject::UpdateObject()
{

}

