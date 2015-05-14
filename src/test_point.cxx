///
/// @author  Thomas Lehmann
/// @file    test_point.cxx
/// @brief   testing of @ref math::point class.
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
#include <math/point.h>

using namespace unittest;
using namespace matcher;

/// testing of class @ref math::point
describe_suite("testing math::point", [](){
    /// testing @ref math::point::get_x and @ref math::point::get_y.
    describe_test("testing getter for x and y", []() {
        const math::point p = {1.0, 2.0};

        assert_that(1.0, is_equal(p.get_x()));
        assert_that(2.0, is_equal(p.get_y()));
    });

    /// testing comparison of two points
    describe_test("testing comparison", []() {
        const math::point p1 = {1.0, 2.0};
        const math::point p2 = {1.0, 2.0};
        const math::point p3 = {2.0, 3.0};

        assert_that(p1, is_equal(p2));
        assert_that(p1, is_not(is_equal(p3)));
    });

    /// testing @ref math::point::operator -
    describe_test("testing difference", []() {
        const math::point v1 = {1.0, 3.0};
        const math::point v2 = {3.0, 4.0};
        assert_that(v2 - v1, is_equal(math::vector(2.0, 1.0)));
    });

    describe_test("testing output streaming", []() {
        const math::point p = {1.0, 3.0};
        std::stringstream stream;
        stream << p;
        assert_that(std::string("point(1, 3)"), is_equal(stream.str()));
    });
});
