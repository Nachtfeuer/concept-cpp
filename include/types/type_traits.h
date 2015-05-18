///
/// @author  Thomas Lehmann
/// @file    type_traits.h
/// @brief   type things which seems not to be covered by STL.
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
#ifndef INCLUDE_TYPES_TYPE_TRAITS_H_
#define INCLUDE_TYPES_TYPE_TRAITS_H_

#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <unordered_set>

namespace types {

template <typename T>
struct is_container final {
    static constexpr bool value = false;
};

template <typename T>
struct is_container<std::vector<T>> final {
    static constexpr bool value = true;
};

template <typename T>
struct is_container<std::deque<T>> final {
    static constexpr bool value = true;
};

template <typename T>
struct is_container<std::list<T>> final {
    static constexpr bool value = true;
};

template <typename T>
struct is_container<std::queue<T>> final {
    static constexpr bool value = true;
};

template <typename T>
struct is_container<std::stack<T>> final {
    static constexpr bool value = true;
};

template <typename T>
struct is_container<std::set<T>> final {
    static constexpr bool value = true;
};

template <typename T>
struct is_container<std::unordered_set<T>> final {
    static constexpr bool value = true;
};

}  // namespace types

#endif  // INCLUDE_TYPES_TYPE_TRAITS_H_
