#ifndef _RVL_MATRIX3X3_H_
#define _RVL_MATRIX3X3_H_

#include <stdexcept>
#include "../Types.h"

namespace revel { namespace math
{

template <typename T> class Vector3;
template <typename T> class Matrix3x3;
template <typename T> class Quaternion;

template <typename T>
class Matrix3x3
{
public:
    /**
     * Default constructor
     */
    Matrix3x3();
    /**
     * Cnstructor, takes 16 elements in row-order.
     *
     * @param[in] m00 Element (0, 0) in the matrix.
     * @param[in] m01 Element (0, 1) in the matrix.
     * @param[in] m02 Element (0, 2) in the matrix.
     * @param[in] m10 Element (1, 0) in the matrix.
     * @param[in] m11 Element (1, 1) in the matrix.
     * @param[in] m12 Element (1, 2) in the matrix.
     * @param[in] m20 Element (2, 0) in the matrix.
     * @param[in] m21 Element (2, 1) in the matrix.
     * @param[in] m22 Element (2, 2) in the matrix.

     */
    Matrix3x3(T m00, T m01, T m02,
              T m10, T m11, T m12,
              T m20, T m21, T m22);

    /**
     * Constructor. Takes one value and initializes all
     * matrix element to the given value.
     *
     * @param[in] x Value for all elements.
     */
    Matrix3x3(T x);

    /**
     * Constructor. Takes a pointer and reads the 16 values
     * to initialize the matrix with. The second parameter controls
     * if the values are in row or column order.
     *
     * @param[in] x Pointer to the elements.
     * @param row_order Set the order of the elements. Defaults to row order.
     */
    Matrix3x3(T* x, bool row_order = true);

    /**
     * Constructor. Takes four vectors and initializes the matrix to
     * the given values. The second parameters controls if the vectors are
     * row or column vectors. The default is to use row order.
     *
     * @param[in] v0 First vector.
     * @param[in] v1 Second vector.
     * @param[in] v2 Third vector.
     * @param[in] row_order Specify which type of vectors are used.
     */
    Matrix3x3(const Vector3<T>& v0,
              const Vector3<T>& v1,
              const Vector3<T>& v2,
              bool row_order = true);
    /**
     * Default copy-constructor. Creates an identical copy of the input matrix.
     *
     * @todo Implement 3x3 matrix.
     */
    Matrix3x3(const Matrix3x3& m);
    
    /**
     * Constructor which creates a (rotation) matrix from a unit quaternion.
     */
    Matrix3x3(const Quaternion<T>& q)
        : e00(1 - 2*q.y*q.y - 2*q.z*q.z)
        , e01(2*q.x*q.y + 2*q.w*q.z)
        , e02(2*q.x*q.z - 2*q.w*q.y)
        , e10(2*q.x*q.y - 2*q.w*q.z)
        , e11(1 - 2*q.x*q.x - 2*q.z*q.z)
        , e12(2*q.y*q.z + 2*q.w*q.x)
        , e20(2*q.x*q.z + 2*q.w*q.y)
        , e21(2*q.y*q.z - 2*q.w*q.x)
        , e22(1 - 2*q.x*q.x - 2*q.y*q.y)
    {
    }
    
    /**
     * Default (virtual) destructor.
     */
    ~Matrix3x3();

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
    Vector3<T> row(u32 x) const;
    
    /**
     * Extract a column vector from the matrix
     *
     * @param x Row number.
     * @return Vector column.
     */  
    Vector3<T> col(u32 x) const;

    /**
     * Matrix addition
     *
     * @param m Input matrix
     * @return Result matrix
     */
    Matrix3x3 operator+(const Matrix3x3& m) const;

    /**
     * Matrix subtraction
     *
     * @param m Input matrix
     * @return Result matrix
     */
    Matrix3x3 operator-(const Matrix3x3& m) const;

    /**
     * Matrix multiplication
     *
     * @param a Input scalar
     * @return Result matrix
     */
    Matrix3x3 operator*(const T& a) const;

    /**
     * Matrix multiplication
     *
     * @param a Input scalar
     * @return Result matrix
     */
    Matrix3x3 operator*(const Matrix3x3& m) const;

    /**
     * Matrix multiplication
     *
     * @param v Input column vector
     * @return Result vector
     */
    Vector3<T> operator*(const Vector3<T>& v) const;

    /**
     * Assignment of all variables in the matrix
     *
     * @param m Source matrix
     * @return Reference to itself
     */
    Matrix3x3& operator=(const Matrix3x3& m);

    /**
     * Matrix addition
     *
     * @param m Input matrix
     * @return Reference to itself
     */
    Matrix3x3& operator+=(const Matrix3x3& m);

    /**
     * Matrix subtraction
     *
     * @param m Input matrix
     * @return Reference to itself
     */
    Matrix3x3& operator-=(const Matrix3x3& m);

    /**
     * Matrix multiplication
     *
     * @param m Input matrix
     * @return Reference to itself
     */
    Matrix3x3& operator*=(const Matrix3x3& m);

    /**
     * Matrix multiplication
     *
     * @param a Scalar
     * @return Reference to itself
     */
    Matrix3x3& operator*=(T a);

    bool operator!=(const Matrix3x3& m) const;

    bool operator==(const Matrix3x3& m) const;

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
    Matrix3x3 transpose() const;

    /**
     * Calculate the determinant of a matrix
     *
     * @return Determinant of 3x3 matrix
     */
    T determinant() const;

    /**
     * Inverse of a matrix
     *
     * @TODO IMPLEMENT
     * @return Matrix inverse
     */
	Matrix3x3 inverse() const
	{
		/*
		Matrix3x3 res;

		T d = determinant();

		//Todo: Float compare?
		if (d == 0)
		{
			// throw exception?
			return zero();
		}

	

		return (res * (1/d));
		*/
	}

//protected:
    union
    {
        T e[9];
        struct
        {
            T e00, e01, e02,
              e10, e11, e12,
              e20, e21, e22;
        };
    };

	static const Matrix3x3 Zero;
	static const Matrix3x3 Identity;
};

template <typename T> inline
Matrix3x3<T>::Matrix3x3()
{

}

template <typename T> inline
Matrix3x3<T>::Matrix3x3(T m00, T m01, T m02,
                        T m10, T m11, T m12,
                        T m20, T m21, T m22)
{
    e00 = m00; e01 = m01; e02 = m02;
    e10 = m10; e11 = m11; e12 = m12;
    e20 = m20; e21 = m21; e22 = m22;
}

template <typename T> inline
Matrix3x3<T>::Matrix3x3(T x)
{
	
}

template <typename T> inline
Matrix3x3<T>::Matrix3x3(const Vector3<T>& v0, 
                        const Vector3<T>& v1,
                        const Vector3<T>& v2,
                        bool row_order)
{
    if (row_order)
    {
        e00 = v0.x; e01 = v0.y; e02 = v0.z;
        e10 = v1.x; e01 = v1.y; e02 = v1.z;
        e10 = v2.x; e01 = v2.y; e02 = v2.z;
    }
    else
    {
        e00 = v0.x; e01 = v1.x; e02 = v2.x;
        e10 = v0.y; e01 = v1.y; e02 = v2.y;
        e10 = v0.z; e01 = v1.z; e02 = v2.z;
    }
}

template <typename T> inline
Matrix3x3<T>::Matrix3x3(T* x, bool row_order)
{
    if (row_order)
    {
        e[ 0] = x[ 0];
        e[ 1] = x[ 1];
        e[ 2] = x[ 2];
        e[ 3] = x[ 3];
        e[ 4] = x[ 4];
        e[ 5] = x[ 5];
        e[ 6] = x[ 6];
        e[ 7] = x[ 7];
        e[ 8] = x[ 8];
    }
    else
    {
        e[ 0] = x[ 0];
        e[ 1] = x[ 3];
        e[ 2] = x[ 6];
        e[ 3] = x[ 1];
        e[ 4] = x[ 4];
        e[ 5] = x[ 7];
        e[ 6] = x[ 2];
        e[ 7] = x[ 5];
        e[ 8] = x[ 8];
    }
}

template <typename T> inline
Matrix3x3<T>::Matrix3x3(const Matrix3x3<T>& m)
{
    e00 = m.e00; e01 = m.e01; e02 = m.e02;
    e10 = m.e10; e11 = m.e11; e12 = m.e12;
    e20 = m.e20; e21 = m.e21; e22 = m.e22;
}


template <typename T> inline
Matrix3x3<T>::~Matrix3x3()
{

}

template <typename T> inline
T&
Matrix3x3<T>::operator()(u32 row, u32 col)
{
    if (row > 2 || col > 2)
        throw std::out_of_range("Trying to access outside matrix");

    return e[row * 3 + col];
}


template <typename T> inline
const T&
Matrix3x3<T>::operator()(u32 row, u32 col) const
{
    if (row > 2 || col > 2)
        throw std::out_of_range("Trying to access outside matrix");

    return e[row * 3 + col];
}

template <typename T> inline
T&
Matrix3x3<T>::operator[](u32 index)
{
    return e[index];
}


template <typename T> inline
const T&
Matrix3x3<T>::operator[](u32 index) const
{
    return e[index];
}


template <typename T> inline
Vector3<T>
Matrix3x3<T>::row(u32 x) const
{
    if (x > 2)
        throw std::out_of_range("Trying to access outside matrix");

    x *= 3;

    return Vector3<T>(e[x], e[x+1], e[x+2]);
}

template <typename T> inline
Vector3<T>
Matrix3x3<T>::col(u32 x) const
{
    if (x > 3)
        throw std::out_of_range("Trying to access outside matrix");

    return Vector3<T>(e[x+0], e[x+3], e[x+6]);
}

template <typename T> inline
Matrix3x3<T>&
Matrix3x3<T>::operator=(const Matrix3x3& m)
{
    if (this != &m)
    {
        e00 = m.e00; e01 = m.e01; e02 = m.e02;
        e10 = m.e10; e11 = m.e11; e12 = m.e12;
        e20 = m.e20; e21 = m.e21; e22 = m.e22;
    }

    return *this;
}

template <typename T> inline
Matrix3x3<T>
Matrix3x3<T>::operator+(const Matrix3x3& m) const
{
    Matrix3x3<T> res;

    res.e00 = e00 + m.e00; res.e01 = e01 + m.e01; res.e02 = e02 + m.e02;
    res.e10 = e10 + m.e10; res.e11 = e11 + m.e11; res.e12 = e12 + m.e12;
    res.e20 = e20 + m.e20; res.e21 = e21 + m.e21; res.e22 = e22 + m.e22;

    return res;
}

template <typename T> inline
Matrix3x3<T>
Matrix3x3<T>::operator-(const Matrix3x3& m) const
{
    Matrix3x3<T> res;

    res.e00 = e00 - m.e00; res.e01 = e01 - m.e01; res.e02 = e02 - m.e02;
    res.e10 = e10 - m.e10; res.e11 = e11 - m.e11; res.e12 = e12 - m.e12;
    res.e20 = e20 - m.e20; res.e21 = e21 - m.e21; res.e22 = e22 - m.e22;

    return res;
}

template <typename T> inline
Matrix3x3<T>
Matrix3x3<T>::operator*(const T& a) const
{
    Matrix3x3<T> res;

    res.e00 = e00 * a; res.e01 = e01 * a; res.e02 = e02 * a;
    res.e10 = e10 * a; res.e11 = e11 * a; res.e12 = e12 * a;
    res.e20 = e20 * a; res.e21 = e21 * a; res.e22 = e22 * a;

    return res;
}

template <typename T> inline
Matrix3x3<T>
Matrix3x3<T>::operator*(const Matrix3x3& m) const
{
    Matrix3x3<T> res;

    res.e00 = e00*m.e00 + e01*m.e10 + e02*m.e20;
    res.e01 = e00*m.e01 + e01*m.e11 + e02*m.e21;
    res.e02 = e00*m.e02 + e01*m.e12 + e02*m.e22;

    res.e10 = e10*m.e00 + e11*m.e10 + e12*m.e20;
    res.e11 = e10*m.e01 + e11*m.e11 + e12*m.e21;
    res.e12 = e10*m.e02 + e11*m.e12 + e12*m.e22;

    res.e20 = e20*m.e00 + e21*m.e10 + e22*m.e20;
    res.e21 = e20*m.e01 + e21*m.e11 + e22*m.e21;
    res.e22 = e20*m.e02 + e21*m.e12 + e22*m.e22;

    return res;
}

template <typename T> inline
Vector3<T>
Matrix3x3<T>::operator*(const Vector3<T>& v) const
{
    Vector3<T> res;

    res.x = e00*v.x + e01*v.y + e02*v.z;
    res.y = e10*v.x + e11*v.y + e12*v.z;
    res.z = e20*v.x + e21*v.y + e22*v.z;

    return res;
}

template <typename T> inline
Matrix3x3<T>&
Matrix3x3<T>::operator+=(const Matrix3x3& m)
{
    e00 += m.e00; e01 += m.e01; e02 += m.e02;
    e10 += m.e10; e11 += m.e11; e12 += m.e12;
    e20 += m.e20; e21 += m.e21; e22 += m.e22;

    return *this;
}

template <typename T> inline
Matrix3x3<T>&
Matrix3x3<T>::operator-=(const Matrix3x3& m)
{
    e00 -= m.e00; e01 -= m.e01; e02 -= m.e02;
    e10 -= m.e10; e11 -= m.e11; e12 -= m.e12;
    e20 -= m.e20; e21 -= m.e21; e22 -= m.e22;

    return *this;
}

template <typename T> inline
Matrix3x3<T>&
Matrix3x3<T>::operator*=(const Matrix3x3& m)
{
    *this = *this * m;
    return *this;
}

template <typename T> inline
Matrix3x3<T>&
Matrix3x3<T>::operator*=(T x)
{
    e[ 0] *= x;
    e[ 1] *= x;
    e[ 2] *= x;
    e[ 3] *= x;
    e[ 4] *= x;
    e[ 5] *= x;
    e[ 6] *= x;
    e[ 7] *= x;
    e[ 8] *= x;

    return *this;
}

template <typename T> inline
T
Matrix3x3<T>::trace() const
{
    return (e00 + e11 + e22);
}

template <typename T> inline
bool
Matrix3x3<T>::operator==(const Matrix3x3& m) const
{
    return (m.e00 == e00 && m.e01 == e01 && m.e02 == e02 &&
            m.e10 == e10 && m.e11 == e11 && m.e12 == e12 &&
            m.e20 == e20 && m.e21 == e21 && m.e22 == e22);
}

template <typename T> inline
bool
Matrix3x3<T>::operator!=(const Matrix3x3& m) const
{
    return !(*this == m);
}

template <typename T> inline
Matrix3x3<T>
Matrix3x3<T>::transpose() const
{
    Matrix3x3<T> res;

    res.e00 = e00; res.e01 = e10; res.e02 = e20;
    res.e10 = e01; res.e11 = e11; res.e12 = e21;
    res.e20 = e02; res.e21 = e12; res.e22 = e22;

    return res;
}

template <typename T>
const Matrix3x3<T>
Matrix3x3<T>::Zero = Matrix3x3<T>
(
	0, 0, 0,
	0, 0, 0,
	0, 0, 0
);

template <typename T>
const Matrix3x3<T>
Matrix3x3<T>::Identity = Matrix3x3<T>
(
	1, 0, 0,
	0, 1, 0,
	0, 0, 1
);

typedef Matrix3x3<f32> mat3;

typedef Matrix3x3<f32> mat3_f32;
typedef Matrix3x3<f64> mat3_f64;

}} // revel::math

#endif /* _RVL_Matrix3x3_H_ */
