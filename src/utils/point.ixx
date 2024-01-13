module;

#include <concepts>
#include <type_traits>
#include <compare>

export module utils:point;

namespace tetris::utils {
    export template <typename T> requires(std::integral<T> || std::floating_point<T>)
    struct Point {
        T x, y;

        constexpr auto operator<=>(Point const&) const noexcept = default;
    };

    template <typename T, typename U>
    Point(T, U) -> Point<std::common_type_t<T, U>>;
}