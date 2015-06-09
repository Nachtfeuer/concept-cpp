///
/// @author  Thomas Lehmann
/// @file    bitset.h
/// @brief
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
#ifndef INCLUDE_TYPES_BITSET_H_
#define INCLUDE_TYPES_BITSET_H_

#include <stdexcept>
#include <memory>
#include <type_traits>
#include <limits>
#include <string>
#include <sstream>

#include <cstdint>
#include <cstring>

namespace types {

/// @class bitset
template <typename T>
class bitset final {
    public:
        /// value type of container
        using value_type = T;
        /// size type for container
        using size_type = uint64_t;
        /// number of bytes per bucket
        enum {BYTES_PER_BUCKET = sizeof(value_type)};
        /// number of bits per bucket 
        enum {BITS_PER_BUCKET = BYTES_PER_BUCKET * 8};

        /// creating a bit set with as many bits aligned to byte
        bitset(const size_type number_of_bits, const bool flag = false)
            : m_number_of_bits(number_of_bits), m_buckets(nullptr) {
            if (number_of_bits == 0) {
                throw std::runtime_error("You cannot have a bitset with no bits");
            }

            m_buckets.reset(new value_type[size()]);
            const value_type all_set = std::numeric_limits<value_type>::max();
            std::fill(m_buckets.get(), m_buckets.get() + buckets() + 1, flag? all_set: 0);
        }

        /// @class proxy
        class bit final {
            public:
                /// init c'tor.
                /// @param bucket for some bits depending on the type
                /// @param nth_bit the n'th bit to set
                bit(value_type* bucket, const size_type nth_bit)
                    : m_bucket(bucket), m_bit_mask(static_cast<value_type>(1) << nth_bit) {}

                /// @return true when bit is set
                inline operator bool() const noexcept {
                    return *m_bucket & m_bit_mask;
                }

                /// Does set or remove bit depending on parameter
                /// @return itself for further operations
                inline const bit& operator = (const bool set_bit) noexcept {
                    if (set_bit) {
                        *m_bucket |= m_bit_mask;
                    } else {
                        *m_bucket &= ~m_bit_mask;
                    }
                    return *this;
                }

            protected:
                /// the bucket where to set or remove the bit
                value_type* m_bucket;
                /// nth bit to set or remove
                size_type m_bit_mask;
        };

        /// @return bit (proxy) for read only access
        inline typename std::add_const<bit>::type operator [](const size_type nth) const {
            return typename std::add_const<bit>::type(&m_buckets[nth/BITS_PER_BUCKET], nth % BITS_PER_BUCKET);
        }

        /// @return bit (proxy) for read and write access.
        inline bit operator [](const size_type nth) {
            return bit(&m_buckets[nth/BITS_PER_BUCKET], nth % BITS_PER_BUCKET);
        }

        /// @return number of buckets
        inline size_type buckets() const noexcept {
            return m_number_of_bits / BITS_PER_BUCKET
                + ((m_number_of_bits % BITS_PER_BUCKET > 0)? 1: 0);
        }

        /// @return number of bits
        inline size_type size() const noexcept {
            return m_number_of_bits;
        }

        /// @return bitset as string with "0"'s and "1"'s
        std::string to_string() const noexcept {
            std::stringstream stream;

            for (auto nth_bit = m_number_of_bits; nth_bit > 0; --nth_bit) {
                if ((*this)[nth_bit]) {
                    stream << "1";
                } else {
                    stream << "0";
                }
            }

            return stream.str();
        }

    private:
        /// number of bits that can be set in this "container"
        size_type m_number_of_bits;
        /// container of buckets
        std::unique_ptr<value_type[]> m_buckets;
};

}  // namespace types

#endif  // INCLUDE_TYPES_BITSET_H_
