///
/// @author  Thomas Lehmann
/// @file    abstract_dumper.h
/// @brief   base class for a concrete dumper.
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
#ifndef INCLUDE_SERIALIZABLE_ABSTRACT_DUMPER_H_
#define INCLUDE_SERIALIZABLE_ABSTRACT_DUMPER_H_

#include <serializable/object.h>
#include <iostream>

namespace serializable {

/// @class abstract_dumper
/// @brief base class for concrete dumper
class abstract_dumper {
    public:
        /// default d'tor
        virtual ~abstract_dumper() = default;
        /// dumping of an object (depends on impl.)
        virtual void dump(const object&, std::ostream&) const = 0;
        /// dumping of a member (depends on impl.)
        virtual void dump(const abstract_member&, std::ostream&) const = 0;
};

}  // namespace serializable

#endif  // INCLUDE_SERIALIZABLE_ABSTRACT_DUMPER_H_
