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
#include <memory>

namespace serializable {

/// @class member
/// @brief serializable class member.
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

        /// @return true when given member is a object value
        virtual bool is_object() const noexcept override {
            return false;
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

/// @class member
/// @brief serializable class member being an object.
/// @note this member takes ownership of the assigned object.
template <typename T>
class object_member : public abstract_member {
    public:
        /// init c'tor
        /// @param name is name of the class member
        /// @param obj is the pointer to the new allocated/assigned object instance
        /// @param owner is the owner of this class member
        object_member(const std::string& name, T* obj, abstract_object& owner)
            : abstract_member(), m_name(name), m_object(obj) {
            static_assert(std::is_base_of<abstract_object, T>::value,
                          "Base class is not serializable::abstract_object!");
            owner.register_member(this);
        }

        /// @return name of the member
        virtual const std::string& get_name() const noexcept override {
            return m_name;
        }

        /// @return true when given member is a string value
        virtual bool is_string() const noexcept override {
            return false;
        }

        /// @return always true (member does keep an object instance only).
        virtual bool is_object() const noexcept override {
            return true;
        }

        /// @return always an empty string (for now)
        virtual std::string to_string() const noexcept override {
            return "";
        }

        /// @return current object instance
        const T* get_value() const noexcept {
            return m_object.get();
        }

        /// @param value new value for the member
        void set_value(T* obj) noexcept {
            m_object.reset(obj);
        }

    private:
        /// name of the class member
        const std::string m_name;
        /// instance of a serializable object
        std::shared_ptr<T> m_object;
};

}  // namespace serializable

#endif  // INCLUDE_SERIALIZABLE_MEMBER_H_
