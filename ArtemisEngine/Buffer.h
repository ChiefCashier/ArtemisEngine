#pragma once
#ifndef BUFFER_H
#define BUFFER_H
#include "glew.h"
class Buffer
{
public:
	Buffer(){};

	Buffer(GLuint buffer)//GL_ELEMENT_ARRAY_BUFFER OR GL_ARRAY_BUFFER
	{
		//bufferPtr[0] = CreateBuffer(buffer);
	};

	GLuint GetBuffer()
	{
		return bufferPtr;
	};

	~Buffer()
	{
		//delete bufferPtr;
	};

	GLuint CreateIndexBuffer(GLuint* indices , int indiceSize)//GL_ELEMENT_ARRAY_BUFFER OR GL_ARRAY_BUFFER
	{
		glGenBuffers(1, &bufferPtr);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferPtr);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indiceSize, indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
		return bufferPtr;
	};
	GLuint CreateVertexBuffer(GLfloat* vertices, int indiceSize)//GL_ELEMENT_ARRAY_BUFFER OR GL_ARRAY_BUFFER
	{
		
		glGenBuffers(1, &bufferPtr);
		glBindBuffer(GL_ARRAY_BUFFER, bufferPtr);
		glBufferData(GL_ARRAY_BUFFER, indiceSize * sizeof(GLfloat)* 8, vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0u);
		return bufferPtr;
	};
	GLuint CreateVertexArray(GLuint vertexBuffer, GLuint indexBuffer, GLuint* indices, GLfloat* vertices, int indiceSize)//GL_ELEMENT_ARRAY_BUFFER OR GL_ARRAY_BUFFER
	{
		GLuint vboID;
		GLuint vboID2;
		
		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, indiceSize * sizeof(GLfloat)* 8, vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0u);

		glGenBuffers(1, &vboID2);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID2);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* indiceSize, indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);

		glGenVertexArrays(1, &bufferPtr);
		glBindVertexArray(bufferPtr);
		//glEnableVertexAttribArray(bufferPtr);

		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID2);

		//glGenBuffers(1, &vboID); // Generate our Vertex Buffer Object  
		//glBindBuffer(GL_ARRAY_BUFFER, vboID); // Bind our Vertex Buffer Object  
		//glBufferData(GL_ARRAY_BUFFER, indiceSize * sizeof(GLfloat) * 8, vertices, GL_STATIC_DRAW);

		

		initialiseVertexArray();

		glBindVertexArray(0u);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
		glBindBuffer(GL_ARRAY_BUFFER, 0u);

		return bufferPtr;
	};
	void initialiseVertexArray()
	{
		glVertexAttribPointer((GLuint)0u, 3u, GL_FLOAT, GL_FALSE, 32, reinterpret_cast<GLvoid*>(0));
		glEnableVertexAttribArray(0u);
		glVertexAttribPointer((GLuint)1u, 3u, GL_FLOAT, GL_FALSE, 32, reinterpret_cast<GLvoid*>(12));
		glEnableVertexAttribArray(1u);
		glVertexAttribPointer((GLuint)2u, 2u, GL_FLOAT, GL_FALSE, 32, reinterpret_cast<GLvoid*>(24));
		glEnableVertexAttribArray(2u);
	}
private:

	GLuint bufferPtr;

};
#endif