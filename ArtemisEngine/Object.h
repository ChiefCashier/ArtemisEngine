#pragma once
#include "glew.h"
#include "Resource.h"
#include <string>

class Object : public Resource
{
public:

	Object();
	Object(std::string path);
	~Object();

	int _indexSize;
	int _vertexSize;

	GLfloat* _vertices;
	GLuint* _indices;

	GLuint vertexBuffer;
	GLuint indexBuffer;
	GLuint vertexArray;

private:

};

