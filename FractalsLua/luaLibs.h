#pragma once
extern "C"
{
#include <lua\lua.h>
#include <lua\lauxlib.h>
#include <lua\lualib.h>
}
#define LUA_PUSH_PTR(L,ptr) ((ptr)==nullptr?lua_pushnil(L):lua_pushlightuserdata(L,ptr))

#define LUA_PUSH_PTRC(L,ptr) ((ptr)==NULL?lua_pushnil(L):lua_pushlightuserdata(L,ptr))
#define LUA_PUSH_HANDLE(L,hnd) ((hnd)==INVALID_HANDLE_VALUE?lua_pushnil(L):LUA_PUSH_PTRC(L,hnd))