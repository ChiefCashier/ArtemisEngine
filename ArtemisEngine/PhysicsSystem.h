#pragma once
#include "System.h"
#include "Physics.h"
#include "glm\common.hpp"
#include <vector>
#include <map>
class PhysicsSystem : public System
{
public:

	PhysicsSystem(float gravity);
	~PhysicsSystem();

	void AddPhysicsComponent(Physics* physComp);
	void DeletePhysicsComponent(Physics* physComp);
	void Update(){ Update(deltaTime); };
	void Update(double deltaTime);

	void UpdateCollisionMap(Physics* comp);

	void SetGravity(float g){ gravity = g; };
	float deltaTime;

private:

	void Collision(Physics* comp);
	void UpdateForces(Physics* comp);
	void UpdateSpeed(Physics* comp);
	void UpdateAngularSpeed(Physics* comp, int x);

	float gravity;

	std::vector<Physics*> physicsComponents;
	std::vector<Physics*>::iterator PCIT;
	std::vector<Physics*>::iterator PCIT2;


	std::map<unsigned int, unsigned int> CollisionMap;
};

