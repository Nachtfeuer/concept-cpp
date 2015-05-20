///
/// @author  Thomas Lehmann
/// @file    test_sorted.cxx
/// @brief   testing of @ref algorithm::sorted
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
#include <algorithm/sorted.h>
#include <vector>
#include <list>
#include <unordered_set>

using namespace unittest;
using namespace matcher;

/// testing of class @ref unittest::suite
describe_suite("testing algorithm::sorted", [](){
    describe_test("testing sorted vector", []() {
        const std::vector<int> values = {9, 2, 5, 1, 7, 6};
        const auto sorted_values = algorithm::sorted(values);
        const std::vector<int> expected_values = {1, 2, 5, 6, 7, 9};

        assert_that(expected_values, is_equal(sorted_values));
    });

    describe_test("testing sorted list", []() {
        const std::list<int> values = {9, 2, 5, 1, 7, 6};
        const auto sorted_values = algorithm::sorted(values);
        const std::vector<int> expected_values = {1, 2, 5, 6, 7, 9};

        assert_that(expected_values, is_equal(sorted_values));
    });

    describe_test("testing sorted unordered set", []() {
        const std::unordered_set<int> values = {9, 2, 5, 1, 7, 6};
        const auto sorted_values = algorithm::sorted(values);
        const std::vector<int> expected_values = {1, 2, 5, 6, 7, 9};

        assert_that(expected_values, is_equal(sorted_values));
    });
});

