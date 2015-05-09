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

/// testing of class @ref unittest::suite
describe_suite("testing query::select", [](){
    describe_test("testing select types", []() {
        assert_that(true, is_equal(
            std::is_same<std::vector<int>,
                query::selector<int, std::vector<int>>::container_type>::value));
    });

    describe_test("testing selector instance for std::vector", []() {
        const std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        auto selector = query::select(values);
        assert_that(std::size_t(10), is_equal(selector.size()));
    });

    describe_test("testing selector for filtering for std::vector", []() {
        const std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        auto results = query::select(values)
            .where([](int value) {return value % 2 == 0;})
            .run();
        assert_that(std::vector<int>::size_type(5), is_equal(results.size()));
        const std::vector<int> exprected_values = {2, 4, 6, 8, 10};
        assert_that(true, is_equal(exprected_values == results));
    });

    describe_test("testing selector for two filtering for std::vector", []() {
        const std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        auto results = query::select(values)
            .where([](int value) {return value % 2 == 0;})
            .where([](int value) {return value % 4 != 0;})
            .run();
        assert_that(std::vector<int>::size_type(3), is_equal(results.size()));
        const std::vector<int> exprected_values = {2, 6, 10};
        assert_that(true, is_equal(exprected_values == results));
    });
});
