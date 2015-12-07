#include "Renderable.h"


Renderable::Renderable(int ID) : Component(ID)
{
	//Hello darkness my old friend
	draw = true;
}


Renderable::~Renderable()
{
	//the sound of silence
}

void Renderable::init(Object* tempObj)
{
	_indexSize = tempObj->_indexSize;
	_vertexSize = tempObj->_vertexSize;

	_vertices = tempObj->_vertices;
	_indices = tempObj->_indices;

	vertexBuffer = tempObj->vertexBuffer;
	indexBuffer = tempObj->indexBuffer;
	vertexArray = tempObj->vertexArray;

	alphaChannel = 0;
}
