#include "NetworkSystem.h"


NetworkSystem::NetworkSystem(Network *nw)
{
	netWork = nw;
	update = 0;
}


NetworkSystem::~NetworkSystem()
{
}

void NetworkSystem::Update()
{
	std::vector<NetworkComponent*> list = netWork->GetListOfRequests();

	if (list.size() > 0); // get reguests from netWork
	{
		for (int i = list.size() - 1; i >= 0; i--)
		{
			if (list[i]->GetCommand().compare("NewComp") == 0)
			{
				NetworkComponent* nci = list[i];
				nci = MakeNewNetworkObject(nci);
				nci->SetCommand("Update");
			}
			else if (list[i]->GetCommand().compare("DeleteComp") == 0)
			{
				RemoveNetworkObject(list[i]);
			}
			else if (list[i]->GetCommand().compare("Update") == 0)
			{
				UpdateComponent(list[i]);
				NCMIT = NetworkComponentMap.find(list[i]->GetObjecti());
				if (NCMIT != NetworkComponentMap.end())
				{
					UpdateComponent(list[i]);
				}
				else
					printf("Network component not in Map");
			}
			else
				printf("Unknown command from network component");
		}
		
	}
	netWork->EmptyListOfRequests();
	NCMIT = NetworkComponentMap.begin();
	if (update < 1)
		update++;
	else
	{
		update = 0;
		while (NCMIT != NetworkComponentMap.end())
		{
			netWork->Send(NCMIT->second->MsgForm());
			NCMIT->second->SetCommand("Update");
			NCMIT++;
		}
	}
}


NetworkComponent* NetworkSystem::MakeNewNetworkObject(NetworkComponent* nc)
{
	if (NetworkComponentMap.find(nc->GetObjecti()) != NetworkComponentMap.end())
	{
		std::string str = nc->GetObjecti();
		str.insert(str.size() - 4, std::to_string(hax));
		nc->SetObject(str);
		hax++;
	}


	NetworkComponent* nci = nc;
	GameObject* obj = new GameObject(nci->GetObjecti());
	std::string object = nci->GetObjecti();
	std::string texture = nci->GetTexture();
	Renderable* rendComp = ComponentFactory::CreateRenderable(nci->GetObjecti(), nci->GetTexture());
	Transformable* transComp = ComponentFactory::CreateTransformable(
		nci->GetOrigin().x, nci->GetOrigin().y, nci->GetOrigin().z,
		nci->GetRotation().x, nci->GetRotation().y, nci->GetRotation().z
		);
	obj->AddComponent(rendComp);
	obj->AddComponent(transComp);
	if (PS != nullptr)
	{
		Physics* physz1 = ComponentFactory::CreatePhysicsComponent(PS);
		physz1->SetForces(nci->GetForce());
		physz1->SetSpeed(nci->GetVelocity());
		obj->AddComponent(physz1);
	}
	obj->AddComponent(nci);
	RS->Draw(obj);
	NetworkedGameObjects.push_back(obj);
	nc->SetCommand("NewComp");

	NetworkComponentMap.insert(std::pair<std::string, NetworkComponent*>(nci->GetObjecti(), nci));

	return nc;
}
void NetworkSystem::RemoveNetworkObject(NetworkComponent* nc)
{
	NGOIT = NetworkedGameObjects.begin();
	while (NGOIT != NetworkedGameObjects.end())
	{
		if ((*NGOIT)->GetComponent<NetworkComponent>()->GetObjecti().compare(nc->GetObjecti()))
		{
			delete *NGOIT;
			NGOIT = NetworkedGameObjects.erase(NGOIT);
		}
		else
			NGOIT++;
	}
}
void NetworkSystem::UpdateComponent(NetworkComponent* nc)
{
	NCMIT = NetworkComponentMap.find(nc->GetObjecti());

	GameObject* updatedGO = (GameObject*)NCMIT->second->GetParent();
	Transformable* trans = updatedGO->GetComponent<Transformable>();
	Physics* phys = updatedGO->GetComponent<Physics>();
	NetworkComponent* net = updatedGO->GetComponent<NetworkComponent>();

	if (netWork->IsServer())
	{
		net->SetForce(nc->GetForce());
		phys->SetForces(nc->GetForce());

		NCMIT->second->SetRotation(trans->GetRotation());
		NCMIT->second->SetOrigin(trans->GetOrigin());

		NCMIT->second->SetVelocity(phys->GetSpeed());
		//NCMIT->second->SetForce(phys->GetForces());
	}
	else
	{
		trans->SetOrigin(nc->GetOrigin());
		trans->SetRotation(nc->GetRotation());
		phys->SetSpeed(nc->GetVelocity());
		net->SetOrigin(nc->GetOrigin());
		net->SetVelocity(nc->GetVelocity());
		net->SetRotation(nc->GetRotation());
	}

	


	//NGOIT = NetworkedGameObjects.begin();
	//while (NGOIT != NetworkedGameObjects.end())
	//{
	//	if ((*NGOIT)->GetComponent<NetworkComponent>()->GetObjecti().compare(nc->GetObjecti()) == 0)
	//	{
	//		(*NGOIT) = updatedGO;
	//		NGOIT++;
	//	}
	//	else
	//		NGOIT++;
	//}
}