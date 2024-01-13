module;

#include <concepts>

export module utils:size;

namespace tetris::utils {
    export template<std::integral T>
    struct Size {
        T width;
        T height;

        constexpr auto operator<=>(Size const&) const noexcept = default;
    };

    template<std::integral T, std::integral U>
    Size(T, U) -> Size<std::common_type_t<T, U>>;
}