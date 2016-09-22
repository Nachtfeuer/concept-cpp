///
/// @author  Thomas Lehmann
/// @file    factory.h
/// @brief   abstract factory.
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
#ifndef INCLUDE_PATTERN_FACTORY_H_
#define INCLUDE_PATTERN_FACTORY_H_

#include <functional>
#include <unordered_map>
#include <memory>

namespace pattern {

/// @class factory
/// @brief abstract factory.
template <typename TKey, typename TClass>
class factory final {
    public:
        /// type for creator function
        using creator_function_type = std::function<std::unique_ptr<TClass> ()>;
        /// type for container of registered creators
        using creators_container_type = std::unordered_map<TKey, creator_function_type>;

        /// providing singleton instance
        static factory& get() noexcept {
            static factory instance;
            return instance;
        }

        /// Does register a creator function for the given key.
        /// You cannot overwrite it by a second call for same key.
        ///
        /// @param  key unique key that may not exist
        /// @param  creator the creator function providing instance of type TClass (may not be nullptr)
        /// @return true when successful registered (unique key may not exist).
        bool register_creator(const TKey& key, creator_function_type creator) noexcept {
            if (nullptr == creator) {
                return false;
            }
            return m_creators.insert(typename creators_container_type::value_type(key, creator)).second;
        }

        /// @param key unique key that must exist.
        /// @return instance if creator for given key does exist and
        ///         if creator provides instance otherwise it's a nullptr.
        std::unique_ptr<TClass> create_instance(const TKey& key) const {
            auto it = m_creators.find(key);
            if (it == m_creators.end()) {
                return std::unique_ptr<TClass>(nullptr);
            }
            return it->second();
        }

        /// Checking whether given key does exist.
        ///
        /// @param key unique key that might exist
        /// return true when given key does exist.
        bool has_key(const TKey& key) const {
            return m_creators.find(key) != m_creators.end();
        }

        /// @return true when there is no registered creator.
        bool empty() const noexcept {
            return m_creators.empty();
        }

        /// @return number of registered creators.
        typename creators_container_type::size_type size() const noexcept {
            return m_creators.size();
        }

        /// @return first creator or end() if no creator has been registered.
        typename creators_container_type::const_iterator begin() const noexcept {
            return m_creators.begin();
        }

        /// @return end of container indicator.
        typename creators_container_type::const_iterator end() const noexcept {
            return m_creators.end();
        }

        /// remove all registered creator
        void clear() noexcept {
            m_creators.clear();
        }

    private:
        /// initializing fields only
        factory() : m_creators() {}

        /// container with registered creators
        creators_container_type m_creators;

        /// disable copy c'tor
        factory(factory&) = delete;
        /// disable assignment
        factory& operator = (const factory&) = delete;
};


}  // namespace pattern

#endif  // INCLUDE_PATTERN_FACTORY_H_
