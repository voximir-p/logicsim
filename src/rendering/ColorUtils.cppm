module;

#include "SFML/Graphics/Color.hpp"

export module rendering.ColorUtils;

export namespace ColorUtils {
    constexpr sf::Color rgb(const std::uint32_t color) {
        return sf::Color(color << 8 | 0xff);
    }
} // namespace col
