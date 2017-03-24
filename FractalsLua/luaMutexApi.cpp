#include "luaMutexApi.h"
#include <windows.h>
int lua_createMutex(lua_State *L)
{
	int argc = lua_gettop(L);
	bool ovnerSetup = false;
	bool nameSetup = false;
	bool initionalOvner=FALSE;
	LPCSTR name = NULL;
	for (int i = 1; i <= argc; i++)
	{
		if (lua_isboolean(L, i)&&!ovnerSetup)
		{
			ovnerSetup = true;
			initionalOvner = lua_toboolean(L, i);
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


	HANDLE mutex=CreateMutexA(NULL, initionalOvner, name);
	LUA_PUSH_HANDLE(L, mutex);
	return 1;
}
int lua_tryLockMutex(lua_State *L)
{
	int argc = lua_gettop(L);
	unsigned int timeout = INFINITE;
	if (argc > 0 && argc<3)
	{
		HANDLE mutex = INVALID_HANDLE_VALUE;
		if (lua_isuserdata(L, 1))
		{
			mutex = lua_touserdata(L, 1);
			if(argc==2)
				if (lua_isinteger(L, 2))
				{
					timeout = lua_tointeger(L, 2);
				}
			bool res = WaitForSingleObject(mutex, timeout)==WAIT_OBJECT_0;
			lua_pushboolean(L, res);
		}
	}
	else
	{
		lua_pushboolean(L, false);
	}
	return 1;
}
int lua_releaseMutex(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc ==1)
	{
		HANDLE mutex = INVALID_HANDLE_VALUE;
		if (lua_isuserdata(L, 1))
		{
			mutex = lua_touserdata(L, 1);
			bool res = ReleaseMutex(mutex);
			lua_pushboolean(L, res);
		}
	}
	else
	{
		lua_pushboolean(L, false);
	}
	return 1;
}
int lua_destroyMutex(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc == 1)
	{
		HANDLE mutex = INVALID_HANDLE_VALUE;
		if (lua_isuserdata(L, 1))
		{
			mutex = lua_touserdata(L, 1);
			bool res = CloseHandle(mutex);
			lua_pushboolean(L, res);
		}
	}
	else
	{
		lua_pushboolean(L, false);
	}
	return 1;
}
static const luaL_Reg mutexLib[] = {
	{ "Create",   lua_createMutex },
	{ "tryLock",   lua_tryLockMutex },
	{ "Release",   lua_releaseMutex },
	{ "Destroy",   lua_destroyMutex },
	{ NULL, NULL }
};
int openMutexLibInit(lua_State *L) {
	luaL_newlib(L, mutexLib);
	return 1;
}
void openMutexLib(lua_State *L)
{
	luaL_newlib(L, mutexLib);
	luaL_requiref(L, "Mutex", openMutexLibInit, 1);
	lua_pop(L, 1);  /* remove lib */
}