#include "Palette.h"



Palette::Palette()
{
}


Palette::~Palette()
{
}

SolidePalette::SolidePalette(const TGAColor & c):
	c_(c)
{
}

TGAColor SolidePalette::getColor(int x, int y) const
{
	return c_;
}

LinePalette::LinePalette(const Vec2i & b, const Vec2i & e, const TGAColor & c0, const TGAColor & c1):
	c0_(c0),
	c1_(c1),
	b_(b),
	e_(e)
{
}

TGAColor LinePalette::getColor(int x, int y) const
{
	int x0 = b_.x_ - x;
	int y0 = b_.y_ - y;
	int x1 = e_.x_ - x;
	int y1 = e_.y_ - y;
	double r0 = sqrt(x0*x0 + y0*y0);
	double r1 = sqrt(x1*x1 + y1*y1);
	return (c0_ * r0 + c1_*r1)/(r1+r0);
}

TrianglePalette::TrianglePalette(
	const Vec2i & v0, const Vec2i & v1, const Vec2i & v2, 
	const TGAColor & c0, const TGAColor & c1, const TGAColor & c2): 
	c0_(c0),
	c1_(c1),
	c2_(c2),
	v0_(v0),
	v1_(v1),
	v2_(v2)
{
}

TrianglePalette::TrianglePalette(const Vec3i & v0, const Vec3i & v1, const Vec3i & v2, 
	const TGAColor & c0, const TGAColor & c1, const TGAColor & c2):
	c0_(c0),
	c1_(c1),
	c2_(c2),
	v0_(v0.x_, v0.y_),
	v1_(v1.x_, v1.y_),
	v2_(v2.x_, v2.y_)
{
}
//по поводу этого алгоритма меня терзают смутные сомнения...
TGAColor TrianglePalette::getColor(int x, int y) const
{
	int x0 = v0_.x_ - x;
	int y0 = v0_.y_ - y;
	int x1 = v1_.x_ - x;
	int y1 = v1_.y_ - y;
	int x2 = v2_.x_ - x;
	int y2 = v2_.y_ - y;
	double r0 = sqrt(x0*x0 + y0*y0);
	double r1 = sqrt(x1*x1 + y1*y1);
	double r2 = sqrt(x2*x2 + y2*y2);
	double n = 2.0/(r2 + r1 + r0);
	r0 = 1.0 - r0* n;
	r1 = 1.0 - r1* n;
	r2 = 1.0 - r2* n;
	return (c0_ *r0 + c1_*r1 + c2_*r2);
}
