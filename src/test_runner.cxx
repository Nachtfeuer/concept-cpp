///
/// @author  Thomas Lehmann
/// @file    test_runner.cxx
/// @brief   testing of @ref unittest::runner
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

/// testing of class @ref unittest::runner
describe_suite("testing unittest::runner", [](){
    describe_test("testing singleton", []() {
        const auto& runner_a = runner::get();
        const auto& runner_b = runner::get();

        assert_that(&runner_a, is_equal(&runner_b));
    });

    describe_test("testing suite bad registration", []() {
        const auto number_of_registered_suites = runner::get().size();
        auto suite_function = []() {/* does nothing */};
        assert_that(false, is_equal(runner::get().register_suite("should not exist", nullptr)));
        assert_that(false, is_equal(runner::get().register_suite("", suite_function)));
        assert_that(number_of_registered_suites, is_equal(runner::get().size()));
    });

    describe_test("testing suite good registration", []() {
        const auto number_of_registered_suites = runner::get().size();
        auto suite_function = []() {/* does nothing */};
        // I'm pretty sure that I don't use "test suite" anywhere else ...
        assert_that(true, is_equal(runner::get().register_suite("test suite", suite_function)));
        assert_that(number_of_registered_suites+1, is_equal(runner::get().size()));
        assert_that(false, is_equal(runner::get().register_suite("test suite", suite_function)));
        assert_that(number_of_registered_suites+1, is_equal(runner::get().size()));
    });
});

