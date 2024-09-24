/**
 * @file Mat3x3.h
 * @brief Declaration of the Mat3x3 class, representing a 3x3 matrix.
 */

#ifndef MAT3X3_H
#define MAT3X3_H

#include <array>
#include <iostream>

/**
 * @class Mat3x3
 * @brief A class for representing and manipulating 3x3 matrices.
 */
class Mat3x3
{

private:
    std::array<std::array<double, 3>, 3> matrix;

    /** @return True if the matrix is the identity matrix, false otherwise. */
    bool isIdentity() const;

public:
    /** @brief Default constructor that initializes the matrix to all zeros. */
    Mat3x3();

    /**
     * @brief Parameterized constructor that initializes the matrix with given values.
     * @param init Initial values for the matrix.
     */
    Mat3x3(std::array<std::array<double, 3>, 3> init);

    /** @brief Default copy constructor. */
    Mat3x3(const Mat3x3 &) = default;

    /** @brief Default move constructor. */
    Mat3x3(Mat3x3 &&) = default;

    /** @brief Default copy assignment operator. */
    Mat3x3 &operator=(const Mat3x3 &) = default;

    /** @brief Default move assignment operator. */
    Mat3x3 &operator=(Mat3x3 &&) = default;

    /** @brief Default destructor. */
    ~Mat3x3() = default;

    /** @brief Stream insertion operator for Mat3x3 objects. */
    friend std::istream &operator>>(std::istream &is, Mat3x3 &mat);

    /** @brief Stream extraction operator for Mat3x3 objects. */
    friend std::ostream &operator<<(std::ostream &os, const Mat3x3 &mat);

    /** @return The determinant of the matrix. */
    double determinant() const;

    /** @return The trace of the matrix. */
    double trace() const;

    /** @return True if the matrix is antisymmetric, false otherwise. */
    bool isAntisymmetric() const;

    /** @return True if the matrix is orthogonal, false otherwise. */
    bool isOrthogonal() const;

    /** @return True if the matrix is invertible, false otherwise. */
    bool isInvertible() const;

    /** @return True if the matrix is symmetric, false otherwise. */
    bool isSymmetric() const;

    /** @return The transpose of the matrix. */
    Mat3x3 transpose() const;

    /** @return The inverse of the matrix, if it exists. */
    Mat3x3 inverse() const;

    /**
     * @brief Adds another matrix to this matrix.
     * @param rhs The matrix to add to this one.
     * @return A reference to this matrix after addition.
     */
    Mat3x3 &operator+=(const Mat3x3 &rhs);

    /**
     * Subtracts another matrix from this matrix.
     *
     * @param rhs The matrix to subtract from this one.
     * @return A reference to this matrix after subtraction.
     */
    Mat3x3 &operator-=(const Mat3x3 &rhs);

    /**
     * Multiplies this matrix by another matrix.
     *
     * @param rhs The matrix to multiply this one by.
     * @return A reference to this matrix after multiplication.
     */
    Mat3x3 &operator*=(const Mat3x3 &rhs);

    /**
     * Adds a scalar value to each element of the matrix.
     *
     * @param x The scalar value to add.
     * @return A reference to this matrix after addition.
     */
    Mat3x3 &operator+=(double x);

    /**
     * Subtracts a scalar value from each element of the matrix.
     *
     * @param x The scalar value to subtract.
     * @return A reference to this matrix after subtraction.
     */
    Mat3x3 &operator-=(double x);

    /**
     * Multiplies each element of the matrix by a scalar value.
     *
     * @param x The scalar value to multiply by.
     * @return A reference to this matrix after multiplication.
     */
    Mat3x3 &operator*=(double x);

    /**
     * Divides each element of the matrix by a scalar value.
     *
     * @param x The scalar value to divide by.
     * @return A reference to this matrix after division.
     * @throws std::overflow_error If x is zero.
     */
    Mat3x3 &operator/=(double x);

    /**
     * Increments each element of the matrix by 1 (pre-increment).
     *
     * @return A reference to this matrix after increment.
     */
    Mat3x3 &operator++();

    /**
     * Increments each element of the matrix by 1 (post-increment).
     *
     * @return A copy of this matrix before the increment.
     */
    Mat3x3 operator++(int);

    /**
     * Decrements each element of the matrix by 1 (pre-decrement).
     *
     * @return A reference to this matrix after decrement.
     */
    Mat3x3 &operator--();

    /**
     * Decrements each element of the matrix by 1 (post-decrement).
     *
     * @return A copy of this matrix before the decrement.
     */
    Mat3x3 operator--(int);

    /**
     * Unary minus operator. Negates each element of the matrix.
     *
     * @return A new matrix with each element negated.
     */
    Mat3x3 operator-() const;

    /**
     * Unary plus operator. Returns a copy of this matrix.
     *
     * @return A copy of this matrix.
     */
    Mat3x3 operator+() const;

    /**
     * Accesses elements of the matrix.
     *
     * @param index A pair of integers representing the row and column to access.
     * @return A reference to the element at the specified row and column.
     * @throws std::invalid_argument If the index is out of bounds.
     */
    double &operator[](std::pair<int, int> index);

    /**
     * Accesses elements of the matrix (const version).
     *
     * @param index A pair of integers representing the row and column to access.
     * @return A const reference to the element at the specified row and column.
     * @throws std::invalid_argument If the index is out of bounds.
     */
    const double &operator[](std::pair<int, int> index) const;

    /**
     * Negation operator. Checks if the matrix is invertible.
     *
     * @return True if the matrix is not invertible, false otherwise.
     */
    bool operator!() const;

    /**
     * Function call operator. Calculates the determinant of the matrix.
     *
     * @return The determinant of the matrix.
     */
    double operator()() const;

    /**
     * Conversion operator to bool. Checks if the matrix is invertible.
     *
     * @return True if the matrix is invertible, false otherwise.
     */
    operator bool() const;

    /**
     * Multiplies this matrix by another matrix.
     *
     * @param rhs The matrix to multiply this one by.
     * @return The result of the multiplication as a new matrix.
     */
    Mat3x3 operator*(const Mat3x3 &rhs) const;

    Mat3x3 operator*(double scalar) const;
};

#endif // MAT3X3_H