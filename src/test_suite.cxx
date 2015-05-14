///
/// @author  Thomas Lehmann
/// @file    test_suite.cxx
/// @brief   testing of @ref unittest::suite class.
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
describe_suite("testing unittest::suite", [](){
    describe_test("testing initial", []() {
        /// we cannot rely that the singelton does not contain yet registered entries
        suite test_suite("test");
        assert_that(std::string("test"), is_equal(test_suite.get_name()));
        assert_that(true, is_equal(test_suite.empty()));
        assert_that(suite::container_type::size_type(0), is_equal(test_suite.size()));
    });

    describe_test("testing registration", []() {
        suite test_suite("test");
        assert_that(false, is_equal(test_suite.register_test("any", nullptr)));
        assert_that(true, is_equal(test_suite.empty()));
        assert_that(true, is_equal(test_suite.register_test("any", []() {/*does nothing*/})));
        assert_that(false, is_equal(test_suite.empty()));
        assert_that(suite::container_type::size_type(1), is_equal(test_suite.size()));
    });
});

