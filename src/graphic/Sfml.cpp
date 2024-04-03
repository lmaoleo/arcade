/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual [WSL: Fedora]
** File description:
** Sfml
*/

#include "Sfml.hpp"

std::map<std::string, sf::Color> colorMap = {
    {"wall", {255, 0, 0, 255}},
    {"snake_head_down", {0, 255, 255, 255}},
    {"snake_head_up", {0, 255, 255, 255}},
    {"snake_head_left", {0, 255, 255, 255}},
    {"snake_head_right", {0, 255, 255, 255}},
    {"snake_body", {0, 255, 0, 255}},
    {"horizontal_snake_body", {0, 255, 0, 255}},
    {"vertical_snake_body", {0, 255, 0, 255}},
    {"angle_left_down_snake_body", {0, 255, 0, 255}},
    {"angle_right_down_snake_body", {0, 255, 0, 255}},
    {"angle_left_up_snake_body", {0, 255, 0, 255}},
    {"angle_right_up_snake_body", {0, 255, 0, 255}},
    {"snake_tail_down", {0, 255, 255, 255}},
    {"snake_tail_up", {0, 255, 255, 255}},
    {"snake_tail_left", {0, 255, 255, 255}},
    {"snake_tail_right", {0, 255, 255, 255}},
    {"pac_wall", {15, 46, 215, 255}},
    {"pac_down", {255, 255, 0, 255}},
    {"pac_up", {255, 255, 0, 255}},
    {"pac_left", {255, 255, 0, 255}},
    {"pac_right", {255, 255, 0, 255}},
    {"ghost", {255, 0, 0, 255}},
    {"pac_food", {231, 154, 149, 255}},
    {"food", {255, 255, 0, 255}}
};

extern "C" {
    graphic::Sfml *createGraphic(std::shared_ptr<state::Keybinds> &keybinds)
    {
        return new graphic::Sfml(keybinds);
    }
};

graphic::Sfml::Sfml(std::shared_ptr<state::Keybinds> &key) : _keys(key)
{
    _keys = key;
    _window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Arcade DE ZINZIN");
    _font = new sf::Font();
    if (!_font->loadFromFile("src/graphic/ARCADE_I.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    if (!_window->isOpen()) {
        std::cerr << "Failed to create window!" << std::endl;
    }
    _keys.get()->bindKey("UP", sf::Keyboard::Up);
    _keys.get()->bindKey("DOWN", sf::Keyboard::Down);
    _keys.get()->bindKey("LEFT", sf::Keyboard::Left);
    _keys.get()->bindKey("RIGHT", sf::Keyboard::Right);
    _keys.get()->bindKey("ESCAPE", sf::Keyboard::Escape);
}

graphic::Sfml::~Sfml()
{
    _window->close();
    delete _window;
    delete _font;
}

void graphic::Sfml::updateKeybinds()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        _keys.get()->keyPressed("UP", true);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        _keys.get()->keyPressed("DOWN", true);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        _keys.get()->keyPressed("LEFT", true);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        _keys.get()->keyPressed("RIGHT", true);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        _keys.get()->keyPressed("ESCAPE", true);
    else {
        _keys.get()->keyPressed("UP", false);
        _keys.get()->keyPressed("DOWN", false);
        _keys.get()->keyPressed("LEFT", false);
        _keys.get()->keyPressed("RIGHT", false);
        _keys.get()->keyPressed("ESCAPE", false);
    }
}

void graphic::Sfml::drawGameElement(sf::RenderWindow &window, const sf::IntRect &rect, const std::string &elementType)
{
    auto colorIt = colorMap.find(elementType);

    if (colorIt != colorMap.end()) {
        const sf::Color &color = colorIt->second;
        sf::RectangleShape rectangle(sf::Vector2f(rect.width, rect.height));
        rectangle.setPosition(rect.left, rect.top);
        rectangle.setFillColor(color);
        window.draw(rectangle);
    }
}

void graphic::Sfml::drawText(const std::string &text, const int &x, const int &y, bool selected)
{
    sf::Text textToDraw = sf::Text(text, *_font, 24);

    textToDraw.setPosition(x, y);
    if (selected) {
        textToDraw.setFillColor(sf::Color::Red);
    }
    _window->draw(textToDraw);
}

std::queue<state::Event> graphic::Sfml::draw()
{
    std::size_t x, y = 0;
    std::string type = "";

    _window->clear();
    for (auto &item : _draw) {
        x = std::get<0>(item);
        y = std::get<1>(item);
        type = std::get<2>(item);
        sf::IntRect rect(x * 40, y * 40, 40, 40);
        drawGameElement(*_window, rect, type);
    }
    for (auto &item : _draw_str) {
        x = std::get<0>(item);
        y = std::get<1>(item);
        std::string str = std::get<2>(item);
        bool selected = std::get<3>(item);
        drawText(str, x, y, selected);
    }
    _window->display();
    _draw.clear();
    _draw_str.clear();
    return std::queue<state::Event>();
}