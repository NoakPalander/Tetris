# Module Tetris
What better way to explore C++20's named modules than with an old classic, in C++23.


# Requirements
Named modules, although from C++20, is a complex feature that has taken many years to implement for the major compiler vendors, thus this project requires some up to date tools.

- Clang >= 16, or a partially C++23 compliant compiler with named module support [Implementation Status](https://en.cppreference.com/w/cpp/compiler_support). 
- CMake >= 3.28

# Dependencies
The project uses the following dependencies:

- [fmtlib 10.1.1](https://github.com/fmtlib/fmt/tree/10.1.1)
- [SFML 2.6.1](https://github.com/SFML/SFML/tree/2.6.1)

Everything else is from the C++ stdlib, tested with GNU's libstdc++.

# Building
