///
/// @author  Thomas Lehmann
/// @file    vector.h
/// @brief   math 2d vector.
///
/// Copyright (c) 2015 Thomas Lehmann
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
/// documentation files (the "Software"), to deal in the Software without restriction, including without limitation
/// the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
/// and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all copies
/// or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
/// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
/// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
/// DAMAGES OR OTHER LIABILITY,
/// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#ifndef INCLUDE_VECTOR_H_
#define INCLUDE_VECTOR_H_

#include <cmath>

namespace math {

class vector final {
    public:
        /// init c'tor for (x, y) coordinates
        constexpr vector(const double x, const double y)
            : m_x(x), m_y(y) {}

        /// getter for x coordinate
        constexpr double get_x() const {
            return m_x;
        }

        /// getter for y coordinate
        constexpr double get_y() const {
            return m_y;
        }

        /// length of vector
        constexpr double length() const {
            return sqrt(m_x * m_x + m_y * m_y);
        }

        /// scalar product of two vectors.
        constexpr double scalar_product(const vector& other) const {
            return m_x * other.get_x() + m_y * other.get_y();
        }

        /// vector rotated by 90 degree to the left
        constexpr vector left_vertical() const {
            return vector(-m_y, m_x);
        }

        /// vector rotated by 90 degree to the right
        constexpr vector right_vertical() const {
            return vector(m_y, -m_x);
        }

        /// providing normed vector
        constexpr vector normed() const {
            return vector(m_x / length(), m_y / length());
        }

        constexpr double angle(const vector& other) const {
            return (180.0/M_PI) * acos(scalar_product(other) / (length() * other.length()));
        }

        /// sum of two vectors
        constexpr friend vector operator + (const vector& lhs, const vector& rhs) {
            return vector(lhs.m_x + rhs.m_x, lhs.m_y + rhs.m_y);
        }

        /// difference of two vectors
        constexpr friend vector operator - (const vector& lhs, const vector& rhs) {
        return vector(lhs.m_x - rhs.m_x, lhs.m_y - rhs.m_y);
        }

        /// compares two vectors on to be equal
        constexpr friend bool operator == (const vector& lhs, const vector& rhs) {
            return lhs.get_x() == rhs.get_x() && lhs.get_y() == rhs.get_y();
        }

        /// dumping vector to stream
        friend std::ostream& operator << (std::ostream& stream, const vector& v) {
            stream << "vector(" << v.m_x << ", " << v.m_y << ")";
            return stream;
        }

    private:
        double m_x; ///< x-coordinate of 2d vector
        double m_y; ///< y-coordinate of 2d vector
};

}  // namespace math

#endif  // INCLUDE_VECTOR_H_
