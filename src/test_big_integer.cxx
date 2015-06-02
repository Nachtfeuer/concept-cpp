///
/// @author  Thomas Lehmann
/// @file    test_big_integer.cxx
/// @brief   testing of @ref math::big_integer
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
#include <math/big_integer.h>
#include <math/big_integer_sum.h>
#include <math/big_integer_multiplication.h>

using namespace unittest;
using namespace matcher;

/// testing of class @ref math::big_integer_sum
describe_suite("testing math::big_integer", [](){
    describe_test("testing defaults", []() {
        math::big_integer bi;
        assert_that(true, is_equal(bi.empty()));
        assert_that(math::digits_type::size_type(0), is_equal(bi.size()));
    });

    describe_test("testing init c'tor with digits_type", []() {
        math::big_integer bi = math::digits_type{4, 2, 0, 1};
        assert_that(false, is_equal(bi.empty()));
        assert_that(math::digits_type::size_type(4), is_equal(bi.size()));
    });

    describe_test("testing big_integer::to_string", []() {
        math::big_integer bi = math::digits_type{4, 2, 0, 1};
        assert_that(std::string("1024"), is_equal(bi.to_string()));
    });

    describe_test("testing output streaming", []() {
        math::big_integer bi = math::digits_type{4, 2, 0, 1};
        std::stringstream stream;
        stream << bi;
        assert_that(std::string("big_integer(1024)"), is_equal(stream.str()));
    });

    describe_test("testing adding a big integer", []() {
        // deleting possibly existing registrations
        math::big_integer::factory::get().clear();
        // registering just the default SUM implementation
        math::big_integer::factory::get().register_creator(
            int(math::big_integer_operation::SUM), []() {
                return std::unique_ptr<math::big_integer_calculate_interface>(new math::big_integer_sum);
            });

        math::big_integer bi = math::digits_type{4, 2, 0, 1};
        bi += bi;
        assert_that(std::string("2048"), is_equal(bi.to_string()));
    });

    describe_test("testing sum of two big integer", []() {
        // deleting possibly existing registrations
        math::big_integer::factory::get().clear();
        // registering just the default SUM implementation
        math::big_integer::factory::get().register_creator(
            int(math::big_integer_operation::SUM), []() {
                return std::unique_ptr<math::big_integer_calculate_interface>(new math::big_integer_sum);
            });

        const math::big_integer bia = math::digits_type{4, 2, 0, 1};
        const math::big_integer bib = math::digits_type{1, 0, 2, 4};
        assert_that(std::string("5225"), is_equal((bia+bib).to_string()));
    });

    describe_test("testing assigning a standard integer", []() {
        const math::big_integer bi = 1234567890;
        assert_that(std::string("1234567890"), is_equal(bi.to_string()));
    });

    describe_test("testing product of two big integer", []() {
        // deleting possibly existing registrations
        math::big_integer::factory::get().clear();
        // registering just the default SUM implementation
        math::big_integer::factory::get().register_creator(
            int(math::big_integer_operation::MULTIPLICATION), []() {
                return std::unique_ptr<math::big_integer_calculate_interface>(new math::big_integer_multiplication);
            });

        /// you can try this on command line (unix): echo "123456789 * 987654321"|bc
        const math::big_integer bia = 123456789;
        const math::big_integer bib = 987654321;
        assert_that(std::string("121932631112635269"), is_equal((bia*bib).to_string()));
    });
});

