#include "Mat3x3.h"
#include <stdexcept>
#include <cmath>
#include <limits>

// Default constructor
Mat3x3::Mat3x3() : matrix{{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}} {} // Initialize all elements to 0

// Parameterized constructor
Mat3x3::Mat3x3(std::array<std::array<double, 3>, 3> init) : matrix(init) {} // give the initial values to the matrix from another 3x3 array

// Overloaded input and output operators
std::istream &operator>>(std::istream &is, Mat3x3 &mat) // take the input from the user and put it in the matrix which is in mat object
{
    for (auto &row : mat.matrix)
    {
        for (double &val : row)
        {
            is >> val;
        }
    }
    return is;
}

// Overloaded '<<' operator to output the matrix to the console
std::ostream &operator<<(std::ostream &os, const Mat3x3 &mat) // output the matrix which is mat obejct
{
    for (const auto &row : mat.matrix)
    {
        for (const double &val : row)
        {
            os << val << " ";
        }
        os << std::endl;
    }
    return os;
}

double Mat3x3::determinant() const
{
    return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2]) -
           matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[2][0] * matrix[1][2]) +
           matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1]);
}

double Mat3x3::trace() const // sum of the diagonal elements
{
    return matrix[0][0] + matrix[1][1] + matrix[2][2];
}

bool Mat3x3::isAntisymmetric() const // if the matrix is equal to its negative transpose
{
    return (matrix[0][1] == -matrix[1][0]) &&
           (matrix[0][2] == -matrix[2][0]) &&
           (matrix[1][2] == -matrix[2][1]);
}

bool Mat3x3::isOrthogonal() const // matrix is orthogonal when the matrix multiplied by its transpose is equal to the identity matrix
{
    Mat3x3 transposed = transpose();
    Mat3x3 identity = *this * transposed;
    return identity.isIdentity();
}

bool Mat3x3::isInvertible() const
{
    return std::abs(determinant()) > std::numeric_limits<double>::epsilon();
}

bool Mat3x3::isSymmetric() const
{
    return (matrix[0][1] == matrix[1][0]) &&
           (matrix[0][2] == matrix[2][0]) &&
           (matrix[1][2] == matrix[2][1]);
}

Mat3x3 Mat3x3::transpose() const
{
    Mat3x3 result; // create a new object of Mat3x3 called result
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            result.matrix[i][j] = matrix[j][i]; // store the transpose (when swap rows and columns) of the matrix in result object
        }
    }
    return result; // return the result object
}

Mat3x3 Mat3x3::inverse() const
{
    double det = determinant(); // get the determinant of the matrix
    if (det == 0)
    {
        throw std::overflow_error("Matrix is not invertible");
    }

    Mat3x3 adjoint; // create a new object of Mat3x3 called adjoint
    adjoint.matrix[0][0] = matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2];
    adjoint.matrix[0][1] = matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2];
    adjoint.matrix[0][2] = matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1];
    adjoint.matrix[1][0] = matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2];
    adjoint.matrix[1][1] = matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0];
    adjoint.matrix[1][2] = matrix[1][0] * matrix[0][2] - matrix[0][0] * matrix[1][2];
    adjoint.matrix[2][0] = matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1];
    adjoint.matrix[2][1] = matrix[2][0] * matrix[0][1] - matrix[0][0] * matrix[2][1];
    adjoint.matrix[2][2] = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];

    return (adjoint *= (1 / det)); // return the inverse of the matrix
}

bool Mat3x3::isIdentity() const // identity matrix is a square matrix in which all the elements of the principal diagonal are ones and all other elements are zeros
{
    // Check diagonal elements
    for (int i = 0; i < 3; ++i)
    {
        if (matrix[i][i] != 1)
        {
            return false; // Diagonal element not equal to 1
        }
    }

    // Check off-diagonal elements
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (i != j && matrix[i][j] != 0)
            {
                return false; // Off-diagonal element not equal to 0
            }
        }
    }

    return true; // Passed all checks, it's an identity matrix
}

// Compound assignment operators
Mat3x3 &Mat3x3::operator+=(const Mat3x3 &rhs)
{
    for (int i = 0; i < 3; ++i) // loop through the rows
    {
        for (int j = 0; j < 3; ++j) // loop through the columns
        {
            this->matrix[i][j] += rhs.matrix[i][j]; // add the elements of the matrix with the elements of the rhs matrix
        }
    }
    return *this;
}

Mat3x3 &Mat3x3::operator-=(const Mat3x3 &rhs)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            this->matrix[i][j] -= rhs.matrix[i][j]; // subtract the elements of the matrix with the elements of the rhs matrix
        }
    }
    return *this;
}

Mat3x3 &Mat3x3::operator*=(const Mat3x3 &rhs)
{
    Mat3x3 temp = *this * rhs; // Assuming operator* for Mat3x3 is already defined
    *this = temp;
    return *this;
}

// Scalar compound assignments
Mat3x3 &Mat3x3::operator+=(double x) // add value x to all the elements of the matrix
{
    for (auto &row : this->matrix)
    {
        for (double &val : row)
        {
            val += x;
        }
    }
    return *this;
}

Mat3x3 &Mat3x3::operator-=(double x) // subtract value x from all the elements of the matrix by calling the operator+= and passing -x
{
    return *this += -x;
}

Mat3x3 &Mat3x3::operator*=(double x)
{
    for (auto &row : this->matrix)
    {
        for (double &val : row)
        {
            val *= x;
        }
    }
    return *this;
}

Mat3x3 &Mat3x3::operator/=(double x)
{
    if (x == 0)
        throw std::overflow_error("Division by zero");
    return *this *= (1 / x);
}

// Pre-increment and post-increment
Mat3x3 &Mat3x3::operator++()
{ // Pre-increment
    return *this += 1;
}

Mat3x3 Mat3x3::operator++(int)
{ // Post-increment
    Mat3x3 temp = *this;
    ++(*this);
    return temp;
}

// Pre-decrement and post-decrement
Mat3x3 &Mat3x3::operator--()
{ // Pre-decrement
    return *this -= 1;
}

Mat3x3 Mat3x3::operator--(int)
{ // Post-decrement
    Mat3x3 temp = *this;
    --(*this);
    return temp;
}

// Unary operators
Mat3x3 Mat3x3::operator-() const
{
    Mat3x3 result;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            result.matrix[i][j] = -this->matrix[i][j];
        }
    }
    return result;
}

Mat3x3 Mat3x3::operator+() const
{
    return *this; // Unary plus does nothing
}

// Subscript operators
double &Mat3x3::operator[](std::pair<int, int> index)
{
    if (index.first < 0 || index.first >= 3 || index.second < 0 || index.second >= 3)
        throw std::invalid_argument("index out of bounds");
    return this->matrix[index.first][index.second];
}

const double &Mat3x3::operator[](std::pair<int, int> index) const
{
    if (index.first < 0 || index.first >= 3 || index.second < 0 || index.second >= 3)
        throw std::invalid_argument("index out of bounds");
    return this->matrix[index.first][index.second];
}

// Negation operator
bool Mat3x3::operator!() const
{
    return !this->isInvertible();
}

// Function object
double Mat3x3::operator()() const
{
    return this->determinant();
}

// Conversion operator
Mat3x3::operator bool() const
{
    return this->isInvertible();
}

// Operator overload for multiplying two Mat3x3 objects
Mat3x3 Mat3x3::operator*(const Mat3x3 &rhs) const
{
    Mat3x3 result;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {

            result.matrix[i][j] += this->matrix[i][j] * rhs.matrix[i][j];
        }
    }
    return result;
}

Mat3x3 Mat3x3::operator*(double scalar) const
{
    Mat3x3 result;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            result.matrix[i][j] = this->matrix[i][j] * scalar;
        }
    }
    return result;
}
