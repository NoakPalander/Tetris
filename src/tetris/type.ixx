module;

#include <fmt/format.h>

#include <utility>
#include <array>
#include <string_view>

export module tetris:type;

import utils;

namespace tetris {
    constexpr int TYPE_COUNT = 7;
    constexpr int CELL_COUNT = 4;

    export enum class Type { I, O, T, J, L, S, Z };

    export constexpr utils::Map<Type, std::array<utils::Point<int>, CELL_COUNT>, TYPE_COUNT> TYPE_MAP {
        std::pair{Type::I, std::array{utils::Point{0, 0}, utils::Point{1, 0}, utils::Point{2, 0}, utils::Point{3, 0}}},
        std::pair{Type::O, std::array{utils::Point{0, 0}, utils::Point{1, 0}, utils::Point{0, 1}, utils::Point{1, 1}}},
        std::pair{Type::T, std::array{utils::Point{0, 1}, utils::Point{1, 1}, utils::Point{2, 1}, utils::Point{1, 0}}},
        std::pair{Type::J, std::array{utils::Point{1, 0}, utils::Point{1, 1}, utils::Point{1, 2}, utils::Point{0, 2}}},
        std::pair{Type::L, std::array{utils::Point{0, 0}, utils::Point{0, 1}, utils::Point{0, 2}, utils::Point{1, 2}}},
        std::pair{Type::S, std::array{utils::Point{0, 1}, utils::Point{1, 1}, utils::Point{1, 0}, utils::Point{2, 0}}},
        std::pair{Type::Z, std::array{utils::Point{0, 0}, utils::Point{1, 0}, utils::Point{1, 1}, utils::Point{2, 1}}},
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