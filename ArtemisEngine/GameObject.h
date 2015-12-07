#pragma once
#include "glew.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Transformable.h"
#include "Renderable.h"
#include "Image.h"
#include "Buffer.h"
#include <vector>
#include <string>
#include <iostream>
#include <typeinfo>
#include <unordered_map>

class GameObject
{
public:

	
	GameObject();
	GameObject(std::string GameObjectName);
	~GameObject();

	void AddComponent(Component* component)
	{
		Components.insert(std::pair<const std::type_info*, Component*>(&typeid(*component), component));
		component->AddParent(this);
	};

	void DeleteComponent(Component* component)
	{
		ComponentMap::const_iterator pos = Components.find(&typeid(*component));
		if (pos == Components.end())
			return;
					
		pos->second->DeleteParent();
		//delete pos->second;
		Components.erase(pos->first);
		
	};

	template<typename T>
	T* GetComponent()
	{
		ComponentMap::const_iterator pos = Components.find(&typeid(T));
		if (pos == Components.end())
			return nullptr;
		else
			return static_cast<T*>(pos->second);
	};

private:

	using ComponentMap = std::unordered_map < const std::type_info*, Component* >;
	
	ComponentMap Components;

	std::string name;
};

