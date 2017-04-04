#include <cstdlib>
#include <cstdio>
#include <fractals\fractals.h>
#include "luaWindowApi.h"
#include "luaGraphicsApi.h"
#include "luaMutexApi.h"
#include "luaEventApi.h"
#include "luaFractalApi.h"

extern "C"
{
#include <lua\lua.h>
#include <lua\lauxlib.h>
#include <lua\lualib.h>
}
void openLibs(lua_State *L)
{
     /* load Lua base libraries */
     luaL_openlibs(L);

     /* load GL procs*/
     openGraphicsLib(L);
     /* load window procs*/
     openWindowLib(L);
     /* load mutex procs*/
     openMutexLib(L);
     /* load event procs*/
     openEventLib(L);
     /* load fractal procs*/
     openFractalLib(L);
     return;
}
int fractals::scriptFileExec(const char * luaScriptFile)
{
     /* initialize Lua */
     lua_State *L = luaL_newstate();

     openLibs(L);

     /* run the script */
     auto ret=luaL_dofile(L, luaScriptFile);
     if (ret != 0) {
          printf("Error occurs when calling luaL_dofile() Hint Machine 0x%x\n", ret);
          printf("Error: %s", lua_tostring(L, -1));
     }
     /* cleanup Lua */
     lua_close(L);
     return 0;
}
int fractals::scriptStringExec(const char* luaScript)
{
     /* initialize Lua */
     lua_State *L = luaL_newstate();

     /* load Lua base libraries */
     openLibs(L);

     /* run the script */
     luaL_dostring(L, luaScript);

     /* cleanup Lua */
     lua_close(L);
     return 0;
}
