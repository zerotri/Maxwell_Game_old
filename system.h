#ifndef __SYSTEM_H__
#define __SYSTEM_H__
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl/gl.h>
#define ENGINENAME    "3D Project"
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define SCREEN_DEPTH  16

class System
{
public:
	System(HWND hWnd, HINSTANCE hInstance, HDC hDC, HGLRC hRC);
	~System();
	static HWND CreateGLWindow(int width, int height);
	static bool SetupPixelFormat(HDC hDC);
	static void InitializeOpenGL(int width, int height);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static void UninitializeSystem();

	static void SizeOpenGLScreen(int width, int height);

	static WPARAM MainLoop();

	HWND	  GetHWND()		 {return _hWnd;}
	HINSTANCE GetHINSTANCE() {return _hInstance;}
	HDC		  GetHDC()		 {return _hDC;}
	HGLRC	  GetHGLRC()	 {return _hRC;}

	HWND	  SetHWND(HWND hWnd)				{return _hWnd = hWnd;}
	HINSTANCE SetHINSTANCE(HINSTANCE hInstance) {return _hInstance = hInstance;}
	HDC		  SetHDC(HDC hDC)					{return _hDC = hDC;}
	HGLRC	  SetHGLRC(HGLRC hRC)				{return _hRC = hRC;}

private:
	static HWND      _hWnd;
	static HINSTANCE _hInstance;
	static HDC		  _hDC;
	static HGLRC	  _hRC;
};

#endif
