///
/// @author  Thomas Lehmann
/// @file    test_generator_select.cxx
/// @brief   testing of @ref generator::select
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
#include <generator/select.h>

#include <string>
#include <vector>
#include <set>
#include <type_traits>

using namespace unittest;
using namespace matcher;

/// testing of class @ref unittest::suite
describe_suite("testing generator::select", [](){
    describe_test("testing generator for ascending range", []() {
        const auto results = generator::select(1, 10, 1).to_vector();
        const std::vector<int> expected_values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        assert_that(expected_values, is_equal(results));
    });

    describe_test("testing generator for descending range", []() {
        const auto results = generator::select(10, 1, -1).to_vector();
        const std::vector<int> expected_values = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        assert_that(expected_values, is_equal(results));
    });

    describe_test("testing generator for even values (step=2)", []() {
        const auto results = generator::select(2, 10, 2).to_vector();
        const std::vector<int> expected_values = {2, 4, 6, 8, 10};
        assert_that(expected_values, is_equal(results));
    });

    describe_test("testing generator transform (to square values)", []() {
        const auto results = generator::select(1, 5, 1)
            .transform([](int& value){value = value*value;})
            .to_vector();
        const std::vector<int> expected_values = {1, 4, 9, 16, 25};
        assert_that(expected_values, is_equal(results));
    });

    describe_test("testing generator where clause (for odd values)", []() {
        const auto results = generator::select(1, 10, 1)
            .where([](int value) {return value % 2 != 0;})
            .to_vector();
        const std::vector<int> expected_values = {1, 3, 5, 7 , 9};
        assert_that(expected_values, is_equal(results));
    });

    describe_test("testing generator sum", []() {
        const auto result = generator::select(1, 10, 1).sum();
        assert_that(55, is_equal(result));
    });

    describe_test("testing generator average", []() {
        const auto result = generator::select(1, 10, 1).average();
        assert_that(5.5, is_equal(result));
    });

    describe_test("testing generator median", []() {
        // median of [1, 2, 3, 4, 5, 6, 7, 8, 9, 10] => (5+6)/2
        const auto result1 = generator::select(1, 10, 1).median();
        assert_that(5.5, is_equal(result1));
        // median of [2, 4, 6] => 4
        const auto result2 = generator::select(2, 6, 2).median();
        assert_that(4.0, is_equal(result2));
    });

    describe_test("testing generator for max", []() {
        auto max = generator::select(1, 10, 1).max();
        assert_that(std::vector<int>::value_type(10), is_equal(max));

        assert_raise<std::range_error>("no elements", []() {
            generator::select(1, 0, 1).max();
        });
    });

    describe_test("testing generator for min", []() {
        auto min = generator::select(1, 10, 1).min();
        assert_that(std::vector<int>::value_type(1), is_equal(min));

        assert_raise<std::range_error>("no elements", []() {
            generator::select(1, 0, 1).min();
        });
    });
});
