///
/// @author  Thomas Lehmann
/// @file    test_select.cxx
/// @brief   testing of @ref query::select
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
#include <query/select.h>

#include <type_traits>

using namespace unittest;
using namespace matcher;

/// testing of class @ref unittest::suite
describe_suite("testing query::select", [](){
    describe_test("testing selector instance for std::vector", []() {
        const std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        auto selector = query::select(values);
        assert_that(std::size_t(10), is_equal(selector.size()));
    });

    describe_test("testing selector for filtering for std::vector", []() {
        const std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        auto results = query::select(values)
            .where([](int value) {return value % 2 == 0;})
            .to_vector();
        assert_that(std::vector<int>::size_type(5), is_equal(results.size()));
        const std::vector<int> exprected_values = {2, 4, 6, 8, 10};
        assert_that(true, is_equal(exprected_values == results));
    });

    describe_test("testing selector for filtering and count for std::vector", []() {
        const std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        auto count = query::select(values)
            .where([](int value) {return value % 2 == 0;})
            .count();
        assert_that(std::vector<int>::size_type(5), is_equal(count));
    });

    describe_test("testing selector for filtering and sum for std::vector", []() {
        const std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        auto sum = query::select(values)
            .where([](int value) {return value % 2 == 0;})
            .sum();
        assert_that(std::vector<int>::value_type(30), is_equal(sum));
    });

    describe_test("testing selector for filtering and min for std::vector", []() {
        const std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        auto min = query::select(values)
            .where([](int value) {return value % 2 == 0;})
            .min();
        assert_that(std::vector<int>::value_type(2), is_equal(min));
        
        assert_raise<std::range_error>("no elements", [values]() {
            query::select(values).where([](int value) {return 0 == value;}).min();
        });
    });

    describe_test("testing selector for filtering and max for std::vector", []() {
        const std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        auto max = query::select(values)
            .where([](int value) {return value % 2 == 0;})
            .max();
        assert_that(std::vector<int>::value_type(10), is_equal(max));
        
        assert_raise<std::range_error>("no elements", [values]() {
            query::select(values).where([](int value) {return 0 == value;}).max();
        });
    });

    describe_test("testing selector for two filtering for std::vector", []() {
        const std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        auto results = query::select(values)
            .where([](int value) {return value % 2 == 0;})
            .where([](int value) {return value % 4 != 0;})
            .to_vector();
        assert_that(std::vector<int>::size_type(3), is_equal(results.size()));
        const std::vector<int> exprected_values = {2, 6, 10};
        assert_that(true, is_equal(exprected_values == results));
    });

    describe_test("testing transform for std::vector", []() {
        const std::vector<int> values = {1, 2, 3, 4};
        auto results = query::select(values)
            .transform([](int& value){value *= 2;})
            .to_vector();
        const std::vector<int> exprected_values = {2, 4, 6, 8};
        assert_that(true, is_equal(exprected_values == results));
    });

    describe_test("testing double transform for std::vector", []() {
        const std::vector<int> values = {1, 2, 3, 4};
        auto results = query::select(values)
            .transform([](int& value){value *= 2;})
            .transform([](int& value){value += 1;})
            .to_vector();
        const std::vector<int> exprected_values = {3, 5, 7, 9};
        assert_that(true, is_equal(exprected_values == results));
    });

    describe_test("testing where+transform+sum for std::vector", []() {
        const std::vector<int> values = {1, 2, 3, 4};
        const auto result = query::select(values)
            .where([](int value){ return value % 2 == 0;})
            .transform([](int& value){value *= 10;})
            .sum();

        assert_that(std::vector<int>::value_type(60), is_equal(result));
    });

});
