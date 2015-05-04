///
/// @author  Thomas Lehmann
/// @file    line.h
/// @brief   math 2d line.
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
#ifndef INCLUDE_MATH_LINE_H_
#define INCLUDE_MATH_LINE_H_

#include <math/vector.h>

namespace math {

class line final {
    public:
        /// default c'tor
        constexpr line() = default;

        /// init c'tor
        constexpr line(const vector& location, const vector& direction)
            : m_location(location), m_direction(direction) {
        }

        /// @return get location vector
        constexpr const vector& get_location() const noexcept {
            return m_location;
        }

        /// @return get direction vector
        constexpr const vector& get_direction() const noexcept {
            return m_direction;
        }

        /// length of line
        constexpr double length() const noexcept {
            return m_direction.length();
        }

        /// dumping line to stream
        friend std::ostream& operator << (std::ostream& stream, const line& l) {
            stream << "line(" << l.get_location()  << ", "
                              << l.get_direction() << ")";
            return stream;
        }

    private:
        /// location vector
        vector m_location;
        /// direction vector
        vector m_direction;
};

}  // namespace math

#endif  // INCLUDE_MATH_LINE_H_
