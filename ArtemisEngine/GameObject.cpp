#include "GameObject.h"
GameObject::GameObject(std::string GameObjectName)
{
	name = GameObjectName;
}

GameObject::~GameObject()
{
	for (ComponentMap::iterator it = Components.begin(); it != Components.end(); it++)
	{
		delete it->second;
		it = Components.erase(it);
	}
}
