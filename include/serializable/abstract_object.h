///
/// @author  Thomas Lehmann
/// @file    abstract_object.h
/// @brief   base class for serializable object.
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
#ifndef INCLUDE_SERIALIZABLE_ABSTRACT_OBJECT_H_
#define INCLUDE_SERIALIZABLE_ABSTRACT_OBJECT_H_

#include <string>

namespace serializable {

/// forward declaration(s):
class abstract_member;

/// @class abstract_object
/// @brief base class for serializable object.
class abstract_object {
    public:
        /// default d'tor
        virtual ~abstract_object() = default;
        /// @return name of the object
        virtual const std::string& get_name() const noexcept = 0;
        /// @return when successfully registered given member
        virtual bool register_member(abstract_member*) noexcept = 0;
};

}  // namespace serializable

#endif  // INCLUDE_SERIALIZABLE_ABSTRACT_OBJECT_H_
