#include "Physics.h"


Physics::Physics(int ID) : Component(ID)
{
	mass = 0;
	elasticity = 0;
	speed = {0,0,0};
	collision = false;
}


Physics::~Physics()
{
}

float Physics::GetMass()
{
	return mass;
}

float Physics::GetElasticity()
{
	return elasticity;
}

Vector3<float> Physics::GetSpeed()
{
	return speed;
}

Vector3<float> Physics::GetAngularSpeed()
{
	return angularSpeed;
}

Vector3<float> Physics::GetForces()
{
	return forces;
}
float Physics::GetFriction()
{
	return friction;
}

void Physics::SetMass(float m)
{
	mass = m;
}

void Physics::SetElasticity(float e)
{
	elasticity = e;
}

void Physics::SetSpeed(Vector3<float> s)
{
	speed = s;
}

void Physics::SetAngularSpeed(Vector3<float> s)
{
	angularSpeed = s;
}

void Physics::SetForces(Vector3<float> f)
{
	forces = f;
}

void Physics::SetFriction(float f)
{
	friction = f;
}