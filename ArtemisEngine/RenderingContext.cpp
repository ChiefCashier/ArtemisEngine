#include "RenderingContext.h"
#include <cassert>
#include <typeinfo>

RenderingContext::RenderingContext(Window *window)
{

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
		24,                        //Colordepth of the framebuffer.		
		24,                        //Number of bits for the depthbuffer
		8,                        //Number of bits for the stencilbuffer
		0,                        //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE
	};
	WORD  nSize = sizeof(PIXELFORMATDESCRIPTOR);
	WORD  nVersion = 1;
	DWORD dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cRedBits = 0;
	pfd.cRedShift = 0;
	pfd.cGreenBits = 0;
	pfd.cGreenShift = 0;
	pfd.cBlueBits = 0;
	pfd.cBlueShift = 0;
	pfd.cAlphaBits = 0;
	pfd.cAlphaShift = 0;
	pfd.cAccumBits = 0;
	pfd.cAccumRedBits = 0;
	pfd.cAccumGreenBits = 0;
	pfd.cAccumBlueBits = 0;
	pfd.cAccumAlphaBits = 0;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.cAuxBuffers = 0;
	pfd.iLayerType = 0;
	pfd.bReserved = 0;
	DWORD dwLayerMask = NULL;
	DWORD dwVisibleMask = NULL;
	DWORD dwDamageMask = NULL;


	HDC ourWindowHandleToDeviceContext = GetDC(window->WindowHandle());// 
	g_HDC = ourWindowHandleToDeviceContext;
	int  letWindowsChooseThisPixelFormat;
	letWindowsChooseThisPixelFormat = ChoosePixelFormat(ourWindowHandleToDeviceContext, &pfd);
	SetPixelFormat(ourWindowHandleToDeviceContext, letWindowsChooseThisPixelFormat, &pfd);

	renderingContext = wglCreateContext(ourWindowHandleToDeviceContext);
	wglMakeCurrent(ourWindowHandleToDeviceContext, renderingContext);


	glewInit();

	_program = glCreateProgram();


	createVertexShader("VertexSource.txt");
	createFragmentShader("FragmentSource.txt");

	linkProgram();

	CreateAttributes();
	CreatePerspective(window);
	GLFinish();

}

void RenderingContext::createVertexShader(char *filename)
{
	GLchar* vertexBuffer = CML::ResourceLoader::LoadFile(filename);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexBuffer, nullptr);
	glCompileShader(vertexShader);

	GLint compileResult;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileResult);
	assert(compileResult == GL_TRUE);

	glAttachShader(_program, vertexShader);
	delete vertexBuffer;
}

void RenderingContext::createFragmentShader(char *filename)
{
	GLchar* fragmentBuffer = CML::ResourceLoader::LoadFile(filename);
	GLint compileResult;

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentBuffer, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileResult);
	assert(compileResult == GL_TRUE);

	glAttachShader(_program, fragmentShader);
	delete fragmentBuffer;
}

void RenderingContext::linkProgram()
{
	GLint compileResult;
	glLinkProgram(_program);

	glGetProgramiv(_program, GL_LINK_STATUS, &compileResult);
	assert(compileResult == GL_TRUE);
}

RenderingContext::~RenderingContext()
{

}

void RenderingContext::CreateAttributes()
{
	//_positionIndex = glGetAttribLocation(_program, "attrPosition");
	//assert(_positionIndex >= 0);
	//glEnableVertexAttribArray(_positionIndex);
	//
	//_colorIndex = glGetAttribLocation(_program, "attrColor");
	//assert(_colorIndex >= 0);
	//glEnableVertexAttribArray(_colorIndex);
	//
	//_textureIndex = glGetAttribLocation(_program, "attrTexCoord");
	//assert(_textureIndex >= 0);
	//glEnableVertexAttribArray(_textureIndex);

	_samplerLocation = glGetUniformLocation(_program, "myTexture");
	assert(_samplerLocation >= 0);

	_projectionIndex = glGetUniformLocation(_program, "unifProjection");
	assert(_projectionIndex >= 0);

	_cameraIndex = glGetUniformLocation(_program, "unifCamera");
	assert(_cameraIndex >= 0);

	_worldIndex = glGetUniformLocation(_program, "unifWorld");
	assert(_projectionIndex >= 0);

	_alphaChannel = glGetUniformLocation(_program, "alphaChannel");
	assert(_alphaChannel >= 0);
}

void RenderingContext::CreatePerspective(Window *window)
{
	_projection = glm::perspective(glm::radians(90.0f), static_cast<GLfloat>(window->_windowWidht) / window->_windowHeight, 0.01f, 1000.0f);

	glUseProgram(_program);
	glUniformMatrix4fv(_projectionIndex, 1, GL_FALSE, glm::value_ptr(_projection));
	glUseProgram(0u);
}

void RenderingContext::GLFinish()
{
	glClearColor(0.7f, 0.2f, 0.1f, 1.0f);
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_BLEND);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//
	//glEnable(GL_CULL_FACE);
}
