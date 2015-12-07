#pragma once
#include "Resource.h"
#include "Image.h"
#include "Object.h"
#include <map>
#include <string>
class ResourceManager
{
public:

	template<typename T>
	static T* createResource(std::string filename)
	{
		if (_resources.find(filename) == _resources.end())
		{
			T *t = new T(filename);
			_resources.insert(std::make_pair<std::string, Resource*>(std::string(filename), (Resource*)t));
			return t;
		}

		std::map<std::string, Resource*>::iterator it = _resources.find(filename);

		T* output = dynamic_cast<T*>(it->second);

		return output;
	}

private:

	static std::map<std::string, Resource*> _resources;
};