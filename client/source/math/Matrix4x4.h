#ifndef MATRIX4X4_H_
#define MATRIX4X4_H_

#include <stdexcept>
#include <cmath>

//#include "math/Quaternion.h"

#include "Types.h"
#include "Constants.h"

//DEBUG
#include <iostream>
#include <memory>

namespace revel 
{ 
namespace math
{

template <typename T> class Vector4;
template <typename T> class Matrix3x3;
template <typename T> class Quaternion;

template <typename T>
class Matrix4x4
{
public:
    /**
     * Default constructor
     */
    Matrix4x4();
    /**
     * Constructor, takes 16 elements in row-order.
     *
     * @param[in] m00 Element (0, 0) in the matrix.
     * @param[in] m01 Element (0, 1) in the matrix.
     * @param[in] m02 Element (0, 2) in the matrix.
     * @param[in] m03 Element (0, 3) in the matrix.
     * @param[in] m10 Element (1, 0) in the matrix.
     * @param[in] m11 Element (1, 1) in the matrix.
     * @param[in] m12 Element (1, 2) in the matrix.
     * @param[in] m13 Element (1, 3) in the matrix.
     * @param[in] m20 Element (2, 0) in the matrix.
     * @param[in] m21 Element (2, 1) in the matrix.
     * @param[in] m22 Element (2, 2) in the matrix.
     * @param[in] m23 Element (2, 3) in the matrix.
     * @param[in] m30 Element (3, 0) in the matrix.
     * @param[in] m31 Element (3, 1) in the matrix.
     * @param[in] m32 Element (3, 2) in the matrix.
     * @param[in] m33 Element (3, 3) in the matrix.
     */
    Matrix4x4(T m00, T m01, T m02, T m03,
              T m10, T m11, T m12, T m13,
              T m20, T m21, T m22, T m23,
              T m30, T m31, T m32, T m33);
    /**
     * Constructor. Takes one value and initializes all
     * matrix element to the given value.
     *
     * @param[in] x Value for all elements.
     */
    Matrix4x4(T x);

    /**
     * Constructor. Takes a pointer and reads the 16 values
     * to initialize the matrix with. The second parameter controls
     * if the values are in row or column order.
     *
     * @param[in] x Pointer to the elements.
     * @param row_order Set the order of the elements. Defaults to row order.
     */
    Matrix4x4(T* x, bool row_order = true);

    /**
     * Constructor. Takes four vectors and initializes the matrix to
     * the given values. The second parameters controls if the vectors are
     * row or column vectors. The default is to use row order.
     *
     * @param[in] v1 First vector.
     * @param[in] v2 Second vector.
     * @param[in] v3 Third vector.
     * @param[in] v4 Fourth vector.
     * @param[in] row_order Specify which type of vectors are used.
     */
    Matrix4x4(const Vector4<T>& v1, const Vector4<T>& v2,
              const Vector4<T>& v3, const Vector4<T>& v4,
              bool row_order = true);
    /**
     * Copy constructor. Creates an identical copy of the input matrix.
     *
     * @todo Implement 3x3 matrix.
     */
    Matrix4x4(const Matrix4x4& m);

    Matrix4x4(Matrix4x4&& m)
    {
        for (int i = 0; i < 16; ++i)
        {
            e[i] = m.e[i];
        }
    }

    /**
     * Constructor which takes a 3x3 matrix and initializes the
     * upper-left part of the matrix to the same values as the input matrix.
     * The last element (3, 3) is set to 1.
     */
    Matrix4x4(const Matrix3x3<T>& m);

    /**
     * Constructor which creates a (rotation) matrix from a unit quaternion.
     */
    //Matrix4x4(const Quaternion<T>& q)

    /**
     * Default destructor.
     */
    ~Matrix4x4();

    /**
     * Get element from Matrix
     *
     * @param row Row number
     * @param col Col number
     * @return Reference to element
     */
    T& operator()(u32 row, u32 col);

    /**
     * Get element from Matrix
     *
     * @param elem Element in array
     * @return Reference to element
     */
    T& operator[](u32 elem);

    /**
     * Get element from Matrix
     *
     * @param row Row number
     * @param col Col number
     * @return Reference to element
     */
    const T& operator()(u32 row, u32 col) const;
    
    /**
     * Get element from Matrix
     *
     * @param elem Element in array
     * @return Reference to element
     */
    const T& operator[](u32 elem) const;
    
    /**
     * Get a pointer to the first element.
     *
     * @return The pointer.
     */  
    const T* get_ptr() const { return e; }

    /**
     * Extract a row vector from the matrix
     *
     * @param x Row number.
     * @return Vector row.
     */  
    Vector4<T> row(u32 x) const;
    
    /**
     * Extract a column vector from the matrix
     *
     * @param x Row number.
     * @return Vector column.
     */  
    Vector4<T> col(u32 x) const;

    /**
     * Matrix addition
     *
     * @param m Input matrix
     * @return Result matrix
     */
    Matrix4x4 operator+(const Matrix4x4& m) const;

    /**
     * Matrix subtraction
     *
     * @param m Input matrix
     * @return Result matrix
     */
    Matrix4x4 operator-(const Matrix4x4& m) const;

    /**
     * Matrix multiplication
     *
     * @param a Input scalar
     * @return Result matrix
     */
    Matrix4x4 operator*(const T& a) const;

    /**
     * Matrix multiplication
     *
     * @param a Input scalar
     * @return Result matrix
     */
    Matrix4x4 operator*(const Matrix4x4& m) const;

    /**
     * Matrix multiplication
     *
     * @param v Input column vector
     * @return Result vector
     */
    Vector4<T> operator*(const Vector4<T>& v) const;

    /**
     * Assignment of all variables in the matrix
     *
     * @param m Source matrix
     * @return Reference to itself
     */
    Matrix4x4& operator=(const Matrix4x4& m);

    /**
     * Test for equality
     */
    bool operator==(const Matrix4x4& m) const;

    bool operator!=(const Matrix4x4& m) const;

    /**
     * Matrix addition
     *
     * @param m Input matrix
     * @return Reference to itself
     */
    Matrix4x4& operator+=(const Matrix4x4& m);

    /**
     * Matrix subtraction
     *
     * @param m Input matrix
     * @return Reference to itself
     */
    Matrix4x4& operator-=(const Matrix4x4& m);

    /**
     * Matrix multiplication
     *
     * @param m Input matrix
     * @return Reference to itself
     */
    Matrix4x4& operator*=(const Matrix4x4& m);

    /**
     * Matrix multiplication
     *
     * @param a Scalar
     * @return Reference to itself
     */
    Matrix4x4& operator*=(T a);

    /**
     * Calculate the trace of a matrix
     *
     * @return Trace
     */
    T trace() const;

    /**
     * Transpose a matrix
     *
     * @return Matrix transpose
     */
    Matrix4x4 transposed() const;

    /**
     * Calculate the determinant of a matrix
     *
     * @return Trace
     */
    T determinant() const;

    /**
     * Inverse of a matrix
     *
     * @return Matrix inverse
     */
    Matrix4x4 inversed(T epsilon = math::EPSILON) const;

    //protected:
    union
    {
        T e[16];
        struct
        {
            T e00, e01, e02, e03,
              e10, e11, e12, e13,
              e20, e21, e22, e23,
              e30, e31, e32, e33;
        };
    };

    friend std::ostream& operator<<(std::ostream &os, const Matrix4x4& m)
    {
        os << m.e[ 0] << "\t " << m.e[ 1] << "\t " << m.e[ 2] << "\t " << m.e[ 3] << "\n";
        os << m.e[ 4] << "\t " << m.e[ 5] << "\t " << m.e[ 6] << "\t " << m.e[ 7] << "\n";
        os << m.e[ 8] << "\t " << m.e[ 9] << "\t " << m.e[10] << "\t " << m.e[11] << "\n";
        os << m.e[12] << "\t " << m.e[13] << "\t " << m.e[14] << "\t " << m.e[15] << "\n";

        return os;
    }

    static const Matrix4x4 Zero;
    static const Matrix4x4 Identity;
};

template <typename T> inline
Matrix4x4<T>::Matrix4x4()
{

}

template <typename T> inline
Matrix4x4<T>::Matrix4x4(T m00, T m01, T m02, T m03,
			T m10, T m11, T m12, T m13,
			T m20, T m21, T m22, T m23,
			T m30, T m31, T m32, T m33)
{
    e[ 0] = m00; e[ 1] = m01; e[ 2] = m02; e[ 3] = m03;
    e[ 4] = m10; e[ 5] = m11; e[ 6] = m12; e[ 7] = m13;
    e[ 8] = m20; e[ 9] = m21; e[10] = m22; e[11] = m23;
    e[12] = m30; e[13] = m31; e[14] = m32; e[15] = m33;
}

template <typename T> inline
Matrix4x4<T>::Matrix4x4(T x)
{
    e[ 0] = x; e[ 1] = x; e[ 2] = x; e[ 3] = x;
    e[ 4] = x; e[ 5] = x; e[ 6] = x; e[ 7] = x;
    e[ 8] = x; e[ 9] = x; e[10] = x; e[11] = x;
    e[12] = x; e[13] = x; e[14] = x; e[15] = x;
}

template <typename T> inline
Matrix4x4<T>::Matrix4x4(const Vector4<T>& v0, 
			const Vector4<T>& v1,
			const Vector4<T>& v2, 
			const Vector4<T>& v3,
			bool row_order)
{
    if (row_order)
    {
        e00 = v0.x; e01 = v0.y; e02 = v0.z; e03 = v0.w;
        e10 = v1.x; e11 = v1.y; e12 = v1.z; e13 = v1.w;
        e20 = v2.x; e21 = v2.y; e22 = v2.z; e23 = v2.w;
        e30 = v3.x; e31 = v3.y; e32 = v3.z; e33 = v3.w;
    }
    else
    {
        e00 = v0.x; e01 = v1.x; e02 = v2.x; e03 = v3.x;
        e10 = v0.y; e11 = v1.y; e12 = v2.y; e13 = v3.y;
        e20 = v0.z; e21 = v1.z; e22 = v2.z; e23 = v3.z;
        e30 = v0.w; e31 = v1.w; e32 = v2.w; e33 = v3.w;
    }
}

template <typename T> inline
Matrix4x4<T>::Matrix4x4(T* x, bool row_order)
{
    if (row_order)
    {
        e[ 0] = x[ 0]; e[ 1] = x[ 1];
        e[ 2] = x[ 2]; e[ 3] = x[ 3];
        e[ 4] = x[ 4]; e[ 5] = x[ 5];
        e[ 6] = x[ 6]; e[ 7] = x[ 7];
        e[ 8] = x[ 8]; e[ 9] = x[ 9];
        e[10] = x[10]; e[11] = x[11];
        e[12] = x[12]; e[13] = x[13];
        e[14] = x[14]; e[15] = x[15];
    }
    else
    {
        e[ 0] = x[ 0]; e[ 1] = x[ 4];
        e[ 2] = x[ 8]; e[ 3] = x[12];
        e[ 4] = x[ 1]; e[ 5] = x[ 5];
        e[ 6] = x[ 9]; e[ 7] = x[13];
        e[ 8] = x[ 2]; e[ 9] = x[ 6];
        e[10] = x[10]; e[11] = x[14];
        e[12] = x[ 3]; e[13] = x[ 7];
        e[14] = x[11]; e[15] = x[15];
    }
}

template <typename T> inline
Matrix4x4<T>::Matrix4x4(const Matrix4x4& m)
{
    e00 = m.e00; e01 = m.e01; e02 = m.e02; e03 = m.e03;
    e10 = m.e10; e11 = m.e11; e12 = m.e12; e13 = m.e13;
    e20 = m.e20; e21 = m.e21; e22 = m.e22; e23 = m.e23;
    e30 = m.e30; e31 = m.e31; e32 = m.e32; e33 = m.e33;
}


template <typename T> inline
Matrix4x4<T>::Matrix4x4(const Matrix3x3<T>& m)
{
    e00 = m.e00; e01 = m.e01; e02 = m.e02; e03 = 0;
    e10 = m.e10; e11 = m.e11; e12 = m.e12; e13 = 0;
    e20 = m.e20; e21 = m.e21; e22 = m.e22; e23 = 0;
    e30 = 0;	 e31 = 0;	  e32 = 0;	   e33 = 1;
}

template <typename T> inline
Matrix4x4<T>::~Matrix4x4()
{

}

template <typename T> inline
T&
Matrix4x4<T>::operator()(u32 row, u32 col)
{
    if (row > 3 || col > 3)
        throw std::out_of_range("Trying to access outside matrix");

    return e[row * 4 + col];
}


template <typename T> inline
const T&
Matrix4x4<T>::operator()(u32 row, u32 col) const
{
    if (row > 3 || col > 3)
        throw std::out_of_range("Trying to access outside matrix");

    return e[row * 4 + col];
}

template <typename T> inline
T&
Matrix4x4<T>::operator[](u32 index)
{
    return e[index];
}


template <typename T> inline
const T&
Matrix4x4<T>::operator[](u32 index) const
{
    return e[index];
}


template <typename T> inline
Vector4<T>
Matrix4x4<T>::row(u32 x) const
{
    if (x > 3)
        throw std::out_of_range("Trying to access outside matrix");

    x *= 4;

    return Vector4<T>(e[x], e[x+1], e[x+2], e[x+3]);
}

template <typename T> inline
Vector4<T>
Matrix4x4<T>::col(u32 x) const
{
    if (x > 3)
        throw std::out_of_range("Trying to access outside matrix");

    return Vector4<T>(e[x+0], e[x+4], e[x+8], e[x+12]);
}

template <typename T> inline
Matrix4x4<T>&
Matrix4x4<T>::operator=(const Matrix4x4& m)
{
    if (this != &m)
    {
        e[ 0] = m.e[ 0]; e[ 1] = m.e[ 1];
        e[ 2] = m.e[ 2]; e[ 3] = m.e[ 3];
        e[ 4] = m.e[ 4]; e[ 5] = m.e[ 5];
        e[ 6] = m.e[ 6]; e[ 7] = m.e[ 7];
        e[ 8] = m.e[ 8]; e[ 9] = m.e[ 9];
        e[10] = m.e[10]; e[11] = m.e[11];
        e[12] = m.e[12]; e[13] = m.e[13];
        e[14] = m.e[14]; e[15] = m.e[15];
    }

    return *this;
}

template <typename T> inline
bool
Matrix4x4<T>::operator==(const Matrix4x4& m) const
{
    if (this == &m)
        return true;

    for(u32 i = 0; i < 16; ++i)
    {
        if (std::abs(e[i] - m.e[i]) > EPSILON)
            return false;
    }

    return true;
}

template <typename T> inline
bool
Matrix4x4<T>::operator!=(const Matrix4x4& m) const
{
    return !(*this == m);
}

template <typename T> inline
Matrix4x4<T>
Matrix4x4<T>::operator+(const Matrix4x4& m) const
{
    Matrix4x4<T> res;

    res.e[ 0] = e[ 0] + m.e[ 0];
    res.e[ 1] = e[ 1] + m.e[ 1];
    res.e[ 2] = e[ 2] + m.e[ 2];
    res.e[ 3] = e[ 3] + m.e[ 3];
    res.e[ 4] = e[ 4] + m.e[ 4];
    res.e[ 5] = e[ 5] + m.e[ 5];
    res.e[ 6] = e[ 6] + m.e[ 6];
    res.e[ 7] = e[ 7] + m.e[ 7];
    res.e[ 8] = e[ 8] + m.e[ 8];
    res.e[ 9] = e[ 9] + m.e[ 9];
    res.e[10] = e[10] + m.e[10];
    res.e[11] = e[11] + m.e[11];
    res.e[12] = e[12] + m.e[12];
    res.e[13] = e[13] + m.e[13];
    res.e[14] = e[14] + m.e[14];
    res.e[15] = e[15] + m.e[15];

    return res;
}

template <typename T> inline
Matrix4x4<T>
Matrix4x4<T>::operator-(const Matrix4x4& m) const
{
    Matrix4x4<T> res;

    res.e[ 0] = e[ 0] - m.e[ 0];
    res.e[ 1] = e[ 1] - m.e[ 1];
    res.e[ 2] = e[ 2] - m.e[ 2];
    res.e[ 3] = e[ 3] - m.e[ 3];
    res.e[ 4] = e[ 4] - m.e[ 4];
    res.e[ 5] = e[ 5] - m.e[ 5];
    res.e[ 6] = e[ 6] - m.e[ 6];
    res.e[ 7] = e[ 7] - m.e[ 7];
    res.e[ 8] = e[ 8] - m.e[ 8];
    res.e[ 9] = e[ 9] - m.e[ 9];
    res.e[10] = e[10] - m.e[10];
    res.e[11] = e[11] - m.e[11];
    res.e[12] = e[12] - m.e[12];
    res.e[13] = e[13] - m.e[13];
    res.e[14] = e[14] - m.e[14];
    res.e[15] = e[15] - m.e[15];

    return res;
}

template <typename T> inline
Matrix4x4<T>
Matrix4x4<T>::operator*(const T& a) const
{
    Matrix4x4<T> res;

    res.e[ 0] = e[ 0] * a;
    res.e[ 1] = e[ 1] * a;
    res.e[ 2] = e[ 2] * a;
    res.e[ 3] = e[ 3] * a;
    res.e[ 4] = e[ 4] * a;
    res.e[ 5] = e[ 5] * a;
    res.e[ 6] = e[ 6] * a;
    res.e[ 7] = e[ 7] * a;
    res.e[ 8] = e[ 8] * a;
    res.e[ 9] = e[ 9] * a;
    res.e[10] = e[10] * a;
    res.e[11] = e[11] * a;
    res.e[12] = e[12] * a;
    res.e[13] = e[13] * a;
    res.e[14] = e[14] * a;
    res.e[15] = e[15] * a;

    return res;
}

template <typename T> inline
Matrix4x4<T>
Matrix4x4<T>::operator*(const Matrix4x4& m) const
{
    Matrix4x4<T> res;

    res.e[ 0]  = e[ 0] * m.e[ 0];
    res.e[ 0] += e[ 1] * m.e[ 4];
    res.e[ 0] += e[ 2] * m.e[ 8];
    res.e[ 0] += e[ 3] * m.e[12];

    res.e[ 1]  = e[ 0] * m.e[ 1];
    res.e[ 1] += e[ 1] * m.e[ 5];
    res.e[ 1] += e[ 2] * m.e[ 9];
    res.e[ 1] += e[ 3] * m.e[13];

    res.e[ 2]  = e[ 0] * m.e[ 2];
    res.e[ 2] += e[ 1] * m.e[ 6];
    res.e[ 2] += e[ 2] * m.e[10];
    res.e[ 2] += e[ 3] * m.e[14];

    res.e[ 3]  = e[ 0] * m.e[ 3];
    res.e[ 3] += e[ 1] * m.e[ 7];
    res.e[ 3] += e[ 2] * m.e[11];
    res.e[ 3] += e[ 3] * m.e[15];

    res.e[ 4]  = e[ 4] * m.e[ 0];
    res.e[ 4] += e[ 5] * m.e[ 4];
    res.e[ 4] += e[ 6] * m.e[ 8];
    res.e[ 4] += e[ 7] * m.e[12];

    res.e[ 5]  = e[ 4] * m.e[ 1];
    res.e[ 5] += e[ 5] * m.e[ 5];
    res.e[ 5] += e[ 6] * m.e[ 9];
    res.e[ 5] += e[ 7] * m.e[13];

    res.e[ 6]  = e[ 4] * m.e[ 2];
    res.e[ 6] += e[ 5] * m.e[ 6];
    res.e[ 6] += e[ 6] * m.e[10];
    res.e[ 6] += e[ 7] * m.e[14];

    res.e[ 7]  = e[ 4] * m.e[ 3];
    res.e[ 7] += e[ 5] * m.e[ 7];
    res.e[ 7] += e[ 6] * m.e[11];
    res.e[ 7] += e[ 7] * m.e[15];

    res.e[ 8]  = e[ 8] * m.e[ 0];
    res.e[ 8] += e[ 9] * m.e[ 4];
    res.e[ 8] += e[10] * m.e[ 8];
    res.e[ 8] += e[11] * m.e[12];

    res.e[ 9]  = e[ 8] * m.e[ 1];
    res.e[ 9] += e[ 9] * m.e[ 5];
    res.e[ 9] += e[10] * m.e[ 9];
    res.e[ 9] += e[11] * m.e[13];

    res.e[10]  = e[ 8] * m.e[ 2];
    res.e[10] += e[ 9] * m.e[ 6];
    res.e[10] += e[10] * m.e[10];
    res.e[10] += e[11] * m.e[14];

    res.e[11]  = e[ 8] * m.e[ 3];
    res.e[11] += e[ 9] * m.e[ 7];
    res.e[11] += e[10] * m.e[11];
    res.e[11] += e[11] * m.e[15];

    res.e[12]  = e[12] * m.e[ 0];
    res.e[12] += e[13] * m.e[ 4];
    res.e[12] += e[14] * m.e[ 8];
    res.e[12] += e[15] * m.e[12];

    res.e[13]  = e[12] * m.e[ 1];
    res.e[13] += e[13] * m.e[ 5];
    res.e[13] += e[14] * m.e[ 9];
    res.e[13] += e[15] * m.e[13];

    res.e[14]  = e[12] * m.e[ 2];
    res.e[14] += e[13] * m.e[ 6];
    res.e[14] += e[14] * m.e[10];
    res.e[14] += e[15] * m.e[14];

    res.e[15]  = e[12] * m.e[ 3];
    res.e[15] += e[13] * m.e[ 7];
    res.e[15] += e[14] * m.e[11];
    res.e[15] += e[15] * m.e[15];

    return res;
}

template <typename T> inline
Vector4<T>
Matrix4x4<T>::operator*(const Vector4<T>& v) const
{
    return Vector4<T>(e[ 0] * v.x +
                      e[ 1] * v.y +
                      e[ 2] * v.z +
                      e[ 3] * v.w,
                      e[ 4] * v.x +
                      e[ 5] * v.y +
                      e[ 6] * v.z +
                      e[ 7] * v.w,
                      e[ 8] * v.x +
                      e[ 9] * v.y +
                      e[10] * v.z +
                      e[11] * v.w,
                      e[12] * v.x +
                      e[13] * v.y +
                      e[14] * v.z +
                      e[15] * v.w);
}

template <typename T> inline
Matrix4x4<T>&
Matrix4x4<T>::operator+=(const Matrix4x4& m)
{
    e[ 0] += m.e[ 0]; e[ 1] += m.e[ 1];
    e[ 2] += m.e[ 2]; e[ 3] += m.e[ 3];
    e[ 4] += m.e[ 4]; e[ 5] += m.e[ 5];
    e[ 6] += m.e[ 6]; e[ 7] += m.e[ 7];
    e[ 8] += m.e[ 8]; e[ 9] += m.e[ 9];
    e[10] += m.e[10]; e[11] += m.e[11];
    e[12] += m.e[12]; e[13] += m.e[13];
    e[14] += m.e[14]; e[15] += m.e[15];

    return *this;
}

template <typename T> inline
Matrix4x4<T>&
Matrix4x4<T>::operator-=(const Matrix4x4& m)
{
    e[ 0] -= m.e[ 0]; e[ 1] -= m.e[ 1];
    e[ 2] -= m.e[ 2]; e[ 3] -= m.e[ 3];
    e[ 4] -= m.e[ 4]; e[ 5] -= m.e[ 5];
    e[ 6] -= m.e[ 6]; e[ 7] -= m.e[ 7];
    e[ 8] -= m.e[ 8]; e[ 9] -= m.e[ 9];
    e[10] -= m.e[10]; e[11] -= m.e[11];
    e[12] -= m.e[12]; e[13] -= m.e[13];
    e[14] -= m.e[14]; e[15] -= m.e[15];

    return *this;
}

template <typename T> inline
Matrix4x4<T>&
Matrix4x4<T>::operator*=(const Matrix4x4& m)
{
    *this = *this * m;
    return *this;
}

template <typename T> inline
Matrix4x4<T>&
Matrix4x4<T>::operator*=(T x)
{
    e[ 0] *= x; e[ 1] *= x; e[ 2] *= x; e[ 3] *= x;
    e[ 4] *= x; e[ 5] *= x; e[ 6] *= x; e[ 7] *= x;
    e[ 8] *= x; e[ 9] *= x; e[10] *= x; e[11] *= x;
    e[12] *= x; e[13] *= x; e[14] *= x; e[15] *= x;

    return *this;
}

template <typename T> inline
T
Matrix4x4<T>::trace() const
{
    return (e[0] + e[5] + e[10] + e[15]);
}

template <typename T> inline
Matrix4x4<T>
Matrix4x4<T>::transposed() const
{
    Matrix4x4<T> res;

    res.e[ 0] = e[ 0]; res.e[ 1] = e[ 4];
    res.e[ 2] = e[ 8]; res.e[ 3] = e[12];
    res.e[ 4] = e[ 1]; res.e[ 5] = e[ 5];
    res.e[ 6] = e[ 9]; res.e[ 7] = e[13];
    res.e[ 8] = e[ 2]; res.e[ 9] = e[ 6];
    res.e[10] = e[10]; res.e[11] = e[14];
    res.e[12] = e[ 3]; res.e[13] = e[ 7];
    res.e[14] = e[11]; res.e[15] = e[15];

    return res;
}

template <typename T> inline
T 
Matrix4x4<T>::determinant() const
{
    return e00*e11*e22*e33 +
           e00*e12*e23*e31 +
           e00*e13*e21*e32 +
           e01*e10*e23*e32 +
           e01*e12*e20*e33 +
           e01*e13*e22*e30 +
           e02*e10*e21*e33 +
           e02*e11*e23*e30 +
           e02*e13*e20*e31 +
           e03*e10*e22*e31 +
           e03*e11*e20*e32 +
           e03*e12*e21*e30 -
           e00*e11*e23*e32 -
           e00*e12*e21*e33 -
           e00*e13*e22*e31 -
           e01*e10*e22*e33 -
           e01*e12*e23*e30 -
           e01*e13*e20*e32 -
           e02*e10*e23*e31 -
           e02*e11*e20*e33 -
           e02*e13*e21*e30 -
           e03*e10*e21*e32 -
           e03*e11*e22*e30 -
           e03*e12*e20*e31;
}

template <typename T> inline
Matrix4x4<T>
Matrix4x4<T>::inversed(const T epsilon) const
{
    //if (*this == Identity)
    //    return Identity;


    //Cofactors
    T a0 = e00*e11 - e01*e10;
    T a1 = e00*e12 - e02*e10;
    T a2 = e00*e13 - e03*e10;
    T a3 = e01*e12 - e02*e11;
    T a4 = e01*e13 - e03*e11;
    T a5 = e02*e13 - e03*e12;

    T b0 = e20*e31 - e21*e30;
    T b1 = e20*e32 - e22*e30;
    T b2 = e20*e33 - e23*e30;
    T b3 = e21*e32 - e22*e31;
    T b4 = e21*e33 - e23*e31;
    T b5 = e22*e33 - e23*e32;

    T det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;

    if (std::abs(det) > epsilon)
    {
        Matrix4x4 inv;

        inv.e00 = + e11*b5 - e12*b4 + e13*b3;
        inv.e10 = - e10*b5 + e12*b2 - e13*b1;
        inv.e20 = + e10*b4 - e11*b2 + e13*b0;
        inv.e30 = - e10*b3 + e11*b1 - e12*b0;

        inv.e01 = - e01*b5 + e02*b4 - e03*b3;
        inv.e11 = + e00*b5 - e02*b2 + e03*b1;
        inv.e21 = - e00*b4 + e01*b2 - e03*b0;
        inv.e31 = + e00*b3 - e01*b1 + e02*b0;

        inv.e02 = + e31*a5 - e32*a4 + e33*a3;
        inv.e12 = - e30*a5 + e32*a2 - e33*a1;
        inv.e22 = + e30*a4 - e31*a2 + e33*a0;
        inv.e32 = - e30*a3 + e31*a1 - e32*a0;

        inv.e03 = - e21*a5 + e22*a4 - e23*a3;
        inv.e13 = + e20*a5 - e22*a2 + e23*a1;
        inv.e23 = - e20*a4 + e21*a2 - e23*a0;
        inv.e33 = + e20*a3 - e21*a1 + e22*a0;

        inv *= 1/det;

        return inv;
    }
    else
        return Matrix4x4::Zero;
}


template <typename T>
const Matrix4x4<T>
Matrix4x4<T>::Zero = Matrix4x4<T>
(
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
);

template <typename T>
const Matrix4x4<T>
Matrix4x4<T>::Identity = Matrix4x4<T>
(
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
);

template <typename T>
Matrix4x4<T>&
transpose(Matrix4x4<T>& m)
{
    std::swap(m.e01, m.e10);
    std::swap(m.e02, m.e20);
    std::swap(m.e03, m.e30);

    std::swap(m.e10, m.e01);
    std::swap(m.e12, m.e21);
    std::swap(m.e13, m.e31);

    std::swap(m.e20, m.e02);
    std::swap(m.e21, m.e12);
    std::swap(m.e23, m.e32);

    std::swap(m.e30, m.e03);
    std::swap(m.e31, m.e13);
    std::swap(m.e32, m.e23);

    return m;
}

template <typename T>
Matrix4x4<T>&
transpose(Matrix4x4<T>&& m)
{
    return transpose<T>(std::ref(m));
}

//--- TYPEDEFS

typedef Matrix4x4<f32> mat4;

typedef Matrix4x4<f32> mat4_f32;
typedef Matrix4x4<f64> mat4_f64;

} // ::revel::math
} // ::revel

#endif /* MATRIX4X4_H_ */
