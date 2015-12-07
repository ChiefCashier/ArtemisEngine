#pragma once
#include "Renderable.h"
#include "Transformable.h"
#include "PhysicsSystem.h"
#include "ResourceManager.h"
#include "ObjectLoader.h"
#include "NetworkComponent.h"

static unsigned int ID = 0;
class ComponentFactory
{ 
public:
	static Renderable* CreateRenderable(std::string object, std::string  texture)
	{
		//ObjectLoader OLO;
		Renderable* temp = new Renderable(ID);
		ID++;
		//temp->init(OLO.LoadObject(object));
		temp->init(ResourceManager::createResource<Object>(object));
		temp->SetTexture(ResourceManager::createResource<Image>(texture));

		return temp;
	};
	static Transformable* CreateTransformable()
	{
		Transformable* temp = CreateTransformable(0,0,0,0,0,0);

		return temp;
	};
	static Transformable* CreateTransformable(float x, float y, float z, float rx, float ry, float rz)
	{
		Transformable* temp = new Transformable(ID);
		ID++;

		temp->SetOrigin(x, y, z);
		temp->SetRotation(rx, ry, rz);

		return temp;
	};
	static Physics* CreatePhysicsComponent(PhysicsSystem* asd)
	{
		Physics* temp = new Physics(ID);
		ID++;

		temp->SetElasticity(1.0);
		temp->SetForces(Vector3<float>(0.0f, 0.0f, 0.0f));
		temp->SetMass(10);
		temp->SetSpeed(Vector3<float>(0.0f, 0.0f, 0.0f));
		temp->SetAngularSpeed(Vector3<float>(0.0f, 0.0f, 0.0f));
		temp->SetFriction(0.3f);

		asd->AddPhysicsComponent(temp);

		return temp;
	};
	static NetworkComponent* CreateNetworkComponent(Physics* P, Transformable* T, char* object, char* texture)
	{
		NetworkComponent* temp = new NetworkComponent(ID, "init", object, texture, T->GetOrigin(), T->GetRotation(), P->GetSpeed(), P->GetForces());
		ID++;

		return temp;
	};
private:

};
