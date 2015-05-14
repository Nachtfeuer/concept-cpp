///
/// @author  Thomas Lehmann
/// @file    test_line.cxx
/// @brief   testing of @ref math::line class.
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
#include <math/line.h>

using namespace unittest;
using namespace matcher;

/// testing of class @ref math::line
describe_suite("testing math::line", [](){
    /// testing getter for default values
    describe_test("testing default", []() {
        const math::line l;

        assert_that(0.0, is_equal(l.get_location().get_x()));
        assert_that(0.0, is_equal(l.get_location().get_y()));
        assert_that(0.0, is_equal(l.get_direction().get_x()));
        assert_that(0.0, is_equal(l.get_direction().get_y()));
    });

    /// testing getter for init values
    describe_test("testing init", []() {
        const math::line l{math::vector{1.0, 2.0}, math::vector{3.0, 4.0}};

        assert_that(1.0, is_equal(l.get_location().get_x()));
        assert_that(2.0, is_equal(l.get_location().get_y()));
        assert_that(3.0, is_equal(l.get_direction().get_x()));
        assert_that(4.0, is_equal(l.get_direction().get_y()));
    });

    /// testing @ref math::line::length
    describe_test("testing line length", []() {
        const math::line l{math::vector{1.0, 2.0}, math::vector{3.0, 4.0}};
        assert_that(5.0, is_equal(l.length()));
    });

    /// testing writing a line to a stream
    describe_test("testing output streaming", []() {
        const math::line l{math::vector{1.0, 2.0}, math::vector{3.0, 4.0}};
        std::stringstream stream;
        stream << l;
        assert_that(std::string("line(vector(1, 2), vector(3, 4))"), is_equal(stream.str()));
    });

    describe_test("testing two lines to be equal", []() {
        const math::line l1{math::vector{1.0, 2.0}, math::vector{3.0, 4.0}};
        const math::line l2{math::vector{1.0, 2.0}, math::vector{3.0, 4.0}};
        const math::line l3{math::vector{4.0, 3.0}, math::vector{2.0, 1.0}};

        assert_that(l1, is_equal(l2));
        assert_that(l1, is_not(is_equal(l3)));
    });
});
