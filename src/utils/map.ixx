module;

#include <fmt/format.h>

#include <utility>
#include <array>
#include <algorithm>
#include <stdexcept>

export module utils:map;

namespace tetris::utils {
    export template<typename Key, typename Value, std::size_t N>
    struct Map {
        std::array<std::pair<Key, Value>, N> data;

        [[nodiscard]] constexpr std::size_t size() const noexcept {
            return N;
        }

        constexpr Value const& at(Key const& key) const {
            auto const at = std::find_if(data.begin(), data.end(), [&key](auto const& v) {
                return v.first == key;
            });

            if (at == data.end()) {
                throw std::out_of_range(fmt::format("Invalid key: {}\n", key));
            }

            return at->second;
        }
    };
}