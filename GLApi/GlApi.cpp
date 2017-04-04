#include "GlApi.h"

std::mutex                GlApi::GlApi::globalLocker;
GlApi::CTX_idT            GlApi::GlApi::selectedContext = OPEN_GL_CONTEXT_ID;
GlApi::GlApi::ContextStor GlApi::GlApi::contextes;

GlApi::CTX_idT GlApi::GlApi::createContext(int width, int height)
{
	bool stateOk = false;
	int id = OPEN_GL_CONTEXT_ID;
	GLibContext *ctx;
	ctx = new GLibContext(width, height);
	globalLocker.lock();
	do
	{
		int id = rand();
		if (contextes.count(id) == 0)
		{
			stateOk = true;
			contextes.insert(ContextStorCell(id, ctx));
		}
	} while (!stateOk);
	globalLocker.unlock();
	return CTX_idT(id);
}

void GlApi::GlApi::UseContext(CTX_idT ctxId)
{
	globalLocker.lock();
	if(ctxId == OPEN_GL_CONTEXT_ID)
		selectedContext = ctxId;
	else if (contextes.count(ctxId) != 0)
		selectedContext = ctxId;
	globalLocker.unlock();
}

void GlApi::GlApi::DestroyContext(CTX_idT ctxId)
{
	globalLocker.lock();
	if (selectedContext == ctxId)
		selectedContext = OPEN_GL_CONTEXT_ID;
	if (contextes.count(ctxId) != 0)
	{
		delete contextes[ctxId];
		contextes.erase(ctxId);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::Begin(BeginMode mode)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glBegin(mode);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibBegin(mode);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::End()
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glEnd();
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibEnd();
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::Perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		gluPerspective(fovy, aspect, zNear, zFar);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibPerspective(fovy, aspect, zNear, zFar);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::Clear()
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibClear();
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::SaveTGA(const char * tgaImageName)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		throw std::exception("Can't save OpenGL context error in function:" __FUNCTION__);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibSave(tgaImageName);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::Vertex2s(GLshort v1, GLshort v2)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glVertex2s(v1,v2);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibVertex2s(v1, v2);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::Vertex2i(GLint v1, GLint v2)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glVertex2i(v1, v2);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibVertex2i(v1, v2);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::Vertex2f(GLfloat v1, GLfloat v2)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glVertex2f(v1, v2);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibVertex2f(v1, v2);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::Vertex2d(GLdouble v1, GLdouble v2)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glVertex2d(v1, v2);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibVertex2d(v1, v2);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::Vertex3s(GLshort v1, GLshort v2, GLshort v3)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glVertex3s(v1, v2,v3);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibVertex3s(v1, v2,v3);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::Vertex3i(GLint v1, GLint v2, GLint v3)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glVertex3i(v1, v2, v3);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibVertex3i(v1, v2, v3);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::Vertex3f(GLfloat v1, GLfloat v2, GLfloat v3)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glVertex3f(v1, v2, v3);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibVertex3f(v1, v2, v3);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::Vertex3d(GLdouble v1, GLdouble v2, GLdouble v3)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glVertex3d(v1, v2, v3);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibVertex3d(v1, v2, v3);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}
void GlApi::GlApi::Color3b(GLbyte v1, GLbyte v2, GLbyte v3)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glColor3b(v1, v2, v3);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibColor3b(v1, v2, v3);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}
void GlApi::GlApi::Color3ub(GLubyte v1, GLubyte v2, GLubyte v3)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glColor3ub(v1, v2, v3);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibColor3ub(v1, v2, v3);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}
void GlApi::GlApi::Color3s(GLshort v1, GLshort v2, GLshort v3)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glColor3s(v1, v2, v3);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibColor3s(v1, v2, v3);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::Color3us(GLushort v1, GLushort v2, GLushort v3)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glColor3us(v1, v2, v3);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibColor3us(v1, v2, v3);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::Color3i(GLint v1, GLint v2, GLint v3)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glColor3i(v1, v2, v3);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibColor3i(v1, v2, v3);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::Color3ui(GLuint v1, GLuint v2, GLuint v3)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glColor3ui(v1, v2, v3);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibColor3ui(v1, v2, v3);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::Color3f(GLfloat v1, GLfloat v2, GLfloat v3)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glColor3f(v1, v2, v3);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibColor3f(v1, v2, v3);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::Color3d(GLdouble v1, GLdouble v2, GLdouble v3)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glColor3d(v1, v2, v3);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibColor3d(v1, v2, v3);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::Color4b(GLbyte v1, GLbyte v2, GLbyte v3, GLbyte v4)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glColor4b(v1, v2, v3, v4);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibColor4b(v1, v2, v3, v4);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::Color4ub(GLubyte v1, GLubyte v2, GLubyte v3, GLubyte v4)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glColor4ub(v1, v2, v3, v4);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibColor4ub(v1, v2, v3, v4);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::Color4s(GLshort v1, GLshort v2, GLshort v3, GLshort v4)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glColor4s(v1, v2, v3, v4);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibColor4s(v1, v2, v3, v4);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::Color4us(GLushort v1, GLushort v2, GLushort v3, GLushort v4)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glColor4us(v1, v2, v3, v4);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibColor4us(v1, v2, v3, v4);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::Color4i(GLint v1, GLint v2, GLint v3, GLint v4)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glColor4i(v1, v2, v3, v4);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibColor4i(v1, v2, v3, v4);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::Color4ui(GLuint v1, GLuint v2, GLuint v3, GLuint v4)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glColor4ui(v1, v2, v3, v4);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibColor4ui(v1, v2, v3, v4);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::Color4f(GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glColor4f(v1, v2, v3, v4);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibColor4f(v1, v2, v3, v4);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::Color4d(GLdouble v1, GLdouble v2, GLdouble v3, GLdouble v4)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glColor4d(v1, v2, v3, v4);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibColor4d(v1, v2, v3, v4);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}

void GlApi::GlApi::Translate(GLdouble v1, GLdouble v2, GLdouble v3)
{
	globalLocker.lock();
	if (selectedContext == OPEN_GL_CONTEXT_ID)
	{
		glTranslated(v1, v2, v3);
	}
	else if (contextes.count(selectedContext) != 0)
	{
		contextes[selectedContext]->GLibTranslate(v1, v2, v3);
	}
	else
	{
		throw std::exception("Error Not select Context in function:" __FUNCTION__);
	}
	globalLocker.unlock();
}
