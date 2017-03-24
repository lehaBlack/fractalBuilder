#include "NeHeWindowGL.h"
NeheWindow::NeheWindowStorageClass  NeheWindow::neheWindowses;

GLvoid NeheWindow::resizeGL(GLsizei width, GLsizei height) {
	if (height == 0)	// prevent a divide by zero
		height = 1;

	glViewport(0, 0, width, height);	//reset the current viewport

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// all setup for OpenGL goes here

int NeheWindow::initGL(GLvoid) {
	glShadeModel(GL_SMOOTH);	//enables smooth shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	//black background
											// depth buffer
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	return TRUE;
}

int NeheWindow::drawGL(GLvoid) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//clear the screen and the deep buffer
	glLoadIdentity();

	luaCall();

	return TRUE;
}

GLvoid NeheWindow::killGL(GLvoid) {
	if (isfullscreen) {
		ChangeDisplaySettings(NULL, 0);		//to original desktop
		ShowCursor(TRUE);
	}
	//....
	if (hRC) {
		if (!wglMakeCurrent(NULL, NULL))
		{
			//MessageBox(NULL, TEXT("release of DC & RC failed"), TEXT("shutdown error"), MB_OK | MB_ICONINFORMATION);
		}
			
		if (!wglDeleteContext(hRC))
		{
			//MessageBox(NULL, TEXT("release rendering context failed"), TEXT("shutdown error"), MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;
	}
	//
	if (hDC && !ReleaseDC(hWnd, hDC)) {
		//MessageBox(NULL, TEXT("release device context failed"), TEXT("shutdown error"), MB_OK | MB_ICONINFORMATION);
		hDC = NULL;
	}
	//
	if (hWnd && !DestroyWindow(hWnd)) {
		//MessageBox(NULL, TEXT("could not release hWnd"), TEXT("shutdown error"), MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;
	}
	//
	if (!UnregisterClass(TEXT("londontown"), hInstance)) {
		//MessageBox(NULL, TEXT("could not unregister class"), TEXT("shutdown error"), MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;
	}
}

int NeheWindow::createGL(wchar_t * title, int width, int height, int bits, BOOL fullscreenflag) {
	GLuint PixelFormat;

	WNDCLASS wnd;

	DWORD dwExStyle;
	DWORD dwStyle;

	RECT windowRect;
	windowRect.left = (long)0;
	windowRect.right = (long)width;
	windowRect.top = (long)0;
	windowRect.bottom = (long)height;

	hInstance = GetModuleHandle(NULL);
	wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wnd.lpfnWndProc = (WNDPROC)WndProc;
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hInstance = hInstance;
	wnd.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd.hbrBackground = NULL;
	wnd.lpszMenuName = NULL;
	wnd.lpszClassName = TEXT("neheWindowClass");

	if (!RegisterClass(&wnd)) {
		MessageBox(NULL, TEXT("failed to register the window class"), TEXT("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	isfullscreen = fullscreenflag;

	if (isfullscreen) {
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = width;
		dmScreenSettings.dmPelsHeight = height;
		dmScreenSettings.dmBitsPerPel = bits;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
			if (MessageBox(NULL, TEXT("the requested fullscreen mode is not supported by\n your video card.")
				TEXT("use windowed mode instead?"), TEXT("londontown"), MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
				isfullscreen = FALSE;
			}
			else {
				MessageBox(NULL, TEXT("program will now close"), TEXT("londontown"), MB_OK | MB_ICONSTOP);
				return FALSE;
			}
		}
	}

	if (isfullscreen) {
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		ShowCursor(FALSE);		// hide mouse pointer
	}
	else {
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

	if (!(hWnd = CreateWindowEx(dwExStyle,
		TEXT("neheWindowClass"),
		title,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle,
		0, 0,
		width,
		height,
		NULL,
		NULL,
		hInstance,
		NULL))) {
		killGL();
		MessageBox(NULL, TEXT("window creation error."), TEXT("error"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	neheWindowses.insert(NeheWindowStorageCellClass(hWnd,this));

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		bits,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	if (!(hDC = GetDC(hWnd))) {
		killGL();
		MessageBox(NULL, TEXT("cannot create a GL device context."), TEXT("error"), MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}
	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd))) {
		killGL();
		MessageBox(NULL, TEXT("cannot find a suitable PixelFormat."), TEXT("error"), MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}
	if (!SetPixelFormat(hDC, PixelFormat, &pfd)) {
		killGL();
		MessageBox(NULL, TEXT("cannot set the PixelFormat."), TEXT("error"), MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}
	if (!(hRC = wglCreateContext(hDC))) {
		killGL();
		MessageBox(NULL, TEXT("cannot create a GL rendering context."), TEXT("error"), MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}
	if (!wglMakeCurrent(hDC, hRC)) {
		killGL();
		MessageBox(NULL, TEXT("cannot activate the GL rendering context."), TEXT("error"), MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	ShowWindow(hWnd, SW_SHOW);
	//SetForegroundWindow(hWnd);
	//SetFocus(hWnd);
	resizeGL(width, height);

	if (!initGL()) {
		killGL();
		MessageBox(NULL, TEXT("Initialization failed."), TEXT("error"), MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	return TRUE;
}

inline int NeheWindow::WinMain(WinInitHelpinData &winParam) {
	MSG msg;
	int done = FALSE;
	isfullscreen = FALSE;
	L = winParam.L;
	luaDrawProcInstruction = winParam.drawInsruct;
	/*if (MessageBox(NULL, TEXT("Would you like to run in fullscreen mode?"), TEXT("Start fullscreen"),
		MB_YESNO | MB_ICONQUESTION) == IDNO) {
		isfullscreen = FALSE;	// windowed mode
	}*/

	if (!createGL(TEXT("Lua's OpenGL Framework"), winParam.width, winParam.height, 16, isfullscreen))
	{
		winParam.Window = NULL;
		SetEvent(winParam.Event);
		return 0;
	}
	CreateThread(NULL, 0, updateWindow, (LPVOID)hWnd, 0, NULL);
	winParam.Window = hWnd;
	SetEvent(winParam.Event);

	while (!done) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
				done = TRUE;
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		/*else {
			if (active) {
				if (keys[VK_ESCAPE])
					done = TRUE;
				else {
					drawGL();
					SwapBuffers(hDC);
				}
			}

			if (keys[VK_F1]) {
				keys[VK_F1] = false;
				killGL();
				isfullscreen = !isfullscreen;

				if (!createGL(TEXT("Lua's OpenGL Framework"), winParam.width, winParam.height, 16, isfullscreen))
					return 0;
			}
		}*/
	}

	killGL();
	delete this;
	return msg.wParam;
}

DWORD WINAPI NeheWindow::createWindow(LPVOID helpinStruct)
{
	WinInitHelpinData winParam = *((WinInitHelpinData*)helpinStruct);
	NeheWindow *newWindow = new NeheWindow();

	newWindow->WinMain(winParam);
	return 0;
}

NeheWindow::NeheWindow():
	hRC(NULL),
	hDC(NULL),
	hWnd(NULL),
	hInstance(GetModuleHandleA(NULL)),
	active(TRUE),
	isfullscreen(FALSE)
{
	memset(keys, false, sizeof(keys));
}

void NeheWindow::luaCall()
{
	if (luaDrawProcInstruction.size() > 0)
	{
		luaL_dostring(L, luaDrawProcInstruction.c_str());
	}
}

DWORD NeheWindow::updateWindow(LPVOID data)
{
	HWND hWnd = (HWND)data;
	BOOL rep = true;
	do
	{
		InvalidateRect(hWnd, NULL, TRUE);
		rep=UpdateWindow(hWnd);
		Sleep(300);
	} while (rep);
	return 0;
}

int NeheWindow::initWindow(initWindowParam* &param, lua_State* L, const std::string &drawInst,int width, int height)
{
	param = nullptr;
	HANDLE Mutex = CreateMutexA(NULL, FALSE, "mutex_" __FUNCTION__);
	if (Mutex == INVALID_HANDLE_VALUE)
	{
		return 1;
	}
	else
	{
		if (WaitForSingleObject(Mutex, 1000) == WAIT_OBJECT_0)
		{
			HANDLE Event = CreateEventA(NULL, FALSE, FALSE, "event_" __FUNCTION__);
			WinInitHelpinData winParam;
			winParam.width = width;
			winParam.height = height;
			winParam.L = L;
			winParam.drawInsruct = drawInst;
			if (Event == INVALID_HANDLE_VALUE)
			{
			}
			else
			{
				param = new initWindowParam;
				winParam.Event = Event;
				param->Thread = CreateThread(NULL, 0, createWindow, &winParam, 0, NULL);
				WaitForSingleObject(Event, INFINITE);

			}
			ReleaseMutex(Mutex);
		}
	}
	return 0;
}

LRESULT CALLBACK NeheWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (neheWindowses.count(hWnd) == 0)
	{
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	NeheWindow* This = neheWindowses[hWnd];
	if(This==nullptr)
	{
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	switch (uMsg) {
	case WM_ACTIVATE: {
		if (!HIWORD(wParam))
			This->active = TRUE;
		else
			This->active = FALSE;
		return 0;
	}
	case WM_SYSCOMMAND: {
		switch (wParam) {
		case SC_SCREENSAVE:
		case SC_MONITORPOWER:
			return 0;
		}
		break;
	}
	case WM_CLOSE: {
		PostQuitMessage(0);
		neheWindowses.erase(hWnd);
		return 0;
	}
	case WM_KEYDOWN: {
		This->keys[wParam] = true;
		return 0;
	}
	case WM_KEYUP: {
		This->keys[wParam] = false;
		return 0;
	}
	case WM_SIZE: {
		This->resizeGL(LOWORD(lParam), HIWORD(lParam));
		return 0;
	}
	case WM_PAINT:
	{
		This->drawGL();
		SwapBuffers(This->hDC);
		break;
	}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
