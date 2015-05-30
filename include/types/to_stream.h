///
/// @author  Thomas Lehmann
/// @file    to_stream.h
/// @brief
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
#ifndef INCLUDE_TYPES_TO_STREAM_H_
#define INCLUDE_TYPES_TO_STREAM_H_

#include <vector>
#include <list>
#include <set>
#include <iostream>

namespace types {

/// @class to_stream<T>
/// @brief general dumper for usual data types
template <class T>
struct to_stream final {
    static void dump(std::ostream& stream, const T& value) {
        stream << value;
    }
};

/// @class to_stream<bool>
/// @brief dumper for bool printing "true" or "false"
template <>
struct to_stream<bool> final {
    static void dump(std::ostream& stream, const bool& value) {
        stream << (value ? "true" : "false");
    }
};

/// @class to_stream<unsigned char>
/// @brief solves the issue print the integer value instead of the character.
template <>
struct to_stream<unsigned char> final {
    static void dump(std::ostream& stream, const unsigned char& value) {
        stream << static_cast<uint32_t>(value);
    }
};

/// @class to_stream<std::vector<T>>
/// @brief dumper for std::vector<T> container
template <typename T>
struct to_stream<std::vector<T>> final {
    static void dump(std::ostream& stream, const std::vector<T>& container) {
        stream << "[";
        auto counter = 0;
        for (const auto& value: container) {
            if (counter > 0) {
                stream << ", ";
            }
            to_stream<T>::dump(stream, value);
            ++counter;
        }
        stream << "]";
    }
};

/// @class to_stream<std::list<T>>
/// @brief dumper for std::list<T> container
template <typename T>
struct to_stream<std::list<T>> final {
    static void dump(std::ostream& stream, const std::list<T>& container) {
        stream << "[";
        auto counter = 0;
        for (const auto& value: container) {
            if (counter > 0) {
                stream << ", ";
            }
            to_stream<T>::dump(stream, value);
            ++counter;
        }
        stream << "]";
    }
};

/// @class to_stream<std::set<T>>
/// @brief dumper for std::set<T> container
template <typename T>
struct to_stream<std::set<T>> final {
    static void dump(std::ostream& stream, const std::set<T>& container) {
        stream << "[";
        auto counter = 0;
        for (const auto& value: container) {
            if (counter > 0) {
                stream << ", ";
            }
            to_stream<T>::dump(stream, value);
            ++counter;
        }
        stream << "]";
    }
};

}  // namespace types

#endif  // INCLUDE_TYPES_TO_STREAM_H_
