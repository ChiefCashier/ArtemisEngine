#pragma once
#include "Window.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "ResourceLoader.h"
#include "GameObject.h"
#include "Renderable.h"
#include "Transformable.h"
class RenderingContext
{
public:

	RenderingContext(Window *window);
	RenderingContext(){};
	~RenderingContext();

	void createVertexShader(char *filename);
	void createFragmentShader(char *filename);
	void linkProgram();

	void CreateAttributes();
	void CreatePerspective(Window *window);
	void GLFinish();


	GLuint getProgramIndex(){ return _program; };
	HDC getHDC(){ return g_HDC; };
	HGLRC getRenderingContext(){ return renderingContext; };

	GLint get_positionIndex(){ return _positionIndex; };
	GLint get_colorIndex(){ return _colorIndex; };
	GLint get_textureIndex(){ return _textureIndex; };

	GLint get_samplerLocation(){ return _samplerLocation; };
	GLint get_projectionIndex(){ return _projectionIndex; };
	GLint get_cameraIndex(){ return _cameraIndex; };
	GLint get_worldIndex(){ return _worldIndex; };
	GLint get_alphaChannel(){ return _alphaChannel; };
	glm::mat4 get_projection(){ return _projection; };

private:

	HGLRC renderingContext;
	HDC g_HDC;
	GLuint _program;
	GLuint vertexShader;
	GLuint fragmentShader;


	GLint _positionIndex;
	GLint _colorIndex;
	GLint _textureIndex;


	GLint _samplerLocation;
	GLint _projectionIndex;
	GLint _cameraIndex;
	GLint _worldIndex;
	GLint _alphaChannel;

	GLint _lightPosition;

	glm::mat4 _projection;

};

