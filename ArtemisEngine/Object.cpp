#include "Object.h"
#include "ObjectLoader.h"

Object::Object() : Resource("")
{

}

Object::Object(std::string path) : Resource(path)
{
	ObjectLoader OLO;
	Object* temp = OLO.LoadObject(path);
	this->_indexSize = temp->_indexSize;
	this->_vertexSize = temp->_vertexSize;
	this->_vertices = temp->_vertices;
	this->vertexBuffer = temp->vertexBuffer;
	this->indexBuffer = temp->indexBuffer;
	this->vertexArray = temp->vertexArray;

	delete temp;
}


Object::~Object()
{
}

