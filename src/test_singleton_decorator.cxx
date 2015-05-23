///
/// @author  Thomas Lehmann
/// @file    test_singleton_decorator.cxx
/// @brief   testing of @ref pattern::singleton_decorator
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
#include <unittest/unittest.h>
#include <pattern/singleton_decorator.h>

using namespace unittest;
using namespace matcher;

/// testing of class @ref pattern::singleton_decorator
describe_suite("testing pattern::singleton_decorator", [](){
    describe_test("testing singleton instance", []() {
        auto& instance_a = pattern::singleton_decorator<int>::get();
        auto& instance_b = pattern::singleton_decorator<int>::get();
        assert_that(true, is_equal(&instance_a == &instance_b));

        instance_a = 10;
        assert_that(instance_a, is_equal(instance_b));
    });
});

