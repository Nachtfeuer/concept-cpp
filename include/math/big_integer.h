///
/// @author  Thomas Lehmann
/// @file    big_integer.h
/// @brief   the big integer class
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
#ifndef INCLUDE_MATH_BIG_INTEGER_H_
#define INCLUDE_MATH_BIG_INTEGER_H_

#include <math/big_integer_base.h>

#include <unordered_map>
#include <iostream>
#include <sstream>
#include <type_traits>
#include <limits>
#include <cstdint>

namespace math {

/// @class big_integer
/// @brief being able to calculate bigger numbers than the standard types.
class big_integer {
    public:
        /// abbreviation for factor inside this class.
        using factory = big_integer_factory;

        /// default c'tor
        big_integer()
            : m_digits() {
        }

        /// init c'tor for a container with digits
        big_integer(const digits_type& digits)
            : m_digits(digits) {
        }

        /// init c'tor for a standard integer
        template <typename T>
        big_integer(const T value)
            : m_digits() {
            assign(value);
        }

        /// adding another big integer to given value
        /// @return this to allow to continue with further operations.
        /// @note for the moment we create an implementation each call
        ///       which will be changed.
        const big_integer& operator += (const big_integer& rhs) {
            auto operation = factory::get().create_instance(int(big_integer_operation::SUM));
            if (!operation) {
                throw std::runtime_error("Missing SUM implementation!");
            }

            operation->calculate(m_digits, rhs.m_digits);
            return *this;
        }

        /// adding another big integer to given value
        /// @return this to allow to continue with further operations.
        /// @note for the moment we create an implementation each call
        ///       which will be changed.
        template <typename T>
        const big_integer& operator += (const T& value) {
            *this += big_integer(value);
            return *this;
        }

        /// multiplication of two big integer
        /// @return this to allow to continue with further operations.
        /// @note for the moment we create an implementation each call
        ///       which will be changed.
        const big_integer& operator *= (const big_integer& rhs) {
            auto operation = factory::get().create_instance(int(big_integer_operation::MULTIPLICATION));
            if (!operation) {
                throw std::runtime_error("Missing MULTIPLICATION implementation!");
            }

            operation->calculate(m_digits, rhs.m_digits);
            return *this;
        }

        /// Assigning a "normal" integer to the big integer class
        /// @return this to allow to continue with further operations.
        template <typename T>
        const big_integer& operator = (const T value) {
            assign(value);
            return *this;
        }

        /// sum of two big integer
        /// @return sum of two big integer
        friend big_integer operator + (const big_integer& lhs, const big_integer& rhs) {
            return big_integer(lhs) += rhs;
        }

        /// multiplication of two big integer
        /// @return product of two big integer
        friend big_integer operator * (const big_integer& lhs, const big_integer& rhs) {
            return big_integer(lhs) *= rhs;
        }

        /// dumping big integer content to stream
        friend std::ostream& operator << (std::ostream& stream, const big_integer& bi) {
            const auto itEnd = bi.m_digits.rend();
            stream << "big_integer(";
            for (auto it = bi.m_digits.rbegin(); it != itEnd; ++it) {
                stream << static_cast<uint32_t>(*it);
            }
            stream << ")";
            return stream;
        }

        /// providing big_integer "value" as string
        std::string to_string() const noexcept {
            const auto itEnd = m_digits.rend();
            std::stringstream stream;
            for (auto it = m_digits.rbegin(); it != itEnd; ++it) {
                stream << static_cast<uint32_t>(*it);
            }
            return stream.str();
        }

        /// @return number of digits in the integer
        digits_type::size_type size() const noexcept {
            return m_digits.size();
        }

        /// @return true when there is no digit defined
        bool empty() const noexcept {
            return m_digits.empty();
        }

    private:

        /// Intention is to be able to assign a standard integer as 
        /// individual digits to this instance
        template <typename T>
        inline void assign(const T value) noexcept {
            static_assert(std::numeric_limits<T>::is_integer, "integer values allowed only");
            
            m_digits.clear();
            for (auto digits = value; digits != 0; digits /= 10) {
                m_digits.push_back(digits % 10);
            }
        }

        /// stored digits
        digits_type m_digits;
};

}  // namespace math


#endif   // INCLUDE_MATH_BIG_INTEGER_H_
