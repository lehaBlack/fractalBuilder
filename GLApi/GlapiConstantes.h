#pragma once
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#define OPEN_GL_CONTEXT_ID          -1
namespace GlApi
{
     enum BeginMode :unsigned short
     {
          GlApi_POINTS = GL_POINTS,
          GlApi_LINES = GL_LINES,
          GlApi_LINE_LOOP = GL_LINE_LOOP,
          GlApi_LINE_STRIP = GL_LINE_STRIP,
          GlApi_TRIANGLES = GL_TRIANGLES,
          GlApi_TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
          GlApi_TRIANGLE_FAN = GL_TRIANGLE_FAN,
          GlApi_QUADS = GL_QUADS,
          GlApi_QUAD_STRIP = GL_QUAD_STRIP,
          GlApi_POLYGON = GL_POLYGON,
          GlApi_NOT_INIT = -1
     };
     using CTX_idT = int;
};