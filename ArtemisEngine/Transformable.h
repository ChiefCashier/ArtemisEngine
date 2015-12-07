#pragma once
#include "Component.h"
#include "Object.h"
#include "Vector3.h"

class Transformable : public Component
{
public:

	Transformable(int ID);
	~Transformable();

	void SetOrigin(float XPosition, float YPosition, float ZPosition)
	{
		position.x = XPosition;
		position.y = YPosition;
		position.z = ZPosition;
	};
	void SetOrigin(Vector3<float> Position)
	{
		position = Position;
	};

	Vector3<float> GetOrigin()
	{
		return position;
	};

	void SetRotation(float xrotation, float yrotation, float zrotation)
	{
		rotation.x = xrotation;
		rotation.y = yrotation;
		rotation.z = zrotation;
	};
	void SetRotation(Vector3<float> Rotation)
	{
		rotation = Rotation;
	};

	Vector3<float> GetRotation()
	{
		return rotation;
	};

private:

	Vector3<float> position;
	Vector3<float> rotation;

};

