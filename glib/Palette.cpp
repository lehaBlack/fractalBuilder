#include "Palette.h"
#include <algorithm>


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
     int x1 = b_.x_ - e_.x_;
     int y1 = b_.y_ - e_.y_;
     r_ = sqrt(static_cast<double>(x1*x1 + y1*y1));
}

TGAColor LinePalette::getColor(int x, int y) const
{
     int x0 = b_.x_ - x;
     int y0 = b_.y_ - y;
     double r1 = sqrt(static_cast<double>(x0*x0 + y0*y0))/r_;
     double r0 = 1.0 - r1;
     return c0_ * r0 + c1_*r1;
}


void TrianglePalette::init()
{
     xM_ = std::max(v0_.x_, std::max(v1_.x_, v2_.x_));
     yM_ = std::max(v0_.y_, std::max(v1_.y_, v2_.y_));
     xm_ = std::min(v0_.x_, std::min(v1_.x_, v2_.x_));
     ym_ = std::min(v0_.y_, std::min(v1_.y_, v2_.y_));
     maxDistance_ = sqrt(static_cast<double>((xM_ - xm_)*(xM_ - xm_) + (yM_ - ym_)*(yM_ - ym_)));
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
     init();
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
     init();
}
TGAColor TrianglePalette::getColor(int x, int y) const
{
     double m2 =
          static_cast<double>(
          (y - v0_.y_)*(v1_.x_ - v0_.x_) -
               (x - v0_.x_)*(v1_.y_ - v0_.y_)) /
          static_cast<double>(
          (v2_.y_ - v0_.y_)*(v1_.x_ - v0_.x_) -
               (v2_.x_ - v0_.x_)*(v1_.y_ - v0_.y_));

     double m1 =
          static_cast<double>(
          (y - v0_.y_)*(v2_.x_ - v0_.x_) -
               (x - v0_.x_)*(v2_.y_ - v0_.y_)) /
          static_cast<double>(
          (v1_.y_ - v0_.y_)*(v2_.x_ - v0_.x_) -
               (v1_.x_ - v0_.x_)*(v2_.y_ - v0_.y_));
     double m0 = 1.0 - m1 - m2;
     return c0_*m0 + c1_*m1 + c2_*m2;
}


