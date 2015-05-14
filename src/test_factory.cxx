///
/// @author  Thomas Lehmann
/// @file    test_factory.cxx
/// @brief   testing of @ref pattern::factory class.
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
#include <pattern/factory.h>

#include <vector>
#include <memory>

using namespace unittest;
using namespace matcher;
using namespace pattern;

/// testing of class @ref math::vector
describe_suite("testing pattern::factory", [](){
    const auto creator = []() { return std::unique_ptr<int>(new int(123)); };
    const auto second_creator = []() { return std::unique_ptr<int>(new int(456)); };

    describe_test("testing initial", []() {
        /// we cannot rely that the singelton does not contain yet registered entries
        factory<int, int>::get().clear();
        assert_that(true, is_equal(factory<int, int>::get().empty()));
        assert_that(factory<int, int>::creators_container_type::size_type(0),
                    is_equal(factory<int, int>::get().size()));
    });

    describe_test("testing registration", [creator]() {
        /// we cannot rely that the singelton does not contain yet registered entries
        factory<int, int>::get().clear();

        /// first registration should succeed
        assert_that(true, is_equal(factory<int, int>::get().register_creator(1, creator)));
        assert_that(false, is_equal(factory<int, int>::get().empty()));
        assert_that(factory<int, int>::creators_container_type::size_type(1),
                    is_equal(factory<int, int>::get().size()));

        // second registration with same key should fail
        assert_that(false, is_equal(factory<int, int>::get().register_creator(1, creator)));
        // should be still the same number of registrations
        assert_that(factory<int, int>::creators_container_type::size_type(1),
                    is_equal(factory<int, int>::get().size()));

        // negative test
        assert_that(false, is_equal(factory<int, int>::get().register_creator(123, nullptr)));
    });

    describe_test("testing instance creation", [creator]() {
        /// we cannot rely that the singelton does not contain yet registered entries
        factory<int, int>::get().clear();
        factory<int, int>::get().register_creator(1, creator);

        auto it = factory<int, int>::get().create_instance(1);
        assert_that(true, is_equal(nullptr != it));
        assert_that(*it, is_equal(123));

        it = factory<int, int>::get().create_instance(2);
        assert_that(true, is_equal(nullptr == it));
    });

    describe_test("testing iteration", [creator, second_creator]() {
        /// we cannot rely that the singelton does not contain yet registered entries
        factory<int, int>::get().clear();
        factory<int, int>::get().register_creator(1, creator);
        factory<int, int>::get().register_creator(2, second_creator);

        auto counter = 0;
        for (auto it : factory<int, int>::get()) {
            std::unique_ptr<int> value(it.second());

            if (1 == it.first) {
                assert_that(123, is_equal(*value));
                ++counter;
            } else if (2 == it.first) {
                assert_that(456, is_equal(*value));
                ++counter;
            }
        }

        assert_that(2, is_equal(counter));
    });
});
