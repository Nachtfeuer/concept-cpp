///
/// @author  Thomas Lehmann
/// @file    test_has_item_matcher.cxx
/// @brief   testing of @ref unittest::has_item_matcher
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
describe_suite("testing unittest::has_item_matcher", [](){
    describe_test("testing container to have a certain item in std::vector", []() {
        const has_item_matcher<std::vector<int>> matcher(5);

        const std::vector<int> values_a = {1, 3, 5, 7, 9};
        assert_that(true, is_equal(matcher.check(values_a)));

        const std::vector<int> values_b = {2, 4, 6, 8, 10};
        assert_that(false, is_equal(matcher.check(values_b)));
    });

    describe_test("testing container to have a certain item in std::set", []() {
        const has_item_matcher<std::set<int>> matcher(5);

        const std::set<int> values_a = {1, 3, 5, 7, 9};
        assert_that(true, is_equal(matcher.check(values_a)));

        const std::set<int> values_b = {2, 4, 6, 8, 10};
        assert_that(false, is_equal(matcher.check(values_b)));
    });

    describe_test("testing has item matcher expression for std::vector", []() {
        const has_item_matcher<std::vector<int>> matcher(5);
        assert_that(std::string("has_item(5)"), is_equal(matcher.get_expression()));
    });
});

