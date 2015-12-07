#include "Transformable.h"


Transformable::Transformable(int ID) : Component(ID)
{
	position.x = 0;
	position.y = 0;
	position.z = 0;

	rotation.x = 0;
	rotation.y = 0;
	rotation.z = 0;
}


Transformable::~Transformable()
{
}
