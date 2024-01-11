module;
#include <filesystem>

export module settings;

namespace tetris {
    export struct Settings {
        std::filesystem::path resources;
    };
}