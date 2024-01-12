module;

#include <fmt/format.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

export module tetris:board;

namespace tetris::board {
    constexpr int ROWS = 20;
    constexpr int COLUMNS = 8;
    constexpr int CELL_SIZE = 18 * 2;

    export void render(sf::RenderWindow& window) {
        constexpr int LINE_COUNT = ROWS + COLUMNS;
        static std::vector<sf::RectangleShape> const lines = []{
            fmt::println("Sup!\n");

            std::vector<sf::RectangleShape> out;
            out.reserve(LINE_COUNT);

            for (int i = 1; i < COLUMNS + 2; ++i) {
                sf::RectangleShape line;
                line.setFillColor(sf::Color::Red);
                line.setSize(sf::Vector2f{1, ROWS * CELL_SIZE});
                line.setPosition(static_cast<float>(i * CELL_SIZE), 0);
                out.emplace_back(std::move(line));
            }

            for (int i = 1; i < ROWS; ++i) {
                sf::RectangleShape line;
                line.setFillColor(sf::Color::Red);
                line.setSize(sf::Vector2f{(COLUMNS + 2) * CELL_SIZE, 1});
                line.setPosition(0, static_cast<float>(i * CELL_SIZE));
                out.emplace_back(std::move(line));
            }

            return out;
        }();

        for (auto&& line : lines) {
            window.draw(line);
        }
    }
}