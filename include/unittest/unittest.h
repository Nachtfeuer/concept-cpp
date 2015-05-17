///
/// @author  Thomas Lehmann
/// @file    unittest.h
/// @brief   providing unit test tools.
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
#ifndef INCLUDE_UNITTEST_H_
#define INCLUDE_UNITTEST_H_

#include <functional>
#include <string>
#include <cstdint>
#include <iostream>

#include <unittest/runner.h>
#include <unittest/assert.h>

#include <matcher/matcher.h>
#include <matcher/is_equal_matcher.h>
#include <matcher/is_not_matcher.h>
#include <matcher/is_range_matcher.h>
#include <matcher/has_item_matcher.h>

namespace unittest {

static void describe_test(const std::string& name, std::function<void()> test_function) {
    runner::get().register_test(name, test_function);
}

struct suite_proxy {
    suite_proxy(const std::string& name, std::function<void ()> suite_function) {
        runner::get().register_suite(name, suite_function);
    }
};

}  // namespace unittest

#define describe_suite \
    static suite_proxy suite_proxy_instance

#endif   // INCLUDE_UNITTEST_H_

