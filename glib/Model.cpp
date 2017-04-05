//
// Created by epicfail on 03.03.16.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <assert.h>
#include <cctype>
#include <algorithm>
#include "Model.h"


Model::Model ():
        verts_ (0),
        vfaces_ (0)
{}


Model::Model (const Model & that)
{
     printf ("Ooooooh, nooooo! You use copy constructor Model::Model (const Model &)\n");
    assert (false);
}

void Model::operator = (const Model & that)
{
    printf ("Ooooooh, nooooo! You use Model::operator = (const Model & that)\n");
    assert (false);
}

Model::~Model ()
{}

void Model::open (const char * filename)
{
    if (!filename)
        THROW (NULL_FILENAME);

    FILE * file = fopen (filename, "rb");
    if (!file)
        THROW (NULL_FILE);

    fseek (file, 0, SEEK_END);
    size_t fsize = (size_t) ftell (file);
    fseek (file, 0, SEEK_SET);

    char * obj = (char *) malloc (fsize * sizeof (char));
    if (!obj)
        THROW (NO_MEMORY_FOR_ALL_FILE);

    size_t fread_size = fread (obj, sizeof (char), fsize, file);
    if (fsize != fread_size)
        THROW (NO_ALL_FILE_WAS_READ);

    char * pobj = strtok (obj, "\n");
    if (!pobj)
        THROW (NO_MODEL_IN_FILE);

    // parcer
    while (pobj)
    {
        char str_to_cmp[3] = {*pobj, *(pobj + 1), '\0'};

        if (strcmp (str_to_cmp, "v ") == 0)
        {
            Vec3f vec;
            char trash = 0;
            sscanf (pobj, "%c%f%f%f", &trash, &vec.x_, &vec.y_, &vec.z_);
            verts_.push_back (vec);
        }
        else if (strcmp (str_to_cmp, "vn") == 0)
        {
            pobj++;
            Vec3f vec;
            char trash = 0;
            sscanf (pobj, "%c%f%f%f", &trash, &vec.x_, &vec.y_, &vec.z_);
            norm_v_.push_back (vec);
        }
        else if (strcmp (str_to_cmp, "f ") == 0)
        {
            Vec3i v;
            Vec3i vt;
            Vec3i vn;

            for (size_t i = 0; i < 3; i++)
            {
                // there are really awful code
                while (!isdigit (*pobj))
                    pobj++;
                sscanf (pobj, "%d", &v[i]);
                while (*pobj != '/')
                    pobj++;
                pobj++;
                if (*pobj != '/')
                    sscanf (pobj, "%d", &vt[i]);
                while (*pobj != '/')
                    pobj++;
                sscanf (pobj, "/%d", &vn[i]);
                while (!isspace (*pobj))
                    pobj++;
            }

            vfaces_.push_back (v);
            norm_f_.push_back (vn);
        }

        pobj = strtok (NULL, "\n");
    }

    if (nverts () == 0)
        THROW (NO_VERTS_IN_FILE);
    if (nvfaces () == 0)
        THROW (NO_FACES_IN_FILE);
}

size_t Model::nvfaces () const
{
    return vfaces_.size ();
}

size_t Model::nverts () const
{
    return verts_.size ();
}

const Vec3f & Model::vert (size_t i) const
{
    if (i >= verts_.size ())
        THROW (TOO_HIGH_VERT_INDEX);
    return verts_[i];
}

const Vec3i & Model::vface (size_t i) const
{
    if (i >= vfaces_.size ())
        THROW (TOO_HIGH_FACE_INDEX);
    return vfaces_[i];
}

Vec3f Model::norm (size_t iface, size_t nvert) const
{
    if (iface >= norm_f_.size ())
        THROW (TOO_HIGH_FACE_INDEX);
    Vec3i vec = norm_f_.at (iface);
    int idx = vec.at (nvert) - 1;
    Vec3f vn = norm_v_[idx];
    return normalize (vn);
}

void Model::normalize_coordinates (size_t width, size_t height)
{
    if (!width || !height)
        THROW (ZERO_SIZE);

    float x_min = 0.0;      //left
    float x_max = 0.0;      //right
    float y_min = 0.0;      //bottom
    float y_max = 0.0;      //top

    // look for extreme coordinates
    for (size_t i = 0; i < nverts (); i++)
    {
        Vec3f v = vert (i);

        x_min = x_min < v.x_ ? x_min : v.x_;
        y_min = y_min < v.y_ ? y_min : v.y_;
        x_max = x_max > v.x_ ? x_max : v.x_;
        y_max = y_max > v.y_ ? y_max : v.y_;
    }

    float ratio_x = (float) std::min (std::abs (1.0 * width / x_min), std::abs (1.0 * width / x_max));
    float ratio_y = (float) std::min (std::abs (1.0 * height / y_min), std::abs (1.0 * height / y_max));
    float best_ratio = std::min (ratio_x, ratio_y);

    // normalized
    for (size_t i = 0; i < nverts (); i++)
    {
        verts_[i].x_ = (verts_[i].x_ * best_ratio + width) / 2;
        verts_[i].y_ = (verts_[i].y_ * best_ratio + height) / 2;
        verts_[i].z_ = (verts_[i].z_ * best_ratio + width) / 2;
    }
}
