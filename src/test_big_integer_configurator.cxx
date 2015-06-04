///
/// @author  Thomas Lehmann
/// @file    test_big_integer_configurator.cxx
/// @brief   testing of @ref math::big_integer_configurator
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
#include <math/big_integer_configurator.h>

using namespace unittest;
using namespace matcher;

/// testing of class @ref math::big_integer_configurator
describe_suite("testing math::big_integer_configurator", [](){
    describe_test("testing configure all", []() {
        math::big_integer_configurator bic;
        bic.configure();

        const math::big_integer bi = math::big_integer(32) * math::big_integer(32)
                                   + math::big_integer(1024);
        assert_that(std::string("2048"), is_equal(bi.to_string()));
    });
});

