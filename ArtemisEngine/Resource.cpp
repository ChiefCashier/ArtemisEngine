#include "Resource.h"


Resource::Resource(std::string name)
{
	this->_name = name;
}


Resource::~Resource()
{
}
std::string Resource::getName()
{
	return _name;
}