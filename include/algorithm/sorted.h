///
/// @author  Thomas Lehmann
/// @file    sorted.h
/// @brief   providing inline access to a sorted container.
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
#ifndef INCLUDE_SORTED_H_
#define INCLUDE_SORTED_H_

#include <algorithm>

namespace algorithm {

/// Providing sorted vector (copy of elements of original container type).
/// @param container potentially unsorted container (list, vector, ...)
/// @return sorted container
///
/// @code
/// const std::vector<int> values = {9, 6, 8, 2, 7, 3, 5};
/// for (const auto& value: sorted(values)) {
///     std::cout << value << std::endl;
/// }
/// @endcode
template <class T>
std::vector<typename T::value_type> sorted(const T& container) {
    std::vector<typename T::value_type> sorted_container(container.begin(), container.end());
    std::sort(sorted_container.begin(), sorted_container.end());
    return sorted_container;
}

} // namespace algorithm

#endif  // INCLUDE_SORTED_H_
