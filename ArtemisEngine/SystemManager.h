#pragma once
#include "PhysicsSystem.h"
#include "RenderingSystem.h"
class SystemManager
{
public:

	SystemManager();
	~SystemManager();

	void AddSystem(System*  system)
	{
		Systems.insert(std::pair<const std::type_info*, System*>(&typeid(*system), system));
	};


	template<typename T>
	T* GetSystem()
	{
		SystemMap::const_iterator pos = Systems.find(&typeid(T));
		if (pos == Systems.end())
			return nullptr;
		else
			return static_cast<T*>(pos->second);
	};

	void UpdateSystems()
	{
		SystemMap::const_iterator pos = Systems.begin();
		while (pos != Systems.end())
		{
			pos->second->Update();
			pos++;
		}
			
	};

private:

	using SystemMap = std::unordered_map < const std::type_info*, System* >;

	SystemMap Systems;
};

