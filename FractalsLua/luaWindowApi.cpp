#include "luaWindowApi.h"
#include "NeHeWindowGL.h"


int lua_intWindow(lua_State *L)
{
	NeheWindow::initWindowParam* newWindowParam = nullptr;
	int argc = lua_gettop(L);
	if(argc>0)
		if(!lua_isstring(L,1))
		{
			lua_pushnil(L);
			return 1;
		}
	if (argc>1)
		if (!lua_isinteger(L, 2))
		{
			lua_pushnil(L);
			return 1;
		}
	if (argc>2)
		if (!lua_isinteger(L, 3))
		{
			lua_pushnil(L);
			return 1;
		}
	switch (argc)
	{
	case 0:
	{
		NeheWindow::initWindow(newWindowParam, L, "");
		LUA_PUSH_PTR(L, newWindowParam);
		return 1;
	}
	case 1:
	{
		NeheWindow::initWindow(newWindowParam,L, lua_tostring(L, 1));
		LUA_PUSH_PTR(L, newWindowParam);
		return 1;
	}
	case 2:
		{
			NeheWindow::initWindow(newWindowParam, L, lua_tostring(L, 1), lua_tointeger(L, 2));
			LUA_PUSH_PTR(L, newWindowParam);
			return 1;
		}
		break;
	case 3:
		{
			NeheWindow::initWindow(newWindowParam, L, lua_tostring(L, 1), lua_tointeger(L, 2), lua_tointeger(L, 3));
			LUA_PUSH_PTR(L, newWindowParam);
			return 1;
		}
		break;
	default:
	{
	}
	}
	lua_pushnil(L);
	return 1;
}
int lua_waitForCloseWindow(lua_State *L)
{
	NeheWindow::initWindowParam* newWindowParam = nullptr;
	int argc = lua_gettop(L);
	unsigned int timeout = INFINITE;
	if (argc>0&& argc<3)
		if (lua_isuserdata(L, 1))
		{
			if(argc==2)
				if (!lua_isinteger(L, 2))
				{
					lua_pushboolean(L, false);
					return 1;
				}
				else
				{
					timeout = lua_tointeger(L, 2);
				}
			newWindowParam = (NeheWindow::initWindowParam*)lua_touserdata(L, 1);
			if (newWindowParam->Thread != NULL&&newWindowParam->Thread != INVALID_HANDLE_VALUE)
			{
				WaitForSingleObject(newWindowParam->Thread, timeout);
				lua_pushboolean(L, true);
				return 1;
			}
		}
	lua_pushboolean(L,false);
	return 1;
}
int lua_suspendWindowThread(lua_State *L)
{
	NeheWindow::initWindowParam* newWindowParam = nullptr;
	int argc = lua_gettop(L);
	if (argc==1)
		if (lua_isuserdata(L, 1))
		{
			
			newWindowParam = (NeheWindow::initWindowParam*)lua_touserdata(L, 1);
			if (newWindowParam->Thread != NULL&&newWindowParam->Thread != INVALID_HANDLE_VALUE)
			{
				if (SuspendThread(newWindowParam->Thread) != -1)
				{
					lua_pushboolean(L, true);
					return 1;
				}
			}
		}
	lua_pushboolean(L, false);
	return 1;
}
int lua_resumeWindowThread(lua_State *L)
{
	NeheWindow::initWindowParam* newWindowParam = nullptr;
	int argc = lua_gettop(L);
	if (argc == 1)
		if (lua_isuserdata(L, 1))
		{

			newWindowParam = (NeheWindow::initWindowParam*)lua_touserdata(L, 1);
			if (newWindowParam->Thread != NULL&&newWindowParam->Thread != INVALID_HANDLE_VALUE)
			{
				if (ResumeThread(newWindowParam->Thread) != -1)
				{
					lua_pushboolean(L, true);
					return 1;
				}
			}
		}
	lua_pushboolean(L, false);
	return 1;
}
int lua_Sleep(lua_State *L)
{
	int argc = lua_gettop(L);
	unsigned int timeout = 1000;
	if (argc >= 0 && argc < 2)
	{
		if (argc == 1)
			if (!lua_isinteger(L, 1))
			{
				lua_pushboolean(L, false);
				return 1;
			}
			else
			{
				timeout = lua_tointeger(L, 1);
			}
		
		Sleep(timeout);
		lua_pushboolean(L, true);
		return 1;
	}
	lua_pushboolean(L, false);
	return 1;
}
static const luaL_Reg windowLib[] = {
	{ "initWindow",   lua_intWindow },
	{ "waitForCloseWindow",   lua_waitForCloseWindow },
	{ "suspendWindowThread",   lua_suspendWindowThread },
	{ "resumeWindowThread",   lua_resumeWindowThread },
	{ "Sleep",   lua_Sleep },
	{ "INFINITE", NULL },
	{ NULL, NULL }
};
int openWindowLibInit(lua_State *L) {
	luaL_newlib(L, windowLib);
	lua_pushinteger(L, INFINITE);
	lua_setfield(L, -2, "INFINITE");
	return 1;
}
void openWindowLib(lua_State *L) {
	luaL_newlib(L, windowLib);
	luaL_requiref(L, "WND", openWindowLibInit, 1);
	lua_pop(L, 1);  /* remove lib */
}
