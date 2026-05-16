module;

#include <SFML/Graphics.hpp>

export module screens.MainMenuScreen;

import rendering.ui.Button;
import rendering.ColorUtils;
import screens.Screen;
import AppState;

export class MainMenuScreen : public Screen {
    sf::Font m_font{"data/fonts/GeistMono-Regular.ttf"};

    sf::Texture m_logoTexture{"data/images/logo.png"};
    sf::Sprite m_logoSprite{m_logoTexture};

    Button m_settingsBtn{"Settings", m_font, 24};
    Button m_exitBtn{"Exit", m_font, 24};

public:
    void buildScreen(sf::RenderWindow &window) override {
        const sf::Vector2u windowSize = window.getSize();
        const sf::Vector2f center = sf::Vector2f(windowSize) / 2.f;

        m_logoSprite.setOrigin({m_logoSprite.getLocalBounds().getCenter().x, 0.f});
        m_logoSprite.setPosition({center.x, 0.f});
        m_logoSprite.setScale({0.5f, 0.5f});

        m_settingsBtn.setSize({240.f, 80.f});
        m_settingsBtn.setPosition(center);
        m_settingsBtn.setFillColor(ColorUtils::rgb(0x494952));

        m_exitBtn.setSize({240.f, 80.f});
        m_exitBtn.setPosition({center.x, center.y + 100.f});
        m_exitBtn.setFillColor(ColorUtils::rgb(0x494952));
    }

    void render(sf::RenderWindow &window) const override {
        window.draw(m_logoSprite);
        window.draw(m_settingsBtn);
        window.draw(m_exitBtn);
    }

    void processEvents(sf::RenderWindow &window, std::optional<sf::Event> &event) override {
        if (const auto mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                // Move
            }
        }
    }

    [[nodiscard]]
    constexpr sf::Color getBackgroundColor() const override {
        return ColorUtils::rgb(0x2f2f35);
    }
};
