///
/// @author  Thomas Lehmann
/// @file    test_is_range_matcher.cxx
/// @brief   testing of @ref unittest::is_range_matcher
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

/// testing of class @ref unittest::is_range_matcher
describe_suite("testing unittest::is_range_matcher", [](){
    describe_test("testing range checking", []() {
        const is_range_matcher<int> matcher(0, 10);
        assert_that(true, is_equal(matcher.check(0)));   // lower bound of range
        assert_that(true, is_equal(matcher.check(5)));   // in the middle of the range
        assert_that(true, is_equal(matcher.check(10)));  // upper bound of range

        assert_that(false, is_equal(matcher.check(-1))); // below range
        assert_that(false, is_equal(matcher.check(11))); // above range
    });

    describe_test("testing range expression", []() {
        const is_range_matcher<int> matcher(0, 10);
        assert_that(std::string("is_range(0, 10)"), is_equal(matcher.get_expression()));
    });
});

