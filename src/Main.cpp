#include <SFML/Graphics.hpp>

import screens.MainMenuScreen;
import rendering.WindowType;
import AppState;

AppState state(
    WindowType::Type::Windowed,
    {1280, 720},
    std::make_unique<MainMenuScreen>(),
    8,
    0,
    false
);

void processKeyboardInput(sf::RenderWindow &window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        window.close();
    }
}

void processEvents(sf::RenderWindow &window) {
    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        processKeyboardInput(window);
        state.getScreen()->processEvents(window, event);
    }
}

void render(sf::RenderWindow &window) {
    window.clear(state.getScreen()->getBackgroundColor());

    state.getScreen()->render(window);

    window.display();
}

int main() {
    while (state.getWindow().isOpen()) {
        auto &window = state.getWindow();
        processEvents(window);
        render(window);
    }

    return 0;
}
