///
/// @author  Thomas Lehmann
/// @file    object.h
/// @brief   serializable object.
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
#ifndef INCLUDE_SERIALIZABLE_OBJECT_H_
#define INCLUDE_SERIALIZABLE_OBJECT_H_

#include <serializable/abstract_object.h>
#include <serializable/abstract_member.h>

#include <string>
#include <unordered_map>

namespace serializable {

/// @class object
/// @brief serializable object
class object : public abstract_object {
    public:
        using member_container_type = std::unordered_map<std::string, abstract_member*>;

        /// init c'tor
        object(const std::string& name)
            : abstract_object(), m_name(name), m_members() {
        }

        /// readonly access to name of member
        virtual const std::string& get_name() const noexcept override {
            return m_name;
        }

        /// @return when member has been successfully registered
        bool register_member(abstract_member* the_member) noexcept override {
            return m_members.insert(
                member_container_type::value_type(the_member->get_name(), the_member)).second;
        }

        /// @return first member in the container or end() indicator if
        ///         no member has been registered.
        member_container_type::const_iterator begin() const noexcept {
            return m_members.begin();
        }

        /// @return end of container indicator for members
        member_container_type::const_iterator end() const noexcept {
            return m_members.end();
        }

        /// @return number of registered members
        member_container_type::size_type size() const noexcept {
            return m_members.size();
        }

        /// @return true when there has been no member registered.
        bool empty() const noexcept {
            return m_members.empty();
        }

    private:
        /// name of the object
        const std::string m_name;
        /// registered members
        member_container_type m_members;
};

}  // namespace serializable

#endif  // INCLUDE_SERIALIZABLE_OBJECT_H_
