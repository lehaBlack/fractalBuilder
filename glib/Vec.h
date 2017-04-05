//
// Created by epicfail on 03.03.16.
//

#ifndef GLLIB_VEC_H
#define GLLIB_VEC_H

#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include "Errors.h"


//! @brief class works with 3 numbers
template <typename t> class Vec3
{
public:
    //{---------------------------------------------------------------
    //! @brief light constructor
    //}---------------------------------------------------------------
    Vec3<t>   (): x_ (0), y_ (0), z_ (0) {}

    //{---------------------------------------------------------------
    //! @brief set coordinates
    //!
    //! @param x, y, z coordinates
    //}---------------------------------------------------------------
    Vec3<t>   (t x, t y=0, t z=0)
    {
        x_ = x;
        y_ = y;
        z_ = z;
    }

    //{---------------------------------------------------------------
    //! @brief set 3 numbers
    //!
    //! @param numbers[3] array with 3 numbers
    //}---------------------------------------------------------------
    Vec3<t>   (t numbers[3])
    {
        x_ = numbers[0];
        y_ = numbers[1];
        z_ = numbers[2];
    }

    //{---------------------------------------------------------------
    //! @brief destructor fills all the poison
    //}---------------------------------------------------------------
    ~Vec3<t>  ()
    {
        x_ = 0xBADF00D;
        y_ = 0xBADF00D;
        z_ = 0xBADF00D;
    }

    //{---------------------------------------------------------------
    //! @brief copy from one Vec3 to another
    //!
    //! @param that sample for copy
    //}---------------------------------------------------------------
    Vec3<t> (const Vec3<t> & that)
    {
        x_ = that.x_;
        y_ = that.y_;
        z_ = that.z_;
    }

    //{---------------------------------------------------------------
    //! @brief you can work with class like as array with 3 elements
    //!
    //! @param i element index
    //!
    //! @warning remember, that there are only three elements in array!
    //!
    //! @throw INDEX_OUT_OF_BOUNDS array index out of bounds
    //!
    //! @return int number that lies on the index
    //}---------------------------------------------------------------
    t & operator [] (size_t i)
    {
        if (i == 0)
            return x_;
        if (i == 1)
            return y_;
        if (i == 2)
            return z_;
        else
            THROW (INDEX_OUT_OF_BOUNDS);
    }

    //{---------------------------------------------------------------
    //! @brief access to the array elements
    //!
    //! @param i element index
    //!
    //! @warning remember, that there are only three elements in array!
    //!
    //! @throw INDEX_OUT_OF_BOUNDS array index out of bounds
    //!
    //! @return int number that lies on the index
    //}---------------------------------------------------------------
    const t & at (size_t i)
    {
        if (i == 0)
            return x_;
        if (i == 1)
            return y_;
        if (i == 2)
            return z_;
        else
            THROW (INDEX_OUT_OF_BOUNDS);
    }

    //{---------------------------------------------------------------
    //! @brief copy from one Vec3 to another
    //!
    //! @param that sample for copy
    //!
    //! @return copy
    //}---------------------------------------------------------------
    const Vec3<t> & operator = (const Vec3<t> & that)
    {
        x_ = that.x_;
        y_ = that.y_;
        z_ = that.z_;

        return *this;
    }

    //{---------------------------------------------------------------
    //! @brief divide Vec3<t> on the number
    //!
    //! @param denominator float number
    //!
    //! @throw ZERO_SIZE denominator = 0
    //}---------------------------------------------------------------
    void operator /= (float denominator)
    {
        if (denominator == 0.0)
            THROW (ZERO_SIZE);

        *this = Vec3<t> (x_ / denominator, y_ / denominator, z_ / denominator);
    }

    //{---------------------------------------------------------------
    //! @brief simple operator += that works like standard +=
    //!
    //! @param that Vec3<t> which we add to this
    //}---------------------------------------------------------------
    void operator += (const Vec3<t> & that)
    {
        x_ += that.x_;
        y_ += that.y_;
        z_ -= that.z_;
    }

    //{---------------------------------------------------------------
    //! @brief simple operator -= that works like standard -=
    //!
    //! @param that Vec3<t> which we subtraction from this
    //}---------------------------------------------------------------
    void operator -= (const Vec3<t> & that)
    {
        x_ -= that.x_;
        y_ -= that.y_;
        z_ -= that.z_;
    }

    //{---------------------------------------------------------------
    //! @brief each coordinate is multiplied by the number and the result is stored in the caller
    //!
    //! @param num  number, which is multiplied by the Vec3<t>
    //}---------------------------------------------------------------
    void operator *= (float num)
    {
        x_ *= num;
        y_ *= num;
        z_ *= num;
    }

    //{---------------------------------------------------------------
    //! @brief x1*x2 + y1*y2 + z1*z2
    //!
    //! @return multiplication result
    //}---------------------------------------------------------------
    float operator* (const Vec3<t> &that)
    {
        return x_*that.x_ + y_*that.y_ + z_*that.z_;
    }

    t x_;   //!<First element of array (You can use x_ if you works with coordinates).
            //!<Otherwise don't use it. Work with elements such as array.
    t y_;   //!<Second element of array (You can use y_ if you works with coordinates).
            //!<Otherwise don't use it. Work with elements such as array.
    t z_;   //!<Third element of array (You can use Z_ if you works with coordinates).
            //!<Otherwise don't use it. Work with elements such as array.
};

//{---------------------------------------------------------------
//! @brief normalize Vec3<t>
//!
//! @param vec Vec3<t> that function normalized
//!
//! @return copy of the normalized Vec3<t>
//}---------------------------------------------------------------
template <typename t> Vec3<t>  normalize (const Vec3<t> & vec)
{
    Vec3<t> new_vec = vec;
    float norm = (float) sqrt (vec.x_ * vec.x_ + vec.y_ * vec.y_ + vec.z_ * vec.z_);

    if (norm == 0.0)
        new_vec = Vec3<t> ((t) 0.0, (t) 0.0, (t) 0.0);
    else
        new_vec /= norm;

    return new_vec;
}

//{---------------------------------------------------------------
//! @brief vector product of the two vectors
//!
//! @param [in] v1, [in] v2 vectors
//!
//! @return copy of vector that is a result of vector product
//}---------------------------------------------------------------
template <typename t> Vec3<t> vector_product (const Vec3<t> & v1, const Vec3<t> & v2)
{
    return Vec3<t> (v1.y_ * v2.z_ - v1.z_ * v2.y_
                  , v1.z_ * v2.x_ - v1.x_ * v2.z_
                  , v1.x_ * v2.y_ - v1.y_ * v2.x_);
}

//{---------------------------------------------------------------
//! @brief scalar product of the two vectors
//!
//! @param [in] v1, [in] v2 vectors
//!
//! @return number that is result of scalar product
//}---------------------------------------------------------------
template <typename t> t scalar_product (const Vec3<t> & v1, const Vec3<t> v2)
{
    return v1.x_ * v2.x_ + v1.y_ * v2.y_ + v1.z_ * v2.z_;
}

//{---------------------------------------------------------------
//! @brief add two vectors
//!
//! @param [in] v1, [in] v2 vectors
//!
//! @return copy of the result addition
//}---------------------------------------------------------------
template <typename t> Vec3<t> operator + (const Vec3<t> & v1, const Vec3<t> & v2)
{
    Vec3<t> new_vec = v1;
    new_vec += v2;

    return new_vec;
}

//{---------------------------------------------------------------
//! @brief calculates the difference of two vectors
//!
//! @param [in] v1, [in] v2 vectors.  Function calculates v1 - v2!
//!
//! @return copy of the result subtraction
//}---------------------------------------------------------------
template <typename t> Vec3<t> operator - (const Vec3<t> & v1, const Vec3<t> & v2)
{
    Vec3<t> new_vec = v1;
    new_vec -= v2;

    return new_vec;
}

//{---------------------------------------------------------------
//! @brief calculates the multiplication of Vec3<t> and num
//!
//! @param [in] vec object Vec3<t>
//! @param [in] num number, which is multiplied by the Vec3<t>
//!
//! @return copy of the result multiplication
//}---------------------------------------------------------------
template <typename t> Vec3<t> operator * (const Vec3<t> & vec, float num)
{
    Vec3<t> res_vec = vec;
    res_vec *= num;
    return res_vec;
}

typedef Vec3<float> Vec3f;
typedef Vec3<int>   Vec3i;






//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

//! @brief class works with 2 numbers
template <class t> class Vec2
{
public:
    //{---------------------------------------------------------------
    //! @brief light constructor
    //}---------------------------------------------------------------
    Vec2<t>   (): x_ (0), y_ (0) {}

    //{---------------------------------------------------------------
    //! @brief set coordinates
    //!
    //! @param x, y coordinates
    //}---------------------------------------------------------------
    Vec2<t>   (t x, t y)
    {
        x_ = x;
        y_ = y;
    }

    //{---------------------------------------------------------------
    //! @brief set 2 numbers
    //!
    //! @param numbers[2] array with 2 numbers
    //}---------------------------------------------------------------
    Vec2<t>   (t numbers[2])
    {
        x_ = numbers[0];
        y_ = numbers[1];
    }

    //{---------------------------------------------------------------
    //! @brief destructor fills all the poison
    //}---------------------------------------------------------------
    ~Vec2<t>  ()
    {
        x_ = 0xBADF00D;
        y_ = 0xBADF00D;
    }

    //{---------------------------------------------------------------
    //! @brief copy from one Vec2 to another
    //!
    //! @param that sample for copy
    //}---------------------------------------------------------------
    Vec2<t> (const Vec2<t> & that)
    {
        x_ = that.x_;
        y_ = that.y_;
    }

    //{---------------------------------------------------------------
    //! @brief you can work with class like as array with 2 elements
    //!
    //! @param i element index
    //!
    //! @warning remember, that there are only 2 elements in array!
    //!
    //! @throw INDEX_OUT_OF_BOUNDS array index out of bounds
    //!
    //! @return int number that lies on the index
    //}---------------------------------------------------------------
    const t & operator [] (size_t i)
    {
        if (i == 0)
            return x_;
        if (i == 1)
            return y_;
        else
            THROW (INDEX_OUT_OF_BOUNDS);
    }

    //{---------------------------------------------------------------
    //! @brief simple operator += that works like standard +=
    //!
    //! @param that Vec3<t> which we add to this
    //}---------------------------------------------------------------
    void operator += (const Vec2<t> & that)
    {
        x_ += that.x_;
        y_ += that.y_;
    }

    //{---------------------------------------------------------------
    //! @brief simple operator -= that works like standard -=
    //!
    //! @param that Vec3<t> which we subtraction from this
    //}---------------------------------------------------------------
    void operator -= (const Vec2<t> & that)
    {
        x_ -= that.x_;
        y_ -= that.y_;
    }

    //{---------------------------------------------------------------
    //! @brief access to the array elements
    //!
    //! @param i element index
    //!
    //! @warning remember, that there are only 2 elements in array!
    //!
    //! @throw INDEX_OUT_OF_BOUNDS array index out of bounds
    //!
    //! @return int number that lies on the index
    //}---------------------------------------------------------------
    const t & at (size_t i)
    {
        if (i == 0)
            return x_;
        if (i == 1)
            return y_;
        else
            THROW (INDEX_OUT_OF_BOUNDS);
    }

    //{---------------------------------------------------------------
    //! @brief copy from one Vec2 to another
    //!
    //! @param that sample for copy
    //!
    //! @return copy
    //}---------------------------------------------------------------
    const Vec2<t> & operator = (const Vec2<t> & that)
    {
        x_ = that.x_;
        y_ = that.y_;

        return *this;
    }
     //{---------------------------------------------------------------
     //! @brief each coordinate is multiplied by the number and the result is stored in the caller
     //!
     //! @param num  number, which is multiplied by the Vec3<t>
     //}---------------------------------------------------------------
     void operator *= (float num)
     {
          x_ *= num;
          y_ *= num;
     }

    t x_;   //!<First element of array (You can use x_ if you works with coordinates).
            //!<Otherwise don't use it. Work with elements such as array.
    t y_;   //!<Second element of array (You can use y_ if you works with coordinates).
            //!<Otherwise don't use it. Work with elements such as array.
};

//{---------------------------------------------------------------
//! @brief add two vectors
//!
//! @param [in] v1, [in] v2 vectors
//!
//! @return copy of the result addition
//}---------------------------------------------------------------
template <typename t> Vec2<t> operator + (const Vec2<t> & v1, const Vec2<t> & v2)
{
    Vec2<t> new_vec = v1;
    new_vec += v2;

    return new_vec;
}

//{---------------------------------------------------------------
//! @brief calculates the difference of two vectors
//!
//! @param [in] v1, [in] v2 vectors.  Function calculates v1 - v2!
//!
//! @return copy of the result subtraction
//}---------------------------------------------------------------
template <typename t> Vec2<t> operator - (const Vec2<t> & v1, const Vec2<t> & v2)
{
    Vec2<t> new_vec = v1;
    new_vec -= v2;

    return new_vec;
}

//{---------------------------------------------------------------
//! @brief calculates the multiplication of Vec3<t> and num
//!
//! @param [in] vec object Vec3<t>
//! @param [in] num number, which is multiplied by the Vec3<t>
//!
//! @return copy of the result multiplication
//}---------------------------------------------------------------
template <typename t> Vec2<t> operator * (const Vec2<t> & vec, float num)
{
     Vec2<t> res_vec = vec;
     res_vec *= num;
     return res_vec;
}
//{---------------------------------------------------------------
//! @brief calculates the multiplication of Vec3<t> and num
//!
//! @param [in] vec object Vec3<t>
//! @param [in] num number, which is multiplied by the Vec3<t>
//!
//! @return copy of the result multiplication
//}---------------------------------------------------------------
template <typename t> 
bool operator == (const Vec2<t> & v0, const Vec2<t> & v1)
{
     return v0.x_==v1.x_ && v0.y_==v1.y_;
}
template <typename t>
bool operator != (const Vec2<t> & v0, const Vec2<t> & v1)
{
     return !(v0==v1);
}
template <typename t>
bool operator == (const Vec3<t> & v0, const Vec3<t> & v1)
{
     return v0.x_ == v1.x_ && v0.y_ == v1.y_ && v0.z_ == v1.z_;
}
template <typename t>
bool operator != (const Vec3<t> & v0, const Vec3<t> & v1)
{
     return !(v0 == v1);
}
typedef Vec2<float> Vec2f;
typedef Vec2<int>   Vec2i;

#endif //GLLIB_VEC_H
