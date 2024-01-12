module;

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <filesystem>

export module tetris;

import :events;
import :tetromino;
import :direction;
import :bag;
import :type;
import :turn;
import :board;
import settings;

namespace tetris {
    export class Game {
        static constexpr int SCREEN_WIDTH = 180 * 2;
        static constexpr int SCREEN_HEIGHT = 360 * 2;

        Settings settings_;
        Bag bag_;
        Tetromino current_;
        Events events_;
        sf::RenderWindow window_;

    public:
        explicit Game(Settings settings)
            : settings_(std::move(settings)),
              bag_(settings_.resources / "tiles.png"),
              current_(bag_.next()),
              window_(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Tetris")
        {
            events_.add(sf::Event::Closed, [this]([[maybe_unused]] sf::Event const& event) { window_.close(); });
            events_.add(sf::Event::KeyPressed, [this](sf::Event const& event) {
                switch (event.key.code) {
                    case sf::Keyboard::Return:
                        current_ = bag_.next();
                        break;

                    case sf::Keyboard::F:
                        current_.rotate(Turn::COUNTER_CLOCKWISE);
                        break;

                    case sf::Keyboard::G:
                        current_.rotate(Turn::CLOCKWISE);
                        break;

                    case sf::Keyboard::Q:
                        window_.close();
                        break;

                    case sf::Keyboard::Left:
                    case sf::Keyboard::A:
                        current_.move(Direction::LEFT, SCREEN_WIDTH, SCREEN_HEIGHT);
                        break;

                    case sf::Keyboard::Right:
                    case sf::Keyboard::D:
                        current_.move(Direction::RIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
                        break;

                    case sf::Keyboard::Up:
                    case sf::Keyboard::W:
                        current_.move(Direction::UP, SCREEN_WIDTH, SCREEN_HEIGHT);
                        break;

                    case sf::Keyboard::Down:
                    case sf::Keyboard::S:
                        current_.move(Direction::DOWN, SCREEN_WIDTH, SCREEN_HEIGHT);
                        break;

                    default:
                        break;
                }
            });
        }

        void run() {
            while (window_.isOpen()) {
                events_.poll(window_);
                window_.clear(sf::Color::White);

                board::render(window_);
                current_.render(window_);
                window_.display();
            }
        }
    };
}