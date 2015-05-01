///
/// @author  Thomas Lehmann
/// @file    member.h
/// @brief   serializable class members.
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
#ifndef INCLUDE_SERIALIZABLE_MEMBER_H_
#define INCLUDE_SERIALIZABLE_MEMBER_H_

#include <serializable/abstract_member.h>
#include <serializable/abstract_object.h>

#include <string>
#include <type_traits>
#include <sstream>

namespace serializable {

/// @class member
/// @brief serializable class members.
template <typename T>
class member : public abstract_member {
    public:
        /// init c'tor
        member(const std::string& name,
               const T& value,
               abstract_object& owner)
            : abstract_member(), m_name(name), m_value(value) {
            owner.register_member(this);
        }

        /// @return name of the member
        virtual const std::string& get_name() const noexcept override {
            return m_name;
        }

        /// @return current value of the member
        const T& get_value() const noexcept {
            return m_value;
        }

        /// @param value new value for the member
        void set_value(const T& value) noexcept {
            m_value = value;
        }

        /// @return true when given member is a string value
        virtual bool is_string() const noexcept override {
            return std::is_same<T, std::string>::value;
        }

        /// @return converts given member into a string value
        virtual std::string to_string() const noexcept override {
            std::stringstream stream;
            stream << m_value;
            return stream.str();
        }

    private:
        /// name of the class member
        const std::string m_name;
        /// value of the class member
        T m_value;
};

}  // namespace serializable

#endif  // INCLUDE_SERIALIZABLE_MEMBER_H_
