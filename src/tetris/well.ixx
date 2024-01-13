module;

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

export module tetris:well;

import utils;

namespace tetris {
    export class Well {
        std::vector<sf::RectangleShape> blocks_;

    public:
        void add(std::vector<sf::RectangleShape> const& blocks) {
            blocks_.reserve(blocks.size());
            std::ranges::copy(blocks, std::back_inserter(blocks_));
        }

        [[nodiscard]] bool collides(sf::Rect<float> const& rect) const {
            return std::ranges::any_of(blocks_, [&rect](sf::RectangleShape const& block){
                //bool from_left = point.x >= block.getPosition().x;
                return block.getGlobalBounds().intersects(rect);
            });
        }

        void render(sf::RenderWindow& window) {
            for (auto&& block : blocks_) {
                window.draw(block);
            }
        }
    };
}