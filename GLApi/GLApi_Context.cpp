#include "GLApi_Context.h"



GlApi::Context::Context(int w, int h, int bpp):
	_image(w,h,bpp),
	_tmpStack(),
	_selectedColor(255,255,255),
	_cearColor(0,0,0),
	_mode(GlApi_POINTS)
{
}


GlApi::Context::~Context()
{
}

void GlApi::Context::drawPoint(Int x, Int y)
{
}

void GlApi::Context::begin(BeginMode mode)
{
	_mode = mode;
}

void GlApi::Context::vertex2i(Int v1, Int v2)
{
	switch (_mode)
	{
	case GlApi_POINTS:
	case GlApi_LINES:
	case GlApi_LINE_LOOP:
	case GlApi_LINE_STRIP:
	case GlApi_TRIANGLES:
	case GlApi_TRIANGLE_STRIP:
	case GlApi_TRIANGLE_FAN:
	case GlApi_QUADS:
	case GlApi_QUAD_STRIP:
	case GlApi_POLYGON:
	default:
	{

	}
	}
}
