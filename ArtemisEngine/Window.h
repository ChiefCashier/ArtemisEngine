#pragma once

#ifndef WIN32_LEAN_AND_MEAN 
#define WIN32_LEAN_AND_MEAN 
#endif


#include <Windows.h>
#include <iostream>

#include "glew.h"
#include "ResourceManager.h"
#include "Image.h"

class Window
{
public:

	//constructors
	Window();
	Window(int windowType, const wchar_t* CLASS_NAME, std::string s,
				int windowWidht, int windowHeight);

	//destructors
	~Window();

	//window handle makers
	HWND WindowHandle();

	//and the rest
	void ShowAWindow();
	void WindowMessageCheck();
	int _windowWidht, _windowHeight;

private:

	//things and stuff
	wchar_t _windowName;

	int _windowType;
	const wchar_t* _CLASS_NAME;

	//thingamabob(s)
	HWND _windowHandle;

};
