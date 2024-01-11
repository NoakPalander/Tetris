module;

#include <functional>
#include <unordered_map>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>

export module tetris:events;

namespace tetris {
    export class Events {
        std::unordered_map<sf::Event::EventType, std::function<void(sf::Event const&)>> event_map_;

    public:
        Events() = default;
        explicit Events(std::unordered_map<sf::Event::EventType, std::function<void(sf::Event const&)>> map) : event_map_(std::move(map)) {}

        template<typename Func>
        void add(sf::Event::EventType type, Func&& f) {
            event_map_.emplace(type, std::forward<Func>(f));
        }

        void poll(sf::Window& window) {
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (auto callable = event_map_.find(event.type); callable != event_map_.end()) {
                    std::invoke(callable->second, event);
                }
            }
        }
    };
}