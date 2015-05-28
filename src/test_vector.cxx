///
/// @author  Thomas Lehmann
/// @file    test_vector.cxx
/// @brief   testing of @ref math::vector class.
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
#include <math/vector.h>

using namespace unittest;
using namespace matcher;

/// testing of class @ref math::vector
describe_suite("testing math::vector", [](){
    /// testing @ref math::vector::get_x and @ref math::vector::get_y.
    describe_test("testing getter for x and y", []() {
        const math::vector v = {1.0, 2.0};

        assert_that(1.0, is_equal(v.get_x()));
        assert_that(2.0, is_equal(v.get_y()));
    });

    /// testing @ref math::vector::operator + and @ref math::vector::operator -.
    describe_test("testing comparison", []() {
        const math::vector v1 = {1.0, 2.0};
        const math::vector v2 = {1.0, 2.0};
        const math::vector v3 = {2.0, 3.0};

        assert_that(v1, is_equal(v2));
        assert_that(v1, is_not(is_equal(v3)));
    });

    /// testing @ref math::vector::length
    describe_test("testing length", []() {
        const math::vector v1 = {3.0, 4.0};
        assert_that(5.0, is_equal(v1.length()));
    });

    /// testing of @ref math::vector::scalar_product
    describe_test("testing scalar product", []() {
        const math::vector v1 = {3.0, 4.0};
        assert_that(25.0, is_equal(v1.scalar_product(v1)));
    });

    /// testing of @ref math::vector::right_vertical
    describe_test("testing vector rotated by 90 degree to the right", []() {
        const math::vector v1 = {0.0, 1.0};
        const math::vector v2 = {1.0, 1.0};

        assert_that(math::vector(1.0, 0.0), is_equal(v1.right_vertical()));
        assert_that(math::vector(1.0, -1.0), is_equal(v2.right_vertical()));
    });

    /// testing of @ref math::vector::left_vertical
    describe_test("testing vector rotated by 90 degree to the left", []() {
        const math::vector v1 = {1.0, 0.0};
        const math::vector v2 = {1.0, -1.0};

        assert_that(math::vector(0.0, 1.0), is_equal(v1.left_vertical()));
        assert_that(math::vector(1.0, 1.0), is_equal(v2.left_vertical()));
    });

    describe_test("testing normed vector", []() {
        math::vector v1 = {3.0, 4.0};
        assert_that(math::vector(0.6, 0.8), is_equal(v1.normed()));
    });

    describe_test("testing angle between two vectors", []() {
        const math::vector v1 = {0.0, 1.0};
        const math::vector v2 = {1.0, 0.0};
        const math::vector v3 = {1.0, 1.0};

        assert_that(fabs(90.0 - v1.angle(v2)) < 1e-10, is_equal(true));
        assert_that(fabs(45.0 - v1.angle(v3)) < 1e-10, is_equal(true));
    });

    /// testing @ref math::vector::operator -
    describe_test("testing difference", []() {
        const math::vector v1 = {1.0, 3.0};
        const math::vector v2 = {3.0, 4.0};
        assert_that(v2 - v1, is_equal(math::vector(2.0, 1.0)));
    });

    /// testing @ref math::vector::operator +
    describe_test("testing sum", []() {
        const math::vector v1 = {1.0, 3.0};
        const math::vector v2 = {3.0, 4.0};
        assert_that(v1 + v2, is_equal(math::vector(4.0, 7.0)));
    });

    /// testing @ref math::vector::scaled.
    describe_test("testing scaled vector", []() {
        assert_that(math::vector(6, 4), is_equal(math::vector(1.5, 1).scaled(4)));
        assert_that(math::vector(3, 2), is_equal(math::vector(9, 6).scaled(1.0/3.0)));
    });

    describe_test("testing output streaming", []() {
        const math::vector v1 = {1.0, 3.0};
        std::stringstream stream;
        stream << v1;
        assert_that(std::string("vector(1, 3)"), is_equal(stream.str()));
    });
});
