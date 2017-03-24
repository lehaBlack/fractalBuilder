//epicfail@gmail.com

#include <stdlib.h>
#include <limits>
#include "tgaimage.h"
#include "glLib.h"
#include "Model.h"

const TGAColor white = TGAColor (255, 255, 255, 255);
const TGAColor red   = TGAColor (255, 0,   0,   255);
const TGAColor green = TGAColor (0,   255, 0,   255);
const TGAColor blue  = TGAColor (0,   0,   255, 255);

const int width  = 10000;
const int height = 10000;

Vec3f light_dir (0.0, 0.0, 1.0);

void draw_grid            (const Model & model, TGAImage & image, const TGAColor & color);
void draw_triangles       (const Model &model, TGAImage &image);
void draw_gouraud_shading (const Model &model, TGAImage &image);         // draw_triangles + Gouraud shading
void draw_zbuffer         (const int * zbuffer);
/*
int main ()
{
    Model model;
    try
    {
        model.open ("obj/african_head.obj");
        model.normalize_coordinates (width, height);
    }
    catch (Error err)
    {
        err.print_error ();
        exit (1);
    }

    TGAImage image(width, height, TGAImage::RGB);

//    draw_grid (model, image, white);
//    draw_triangles (model, image);
    draw_gouraud_shading (model, image);

    image.flip_vertically();               // rotate picture
    image.write_tga_file("output.tga");

    return 0;
}*/

void draw_grid (const Model & model , TGAImage & image, const TGAColor & color)
{
    for (size_t i = 0; i < model.nvfaces (); i++)
    {
        Vec3i face;
        try
        {
            face = model.vface (i);
        }
        catch (Error err)
        {
            err.print_error ();
            exit (1);
        }
        for (size_t j = 0; j < 3; j++)
        {
            // get begin and end points
            Vec3f v0, v1;
            try
            {
                v0 = model.vert ((size_t) face[j] - 1);
                v1 = model.vert ((size_t) face[(j + 1) % 3] - 1);
            }
            catch (Error err)
            {
                err.print_error ();
                exit (1);
            }

            // I'm too lazy to write a special function or constructor
            Vec2i begin, end;
            begin.x_ = (int) v0.x_;
            begin.y_ = (int) v0.y_;
            end.x_   = (int) v1.x_;
            end.y_   = (int) v1.y_;

            try
            {
                glLib::line (begin, end, image, color);
            }
            catch (Error err)
            {
                err.print_error ();
                exit (1);
            }
        }
    }
}

void draw_triangles (const Model &model, TGAImage &image)
{
    // width and height are global constants
    if ((size_t) width * height >= (size_t) std::numeric_limits<int>::max ())
        WPRINT (WBIG_SIZE)

    int * zbuffer = new int[width * height];
    if (!zbuffer)
        THROW (ZERO_POINTER);
    for (int i = width * height - 1; i >= 0; i--)
        zbuffer[i] = std::numeric_limits<int>::min ();

    for (size_t i=0; i< model.nvfaces (); i++) {
        Vec3i face = model.vface (i);
        Vec3i screen_coords[3];
        Vec3f world_coords[3];
        for (size_t j = 0; j < 3; j++)
        {
            world_coords[j] = model.vert ((size_t) face[j] - 1);
            // this is correct, because I normalized coordinates in main ()
            screen_coords[j] = Vec3i ((int) world_coords[j].x_, (int) world_coords[j].y_, (int) world_coords[j].z_);
        }

        // get a normal to triangle
        Vec3f triangle_norm = vector_product (world_coords[1] - world_coords[0], world_coords[2] - world_coords[0]);
        triangle_norm = normalize (triangle_norm);

        float intensity = scalar_product (triangle_norm, light_dir);
        if (intensity > 0)
            glLib::triangle (screen_coords[0], screen_coords[1], screen_coords[2], image,
                             TGAColor (255, 255, 255) * intensity, zbuffer);
    }

    // only for debug
    draw_zbuffer (zbuffer);

    delete[] zbuffer;
}

void draw_gouraud_shading (const Model &model, TGAImage &image)
{
    // width and height are global constants
    if ((float) width * height >= (float) std::numeric_limits<int>::max ())
        WPRINT (WBIG_SIZE);

    int * zbuffer = new int[width * height];
    if (!zbuffer)
        THROW (ZERO_POINTER);
    for (int i = width * height - 1; i >= 0; i--)
        zbuffer[i] = std::numeric_limits<int>::min ();

    for (size_t i=0; i< model.nvfaces (); i++) {
        Vec3i face = model.vface (i);
        Vec3i screen_coords[3];
        Vec3f world_coords[3];
        float intensity[3];
        for (size_t j = 0; j <3; j++)
        {
            world_coords[j] = model.vert ((size_t) face[j] - 1);
            // this is correct, because I normalized coordinates in main ()
            screen_coords[j] = Vec3i ((int) world_coords[j].x_, (int) world_coords[j].y_, (int) world_coords[j].z_);
            intensity[j] = model.norm (i, j) * light_dir;
        }

        glLib::gouraud_shading_traingle (screen_coords[0], screen_coords[1], screen_coords[2], intensity[0],
                                         intensity[1], intensity[2], image, zbuffer);
    }

    draw_zbuffer (zbuffer);

    delete[] zbuffer;
}

void draw_zbuffer (const int * zbuffer)
{
    // look for min and max z coorditanes in zbuffer
    int min = std::numeric_limits<int>::max ();
    int max = std::numeric_limits<int>::min ();
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (min > zbuffer[i + j * width] && zbuffer[i + j * width] != std::numeric_limits<int>::min ())
                min = zbuffer[i + j * width];
            if (max < zbuffer[i + j * width])
                max = zbuffer[i + j * width];
        }
    }

    // draw zbuffer
    TGAImage zbimage (width, height, TGAImage::GRAYSCALE);
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            // extra smart formula, because grayscale has only 256 colours, but z coordinates can be more
            zbimage.set (i, j, TGAColor ((zbuffer[i + j * width] + std::abs (min)) * 256 / (max + std::abs (min)) - 50));
    zbimage.flip_vertically (); // i want to have the origin at the left bottom corner of the image
    zbimage.write_tga_file ("zbuffer.tga");
}

