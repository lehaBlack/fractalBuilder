#pragma once
#include "glLib.h"

#define TEST_INTERSECT(val, i) ((val)&(i)==(i))
inline void averageVec(const Vec2i& v0, const Vec2i& v1, Vec2i& r)
{
	r.x_ = (v0.x_ + v1.x_) / 2;
	r.y_ = (v0.y_ + v1.y_) / 2;
}
inline void averageVec(const Vec3i& v0, const Vec3i& v1, Vec3i& r)
{
	r.x_ = (v0.x_ + v1.x_) / 2;
	r.y_ = (v0.y_ + v1.y_) / 2;
	r.z_ = (v0.z_ + v1.z_) / 2;
}
template<typename T>
inline int countD(const T& v0, const T& v1, const T& v2)
{
	double d0 = static_cast<double>(v2.x_ - v0.x_);
	double d1 = static_cast<double>(v1.y_ - v0.y_);
	double d2 = static_cast<double>(v2.y_ - v0.y_);
	double d3 = static_cast<double>(v1.x_ - v0.x_);
	double r = d0*d1 - d2*d3;
	return r<0 ? -1 : r == 0 ? 0 : 1;
}
inline int calculateZc(
	int x, int y,
	int v0_x, int v0_y, int v0_z,
	int v1_x, int v1_y, int v1_z,
	int v2_x, int v2_y, int v2_z)
{
	//|X0 Y0 Z0|
	//|X1 Y1 Z1| == 0
	//|X2 Y2 Y3|
	int X0 = (x - v0_x);	int X1 = (v1_x - v0_x);	int X2 = (v2_x - v0_x);
	int Y0 = (y - v0_y);	int Y1 = (v1_y - v0_y);	int Y2 = (v2_y - v0_y);
	/*Z0=?;*/				int Z1 = (v1_z - v0_z);	int Z2 = (v2_z - v0_z);
	int D = X0*(Y1*Z2-Y2*Z1)-Y0*(X1*Z2+X2*Z2);
	return Z1 - (D / ((X1*Y2 - X2*Y1)));
}
template<typename T>
inline glLib::IntersectT glLib::fingBorder_(T begin, T & res, const TGAImage & image)
{
	IntersectT rb, ra, re;
	T v;
	rb = intersect(begin, image);
	re = intersect(res, image);

	while (!onborder(res, rb, image) && (rb&re) == INSIDE)
	{
		T oldv = v;
		averageVec(begin, res, v);

		if (oldv == v)
			return INSIDE;

		ra = intersect(v, image);
		if ((rb&ra) != INSIDE)
		{
			rb = ra;
			begin = v;
		}
		else
		{
			res = v;
			re = ra;
		}
	}
	return static_cast<IntersectT>(rb&re);
}
template<typename T>
inline glLib::IntersectT glLib::intersect(const T & point, const TGAImage & image)
{
	IntersectT r = INSIDE;

	if (point.x_ < 0)
		r = static_cast<IntersectT>(r | LEFT);
	if (point.y_ < 0)
		r = static_cast<IntersectT>(r | TOP);
	if (point.x_ > image.get_width())
		r = static_cast<IntersectT>(r | RIGHT);
	if (point.y_ > image.get_height())
		r = static_cast<IntersectT>(r | BOTTOM);

	return r;
}

template<typename T>
inline bool glLib::onborder(const T & v, IntersectT i, const TGAImage & image)
{
	bool res = false;
	if (!res&&TEST_INTERSECT(i, LEFT))
		res = v.x_ == 0;
	if (!res&&TEST_INTERSECT(i, TOP))
		res = v.y_ == 0;
	if (!res&&TEST_INTERSECT(i, RIGHT))
		res = v.x_ == image.get_width() - 1;
	if (!res&&TEST_INTERSECT(i, BOTTOM))
		res = v.y_ == image.get_height() - 1;
	return res;
}

template<typename T>
inline  glLib::IntersectT glLib::fingBorder(T& begin, T & end, const TGAImage & image)
{
	T v;
	IntersectT rb, ra, re;

	if (begin == end)
		return NONE;
	rb = intersect(begin, image);
	re = intersect(end, image);

	if (rb == INSIDE && re == INSIDE)
		return INSIDE;

	do
	{
		averageVec(begin, end, v);

		ra = intersect(v, image);

		if ((ra & rb) != INSIDE)
		{
			begin = v;
			rb = ra;
		}
		else if ((ra & re) != INSIDE)
		{
			end = v;
			re = ra;
		}
	} while (ra != INSIDE && (rb & re) == INSIDE);
	if (ra == INSIDE)
	{
		if (rb != INSIDE)
		{
			T v_ = v;
			rb = fingBorder_(begin, v_, image);
			begin = v_;
		}
		if (re != INSIDE)
		{
			T v_ = v;
			re = fingBorder_(end, v_, image);
			end = v_;
		}
		return INSIDE;
	}
	return NONE;
}

template<typename T>
inline void glLib::cutOffTriangleVerticles(T t0, T t1, T t2, const TGAImage & image, VertStack<T>& vstor)
{
	T v0_0 = t0;
	T v0_1 = t0;
	T v1_0 = t1;
	T v1_1 = t1;
	T v2_0 = t2;
	T v2_1 = t2;
	int min_x, min_y, max_x, max_y;

	IntersectT l0, l1, l2;
	bool needSrt = false;

	min_x = std::min(t0.x_, std::min(t1.x_, t2.x_));
	min_y = std::min(t0.y_, std::min(t1.y_, t2.y_));
	max_x = std::max(t0.x_, std::max(t1.x_, t2.x_));
	max_y = std::max(t0.y_, std::max(t1.y_, t2.y_));

	if ((min_x >= 0 && min_y >= 0) &&
		(max_x < image.get_width() && max_y < image.get_height()))
	{
		vstor.push(t0, 0.0);
		vstor.push(t1, 0.0);
		vstor.push(t2, 0.0);
		return;
	}
	l0 = fingBorder(v0_0, v1_1, image);
	l1 = fingBorder(v1_0, v2_1, image);
	l2 = fingBorder(v2_0, v0_1, image);
	if ((l0 & l1 & l2) != INSIDE)
	{
		if ((min_x < 0 && min_y < 0) &&
			(max_x >= image.get_width() && max_y >= image.get_height()))
		{
			vstor.push(T(0, 0), 0.0);
			vstor.push(T(image.get_width() - 1, 0), 0.0);
			vstor.push(T(image.get_width() - 1, image.get_height() - 1), 0.0);
			vstor.push(T(0, image.get_height() - 1), 0.0);
		}
		return;
	}

	if (l0 == INSIDE)
	{
		vstor.push(v0_0, 0.0);
		if (v1_1 != t1)
			vstor.push(v1_1, 0.0);
	}
	if (l1 == INSIDE)
	{
		vstor.push(v1_0, 0.0);
		if (v2_1 != t2)
			vstor.push(v2_1, 0.0);
	}
	if (l2 == INSIDE)
	{
		vstor.push(v2_0, 0.0);
		if (v0_1 != t0)
			vstor.push(v0_1, 0.0);
	}
	{
		if (min_x <= 0 && min_y <= 0)
		{
			pushIfInTriangle(t0, t1, t2, T(0, 0), vstor);
			needSrt = true;
		}
		if (max_x >= image.get_width() - 1 && min_y <= 0)
		{
			pushIfInTriangle(t0, t1, t2, T(image.get_width() - 1, 0), vstor);
			needSrt = true;
		}
		if (max_x >= image.get_width() - 1 && max_y >= image.get_height() - 1)
		{
			pushIfInTriangle(t0, t1, t2, T(image.get_width() - 1, image.get_height() - 1), vstor);
			needSrt = true;
		}
		if (min_x <= 0 && max_y >= image.get_height() - 1)
		{
			pushIfInTriangle(t0, t1, t2, T(0, image.get_height() - 1), vstor);
			needSrt = true;
		}
		if (needSrt)
		{
			vstor.sort();
		}
	}
}

template<typename T>
inline void glLib::pushIfInTriangle(const T & t0, const T & t1, const T & t2, const T & v, VertStack<T>& vstor)
{
	int r0, r1, r2;
	r0 = countD(t0, t1, v);
	r1 = countD(t1, t2, v);
	r2 = countD(t2, t0, v);
	if (r0 == r1&&r1 == r2)
		vstor.push(v, 0.0);
}
