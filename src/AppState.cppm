module;

#include <SFML/Graphics.hpp>

export module AppState;

import rendering.WindowType;
import screens.Screen;

export class AppState {
public:
    AppState(
        const WindowType::Type &windowType,
        const sf::Vector2u &windowSize,
        std::unique_ptr<Screen> screen,
        std::uint32_t antiAliasingLevel,
        std::uint32_t framerateLimit,
        bool verticalSyncEnabled
    ) : m_windowType(windowType)
        , m_framerateLimit(framerateLimit)
        , m_verticalSyncEnabled(verticalSyncEnabled)
        , m_settings{.antiAliasingLevel = antiAliasingLevel} {
        setScreen(screen);
        recreateWindow(windowSize);
    }

    sf::RenderWindow &getWindow() noexcept {
        return m_window;
    }

    const WindowType &getWindowType() const noexcept {
        return m_windowType;
    }

    void setWindowType(WindowType::Type windowType) {
        m_windowType = WindowType(windowType);
        recreateWindow();
    }

    const std::unique_ptr<Screen> &getScreen() const noexcept {
        return m_screen;
    }

    void setScreen(std::unique_ptr<Screen> &screen) {
        m_screen = std::move(screen);
        m_screen->buildScreen(m_window);
    }

    void setWindowSize(sf::Vector2u windowSize) {
        recreateWindow(windowSize);
    }

    std::uint32_t getAntiAliasingLevel() const noexcept {
        return m_settings.antiAliasingLevel;
    }

    void setAntiAliasingLevel(std::uint32_t antiAliasingLevel) {
        m_settings.antiAliasingLevel = antiAliasingLevel;
        recreateWindow();
    }

    std::uint32_t getFramerateLimit() const noexcept {
        return m_framerateLimit;
    }

    void setFramerateLimit(std::uint32_t framerateLimit) {
        m_framerateLimit = framerateLimit;
        applyWindowSettings();
    }

    bool isVerticalSyncEnabled() const noexcept {
        return m_verticalSyncEnabled;
    }

    void setVerticalSyncEnabled(bool verticalSyncEnabled) {
        m_verticalSyncEnabled = verticalSyncEnabled;
        applyWindowSettings();
    }

private:
    sf::RenderWindow m_window;
    WindowType m_windowType;
    std::unique_ptr<Screen> m_screen;
    std::uint32_t m_framerateLimit;
    bool m_verticalSyncEnabled;
    sf::ContextSettings m_settings{};

    void recreateWindow() {
        const auto size = m_window.getSize();
        recreateWindow(size);
    }

    void recreateWindow(sf::Vector2u windowSize) {
        if (windowSize.x == 0) {
            windowSize.x = 1280;
        }
        if (windowSize.y == 0) {
            windowSize.y = 720;
        }

        m_window.create(
            sf::VideoMode(windowSize),
            "Logicsim",
            m_windowType.getStyle(),
            m_windowType.getState(),
            m_settings
        );

        setScreen(m_screen);
        applyWindowSettings();
    }

    void applyWindowSettings() {
        m_window.setFramerateLimit(m_framerateLimit);
        m_window.setVerticalSyncEnabled(m_verticalSyncEnabled);
    }
};
