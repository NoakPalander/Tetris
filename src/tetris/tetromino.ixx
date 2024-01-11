module;

#include <fmt/format.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

export module tetris:tetromino;

import :direction;
import :type;
import :turn;
import :color;

namespace tetris {
    export {
        class Tetromino {
            static constexpr int WIDTH = 18;
            static constexpr int HEIGHT = 18;

            Type type_;
            std::vector<sf::Sprite> cells_;

            // Validates all points to be inside the board
            static bool valid_positions(std::vector<Point<float>> const& points, float width, float height) {
                return std::ranges::all_of(points, [=](Point<float> p) {
                    return (p.x >= 0 && p.x < width - WIDTH) && (p.y >= 0 && p.y < height - HEIGHT);
                });
            }

            // ReSharper disable once CppParameterMayBeConstPtrOrRef
            static void rotate_cw(std::vector<Point<float>>& cells, float center_x, float center_y) {
                for (auto&& [x, y] : cells) {
                    float const new_x = y - center_y;
                    float const new_y = x - center_x;

                    x = center_x - new_x;
                    y = center_y + new_y;
                }
            }

            // ReSharper disable once CppParameterMayBeConstPtrOrRef
            static void rotate_ccw(std::vector<Point<float>>& cells, float center_x, float center_y) {
                for (auto&& [x, y] : cells) {
                    float const new_x = y - center_y;
                    float const new_y = x - center_x;

                    x = center_x + new_x;
                    y = center_y - new_y;
                }
            }

            // Sets the positions of the cells to the points
            void set_positions(std::vector<Point<float>> const& points) {
                assert(points.size() == cells_.size());

                for (std::size_t i = 0; i < points.size(); ++i) {
                    cells_[i].setPosition(points[i].x, points[i].y);
                }
            }

        public:
            explicit Tetromino(Type type, sf::Texture const& texture, Point<float> initial = {0, 0}) : type_{type} {
                cells_.reserve(CELL_COUNT);
                int const x_offset = static_cast<int>(COLOR_MAP.at(type)) * WIDTH;

                for (auto[x, y] : TYPE_MAP.at(type)) {
                    sf::Sprite sprite(texture);
                    sprite.setTextureRect(sf::IntRect(x_offset, 0, WIDTH, HEIGHT));
                    sprite.setPosition(static_cast<float>(x) * WIDTH + initial.x, static_cast<float>(y) * HEIGHT + initial.y);

                    cells_.emplace_back(std::move(sprite));
                }
            }

            void set_position(Point<float> p) {
                for (auto&& cell : cells_) {
                    auto [x, y] = cell.getPosition();
                    cell.setPosition(x + p.x, y + p.y);
                }
            }

            void move(Direction direction, int screen_width, int screen_height) {
                auto next_position = [direction](sf::Sprite const& cell) {
                    auto [x, y] = cell.getPosition();
                    switch (direction) {
                        case Direction::LEFT:
                            return Point{x - WIDTH, y};

                        case Direction::RIGHT:
                            return Point{x + WIDTH, y};

                        case Direction::UP:
                            return Point{x, y - HEIGHT};

                        case Direction::DOWN:
                            return Point{x, y + HEIGHT};

                        default:
                            std::unreachable();
                    }
                };

                std::vector<Point<float>> new_points;
                for (auto const& cell : cells_) {
                    new_points.emplace_back(next_position(cell));
                }

                if (valid_positions(new_points, static_cast<float>(screen_width), static_cast<float>(screen_height))) {
                    set_positions(new_points);
                }
            }

            void rotate(Turn turn) {
                // Rotations on O-shapes is a noop
                if (type_ == Type::O) [[unlikely]]
                    return;

                std::vector<Point<float>> points;
                std::ranges::transform(cells_, std::back_inserter(points), [](auto&& cell) {
                    return Point{cell.getPosition().x, cell.getPosition().y};
                });

                if (turn == Turn::CLOCKWISE) {
                    // TODO: validate / wall-kick / try next center
                    rotate_cw(points, points[1].x, points[1].y);
                    set_positions(points);
                }
                else {
                    rotate_ccw(points, points[1].x, points[1].y);
                    set_positions(points);
                }
            }

            void render(sf::RenderWindow& window) const {
                for (auto&& cell : cells_) {
                    window.draw(cell);
                }
            }
        };
    }
}