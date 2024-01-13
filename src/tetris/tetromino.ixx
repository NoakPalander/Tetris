module;

#include <fmt/format.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>
#include <array>

export module tetris:tetromino;

import :direction;
import :type;
import :color;
import :turn;
import :well;
import utils;

namespace tetris {
    export class Tetromino {
        constexpr static std::array ADJUSTMENTS{utils::Point{0, 1}, utils::Point{-1, 0}, utils::Point{0, -1}, utils::Point{1, 0}};
        utils::Modulo<int> index_;

        Type type_;
        std::vector<sf::RectangleShape> cells_;
        utils::Size<int> size_;

        [[nodiscard]]
        bool well_collision(std::vector<utils::Point<float>> const& points, Well const& well) const {
            return std::ranges::any_of(points, [&well, this](auto&& block) {
                return well.collides(sf::Rect<float>(
                    block.x,
                    block.y,
                    static_cast<float>(size_.width),
                    static_cast<float>(size_.height))
                );
            });
        }

        [[nodiscard]]
        bool wall_collision(std::vector<utils::Point<float>> const& points, float width, float height) const {
            return std::ranges::any_of(points,[=](utils::Point<float> p) {
                return (p.x < 0 || p.x >= width) || (p.y < 0 || p.y >= height);
            });
        }

        [[nodiscard]]
        bool valid_move(std::vector<utils::Point<float>> const& points, Well const& well, float width, float height) const {
            return !wall_collision(points, width, height) && !well_collision(points, well);
        }

        void rotate_cw(std::vector<utils::Point<float>>& cells) {
            if (type_ == Type::O) [[unlikely]]
                return;

            auto [center_x, center_y] = cells[1];
            if (type_ == Type::I) {
                center_x = cells[2].x;
                center_y = cells[2].y;
            }

            for (auto&& [x, y] : cells) {
                float const new_x = y - center_y;
                float const new_y = x - center_x;

                x = center_x - new_x;
                y = center_y + new_y;

                if (type_ == Type::I) {
                    utils::Point const offsets = ADJUSTMENTS[static_cast<std::size_t>(index_)];
                    x += static_cast<float>(offsets.x * size_.width);
                    y += static_cast<float>(offsets.y * size_.height);
                }
            }

            if (type_ == Type::I) {
                ++index_;
            }
        }

        void rotate_ccw(std::vector<utils::Point<float>>& cells) {
            if (type_ == Type::O) [[unlikely]]
                return;

            auto [center_x, center_y] = cells[1];
            for (auto&& [x, y] : cells) {
                float const new_x = y - center_y;
                float const new_y = x - center_x;

                x = center_x + new_x;
                y = center_y - new_y;

                if (type_ == Type::I) {
                    utils::Point const offsets = ADJUSTMENTS[static_cast<std::size_t>(index_)];
                    x += static_cast<float>(offsets.x * size_.width);
                    y += static_cast<float>(offsets.y * size_.height);
                }
            }

            if (type_ == Type::I) {
                --index_;
            }
        }

        // Sets the positions of the cells to the points
        void set_positions(std::vector<utils::Point<float>> const& points) {
            assert(points.size() == cells_.size());

            for (std::size_t i = 0; i < points.size(); ++i) {
                cells_[i].setPosition(points[i].x, points[i].y);
            }
        }

    public:
        explicit Tetromino(Type type, utils::Size<int> size, utils::Point<float> initial = {0, 0})
            : index_{0, ADJUSTMENTS.size()}, type_{type}, size_{size}
        {
            cells_.reserve(CELL_COUNT);
            for (auto[x, y] : TYPE_MAP.at(type)) {

                sf::RectangleShape shape;
                shape.setPosition(
                    static_cast<float>(x) * static_cast<float>(size_.width) + initial.x,
                    static_cast<float>(y) * static_cast<float>(size_.height) + initial.y
                );

                shape.setSize({static_cast<float>(size_.width), static_cast<float>(size_.height)});
                shape.setFillColor(sf::Color(std::to_underlying(COLOR_MAP.at(type))));
                shape.setOutlineColor(sf::Color::Black);
                cells_.emplace_back(std::move(shape));
            }
        }

        void set_position(utils::Point<float> p) {
            for (auto&& cell : cells_) {
                auto [x, y] = cell.getPosition();
                cell.setPosition(x + p.x, y + p.y);
            }
        }

        [[nodiscard]] std::vector<sf::RectangleShape> const& blocks() const {
            return cells_;
        }

        bool move(Direction direction, Well const& well, int screen_width, int screen_height) {
            std::vector<utils::Point<float>> new_points;
            std::ranges::transform(cells_, std::back_inserter(new_points), [this, direction](auto&& cell){
                auto [x, y] = cell.getPosition();
                switch (direction) {
                    case Direction::LEFT:
                        return utils::Point{x - size_.width, y};

                    case Direction::RIGHT:
                        return utils::Point{x + size_.width, y};

                    case Direction::UP:
                        return utils::Point{x, y - size_.height};

                    case Direction::DOWN:
                        return utils::Point{x, y + size_.height};

                    default:
                        std::unreachable();
                }
            });

            if (valid_move(new_points, well, static_cast<float>(screen_width), static_cast<float>(screen_height))) {
                set_positions(new_points);
                return true;
            }

            return false;
        }

        void rotate(Turn turn) {
            // Rotations on O-shapes is a noop
            if (type_ == Type::O) [[unlikely]]
                return;

            std::vector<utils::Point<float>> points;
            std::ranges::transform(cells_, std::back_inserter(points), [](auto&& cell) {
                return utils::Point{cell.getPosition().x, cell.getPosition().y};
            });

            if (turn == Turn::CLOCKWISE) {
                // TODO: validate / wall-kick / try next center
                rotate_cw(points);
                set_positions(points);
            }
            else {
                rotate_ccw(points);
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
