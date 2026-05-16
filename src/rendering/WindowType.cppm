module;

#include <SFML/Window.hpp>

export module rendering.WindowType;

export class WindowType {
public:
    enum class Type {
        Windowed,
        Fullscreen,
        Borderless
    };

    constexpr explicit WindowType(const Type type)
        : m_type(type) {
    }

    constexpr int getStyle() const {
        switch (m_type) {
            case Type::Windowed:
                return sf::Style::Close;

            case Type::Fullscreen:
                return sf::Style::None;

            case Type::Borderless:
                return sf::Style::None;
        }

        return sf::Style::Default;
    }

    constexpr sf::State getState() const {
        switch (m_type) {
            case Type::Windowed:
                return sf::State::Windowed;

            case Type::Fullscreen:
                return sf::State::Fullscreen;

            case Type::Borderless:
                return sf::State::Windowed;
        }

        return sf::State::Windowed;
    }

private:
    Type m_type;
};
