module;

#include <fmt/format.h>

#include <utility>
#include <array>
#include <string_view>

export module tetris:type;

import utils;

export namespace tetris {
    constexpr int TYPE_COUNT = 7;
    constexpr int CELL_COUNT = 4;

    enum class Type { I, O, T, J, L, S, Z };

    template<typename T>
    struct Point {
        T x, y;

        constexpr auto operator<=>(Point const&) const noexcept = default;
    };

    template<typename T, typename U>
    Point(T, U) -> Point<std::common_type_t<T, U>>;

    constexpr utils::Map<Type, std::array<Point<int>, CELL_COUNT>, TYPE_COUNT> TYPE_MAP {
        std::pair{Type::I, std::array{Point{0, 0}, Point{1, 0}, Point{2, 0}, Point{3, 0}}},
        std::pair{Type::O, std::array{Point{0, 0}, Point{1, 0}, Point{0, 1}, Point{1, 1}}},
        std::pair{Type::T, std::array{Point{0, 1}, Point{1, 1}, Point{2, 1}, Point{1, 0}}},
        std::pair{Type::J, std::array{Point{1, 0}, Point{1, 1}, Point{1, 2}, Point{0, 2}}},
        std::pair{Type::L, std::array{Point{0, 0}, Point{0, 1}, Point{0, 2}, Point{1, 2}}},
        std::pair{Type::S, std::array{Point{0, 1}, Point{1, 1}, Point{1, 0}, Point{2, 0}}},
        std::pair{Type::Z, std::array{Point{0, 0}, Point{1, 0}, Point{1, 1}, Point{2, 1}}},
    };
}

export template<>
struct fmt::formatter<tetris::Type> : formatter<std::string_view> {
    auto format(tetris::Type type, format_context& ctx) const {
        using tetris::Type;
        std::string_view const str = [type] {
            switch (type) {
                case Type::I:
                    return "I";

                case Type::O:
                    return "O";

                case Type::T:
                    return "T";

                case Type::J:
                    return "J";

                case Type::L:
                    return "L";

                case Type::S:
                    return "S";

                case Type::Z:
                    return "Z";

                default:
                    std::unreachable();
            }
        }();

        return formatter<string_view>::format(str, ctx);
    }
};