#pragma once
#include "tgaimage.h"
#include "Vec.h"
class Palette
{
public:
     Palette();
     ~Palette();
     virtual TGAColor getColor(int x, int y) const = 0;
};

class SolidePalette: 
     public Palette
{
private:
     TGAColor c_;
public:
     SolidePalette(const TGAColor& c);
     virtual TGAColor getColor(int x, int y) const override;
};
class LinePalette: 
     public Palette
{
private:
     TGAColor c0_;
     TGAColor c1_;
     Vec2i b_;
     Vec2i e_;
     double r_;
public:
     LinePalette(const Vec2i &b,const Vec2i &e,const TGAColor& c0, const TGAColor& c1);
     virtual TGAColor getColor(int x, int y) const override;
};
class TrianglePalette:
     public Palette
{
private:
private:
     TGAColor c0_;
     TGAColor c1_;
     TGAColor c2_;
     Vec2i v0_;
     Vec2i v1_;
     Vec2i v2_;
     int xM_;
     int xm_;
     int yM_;
     int ym_;

     double maxDistance_;

     void init();
public:
     TrianglePalette(
          const Vec2i &v0, const Vec2i &v1, const Vec2i &v2, 
          const TGAColor& c0, const TGAColor& c1, const TGAColor& c2);
     TrianglePalette(
          const Vec3i &v0, const Vec3i &v1, const Vec3i &v2,
          const TGAColor& c0, const TGAColor& c1, const TGAColor& c2);
     virtual TGAColor getColor(int x, int y) const override;
};