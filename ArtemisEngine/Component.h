#pragma once
class Component
{
enum IDENTIFIER
	{
		RENDERABLE,
		TRANSFORMABLE
	};
public:

	Component(int ID);
	virtual ~Component();
	class GameObject;
	void AddParent(void* GO) { parent = (GameObject*)GO; };
	void DeleteParent() { parent = nullptr; };
	GameObject* GetParent() { return parent; };
	unsigned int componentId;

protected:

	GameObject* parent;
};

