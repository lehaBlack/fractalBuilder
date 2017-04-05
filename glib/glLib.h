//epicfail@gmail.com

//! @brief  Do graphic


#ifndef GLLIB_GLLIB_H
#define GLLIB_GLLIB_H

#include "tgaimage.h"
#include "Vec.h"
#include "VertStack.h"
#include "Palette.h"

class glLib
{
private:
     enum IntersectT
     {
          INSIDE = 0,
          LEFT = 1,
          TOP = 2,
          RIGHT = 4,
          BOTTOM = 8,
          NONE = 15
     };
     static void ns_point(const Vec2i &point, TGAImage & image, const Palette& palete);
     static void ns_point(const Vec3i &point, TGAImage & image, const Palette& palete, int * zbuffer);
     static void ns_point(int x, int y, int z, TGAImage & image, const Palette& palete, int * zbuffer);
     static void ns_line(Vec2i begin, Vec2i end, TGAImage & image, const Palette& palete);
     static void ns_line(Vec3i begin, Vec3i end, TGAImage & image, const Palette& palete, int * zbuffer);
     static void ns_triangle (Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, const Palette& palete);
    static void ns_triangle (Vec3i t0, Vec3i t1, Vec3i t2, TGAImage & image, const Palette& palete, int * zbuffer);

     template <typename T> static IntersectT fingBorder_(T begin, T &res, const TGAImage & image);
     template <typename T> static glLib::IntersectT intersect(const T& point, const TGAImage & image);
     template <typename T> static bool onborder(const T &v, IntersectT i, const TGAImage & image);
     template <typename T> static IntersectT fingBorder(T& begin, T & end, const TGAImage & image);
     template <typename T> static void cutOffTriangleVerticles(T t0, T t1, T t2, const TGAImage &image, VertStack<T> &vstor);
     template <typename T> static void pushIfInTriangle(const T&t0, const T&t1, const T&t2, const T&v, VertStack<T> &vstor);
     static void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, const Palette& palete);
     static void triangle(Vec3i t0, Vec3i t1, Vec3i t2, TGAImage & image, const Palette& palete, int * zbuffer);
public:
     static void point(const Vec2i &point, TGAImage & image, const TGAColor & color);
     static void point (const Vec3i &point, TGAImage & image, const TGAColor & color, int * zbuffer);
    //{-----------------------------------------------------------------------
    //! @brief draw a line in .tga image
    //! @brief function use a Bresenham's line algorithm
    //!
    //! @param [in]  begin, end Vec2i   object which contain x and y coordinates
    //! @param [out] image              TGAImage object in which line is drawn
    //! @param [in]  color              line color
    //!
    //! @warning function sorts coordinates itself
    //!
    //! @throw NEGATIVE_COORDINATE  coordinate is less than zero
    //! @throw TOO_BIG_COORDINATE   coordinate is bigger than image width or height
    //}-----------------------------------------------------------------------
     static void line(Vec2i begin, Vec2i end, TGAImage & image, const TGAColor & color);
     static void line(Vec3i begin, Vec3i end, TGAImage & image, const TGAColor & color, int * zbuffer);
    static void line (Vec2i begin, Vec2i end, TGAImage & image, const TGAColor & c0, const TGAColor & c1);
     static void line (Vec3i begin, Vec3i end, TGAImage & image, const TGAColor & c0, const TGAColor & c1, int * zbuffer);

    //{-----------------------------------------------------------------------
    //! @brief draw a triangle in .tga  image
    //!
    //! @param [in]  t0, t1, t2     3 dots forming a triangle
    //! @param [out] image          TGAImage object in which line is drawn
    //! @param [in]  color          triangle color
    //! @param [in]  zbuffer        int array with image width * height size
    //!
    //! @warning there aren't "const Vec3i &", because function swapping objects into yourself.
    //!          So, you can see copy constructor here.
    //}-----------------------------------------------------------------------
     static void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, const  TGAColor color);
     static void triangle(Vec3i t0, Vec3i t1, Vec3i t2, TGAImage & image, const TGAColor& color, int * zbuffer);
     static void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, const  TGAColor& c0, const  TGAColor& c1, const  TGAColor& c2);
     static void triangle(Vec3i t0, Vec3i t1, Vec3i t2, TGAImage & image, const  TGAColor& c0, const  TGAColor& c1, const  TGAColor& c2, int * zbuffer);
    //{-----------------------------------------------------------------------
    //! @brief draw a triangle in .tga  image using gouraud shading method
    //!
    //! @param [in]  t0, t1, t2       3 dots forming a triangle
    //! @param [in]  ity0, ity1, ity2 normal vectors
    //! @param [out] image            TGAImage object in which line is drawn
    //! @param [in]  zbuffer          int array with image width * height size
    //!
    //! @warning there aren't "const Vec3i &", because function swapping objects into yourself.
    //!          So, you can see copy constructor here.
    //}-----------------------------------------------------------------------
    static void gouraud_shading_traingle (Vec3i t0, Vec3i t1, Vec3i t2, float ity0, float ity1, float ity2,
                                          TGAImage & image, int * zbuffer);

};



#endif //GLLIB_GLLIB_H
