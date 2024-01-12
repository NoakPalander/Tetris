module;

#include <fmt/format.h>
#include <utility>
#include <string_view>


export module tetris:turn;

namespace tetris {
    export enum class Turn {
        CLOCKWISE,
        COUNTER_CLOCKWISE
    };
}

export template<>
struct fmt::formatter<tetris::Turn> : formatter<std::string_view> {
    auto format(tetris::Turn turn, format_context& ctx) const {
        using tetris::Turn;
        std::string_view const str = [turn] {
            switch (turn) {
                case Turn::CLOCKWISE:
                    return "cw";

                case Turn::COUNTER_CLOCKWISE:
                    return "ccw";

                default:
                    std::unreachable();
            }
        }();

        return formatter<string_view>::format(str, ctx);
    }
};