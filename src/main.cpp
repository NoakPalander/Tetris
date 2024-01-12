import settings;
import tetris;

#include <fmt/format.h>
#include <filesystem>

int main() {
    try {
        tetris::Game game({
            .resources = std::filesystem::current_path().parent_path().parent_path() / "rsc"
        });

        game.run();
    }
    catch (std::exception& e) {
        fmt::println(::stderr, "Failed to run the game, reason: {}", e.what());
    }
    catch (...) {
        fmt::println(::stderr, "Unknown error launching the game");
    }
}