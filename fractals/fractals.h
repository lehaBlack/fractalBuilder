#pragma once
#include <cstdlib>
#include <cstdio>

namespace fractals
{
     int scriptFileExec(const char* luaScriptFile);
     int scriptStringExec(const char* luaScript);
}