#include "NetworkComponent.h"


NetworkComponent::NetworkComponent(int ID) : Component(ID)
{
	command = "init";
	object = "";
	texture = "";

	origin  = Vector3<float>(0, 0, 0);
	rotation = Vector3<float>(0, 0, 0);
	velocity = Vector3<float>(0, 0, 0);
	force = Vector3<float>(0, 0, 0);
}

NetworkComponent::NetworkComponent(
	int ID,
	std::string command,	 std::string object,	std::string texture,
	Vector3<float> origin,	 Vector3<float> rotation,
	Vector3<float> velocity, Vector3<float> force
	) : Component(ID)
{
	this->command = command;
	this->object = object;
	this->texture = texture;
	this->origin = origin;
	this->rotation = rotation;
	this->velocity = velocity;
	this->force = force;
}

NetworkComponent::~NetworkComponent()
{
}
