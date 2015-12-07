#pragma once
#include "Network.h"
#include "System.h"
#include "ComponentFactory.h"
#include "GameObject.h"
#include "RenderingSystem.h"


#include <vector>
#include <map>


class NetworkSystem : public System
{
public:

	NetworkSystem(Network* nw);
	~NetworkSystem();

	void Update();
	void AddNetworkComponent(NetworkComponent* nc)
	{
		NetworkComponentMap.insert(std::pair<std::string, NetworkComponent*>(nc->GetObjecti(), nc));
		NetworkedGameObjects.push_back((GameObject *)nc->GetParent());
	};

	void AddPhysSys(PhysicsSystem* physicsSystem){ PS = physicsSystem; };
	void AddRendSys(RenderingSystem* renderingSystem){ RS = renderingSystem; };
	NetworkComponent* MakeNewNetworkObject(NetworkComponent*);

private:

	void RemoveNetworkObject(NetworkComponent*);
	void UpdateComponent(NetworkComponent*);

	std::map<std::string, NetworkComponent*> NetworkComponentMap;
	std::map<std::string, NetworkComponent*>::iterator NCMIT;//NetWork Component Map Iterator

	std::vector<GameObject*> NetworkedGameObjects;
	std::vector<GameObject*>::iterator NGOIT;// Networked GameObjects Iterator

	Network* netWork;
	PhysicsSystem* PS;
	RenderingSystem* RS;

	int update;
	int hax = 0;
};

