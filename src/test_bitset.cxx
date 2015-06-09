///
/// @author  Thomas Lehmann
/// @file    test_bitset.cxx
/// @brief   testing of @ref types::bitset
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
#include <types/bitset.h>
#include <cstdint>

using namespace unittest;
using namespace matcher;

/// testing of class @ref types::bitset
describe_suite("testing types::bitset", [](){
    describe_test("testing default, 8 bits per bucket, check bucket (one bucket)", []() {
        constexpr auto max_n = 8;
        const types::bitset<unsigned char> bs(max_n);
        assert_that(8, is_equal(static_cast<int>(types::bitset<unsigned char>::BITS_PER_BUCKET)));
        assert_that(types::bitset<unsigned char>::size_type(1), is_equal(bs.buckets()));
        assert_that(types::bitset<unsigned char>::size_type(8), is_equal(bs.size()));
    });

    describe_test("testing default, 16 bits per bucket, check bucket (one bucket)", []() {
        constexpr auto max_n = 16;
        const types::bitset<unsigned short> bs(max_n);
        assert_that(16, is_equal(static_cast<int>(types::bitset<unsigned short>::BITS_PER_BUCKET)));
        assert_that(types::bitset<unsigned short>::size_type(1), is_equal(bs.buckets()));
        assert_that(types::bitset<unsigned short>::size_type(16), is_equal(bs.size()));
    });

    describe_test("testing default, 32 bits per bucket, check bucket (one bucket)", []() {
        constexpr auto max_n = 32;
        const types::bitset<uint32_t> bs(max_n);
        assert_that(32, is_equal(static_cast<int>(types::bitset<uint32_t>::BITS_PER_BUCKET)));
        assert_that(types::bitset<uint32_t>::size_type(1), is_equal(bs.buckets()));
        assert_that(types::bitset<uint32_t>::size_type(32), is_equal(bs.size()));
    });

    describe_test("testing default, 8 bits per bucket, nothing set, dump (one bucket)", []() {
        constexpr auto max_n = 8;
        const types::bitset<unsigned char> bs(max_n);
        assert_that(std::string("00000000"), is_equal(bs.to_string()));
    });

    describe_test("testing default, 16 bits per bucket, nothing set, dump (one bucket)", []() {
        constexpr auto max_n = 16;
        const types::bitset<unsigned short> bs(max_n);
        assert_that(std::string("0000000000000000"), is_equal(bs.to_string()));
    });

    describe_test("testing default, 32 bits per bucket, nothing set, dump (one bucket)", []() {
        constexpr auto max_n = 32;
        const types::bitset<uint32_t> bs(max_n);
        assert_that(std::string("00000000000000000000000000000000"), is_equal(bs.to_string()));
    });

    describe_test("testing default, 8 bits per bucket, all set, dump (one bucket)", []() {
        constexpr auto max_n = 8;
        const types::bitset<unsigned char> bs(max_n, true);
        assert_that(std::string("11111111"), is_equal(bs.to_string()));
    });

    describe_test("testing default, 16 bits per bucket, all set, dump (one bucket)", []() {
        constexpr auto max_n = 16;
        const types::bitset<unsigned short> bs(max_n, true);
        assert_that(std::string("1111111111111111"), is_equal(bs.to_string()));
    });

    describe_test("testing default, 32 bits per bucket, all set, dump (one bucket)", []() {
        constexpr auto max_n = 32;
        const types::bitset<uint32_t> bs(max_n, true);
        assert_that(std::string("11111111111111111111111111111111"), is_equal(bs.to_string()));
    });

    describe_test("testing default, 8 bits per bucket, set some bits (one bucket)", []() {
        constexpr auto max_n = 8;
        types::bitset<unsigned char> bs(max_n, true);

        bs[1] = false; // set first bit of bucket
        bs[8] = false; // set last bit of bucket
        assert_that(std::string("01111110"), is_equal(bs.to_string()));
    });

    describe_test("testing default, 16 bits per bucket, set some bits (one bucket)", []() {
        constexpr auto max_n = 16;
        types::bitset<unsigned short> bs(max_n, true);

        bs[1]  = false; // set first bit of bucket
        bs[16] = false; // set last bit of bucket
        assert_that(std::string("0111111111111110"), is_equal(bs.to_string()));
    });

    describe_test("testing default, 32 bits per bucket, set some bits (one bucket)", []() {
        constexpr auto max_n = 32;
        types::bitset<uint32_t> bs(max_n, true);

        bs[1]  = false; // set first bit of bucket
        bs[32] = false; // set last bit of bucket
        assert_that(std::string("01111111111111111111111111111110"), is_equal(bs.to_string()));
    });

    describe_test("testing default, 8 bits per bucket, set some bits (two buckets)", []() {
        constexpr auto max_n = 16;
        types::bitset<unsigned char> bs(max_n, true);

        bs[1] = false;  // set first bit of first bucket
        bs[8] = false;  // set last bit of first bucket
        bs[9] = false;  // set first bit of second bucket
        bs[16] = false; // set last bit of second bucket
        assert_that(std::string("0111111001111110"), is_equal(bs.to_string()));
    });

    describe_test("testing default, 16 bits per bucket, set some bits (two buckets)", []() {
        constexpr auto max_n = 32;
        types::bitset<unsigned short> bs(max_n, true);

        bs[1]  = false;  // set first bit of first bucket
        bs[16] = false;  // set last bit of first bucket
        bs[17] = false;  // set first bit of second bucket
        bs[32] = false; // set last bit of second bucket
        assert_that(std::string("01111111111111100111111111111110"), is_equal(bs.to_string()));
    });

    describe_test("testing default, 32 bits per bucket, set some bits (two buckets)", []() {
        constexpr auto max_n = 64;
        types::bitset<unsigned short> bs(max_n, true);

        bs[1]  = false; // set first bit of first bucket
        bs[32] = false; // set last bit of first bucket
        bs[33] = false; // set first bit of second bucket
        bs[64] = false; // set last bit of second bucket
        assert_that(std::string("0111111111111111111111111111111001111111111111111111111111111110"),
                    is_equal(bs.to_string()));
    });
});
