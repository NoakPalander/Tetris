module;

#include <fmt/format.h>
#include <string_view>
#include <concepts>
#include <cmath>
#include <numeric>
#include <stdexcept>

export module utils:modulo;

namespace tetris::utils {
    export template<std::signed_integral T>
    class Modulo {
        int class_;
        T number_;

        constexpr T mod(T number) const {
            auto result = number % class_;
            return (number >= 0) ? result : result + std::abs(class_);
        }

    public:
        constexpr explicit Modulo(T number, int mod_class) {
            if (mod_class == 0) {
                throw std::invalid_argument("Modulo class zero doesn't exist");
            }
            else if (mod_class < 0) {
                throw std::invalid_argument("Negative modulo classes don't exist");
            }

            class_ = mod_class;
            number_ = mod(number);
        }

        template<typename U>
        [[nodiscard]] constexpr explicit operator U() const noexcept {
            return static_cast<U>(number_);
        }

        [[nodiscard]] constexpr T number() const noexcept {
            return number_;
        }

        [[nodiscard]] constexpr int mod_class() const noexcept {
            return class_;
        }

        constexpr Modulo operator+(Modulo const& other) const {
            Modulo result(0, std::lcm(class_, other.class_));
            result.number_ = result.mod(number_ + other.number_);
            return result;
        }

        constexpr Modulo operator-(Modulo const& other) const {
            Modulo result(0, std::lcm(class_, other.class_));
            result.number_ = result.mod(number_ - other.number_);
            return result;
        }

        constexpr Modulo operator*(Modulo const& other) const {
            Modulo result(0, std::lcm(class_, other.class_));
            result.number_ = result.mod(number_ * other.number_);
            return result;
        }

        constexpr Modulo& operator+=(int n) {
            number_ = mod(number_ + n);
            return *this;
        }

        constexpr Modulo& operator++() {
            return *this += 1;
        }

        constexpr Modulo operator++(int) & {
            Modulo copy = *this;
            number_ = mod(number_ + 1);
            return copy;
        }

        constexpr Modulo operator+(int n) const {
            return Modulo(number_ + n, class_);
        }

        constexpr Modulo& operator-=(int n) {
            number_ = mod(number_ - n);
            return *this;
        }

        constexpr Modulo& operator--() {
            return *this -= 1;
        }

        constexpr Modulo operator--(int) & {
            Modulo copy = *this;
            number_ = mod(number_ - 1);
            return copy;
        }

        constexpr Modulo operator-(int n) const {
            return Modulo(number_ - n, class_);
        }

        constexpr Modulo& operator*=(int n) {
            number_ = mod(number_ * n);
            return *this;
        }

        constexpr Modulo operator*(int n) const {
            Modulo copy = *this;
            copy.number_ = mod(number_ * n);
            return copy;
        }

        constexpr Modulo& operator/=(int n) {
            if (n == 0) {
                throw std::invalid_argument("Division by zero is invalid");
            }

            number_ = mod(number_ / n);
            return *this;
        }

        constexpr Modulo operator/(int n) const {
            if (n == 0) {
                throw std::invalid_argument("Division by zero is invalid");
            }

            Modulo copy = *this;
            copy.number_ = mod(number_ / n);
            return copy;
        }

        friend std::ostream& operator<<(std::ostream& stream, Modulo const& m) {
            return stream << m.number_;
        }
    };
}

export template<typename T>
struct fmt::formatter<tetris::utils::Modulo<T>> : formatter<std::string_view> {
    auto format(tetris::utils::Modulo<T> mod, format_context& ctx) const {
        return formatter<string_view>::format(fmt::format("{} mod {}", mod.number(), mod.mod_class()), ctx);
    }
};