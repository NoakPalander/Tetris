module;

#include <fmt/format.h>
#include <SFML/Graphics/Texture.hpp>

#include <filesystem>
#include <vector>
#include <random>
#include <stdexcept>

export module tetris:bag;

import :tetromino;
import :type;
import utils;

namespace tetris {
    class Bag {
        std::vector<Tetromino> bag_;
        sf::Texture texture_;

        void fill() {
            // Tetris guarantees that no shape can occur more than once per 7 pieces
            for (int i = 0; i < TYPE_COUNT; ++i) {
                bag_.emplace_back(static_cast<Type>(i), utils::Size{18 * 2, 18 * 2});
            }

            thread_local std::random_device rd;
            thread_local std::mt19937 engine(rd());
            std::ranges::shuffle(bag_, engine);
        }

    public:
        explicit Bag(std::filesystem::path const& path) {
            if (!texture_.loadFromFile(path)) {
                throw std::invalid_argument(fmt::format("Couldn't find the texture {}", path.c_str()));
            }

            texture_.setSmooth(true);
            fill();
        }

        Tetromino next(utils::Point<float> p = {0, 0}) {
            if (bag_.empty()) {
                fill();
            }

            Tetromino tetromino = std::move(bag_.back());
            bag_.pop_back();

            tetromino.set_position(p);
            return tetromino;
        }
    };
}