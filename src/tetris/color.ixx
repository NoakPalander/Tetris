module;

#include <fmt/format.h>
#include <utility>
#include <string_view>

export module tetris:color;

import :type;
import utils;

export namespace tetris {
    enum class Color { BLUE, PURPLE, RED, GREEN, YELLOW, CYAN, ORANGE };

    constexpr utils::Map<Type, Color, TYPE_COUNT> COLOR_MAP {
        std::pair{Type::I, Color::CYAN},
        std::pair{Type::O, Color::YELLOW},
        std::pair{Type::T, Color::PURPLE},
        std::pair{Type::L, Color::ORANGE},
        std::pair{Type::J, Color::BLUE},
        std::pair{Type::S, Color::GREEN},
        std::pair{Type::Z, Color::RED}
    };
}

export template<>
struct fmt::formatter<tetris::Color> : formatter<std::string_view> {
    auto format(tetris::Color color, format_context& ctx) const {
        using tetris::Color;
        std::string_view const str = [color] {
            switch (color) {
                case Color::BLUE:
                    return "blue";

                case Color::PURPLE:
                    return "purple";

                case Color::RED:
                    return "red";

                case Color::GREEN:
                    return "green";

                case Color::YELLOW:
                    return "yellow";

                case Color::CYAN:
                    return "cyan";

                case Color::ORANGE:
                    return "orange";

                default:
                    std::unreachable();
            }
        }();

        return formatter<string_view>::format(str, ctx);
    }
};