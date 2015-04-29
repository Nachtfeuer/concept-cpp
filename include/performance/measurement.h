///
/// @author  Thomas Lehmann
/// @file    measurement.h
/// @brief   about time measurement.
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

#ifndef INCLUDE_PERFORMANCE_MEASUREMENT_H_
#define INCLUDE_PERFORMANCE_MEASUREMENT_H_

#include <functional>
#include <chrono>

namespace performance {

/// @return duration by provided unit
/// @code
/// const auto duration = time::measure<std::milli>([]() {
///     std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(100));
/// });
/// @endcode
template <class TUnit>
inline double measure(std::function<void()> func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    return std::chrono::duration<double, TUnit>(
        std::chrono::high_resolution_clock::now() - start).count();
}

}  // namespace time

#endif  // INCLUDE_PERFORMANCE_MEASUREMENT_H_
