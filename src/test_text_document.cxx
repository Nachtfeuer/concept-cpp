///
/// @author  Thomas Lehmann
/// @file    test_text_document.cxx
/// @brief   testing of @ref document::text_document
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
#include <document/text.h>

using namespace unittest;

/// testing of class @ref unittest::suite
describe_suite("testing document::text_document", [](){
    describe_test("testing simple word count", []() {
        document::text_document td1("hello world");
        assert_that(document::text_document::count_type(2), is_equal(td1.count_words()));
        document::text_document td2("it is a wonderful world");
        assert_that(document::text_document::count_type(5), is_equal(td2.count_words()));
        document::text_document td3("line1\nline2\nline3");
        assert_that(document::text_document::count_type(3), is_equal(td3.count_words()));
    });
});

