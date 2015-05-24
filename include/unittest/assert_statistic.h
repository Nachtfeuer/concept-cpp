///
/// @author  Thomas Lehmann
/// @file    assert_statistic.h
/// @brief   assert statistic (counters)
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
#ifndef INCLUDE_UNITTEST_ASSERT_STATISTIC_H_
#define INCLUDE_UNITTEST_ASSERT_STATISTIC_H_

#include <cstdint>

namespace unittest {

/// @struct assert_statistic
/// @brief global counter for success and failure
struct assert_statistic final {
    /// @return read/write access to success counter
    static uint64_t& get_succeeded() noexcept {
        static uint64_t counter = 0;
        return counter;
    }

    /// @return read/write access to failed counter
    static uint64_t& get_failed() noexcept {
        static uint64_t counter = 0;
        return counter;
    }

    /// @return total number of assert calls.
    static uint64_t total() noexcept {
        return get_succeeded() + get_failed();
    }
};

}  // namespace unittest

#endif  // INCLUDE_UNITTEST_ASSERT_STATISTIC_H_
