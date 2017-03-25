#include "luaEventApi.h"
#include <Windows.h>

int lua_createEvent(lua_State *L)
{
	int argc = lua_gettop(L);
	bool startStateSetup = false;
	bool nameSetup = false;
	bool initionalState = FALSE;
	LPCSTR name = NULL;
	for (int i = 1; i <= argc; i++)
	{
		if (lua_isboolean(L, i) && !startStateSetup)
		{
			startStateSetup = true;
			initionalState = lua_toboolean(L, i);
		}
		else if (lua_isstring(L, i) && !nameSetup)
		{
			nameSetup = true;
			name = lua_tostring(L, i);
		}
		else
		{
			lua_pushnil(L);
			return 1;
		}
	}
	
	HANDLE e = CreateEventA(NULL, FALSE, initionalState, name);
	LUA_PUSH_HANDLE(L, e);
	return 1;
}
int lua_waitEvent(lua_State *L)
{
	int argc = lua_gettop(L);
	unsigned int timeout = 0;
	if (argc > 0 && argc<3)
	{
		HANDLE e = INVALID_HANDLE_VALUE;
		if (lua_isuserdata(L, 1))
		{
			e = lua_touserdata(L, 1);
			if (argc == 2)
				if (lua_isinteger(L, 2))
				{
					timeout = lua_tointeger(L, 2);
				}
			bool res = WaitForSingleObject(e, timeout) == WAIT_OBJECT_0;
			lua_pushboolean(L, res);
		}
	}
	else
	{
		lua_pushboolean(L, false);
	}
	return 1;
}
int lua_setEvent(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc == 1)
	{
		HANDLE e = INVALID_HANDLE_VALUE;
		if (lua_isuserdata(L, 1))
		{
			e = lua_touserdata(L, 1);
			bool res = SetEvent(e);
			lua_pushboolean(L, res);
		}
	}
	else
	{
		lua_pushboolean(L, false);
	}
	return 1;
}
int lua_resetEvent(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc == 1)
	{
		HANDLE e = INVALID_HANDLE_VALUE;
		if (lua_isuserdata(L, 1))
		{
			e = lua_touserdata(L, 1);
			bool res = ResetEvent(e);
			lua_pushboolean(L, res);
		}
	}
	else
	{
		lua_pushboolean(L, false);
	}
	return 1;
}
int lua_destroyEvent(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc == 1)
	{
		HANDLE e = INVALID_HANDLE_VALUE;
		if (lua_isuserdata(L, 1))
		{
			e = lua_touserdata(L, 1);
			bool res = CloseHandle(e);
			lua_pushboolean(L, res);
		}
	}
	else
	{
		lua_pushboolean(L, false);
	}
	return 1;
}
static const luaL_Reg eventLib[] = {
	{ "Create",   lua_createEvent },
	{ "Wait",     lua_waitEvent },
	{ "Set",      lua_setEvent },
	{ "Reset",	  lua_resetEvent },
	{ "Destroy",  lua_destroyEvent },
	{ NULL, NULL }
};
int openEventLibInit(lua_State *L) {
	luaL_newlib(L, eventLib);
	return 1;
}
void openEventLib(lua_State *L)
{
	luaL_newlib(L, eventLib);
	luaL_requiref(L, "Event", openEventLibInit, 1);
	lua_pop(L, 1);  /* remove lib */
}