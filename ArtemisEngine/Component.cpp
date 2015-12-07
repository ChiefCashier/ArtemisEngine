#include "Component.h"


Component::Component(int ID)
{
	componentId = ID;
	parent = nullptr;
}


Component::~Component()
{
}

