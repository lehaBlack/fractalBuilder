#pragma once
#include "GlApi.h"
#include <glib\glLib.h>
#include <stack>
namespace GlApi
{
	using Int = int;

	class Context
	{
		using VectStackT = std::stack<Vec3i>;
	private:
		TGAImage _image;
		VectStackT _tmpStack;
		TGAColor _selectedColor;
		TGAColor _cearColor;
		BeginMode _mode;

	public:
		Context(int w, int h, int bpp = 3);
		~Context();
		void drawPoint(Int x, Int y);

		void begin(BeginMode mode);
		void vertex2i(Int v1, Int v2);
	};
}
