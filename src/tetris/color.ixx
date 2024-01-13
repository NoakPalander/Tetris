module;

#include <fmt/format.h>
#include <utility>
#include <string>

export module tetris:color;

import :type;
import utils;

export namespace tetris {
    enum class Color : std::uint32_t {
        BLUE   = 0x00'00'FF'FF,
        PURPLE = 0x80'00'80'FF,
        RED    = 0xFF'00'00'FF,
        GREEN  = 0x00'FF'00'FF,
        YELLOW = 0xFF'FF'00'FF,
        CYAN   = 0x00'FF'FF'FF,
        ORANGE = 0xFF'7F'00'FF,
        GRAY   = 0x7F'7F'7F'FF,
    };

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
struct fmt::formatter<tetris::Color> : formatter<std::string> {
    auto format(tetris::Color color, format_context& ctx) const {
        using namespace std::string_literals;
        using tetris::Color;
        std::string const str = [color] {
            switch (color) {
                case Color::BLUE:
                    return "blue"s;

                case Color::PURPLE:
                    return "purple"s;

                case Color::RED:
                    return "red"s;

                case Color::GREEN:
                    return "green"s;

                case Color::YELLOW:
                    return "yellow"s;

                case Color::CYAN:
                    return "cyan"s;

                case Color::ORANGE:
                    return "orange"s;

                default:
                    return fmt::format("{}", std::to_underlying(color));
            }
        }();

        return formatter<std::string>::format(str, ctx);
    }
};