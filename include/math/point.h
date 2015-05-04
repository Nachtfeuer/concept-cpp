///
/// @author  Thomas Lehmann
/// @file    point.h
/// @brief   math 2d point.
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
#ifndef INCLUDE_MATH_POINT_H_
#define INCLUDE_MATH_POINT_H_

#include <math/vector.h>
#include <iostream>

namespace math {

/// @class point
/// @brief math 2d point.
class point final {
    public:
        /// init c'tor for (x, y) coordinates
        constexpr point(const double x = 0.0, const double y = 0.0) noexcept
            : m_x(x), m_y(y) {}

        /// getter for x coordinate
        constexpr double get_x() const noexcept {
            return m_x;
        }

        /// getter for y coordinate
        constexpr double get_y() const noexcept {
            return m_y;
        }

        /// difference of two points is a vector
        constexpr friend vector operator - (const point& lhs, const point& rhs) noexcept {
        return vector(lhs.m_x - rhs.m_x, lhs.m_y - rhs.m_y);
        }

        /// compares two points on to be equal
        constexpr friend bool operator == (const point& lhs, const point& rhs) noexcept {
            return lhs.get_x() == rhs.get_x() && lhs.get_y() == rhs.get_y();
        }

        /// dumping point to stream
        friend std::ostream& operator << (std::ostream& stream, const point& p) {
            stream << "point(" << p.m_x << ", " << p.m_y << ")";
            return stream;
        }

    private:
        double m_x; ///< x-coordinate of 2d point
        double m_y; ///< y-coordinate of 2d point
};

}  // namespace math

#endif  // INCLUDE_MATH_POINT_H_
