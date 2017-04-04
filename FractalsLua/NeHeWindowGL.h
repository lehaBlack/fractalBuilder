#pragma once
#include "luaLibs.h"
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <map>
#include <string>

#define DEFAULT_WIN_WIDTH     640
#define DEFAULT_WIN_HEIGHT     480

class NeheWindow
{
     using NeheWindowStorageClass = std::map<HWND, NeheWindow*>;
     using NeheWindowStorageCellClass = std::pair<HWND, NeheWindow*>;
     static NeheWindowStorageClass neheWindowses;

     struct WinInitHelpinData
     {
          int width= DEFAULT_WIN_WIDTH;
          int height= DEFAULT_WIN_HEIGHT;
          HANDLE Event=INVALID_HANDLE_VALUE;
          HWND Window=NULL;
          lua_State* L=nullptr;
          std::string drawInsruct = "";
     };

     HGLRC hRC;     // permanent rendering context
     HDC hDC;          // private GDI device context
     HWND hWnd;
     HINSTANCE hInstance;

     bool keys[256];
     BOOL active;
     BOOL isfullscreen;
     std::string luaDrawProcInstruction;
     lua_State *L;

     // declaration for 
     static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

     GLvoid resizeGL(GLsizei width, GLsizei height);

     // all setup for OpenGL goes here
     int initGL(GLvoid);

     int drawGL(GLvoid);

     GLvoid killGL(GLvoid);

     int createGL(wchar_t * title, int width, int height, int bits, BOOL fullscreenflag);
     int WinMain(WinInitHelpinData &winParam);
     static DWORD WINAPI createWindow(LPVOID helpinStruct);
     NeheWindow();
     void luaCall();
     static DWORD WINAPI updateWindow(LPVOID data);
public:
     struct initWindowParam
     {
          HWND hWnd;
          HANDLE Thread;
     };
     static int initWindow(initWindowParam* &param, lua_State* L,const std::string &drawInst,int width = DEFAULT_WIN_WIDTH, int height = DEFAULT_WIN_HEIGHT);
};