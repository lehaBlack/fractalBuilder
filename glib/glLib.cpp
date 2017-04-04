//epicfail@gmail.com

#include <cmath>
#include <cmath>
#include <algorithm>
#include "GlibHelp.h"


void glLib::ns_point(const Vec2i & point, TGAImage & image, const Palette& palete)
{
	image.set(point.x_, point.y_, palete.getColor(point.x_, point.y_));
}

void glLib::ns_point(const Vec3i & point, TGAImage & image, const Palette& palete, int * zbuffer)
{
	ns_point(point.x_, point.y_, point.z_, image, palete, zbuffer);
}

void glLib::ns_point(int x, int y, int z, TGAImage & image, const Palette& palete, int * zbuffer)
{
	size_t idx = y * image.get_width() + x;
	if (zbuffer[idx] < z)
	{
		zbuffer[idx] = z;
		image.set(x, y, palete.getColor(x, y));
	}
}

void glLib::point(const Vec2i & point, TGAImage & image, const TGAColor & color)
{
	if (point.x_ < 0 || point.y_ < 0)
		return;
	if (point.x_ > image.get_width() || point.y_ > image.get_height())
		return;
	SolidePalette p(color);
	ns_point(point, image, p);
}

void glLib::point(const Vec3i & point, TGAImage & image, const TGAColor & color, int * zbuffer)
{
	if (point.x_<0 || point.y_<0)
		return;
	if (point.x_ > image.get_width() || point.y_ > image.get_height())
		return;
	SolidePalette p(color);
	ns_point(point, image, p, zbuffer);
}

void glLib::ns_line (Vec2i begin, Vec2i end, TGAImage & image, const Palette& palete)
{
    int x0 = begin.x_;
    int y0 = begin.y_;
    int x1 = end.x_;
    int y1 = end.y_;

    // if you don't understand what is happens here, you can read about Bresenham's algorithm
    bool swap = false;
    if (std::abs (x1 - x0) < std::abs (y1 - y0))
    {
        std::swap (x0, y0);
        std::swap (x1, y1);
        swap = true;
    }

    if (x0 > x1)
    {
        std::swap (x0, x1);
        std::swap (y0, y1);
    }

    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror = std::abs (dy) * 2;
    int error  = 0;
    for (; x0 <= x1; x0++)
    {
        if (swap)
            image.set(y0, x0, palete.getColor(y0, x0));
        else
            image.set(x0, y0, palete.getColor(x0, y0));

        error += derror;

        if (error > dx)
        {
            y0 += (dy > 0 ? 1 : -1);
            error -= dx * 2;
        }
    }
}

void glLib::ns_line(Vec3i begin, Vec3i end, TGAImage & image, const Palette& palete, int * zbuffer)
{
	int x0 = begin.x_;
	int y0 = begin.y_;
	int z0 = begin.z_;
	int x1 = end.x_;
	int y1 = end.y_;
	int z1 = end.z_;

	// if you don't understand what is happens here, you can read about Bresenham's algorithm
	bool swap = false;
	if (std::abs(x1 - x0) < std::abs(y1 - y0))
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
		swap = true;
	}

	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
		std::swap(z0, z1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;
	int dz = z1 - z0;

	int derror = std::abs(dy) * 2;
	int zderror = std::abs(dz) * 2;
	int error = 0;
	int zerror = 0;
	for (; x0 <= x1; x0++)
	{
		if (swap)
		{
				ns_point(y0, x0, z0, image, palete, zbuffer);
		}
		else
		{
				ns_point(x0, y0, z0, image, palete, zbuffer);
		}
		error += derror;
		zerror += zderror;

		if (error > dx)
		{
			y0 += (dy > 0 ? 1 : -1);
			error -= dx * 2;
		}
		if (zerror > dx)
		{
			z0 += (dz > 0 ? 1 : -1);
			error -= dx * 2;
		}
	}
}

void glLib::line(Vec2i begin, Vec2i end, TGAImage & image, const TGAColor & color)
{
	SolidePalette p(color);
	if (fingBorder(begin, end, image) == INSIDE)
		ns_line(begin, end, image, p);
}

void glLib::line(Vec3i begin, Vec3i end, TGAImage & image, const TGAColor & color, int * zbuffer)
{
	SolidePalette p(color);
	if(fingBorder(begin, end, image)==INSIDE)
		ns_line(begin, end, image, p, zbuffer);
}

void glLib::line(Vec2i begin, Vec2i end, TGAImage& image, const TGAColor & c0, const TGAColor & c1)
{
	LinePalette palite(begin, end, c0, c1);
	if (fingBorder(begin, end, image) == INSIDE)
		ns_line(begin, end, image, palite);
}

void glLib::line(Vec3i begin, Vec3i end, TGAImage & image, const TGAColor & c0, const TGAColor & c1, int * zbuffer)
{
	Vec2i b(begin.x_,begin.y_);
	Vec2i e(end.x_, end.y_);
	LinePalette palite(b, e, c0, c1);
	if (fingBorder(begin, end, image) == INSIDE)
		ns_line(begin, end, image, palite, zbuffer);
}

void glLib::triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage & image, const  TGAColor color)
{
	SolidePalette p(color);
	triangle(t0, t1, t2, image, p);
}

void glLib::triangle(Vec3i t0, Vec3i t1, Vec3i t2, TGAImage & image, const TGAColor & color, int * zbuffer)
{
	SolidePalette p(color);
	triangle(t0, t1, t2, image, p,zbuffer);
}

void glLib::triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage & image, const TGAColor & c0, const TGAColor & c1, const TGAColor & c2)
{
	TrianglePalette p(t0, t1, t2, c0, c1, c2);
	triangle(t0, t1, t2, image, p);
}

void glLib::triangle(Vec3i t0, Vec3i t1, Vec3i t2, TGAImage & image, const TGAColor & c0, const TGAColor & c1, const TGAColor & c2, int * zbuffer)
{
	TrianglePalette p(t0, t1, t2, c0, c1, c2);
	triangle(t0, t1, t2, image, p,zbuffer);
}

void glLib::triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage & image, const Palette& p)
{
	VertStack<Vec2i> stack;
	cutOffTriangleVerticles(t0, t1, t2, image, stack);
	for (int i = 0; i < stack.size() - 2; i++)
	{
		ns_triangle(stack.get(0).v, stack.get(i + 1).v, stack.get(i + 2).v,image, p);
	}
}

void glLib::triangle(Vec3i t0, Vec3i t1, Vec3i t2, TGAImage & image, const Palette& p, int * zbuffer)
{
	VertStack<Vec3i> stack;
	cutOffTriangleVerticles(t0, t1, t2, image, stack);
	for (int i = 0; i < stack.size(); i++)
	{
		stack.get(i).v.z_ = calculateZc(
			stack.get(i).v.x_, stack.get(i).v.y_,
			t0.x_, t0.y_, t0.z_,
			t1.x_, t1.y_, t1.z_,
			t2.x_, t2.y_, t2.z_);
	}
	for (int i = 0; i < stack.size() - 2; i++)
	{
		ns_triangle(stack.get(0).v, stack.get(i + 1).v, stack.get(i + 2).v, image, p, zbuffer);
	}
}

void glLib::ns_triangle (Vec3i t0, Vec3i t1, Vec3i t2, TGAImage & image, const Palette& palete, int * zbuffer)
{
	if (!zbuffer)
		THROW(ZERO_POINTER);
	int xm;
	int ym;
	int xM;
	int yM;
	size_t width = (size_t)image.get_width();
	xM = std::max(t0.x_, std::max(t1.x_, t2.x_));
	xm = std::min(t0.x_, std::min(t1.x_, t2.x_));
	yM = std::max(t0.y_, std::max(t1.y_, t2.y_));
	ym = std::min(t0.y_, std::min(t1.y_, t2.y_));
	for (int x = xm; x <= xM; x++)
	{
		for (int y = ym; y < yM; y++)
		{
			int d0 = countD(t0, t1, Vec3i(x, y));
			int d1 = countD(t1, t2, Vec3i(x, y));
			int d2 = countD(t2, t0, Vec3i(x, y));
			if (
				(d0 == d1 && d1 == d2)||
				(d0 == d1 && d2 == 0) ||
				(d1 == d2 && d0 == 0) ||
				(d0 == d2 && d1 == 0) ||
				(d0 == d1 && d0 == 0) ||
				(d0 == d2 && d0 == 0) ||
				(d1 == d2 && d1 == 0))
			{
				int z = calculateZc(x, y,
					t0.x_, t0.y_, t0.z_,
					t1.x_, t1.y_, t1.z_,
					t2.x_, t2.y_, t2.z_);
				size_t idx = y * width + x;
				if (zbuffer[idx] < z)
				{
					image.set(x, y, palete.getColor(x, y));
					zbuffer[idx] = z;
				}
			}
		}
	}
}

void glLib::ns_triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, const Palette& palete) {
	int xm;
	int ym;
	int xM;
	int yM;
	xM = std::max(t0.x_, std::max(t1.x_, t2.x_));
	xm = std::min(t0.x_, std::min(t1.x_, t2.x_));
	yM = std::max(t0.y_, std::max(t1.y_, t2.y_));
	ym = std::min(t0.y_, std::min(t1.y_, t2.y_));
	for (int x = xm; x <= xM; x++)
	{
		for (int y = ym; y < yM; y++)
		{
			int d0 = countD(t0, t1, Vec2i(x, y));
			int d1 = countD(t1, t2, Vec2i(x, y));
			int d2 = countD(t2, t0, Vec2i(x, y));
			if (
				(d0 == d1 && d1 == d2)||
				(d0 == d1 && d2 == 0) ||
				(d1 == d2 && d0 == 0) ||
				(d0 == d2 && d1 == 0) ||
				(d0 == d1 && d0 == 0) ||
				(d0 == d2 && d0 == 0) ||
				(d1 == d2 && d1 == 0))
			{
				image.set(x, y, palete.getColor(x, y));
			}
		}
	}
}

void glLib::gouraud_shading_traingle (Vec3i t0, Vec3i t1, Vec3i t2, float ity0, float ity1, float ity2, TGAImage &image,
                                      int *zbuffer)
{
    if (!zbuffer)
    THROW (ZERO_POINTER);

    // simple sort
    if (t0.y_ > t1.y_) { std::swap (t0, t1); std::swap (ity0, ity1); }
    if (t0.y_ > t2.y_) { std::swap (t0, t2); std::swap (ity0, ity2); }
    if (t1.y_ > t2.y_) { std::swap (t1, t2); std::swap (ity1, ity2); }

    // drawing triangle
    size_t width = (size_t) image.get_width ();
    Vec3i full_vec = t2 - t0;
    for (int y = t0.y_; y <= t2.y_; y++)
    {
        int dy            = y <= t1.y_ ? (y - t0.y_) : (t2.y_ - y);
        Vec3i segment_vec = y <= t1.y_ ? (t1 - t0) : (t2 - t1);

        float alpha = 0.0;
        if (full_vec.y_ != 0.0)
            alpha = (float) dy / full_vec.y_;
        float beta = 0.0;
        if (segment_vec.y_ != 0)
            beta = (float) dy / segment_vec.y_;

        int   beg_x = (int) (y <= t1.y_ ? (alpha * full_vec.x_    + t0.x_) : (t2.x_ - alpha * full_vec.x_));
        int   end_x = (int) (y <= t1.y_ ? (beta  * segment_vec.x_ + t0.x_) : (t2.x_ - beta  * segment_vec.x_));
        int   beg_z = (int) (y <= t1.y_ ? (alpha * full_vec.z_    + t0.z_) : (t2.z_ - alpha * full_vec.z_));
        int   end_z = (int) (y <= t1.y_ ? (beta  * segment_vec.z_ + t0.z_) : (t2.z_ - beta  * segment_vec.z_));
        float beg_n =        y <= t1.y_ ? (alpha * (ity2 - ity0)  + ity0)  : (ity2  - alpha * (ity2 - ity0));
        float end_n =        y <= t1.y_ ? (beta  * (ity1 - ity0)  + ity0)  : (ity2  - beta  * (ity2 - ity1));

        if (beg_x > end_x) { std::swap (beg_x, end_x); std::swap (beg_z, end_z); std::swap (beg_n, end_n);}
        for (int x = beg_x; x <= end_x; x++)      // draw a horizontal line
        {
            size_t idx = (size_t) y * width + (size_t) x;
            double gamma = (beg_x == end_x) ? 1.0 : (double) (x - beg_x) / (end_x - beg_x);
            int   z = (int) (gamma * (end_z - beg_z) + beg_z);
            double k =        gamma * (end_n - beg_n) + beg_n;
            if (zbuffer[idx] < z)
            {
                zbuffer[idx] = z;
                image.set (x, y, TGAColor(255, 255, 255) * k);
            }
        }
    }
}
