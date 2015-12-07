#pragma once
#include <string>
class Resource
{
public:
	Resource(std::string name);
	virtual ~Resource() = 0;

	std::string getName();

private:

	std::string _name;
};

