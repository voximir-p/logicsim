module;

#include <SFML/Graphics.hpp>

export module screens.Screen;

export class Screen {
public:
    virtual ~Screen() = default;

    Screen() = default;

    Screen(const Screen&) = delete;
    Screen& operator=(const Screen&) = delete;

    Screen(Screen&&) noexcept = default;
    Screen& operator=(Screen&&) noexcept = default;

    virtual void buildScreen(sf::RenderWindow &window) = 0;

    virtual void render(sf::RenderWindow &window) const = 0;

    virtual void processEvents(sf::RenderWindow &window, std::optional<sf::Event> &event) = 0;

    [[nodiscard]]
    constexpr virtual sf::Color getBackgroundColor() const = 0;

protected:
    std::vector<std::unique_ptr<sf::Drawable> > m_drawBuffer;
};
