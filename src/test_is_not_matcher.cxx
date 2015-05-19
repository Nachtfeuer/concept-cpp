///
/// @author  Thomas Lehmann
/// @file    test_is_not_matcher.cxx
/// @brief   testing of @ref unittest::is_not_matcher
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

using namespace unittest;
using namespace matcher;

/// testing of class @ref unittest::suite
describe_suite("testing unittest::is_not_matcher", [](){
    describe_test("testing not equal (same value)", []() {
        const is_not_matcher<int> matcher_a(is_equal(123));
        assert_that(false, is_equal(matcher_a.check(123)));
    });

    describe_test("testing not equal (different value)", []() {
        const is_not_matcher<int> matcher_b(is_equal(123));
        assert_that(true, is_equal(matcher_b.check(321)));
    });

    describe_test("testing expression", []() {
        const is_not_matcher<int> matcher_c(is_equal(123));
        assert_that(std::string("is_not(is_equal(123))"), is_equal(matcher_c.get_expression()));
    });
});

