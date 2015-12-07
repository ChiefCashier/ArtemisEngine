#include "Window.h"
#include <cassert>


LRESULT CALLBACK WindowProc(HWND asd, UINT uMsg, WPARAM wParam, LPARAM lParam);


LRESULT CALLBACK WindowProc(HWND asd, UINT uMsg, WPARAM wParam, LPARAM lParam) //without this nothing works, so I say we keep it
{
	switch (uMsg){
	case WM_CREATE:
	{
		return 0;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		DestroyWindow(asd);
		return 0;
	}
	default:

		return DefWindowProc(asd, uMsg, wParam, lParam);

	}
}
std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

Window::Window(int windowType,const wchar_t* CLASS_NAME, std::string s, int windowWidht, int windowHeight)//constructor for window with "parameters"
{
		

	WNDCLASS wc = {};

	_CLASS_NAME = CLASS_NAME;
	_windowWidht = windowWidht;
	_windowHeight = windowHeight;

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = GetModuleHandle(nullptr);


	wc.lpszClassName = _CLASS_NAME;

	RegisterClass(&wc);

	std::wstring stemp = s2ws(s);
	LPCWSTR result = stemp.c_str();

	_windowHandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, _CLASS_NAME, result, WS_OVERLAPPEDWINDOW, 100, 100, _windowWidht, _windowHeight, //Windowhandle pointer creation
		NULL, NULL, GetModuleHandle(nullptr), NULL);
	if (_windowHandle == nullptr)
	{

		std::cout << "Window handle creation failed" << std::endl;

	}


}
Window::Window()
{
	Window(0, L"asd", "fuck", 800, 600);
}


Window::~Window() //window destructor MARK 1 "The Eliminator"
{
	/* I'm useful! */
	//delete _windowHandle;
}


HWND Window::WindowHandle()// Return handle to the window
{
	return _windowHandle;
}

void Window::ShowAWindow()
{
	ShowWindow(_windowHandle, SW_SHOWNORMAL);
}


void Window::WindowMessageCheck(){
	MSG msg;//I don't even...

	while (PeekMessage(&msg, _windowHandle, NULL, NULL, PM_REMOVE))
	{
			
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
