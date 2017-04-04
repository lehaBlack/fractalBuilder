#pragma once
#include <glib\glLib.h>
#include <map>
#include <mutex>
#include "GLApi_Context.h"
namespace GlApi
{
     class GlApi
     {
     private:
          using ContextStor = std::map<CTX_idT,  GLibContext*>;
          using ContextStorCell = std::pair<CTX_idT,  GLibContext*>;

          static std::mutex globalLocker;
          static CTX_idT selectedContext;
          static ContextStor contextes;
     public:
          static CTX_idT createContext(int width, int height);
          static void UseContext(CTX_idT ctxId);
          static void DestroyContext(CTX_idT ctxId);

          static void Begin(BeginMode mode);
          static void End();
          
          static void Vertex2s(GLshort v1, GLshort v2);
          static void Vertex2i(GLint v1, GLint v2);
          static void Vertex2f(GLfloat v1, GLfloat v2);
          static void Vertex2d(GLdouble v1, GLdouble v2);

          static void Vertex3s(GLshort v1, GLshort v2, GLshort v3);
          static void Vertex3i(GLint v1, GLint v2, GLint v3);
          static void Vertex3f(GLfloat v1, GLfloat v2, GLfloat v3);
          static void Vertex3d(GLdouble v1, GLdouble v2, GLdouble v3);
          
          static void Color3b(GLbyte v1, GLbyte v2, GLbyte v3);
          static void Color3ub(GLubyte v1, GLubyte v2, GLubyte v3);
          static void Color3s(GLshort v1, GLshort v2, GLshort v3);
          static void Color3us(GLushort v1, GLushort v2, GLushort v3);
          static void Color3i(GLint v1, GLint v2, GLint v3);
          static void Color3ui(GLuint v1, GLuint v2, GLuint v3);
          static void Color3f(GLfloat v1, GLfloat v2, GLfloat v3);
          static void Color3d(GLdouble v1, GLdouble v2, GLdouble v3);

          static void Color4b(GLbyte v1, GLbyte v2, GLbyte v3, GLbyte v4);
          static void Color4ub(GLubyte v1, GLubyte v2, GLubyte v3, GLubyte v4);
          static void Color4s(GLshort v1, GLshort v2, GLshort v3, GLshort v4);
          static void Color4us(GLushort v1, GLushort v2, GLushort v3, GLushort v4);
          static void Color4i(GLint v1, GLint v2, GLint v3, GLint v4);
          static void Color4ui(GLuint v1, GLuint v2, GLuint v3, GLuint v4);
          static void Color4f(GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4);
          static void Color4d(GLdouble v1, GLdouble v2, GLdouble v3, GLdouble v4);
          
          static void Translate(GLdouble v1, GLdouble v2, GLdouble v3);
          static void Perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
          static void Clear();

          static void SaveTGA(const char* tgaImageName);
     };

}