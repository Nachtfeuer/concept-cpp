///
/// @author  Thomas Lehmann
/// @file    test_shuffled.cxx
/// @brief   testing of @ref algorithm::shuffled
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
#include <algorithm/shuffled.h>
#include <query/select.h>

#include <vector>
#include <list>
#include <set>

using namespace unittest;
using namespace matcher;

/// testing of class @ref unittest::suite
describe_suite("testing algorithm::shuffled", [](){
    describe_test("testing shuffled vector", []() {
        const std::vector<int> values = {1, 2, 2, 3, 4, 5, 6, 7, 7, 9, 10, 12, 20};
        const auto shuffled_values = algorithm::shuffled(values);
        // ensure that sorted shuffled vector is same as original
        const auto sorted_values = algorithm::sorted(shuffled_values);

        assert_that(shuffled_values, is_not(is_equal(sorted_values)));
        assert_that(sorted_values, is_equal(values));
    });

    describe_test("testing shuffled list", []() {
        const std::list<int> values = {1, 2, 2, 3, 4, 5, 6, 7, 7, 9, 10, 12, 20};
        const auto shuffled_values = algorithm::shuffled(values);
        // ensure that sorted shuffled vector is same as original
        const auto sorted_values = algorithm::sorted(shuffled_values);

        assert_that(shuffled_values, is_not(is_equal(sorted_values)));
        assert_that(sorted_values, is_equal(query::select(values).to_vector()));
    });

    describe_test("testing shuffled (ordered) set", []() {
        const std::set<int> values = {1, 2, 2, 3, 4, 5, 6, 7, 7, 9, 10, 12, 20};
        const auto shuffled_values = algorithm::shuffled(values);
        // ensure that sorted shuffled vector is same as original
        const auto sorted_values = algorithm::sorted(shuffled_values);

        assert_that(shuffled_values, is_not(is_equal(sorted_values)));
        assert_that(sorted_values, is_equal(query::select(values).to_vector()));
    });
});
