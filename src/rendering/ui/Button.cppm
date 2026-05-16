module;

#include <SFML/Graphics.hpp>

export module rendering.ui.Button;

import rendering.shapes.Superelipse;

export class Button : public sf::Drawable {
public:
    Button(
        const std::string &text,
        const sf::Font &font,
        std::uint32_t characterSize
    ) : m_text(font) {
        auto &fontTexture = const_cast<sf::Texture &>(font.getTexture(characterSize));
        fontTexture.setSmooth(false);

        m_text.setString(text);
        m_text.setCharacterSize(characterSize);
        m_text.setFillColor(sf::Color::White);
        m_text.setOrigin(m_text.getLocalBounds().getCenter());
    }

    void setSize(const sf::Vector2f &size) {
        m_shape.setSize(size);
    }

    void setPosition(const sf::Vector2f &position) {
        m_shape.setPosition(position);
        m_text.setPosition({std::round(position.x), std::round(position.y)});
    }

    void setFillColor(const sf::Color &color) {
        m_shape.setFillColor(color);
    }

    void onMouseOver(const std::function<void()> &callback) {
        m_onMouseHover = callback;
    }

    void onMouseOut(const std::function<void()> &callback) {
        m_onMouseOut = callback;
    }

    void onClick(const std::function<void()> &callback) {
        m_onClick = callback;
    }

    void processEvents(std::optional<sf::Event> &event) const {
        if (const auto mouseButton = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseButton->button == sf::Mouse::Button::Left) {
                if (const auto mousePos = sf::Vector2f(mouseButton->position);
                    m_shape.getGlobalBounds().contains(mousePos)) {
                    if (m_onClick) {
                        m_onClick();
                    }
                }
            }
        }

        if (const auto mouseMove = event->getIf<sf::Event::MouseMoved>()) {
            if (const auto mousePos = sf::Vector2f(mouseMove->position);
                m_shape.getGlobalBounds().contains(mousePos)) {
                if (m_onMouseHover) {
                    m_onMouseHover();
                }
            } else {
                if (m_onMouseOut) {
                    m_onMouseOut();
                }
            }
        }
    }

private:
    Superellipse m_shape;
    sf::Text m_text;
    std::function<void()> m_onMouseHover;
    std::function<void()> m_onMouseOut;
    std::function<void()> m_onClick;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        target.draw(m_shape, states);
        target.draw(m_text, states);
    }
};
