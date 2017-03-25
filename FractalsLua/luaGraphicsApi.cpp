#include "luaGraphicsApi.h"
#include <Windows.h>
#include <GL/GL.h>
#include <gl/GLU.h>
#include "NeHeWindowGL.h"
#define LUA_PUSH_PTR(L,ptr) ((ptr)==nullptr?lua_pushnil(L):lua_pushlightuserdata(L,ptr))
//Gl Begin/End
int lua_glBegin(lua_State *L)
{
	bool res = false;
	int argc = lua_gettop(L);
	if(argc==1)
		if (lua_isinteger(L, 1))
		{
			glBegin((GLenum)lua_tointeger(L,1));
			res = true;
		}
	lua_pushboolean(L, res);
	return 1;
}
int lua_glEnd(lua_State *L)
{
	bool res = false;
	int argc = lua_gettop(L);
	if (argc == 0)
	{
		glEnd();
		res = true;
	}
	lua_pushboolean(L, res);
	return 1;
}
//Vertexes
int lua_glVertexs(lua_State *L)
{
	bool res = false;
	int argc = lua_gettop(L);
	switch (argc)
	{
	case 2:
	{
		if (lua_isinteger(L, 1) && lua_isinteger(L, 2))
		{
			res = true;
			glVertex2s((GLshort)lua_tointeger(L, 1), (GLshort)lua_tointeger(L, 2));
		}
	}
	break;
	case 3:
	{
		if (lua_isinteger(L, 1) && lua_isinteger(L, 2) && lua_isinteger(L, 3))
		{
			res = true;
			glVertex3s((GLshort)lua_tointeger(L, 1), (GLshort)lua_tointeger(L, 2), (GLshort)lua_tointeger(L, 3));
		}
	}
		break;
	}
	lua_pushboolean(L, res);
	return 1;
}
int lua_glVertexi(lua_State *L)
{
	bool res = false;
	int argc = lua_gettop(L);
	switch (argc)
	{
	case 2:
	{
		if (lua_isinteger(L, 1) && lua_isinteger(L, 2))
		{
			res = true;
			glVertex2i((GLint) lua_tointeger(L, 1), (GLint)lua_tointeger(L, 2));
		}
	}
	break;
	case 3:
	{
		if (lua_isinteger(L, 1) && lua_isinteger(L, 2) && lua_isinteger(L, 3))
		{
			res = true;
			glVertex3i((GLint)lua_tointeger(L, 1), (GLint)lua_tointeger(L, 2), (GLint)lua_tointeger(L, 3));
		}
	}
	break;
	}
	lua_pushboolean(L, res);
	return 1;
}
int lua_glVertexf(lua_State *L)
{
	bool res = false;
	int argc = lua_gettop(L);
	switch (argc)
	{
	case 2:
	{
		if (lua_isnumber(L, 1) && lua_isnumber(L, 2))
		{
			res = true;
			glVertex2f((GLfloat)lua_tonumber(L, 1), (GLfloat)lua_tonumber(L, 2));
		}
	}
	break;
	case 3:
	{
		if (lua_isnumber(L, 1) && lua_isnumber(L, 2) && lua_isnumber(L, 3))
		{
			res = true;
			glVertex3f((GLfloat)lua_tonumber(L, 1), (GLfloat)lua_tonumber(L, 2), (GLfloat)lua_tonumber(L, 3));
		}
	}
	break;
	}
	lua_pushboolean(L, res);
	return 1;
}
int lua_glVertexd(lua_State *L)
{
	bool res = false;
	int argc = lua_gettop(L);
	switch (argc)
	{
	case 2:
	{
		if (lua_isnumber(L, 1) && lua_isnumber(L, 2))
		{
			res = true;
			glVertex2d(lua_tonumber(L, 1), lua_tonumber(L, 2));
		}
	}
	break;
	case 3:
	{
		if (lua_isnumber(L, 1) && lua_isnumber(L, 2) && lua_isnumber(L, 3))
		{
			res = true;
			glVertex3d(lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3));
		}
	}
	break;
	}
	lua_pushboolean(L, res);
	return 1;
}
int lua_glVertex(lua_State *L)
{
	int argc = lua_gettop(L);
	switch (argc)
	{
	case 2:
	{
		if (lua_isinteger(L, 1) && lua_isinteger(L, 2))
			return lua_glVertexi(L);
		if (lua_isnumber(L, 1) && lua_isnumber(L, 2))
			return lua_glVertexd(L);
	}
	break;
	case 3:
	{
		if (lua_isinteger(L, 1) && lua_isinteger(L, 2) && lua_isinteger(L, 3))
			return lua_glVertexi(L);
		if (lua_isnumber(L, 1) && lua_isnumber(L, 2) && lua_isnumber(L, 3))
			return lua_glVertexd(L);
	}
	break;
	}
	lua_pushboolean(L, false);
	return 1;
}
//GL colors
int lua_glColorb(lua_State *L)
{
	int argc = lua_gettop(L);
	switch (argc)
	{
	case 3:
	{
		if (lua_isinteger(L, 1) && lua_isinteger(L, 2) && lua_isinteger(L, 3))
		{
			glColor3b((GLbyte)lua_tointeger(L, 1), (GLbyte)lua_tointeger(L, 2), (GLbyte)lua_tointeger(L, 3));
		}
		lua_pushboolean(L, true);
	}
	break;
	case 4:
	{
		if (lua_isinteger(L, 1) && lua_isinteger(L, 2) && lua_isinteger(L, 3) && lua_isinteger(L, 4))
		{
			glColor4b((GLbyte)lua_tointeger(L, 1), (GLbyte)lua_tointeger(L, 2), (GLbyte)lua_tointeger(L, 3), (GLbyte)lua_tointeger(L, 4));
		}
		lua_pushboolean(L, true);
	}
	break;
	default:
	{
		lua_pushboolean(L, false);
	}
	break;
	}
	return 1;
}
int lua_glColorub(lua_State *L)
{
	int argc = lua_gettop(L);
	switch (argc)
	{
	case 3:
	{
		if (lua_isinteger(L, 1) && lua_isinteger(L, 2) && lua_isinteger(L, 3))
		{
			glColor3ub((GLubyte)lua_tointeger(L, 1), (GLubyte)lua_tointeger(L, 2), (GLubyte)lua_tointeger(L, 3));
		}
		lua_pushboolean(L, true);
	}
	break;
	case 4:
	{
		if (lua_isinteger(L, 1) && lua_isinteger(L, 2) && lua_isinteger(L, 3) && lua_isinteger(L, 4))
		{
			glColor4ub((GLubyte)lua_tointeger(L, 1), (GLubyte)lua_tointeger(L, 2), (GLubyte)lua_tointeger(L, 3), (GLubyte)lua_tointeger(L, 4));
		}
		lua_pushboolean(L, true);
	}
	break;
	default:
	{
		lua_pushboolean(L, false);
	}
	break;
	}
	return 1;
}
int lua_glColors(lua_State *L)
{
	int argc = lua_gettop(L);
	switch (argc)
	{
	case 3:
	{
		if (lua_isinteger(L, 1) && lua_isinteger(L, 2) && lua_isinteger(L, 3))
		{
			glColor3s((GLshort)lua_tointeger(L, 1), (GLshort)lua_tointeger(L, 2), (GLshort)lua_tointeger(L, 3));
		}
		lua_pushboolean(L, true);
	}
	break;
	case 4:
	{
		if (lua_isinteger(L, 1) && lua_isinteger(L, 2) && lua_isinteger(L, 3) && lua_isinteger(L, 4))
		{
			glColor4s((GLshort)lua_tointeger(L, 1), (GLshort)lua_tointeger(L, 2), (GLshort)lua_tointeger(L, 3), (GLshort)lua_tointeger(L, 4));
		}
		lua_pushboolean(L, true);
	}
	break;
	default:
	{
		lua_pushboolean(L, false);
	}
	break;
	}
	return 1;
}
int lua_glColorus(lua_State *L)
{
	int argc = lua_gettop(L);
	switch (argc)
	{
	case 3:
	{
		if (lua_isinteger(L, 1) && lua_isinteger(L, 2) && lua_isinteger(L, 3))
		{
			glColor3us((GLushort)lua_tointeger(L, 1), (GLushort)lua_tointeger(L, 2), (GLushort)lua_tointeger(L, 3));
		}
		lua_pushboolean(L, true);
	}
	break;
	case 4:
	{
		if (lua_isinteger(L, 1) && lua_isinteger(L, 2) && lua_isinteger(L, 3) && lua_isinteger(L, 4))
		{
			glColor4us((GLushort)lua_tointeger(L, 1), (GLushort)lua_tointeger(L, 2), (GLushort)lua_tointeger(L, 3), (GLushort)lua_tointeger(L, 4));
		}
		lua_pushboolean(L, true);
	}
	break;
	default:
	{
		lua_pushboolean(L, false);
	}
	break;
	}
	return 1;
}
int lua_glColori(lua_State *L)
{
	int argc = lua_gettop(L);
	switch (argc)
	{
	case 3:
	{
		if (lua_isinteger(L, 1) && lua_isinteger(L, 2) && lua_isinteger(L, 3))
		{
			glColor3i((GLint)lua_tointeger(L, 1), (GLint)lua_tointeger(L, 2), (GLint)lua_tointeger(L, 3));
		}
		lua_pushboolean(L, true);
	}
	break;
	case 4:
	{
		if (lua_isinteger(L, 1) && lua_isinteger(L, 2) && lua_isinteger(L, 3) && lua_isinteger(L, 4))
		{
			glColor4i((GLint)lua_tointeger(L, 1), (GLint)lua_tointeger(L, 2), (GLint)lua_tointeger(L, 3), (GLint)lua_tointeger(L, 4));
		}
		lua_pushboolean(L, true);
	}
	break;
	default:
	{
		lua_pushboolean(L, false);
	}
	break;
	}
	return 1;
}
int lua_glColorui(lua_State *L)
{
	int argc = lua_gettop(L);
	switch (argc)
	{
	case 3:
	{
		if (lua_isinteger(L, 1) && lua_isinteger(L, 2) && lua_isinteger(L, 3))
		{
			glColor3ui((GLuint)lua_tointeger(L, 1), (GLuint)lua_tointeger(L, 2), (GLuint)lua_tointeger(L, 3));
		}
		lua_pushboolean(L, true);
	}
	break;
	case 4:
	{
		if (lua_isinteger(L, 1) && lua_isinteger(L, 2) && lua_isinteger(L, 3) && lua_isinteger(L, 4))
		{
			glColor4ui((GLuint)lua_tointeger(L, 1), (GLuint)lua_tointeger(L, 2), (GLuint)lua_tointeger(L, 3), (GLuint)lua_tointeger(L, 4));
		}
		lua_pushboolean(L, true);
	}
	break;
	default:
	{
		lua_pushboolean(L, false);
	}
	break;
	}
	return 1;
}
int lua_glColorf(lua_State *L)
{
	int argc = lua_gettop(L);
	switch (argc)
	{
	case 3:
	{
		if (lua_isnumber(L, 1) && lua_isnumber(L, 2) && lua_isnumber(L, 3))
		{
			glColor3f((GLfloat)lua_tonumber(L, 1), (GLfloat)lua_tonumber(L, 2), (GLfloat)lua_tonumber(L, 3));
		}
		lua_pushboolean(L, true);
	}
	break;
	case 4:
	{
		if (lua_isnumber(L, 1) && lua_isnumber(L, 2) && lua_isnumber(L, 3) && lua_isnumber(L, 4))
		{
			glColor4f((GLfloat)lua_tonumber(L, 1), (GLfloat)lua_tonumber(L, 2), (GLfloat)lua_tonumber(L, 3), (GLfloat)lua_tonumber(L, 4));
		}
		lua_pushboolean(L, true);
	}
	break;
	default:
	{
		lua_pushboolean(L, false);
	}
	break;
	}
	return 1;
}
int lua_glColord(lua_State *L)
{
	int argc = lua_gettop(L);
	switch (argc)
	{
	case 3:
	{
		if (lua_isnumber(L, 1) && lua_isnumber(L, 2) && lua_isnumber(L, 3))
		{
			glColor3d((GLdouble)lua_tonumber(L, 1), (GLdouble)lua_tonumber(L, 2), (GLdouble)lua_tonumber(L, 3));
		}
		lua_pushboolean(L, true);
	}
	break;
	case 4:
	{
		if (lua_isnumber(L, 1) && lua_isnumber(L, 2) && lua_isnumber(L, 3) && lua_isnumber(L, 4))
		{
			glColor4d((GLdouble)lua_tonumber(L, 1), (GLdouble)lua_tonumber(L, 2), (GLdouble)lua_tonumber(L, 3), (GLdouble)lua_tonumber(L, 4));
		}
		lua_pushboolean(L, true);
	}
	break;
	default:
	{
		lua_pushboolean(L, false);
	}
	break;
	}
	return 1;
}
//GL Translate
int lua_glTranslate(lua_State* L)
{
	int argc = lua_gettop(L);
	switch (argc)
	{
	case 3:
	{
		if (lua_isnumber(L, 1) && lua_isnumber(L, 2) && lua_isnumber(L, 3))
		{
			glTranslated((GLdouble)lua_tonumber(L, 1), (GLdouble)lua_tonumber(L, 2), (GLdouble)lua_tonumber(L, 3));
		}
		lua_pushboolean(L, true);
	}
	break;
	default:
	{
		lua_pushboolean(L, false);
	}
	break;
	}
	return 1;
}
static const luaL_Reg graphicsLib[] = {
	{ "Begin", lua_glBegin },
	{ "End", lua_glEnd },
	{ "Vertex", lua_glVertex },	
	{ "Vertexs", lua_glVertexs },
	{ "Vertexi", lua_glVertexi },
	{ "Vertexf", lua_glVertexf },
	{ "Vertexd", lua_glVertexd },
	{ "Colorb", lua_glColorb },
	{ "Colorub", lua_glColorub },
	{ "Colors", lua_glColors },
	{ "Colorus", lua_glColorus },
	{ "Colori", lua_glColori },
	{ "Colorui", lua_glColorui },
	{ "Colorf", lua_glColorf },
	{ "Colord", lua_glColord },
	{ "Translate", lua_glTranslate },
	// BeginMode 
	{ "POINTS", NULL },
	{ "LINES", NULL },
	{ "LINE_LOOP", NULL },
	{ "LINE_STRIP", NULL },
	{ "TRIANGLES", NULL },
	{ "TRIANGLE_STRIP", NULL },
	{ "TRIANGLE_FAN", NULL },
	{ "QUADS", NULL },
	{ "QUAD_STRIP", NULL },
	{ "POLYGON", NULL },
	{ NULL, NULL }
};
int openGraphicsLibInit(lua_State *L) {
	luaL_newlib(L, graphicsLib);
	lua_pushinteger(L, GL_POINTS);
	lua_setfield(L, -2, "POINTS");
	lua_pushinteger(L, GL_LINES);
	lua_setfield(L, -2, "LINES");
	lua_pushinteger(L, GL_LINE_LOOP);
	lua_setfield(L, -2, "LINE_LOOP");
	lua_pushinteger(L, GL_LINE_STRIP);
	lua_setfield(L, -2, "LINE_STRIP");
	lua_pushinteger(L, GL_TRIANGLES);
	lua_setfield(L, -2, "TRIANGLES");
	lua_pushinteger(L, GL_TRIANGLE_STRIP);
	lua_setfield(L, -2, "TRIANGLE_STRIP");
	lua_pushinteger(L, GL_TRIANGLE_FAN);
	lua_setfield(L, -2, "TRIANGLE_FAN");
	lua_pushinteger(L, GL_QUADS);
	lua_setfield(L, -2, "QUADS");
	lua_pushinteger(L, GL_QUAD_STRIP);
	lua_setfield(L, -2, "QUAD_STRIP");
	lua_pushinteger(L, GL_POLYGON);
	lua_setfield(L, -2, "POLYGON");
	
	return 1;
}
void openGraphicsLib(lua_State *L){
	luaL_newlib(L, graphicsLib);
	luaL_requiref(L, "GL", openGraphicsLibInit, 1);
	lua_pop(L, 1);  /* remove lib */
}

