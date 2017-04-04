#include "luaFractalApi.h"
#include <fractals\TockensStream.h>

int lua_createFreeFractalStream(lua_State *L)
{
     int argc = lua_gettop(L);
     int size;
     if (argc != 1)
     {
          lua_pushnil(L);
          return 1;
     }
     if (!lua_isinteger(L,1))
     {
          lua_pushnil(L);
          return 1;
     }
     size = lua_tointeger(L, 1);
     Fr_streamT *stream=new Fr_streamT();
     if (!initFractalStream(stream, size))
     {
          lua_pushnil(L);
          return 1;
     }
     lua_pushlightuserdata(L, stream);
     return 1;
}
int lua_createFractalStream(lua_State *L)
{
     int argc = lua_gettop(L);
     int size=0;
     if (argc ==0)
     {
          lua_pushnil(L);
          return 1;
     }
     for(int i=1;i<=argc;i++, size++)
          if (!lua_isinteger(L, i))
          {
               lua_pushnil(L);
               return 1;
          }
     Fr_streamT *stream = new Fr_streamT();
     Fr_tockenT *tockens = new Fr_tockenT[size];
     for (int i = 1; i <= argc; i++)
     {
          tockens[i-1]=lua_tointeger(L, i);
     }
     bool res = createFractalStream(stream, tockens, size);

     delete[] tockens;
     if(!res)
     {
          delete stream;
          lua_pushnil(L);
          return 1;
     }
     lua_pushlightuserdata(L, stream);
     return 1;
}

int lua_createFractalState(lua_State *L)
{
     int argc = lua_gettop(L);
     if (argc != 1)
     {
          lua_pushnil(L);
          return 1;
     }
     if (!lua_isuserdata(L, 1))
     {
          lua_pushnil(L);
          return 1;
     }
     Fr_streamT *stream = (Fr_streamT*)lua_touserdata(L, 1);
     Fr_stateT* state = new Fr_stateT(stream);
     lua_pushlightuserdata(L, state);
     return 1;
}
int lua_freeFractalStream(lua_State *L)
{
     int argc = lua_gettop(L);
     if (argc != 1)
     {
          lua_pushboolean(L, false);
          return 1;
     }
     if (!lua_isuserdata(L, 1))
     {
          lua_pushboolean(L, false);
          return 1;
     }
     Fr_streamT *stream = (Fr_streamT*)lua_touserdata(L, 1);
     lua_pushboolean(L, freeStream(stream));
     delete stream;
     return 1;
}
int lua_setFractalStreamTocken(lua_State* L)
{
     int argc = lua_gettop(L);
     if (argc != 3)
     {
          lua_pushboolean(L, false);
          return 1;
     }
     if (!lua_isuserdata(L, 1) && !lua_isinteger(L, 2) && !lua_isinteger(L, 3))
     {
          lua_pushboolean(L, false);
          return 1;
     }

     Fr_streamT* stream = (Fr_streamT*)lua_touserdata(L, 1);
     int position = lua_tointeger(L, 2);
     Fr_tockenT t = (Fr_tockenT)lua_tointeger(L, 3);

     lua_pushboolean(L, setFractalStreamTocken(stream, position, t));
     return 1;
}
//-------------------------------------------------------------
int lua_setReplaceTockenData(lua_State* L)
{
     int argc = lua_gettop(L);
     if (argc != 3)
     {
          lua_pushboolean(L,false);
          return 1;
     }
     if (!lua_isuserdata(L, 1)&& !lua_isinteger(L, 2) && !lua_isuserdata(L, 3))
     {
          lua_pushboolean(L, false);
          return 1;
     }
     Fr_stateT* state   = (Fr_stateT*) lua_touserdata(L, 1);
     Fr_tockenT t       = (Fr_tockenT) lua_tointeger(L, 2);
     Fr_streamT *stream = (Fr_streamT*)lua_touserdata(L, 3);
     state->setReplaceTockenData(t, stream);
     lua_pushboolean(L, true);
     return 1;
}
int lua_newFractalLevel(lua_State* L)
{
     int argc = lua_gettop(L);
     if (argc != 1)
     {
          lua_pushboolean(L, false);
          return 1;
     }
     if (!lua_isuserdata(L, 1))
     {
          lua_pushboolean(L, false);
          return 1;
     }
     Fr_stateT* state = (Fr_stateT*)lua_touserdata(L, 1);
     state->newFractalLevel();
     lua_pushboolean(L, true);
     return 1;
}
//---------------------------------------------------------------
int lua_tckStreamEos(lua_State* L)
{
     int argc = lua_gettop(L);
     if (argc != 1)
     {
          lua_pushboolean(L, false);
          return 1;
     }
     if (!lua_isuserdata(L, 1))
     {
          lua_pushboolean(L, false);
          return 1;
     }
     Fr_tckStreamT *stream = (Fr_tckStreamT*)lua_touserdata(L, 1);

     lua_pushboolean(L, stream->eos());
     return 1;
}
int lua_tckStreamReset(lua_State* L)
{
     int argc = lua_gettop(L);
     if (argc != 1)
     {
          lua_pushboolean(L, false);
          return 1;
     }
     if (!lua_isuserdata(L, 1))
     {
          lua_pushboolean(L, false);
          return 1;
     }
     Fr_tckStreamT *stream = (Fr_tckStreamT*)lua_touserdata(L, 1);
     stream->reset();
     lua_pushboolean(L, true);
     return 1;
}
int lua_tckStreamPeekNextTocken(lua_State* L)
{
     int argc = lua_gettop(L);
     if (argc != 1)
     {
          lua_pushboolean(L, false);
          lua_pushinteger(L, -1);
          return 2;
     }
     if (!lua_isuserdata(L, 1))
     {
          lua_pushboolean(L, false);
          lua_pushinteger(L, -1);
          return 2;
     }
     Fr_tckStreamT *stream = (Fr_tckStreamT*)lua_touserdata(L, 1);
     Fr_tockenT t = stream->peekNextTocken();
     lua_pushboolean(L, true);
     lua_pushinteger(L, t);
     return 2;
}
int lua_tckStreamGetNextTocken(lua_State* L)
{
     int argc = lua_gettop(L);
     if (argc != 1)
     {
          lua_pushboolean(L, false);
          lua_pushinteger(L, -1);
          return 2;
     }
     if (!lua_isuserdata(L, 1))
     {
          lua_pushboolean(L, false);
          lua_pushinteger(L, -1);
          return 2;
     }
     Fr_tckStreamT *stream = (Fr_tckStreamT*)lua_touserdata(L, 1);
     Fr_tockenT t = stream->getNextTocken();
     lua_pushboolean(L, true);
     lua_pushinteger(L, t);
     return 2;
}
//--------------------------------------------------------------------
static const luaL_Reg fractalLib[] = {
     { "createFreeFractalStream",   lua_createFreeFractalStream },
     { "createFractalStream",   lua_createFractalStream },
     { "createFractalState",   lua_createFractalState },
     { "freeFractalStream",   lua_freeFractalStream },
     { "setFractalStreamTocken",   lua_setFractalStreamTocken },
     { "setReplaceTockenData",   lua_setReplaceTockenData },
     { "newLevel",   lua_newFractalLevel },
     { "stream_eos",   lua_tckStreamEos },
     { "stream_reset",   lua_tckStreamReset },
     { "stream_peek",   lua_tckStreamPeekNextTocken },
     { "stream_get",   lua_tckStreamGetNextTocken },
     { NULL, NULL }
};
int openFractalLibInit(lua_State *L) {
     luaL_newlib(L, fractalLib);
     return 1;
}
void openFractalLib(lua_State *L) {
     luaL_newlib(L, fractalLib);
     luaL_requiref(L, "Fractal", openFractalLibInit, 1);
     lua_pop(L, 1);  /* remove lib */
}