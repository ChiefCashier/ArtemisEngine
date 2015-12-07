#pragma once
#include "glew.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Component.h"
#include "Image.h"
#include "Object.h"
#include "Buffer.h"
#include <vector>

class Renderable : public Component
{
public:

	Renderable(int ID);
	~Renderable();

	void SetTexture(Image* tex) { hasTexture = true; texture = tex; };
	GLuint getTextureID()
	{
		if (hasTexture == true)
			return texture->getTextureId();
		else
			return 0;
	};

	void init(Object* obj);

	int get_indexSize(){ return _indexSize; };
	int get_vertexSize(){ return _indexSize; };

	GLfloat* get_vertices(){  return _vertices; };
	GLuint* get_indices(){ return _indices; };

	void setAlpha(float alpha){ alphaChannel = alpha; };
	float getAlpha(){ return alphaChannel; };

	

	bool hasTexture;

	GLuint vertexBuffer;
	GLuint indexBuffer;
	GLuint vertexArray;

	bool draw;

private:



	Image* texture;

	int _indexSize;
	int _vertexSize;

	GLfloat* _vertices;
	GLuint* _indices;

	float alphaChannel;



};

