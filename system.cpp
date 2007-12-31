#include "system.h"
HWND		System::_hWnd;
HINSTANCE	System::_hInstance;
HDC			System::_hDC;
HGLRC		System::_hRC;
HWND System::CreateGLWindow(int width, int height)
{
	UINT msg;
	WPARAM wParam;
	LPARAM lParam;
	WNDCLASSEX wce;
	wce.cbClsExtra	  = 0;
	wce.cbWndExtra    = 0;
	wce.style		  = CS_HREDRAW | CS_VREDRAW;
	wce.cbSize	      = sizeof(WNDCLASSEX);
	wce.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wce.lpfnWndProc	  = WndProc;
	wce.hIcon		  = LoadIcon(NULL, IDI_APPLICATION);
	wce.hIconSm		  = LoadIcon(NULL, IDI_APPLICATION);
	wce.lpszClassName = ENGINENAME;
	wce.hInstance	  = _hInstance;
	wce.hCursor		  = LoadCursor(NULL, IDC_ARROW);

	if(!RegisterClassEx(&wce))
	{
		return 0;
	}

	DEVMODE dm;
	memset(&dm, 0, sizeof(DEVMODE));
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);
	dm.dmPelsWidth = SCREEN_WIDTH;
	dm.dmPelsHeight = SCREEN_HEIGHT;

	int change = ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
	if(change != DISP_CHANGE_SUCCESSFUL)
		return 0;

	_hWnd = CreateWindowEx(NULL, ENGINENAME, "3d Project", WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
								CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, _hInstance, NULL);

	ShowWindow(_hWnd, SW_SHOWNORMAL);
	UpdateWindow(_hWnd);

	SetFocus(_hWnd);
	return _hWnd;
}

bool System::SetupPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pfd = {0};
	int pixelFormat;

    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.dwLayerMask = PFD_MAIN_PLANE;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = SCREEN_DEPTH;
    pfd.cDepthBits = SCREEN_DEPTH;
    pfd.cAccumBits = 0;
    pfd.cStencilBits = 0;

	pixelFormat = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, pixelFormat, &pfd);

	return true;
}

/*void InitializeOpenGL(int width, int height)
{
    g_hDC = GetDC(g_hWnd);

    if (!System::SetupPixelFormat(g_hDC))
        PostQuitMessage (0);

	g_hRC = wglCreateContext(g_hDC);
    //wglMakeCurrent(g_hDC, g_hRC);

	//glEnable(GL_TEXTURE_2D);
	System::SizeOpenGLScreen(width, height);

	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport(0,0,width,height);
}

void SizeOpenGLScreen(int width, int height)
{
	if (height == 0)
	{
		height = 1;
	}

	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}*/

LRESULT CALLBACK System::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_KEYDOWN:
		if(wParam == VK_ESCAPE)
			PostQuitMessage(0);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

void System::UninitializeSystem()
{
	if(_hRC)
	{
		//wglMakeCurrent(NULL, NULL);
		//wglDeleteContext(_hRC);
	}

	if(_hDC)
		ReleaseDC(_hWnd, _hDC);

	ChangeDisplaySettings(NULL,0);
	ShowCursor(true);

	UnregisterClass(ENGINENAME, _hInstance);
	PostQuitMessage(0);
}

WPARAM System::MainLoop()
{
	MSG msg;
	while(true)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			RenderScene();
		}
	}
	return msg.wParam;
}
