#pragma once
#include "GlApi.h"
#include <glib\glLib.h>
#include <stack>
#include <vector>
#include <deque>
namespace GlApi
{
	class GLibContext
	{
	private:
		struct ColoredVert
		{
			double coordinates[3];
			union
			{
				byte color4B[4];
				int color1i;
			};

			ColoredVert();
			ColoredVert(const ColoredVert&);
			ColoredVert& operator=(const ColoredVert&);
			void setColor(byte* c);
			double &x();
			double &y();
			double &z();
			const double &x() const;
			const double &y() const;
			const double &z() const;
		};
		using coordVertT = ColoredVert;
		using VectorStorageT = std::deque<coordVertT>;
	private:
		TGAImage image_;
		int *zBuffer_;
		int maxZ_;
		//угол объектива=60гр
		//нижняя граница отсечения=0
		//верхняя граница отсечения=100
		double pM_[4][4];
		VectorStorageT vertexStor_;
		BeginMode mode_;
		byte selectedColor_[4];
		byte clearColor_[4];
		int pointW_;

		double translatedV_[3];
		//переводим координаты из пользовательских
		//в координаты на картинке+глубина
		bool convert(double x, double y, double z, Vec3i &answer);
		//---------------------------
		void drawPoint(
			double x, double y, double z, 
			const byte* color);
		//---------------------------
		void drawLine(
			double x0, double y0, double z0,
			double x1, double y1, double z1,
			const byte* color);
		void drawLine(
			double x0, double y0, double z0, 
			double x1, double y1, double z1, 
			const byte* color0, const byte* color1);
		//---------------------------
		void drawTriangle(
			double x0, double y0, double z0,
			double x1, double y1, double z1,
			double x2, double y2, double z2,
			const byte* color);
		void drawTriangle(
			double x0, double y0, double z0,
			double x1, double y1, double z1,
			double x2, double y2, double z2,
			const byte* color0, const byte* color1, const byte* color2);
		//---------------------------
		void drawLine(const ColoredVert& v0, const ColoredVert &v1);
		void drawTriangle(const ColoredVert& v0, const ColoredVert &v1, const ColoredVert &v2);
		void drawQuade(const ColoredVert& v0, const ColoredVert &v1,
			const ColoredVert &v2, const ColoredVert &v3);
		//---------------------------
		void TPoints();
		//---------------------------
		void TLines();
		void TLinesLoop();
		void TLinesStrip();
		//---------------------------
		void Ttriangles();
		void TtrianglesStrip();
		void TtrianglesFan();
		//---------------------------
		void Tquads();
		void TquadsStrip();
		//---------------------------
		void Tprocessing();
	public:
		GLibContext(int width, int height);
		~GLibContext();
		//------------------------------------------------
		void GLibPerspective(double fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
		void GLibBegin(BeginMode mode);
		void GLibEnd();
		void GLibClear();
		void GLibColor4d(double r, double g, double b, double a);
		void GLibColor3d(double r, double g, double b);
		void GLibColor4f(float r, float g, float b, float a);
		void GLibColor3f(float r, float g, float b);
		void GLibColor4ub(byte r, byte g, byte b, byte a);
		void GLibColor4b(char r, char g, char b, char a);
		void GLibColor3ub(byte r, byte g, byte b);
		void GLibColor3b(char r, char g, char b);
		void GLibColor4ui(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
		void GLibColor4i(int r, int g, int b, int a);
		void GLibColor3ui(unsigned int r, unsigned int g, unsigned int b);
		void GLibColor3i(int r, int g, int b);
		void GLibColor4us(unsigned short r, unsigned short g, unsigned short b, unsigned short a);
		void GLibColor4s(short r, short g, short b, short a);
		void GLibColor3us(unsigned short r, unsigned short g, unsigned short b);
		void GLibColor3s(short r, short g, short b);
		//------------------------------------------------
		void GLibVertex3d(double x, double y, double z);
		void GLibVertex2d(double x, double y);
		void GLibVertex3f(float x, float y, float z);
		void GLibVertex2f(float x, float y);
		void GLibVertex3s(short x, short y, short z);
		void GLibVertex2s(short x, short y);
		void GLibVertex3i(int x, int y, int z);
		void GLibVertex2i(int x, int y);
	};
}
