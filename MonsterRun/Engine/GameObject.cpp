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

GameObject::~GameObject()
{
    const size_t count = components.size();
    for (size_t i = 0; i < count; i++)
    {
        assert(components[i]);
        delete components[i];
    }
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

