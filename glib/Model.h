//
// Created by epicfail on 03.03.16.
//

//! @brief Work with .obj files (open, read, contains the necessary data).
#ifndef GLLIB_MODEL_H
#define GLLIB_MODEL_H

#include <vector>
#include "Vec.h"
#include "Errors.h"


class Model
{
public:
    Model ();

    ~Model ();

    //{-------------------------------------------------------
    //! @brief open .obj file and save faces ans verts into arrays
    //!
    //! @param filename name of the .obj file
    //!
    //! @throw NULL_FILENAME            param filename is NULL
    //! @throw NULL_FILE                file pointer is NULL
    //! @throw NO_MEMORY_FOR_ALL_FILE   can't malloc memory for file
    //! @throw NO_ALL_FILE_WAS_READ     file size != fread size
    //! @throw NO_MODEL_IN_FILE         strtok can't find "\n"
    //! @throw NO_VERTS_IN_FILE         file doesn't contain verts
    //! @throw NO_FACES_IN_FILE         file doesn't contain faces
    //}-------------------------------------------------------
    void open (const char *filename);

    //{-------------------------------------------------------
    //! @return number of faces with contained in this model
    //}-------------------------------------------------------
    size_t nvfaces () const;

    //{-------------------------------------------------------
    //! @return number of verts with contained in this model
    //}-------------------------------------------------------
    size_t nverts () const;

    //{-------------------------------------------------------
    //! @param i vert index
    //!
    //! @throw TOO_HIGH_VERT_INDEX  index is more than number of verts in array
    //!
    //! @return vert with index i
    //}-------------------------------------------------------
    const Vec3f &vert (size_t i) const;

    //{-------------------------------------------------------
    //! @param i vface index
    //!
    //! @throw TOO_HIGH_FACE_INDEX  index is more than number of faces in array
    //!
    //! @return vface with index i
    //}-------------------------------------------------------
    const Vec3i &vface (size_t i) const;

    //{-------------------------------------------------------
    //! @param iface index in f
    //! @param nvert vert index in f
    //!
    //! return normalized vn vector
    //}-------------------------------------------------------
    Vec3f norm (size_t iface, size_t nvert) const;

    //{-------------------------------------------------------
    //! @brief change the coordinates to the image has been in full screen
    //!
    //! @param width    Image width
    //! @param height   Image height
    //!
    //! @throw ZERO_SIZE    width or height is 0
    //!
    //! @warning it can greatly slow down program
    //}-------------------------------------------------------
    void    normalize_coordinates (size_t width, size_t height);
private:
    //{-------------------------------------------------------
    //! @brief copy constructor is disabled
    //!
    //! @warning if you use it, function causes assert with message and aborts all program :)
    //}-------------------------------------------------------
    Model   (const Model &);

    //{-------------------------------------------------------
    //! @brief operator = is disabled
    //!
    //! @warning if you use it, function causes assert with message and aborts all program :)
    //}-------------------------------------------------------
    void    operator = (const Model & that);

    std::vector <Vec3f> verts_;     //!<array of verts
    std::vector <Vec3i> vfaces_;    //!<array of faces
    std::vector <Vec3f> norm_v_;    //!<array of norm verts
    std::vector <Vec3i> norm_f_;    //!<array of norm faces
};


#endif //GLLIB_MODEL_H
