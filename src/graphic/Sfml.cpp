/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual [WSL: Fedora]
** File description:
** Sfml
*/

#include "Sfml.hpp"

extern "C" {
    graphic::Sfml *createGraphic(std::shared_ptr<std::map<std::string, bool>> &keybinds)
    {
        return new graphic::Sfml(keybinds);
    }
};

graphic::Sfml::Sfml(std::shared_ptr<std::map<std::string, bool>> &key) : _keys(key)
{
    _keys = key;
    _window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Arcade DE ZINZIN");
    _font = new sf::Font();
    if (!_font->loadFromFile("assets/ARCADE_I.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    if (!_window->isOpen()) {
        std::cerr << "Failed to create window!" << std::endl;
    }
}

graphic::Sfml::~Sfml()
{
    _window->close();
    delete _window;
    delete _font;
}

void graphic::Sfml::updateKeybinds()
{
    sf::Event event;
    _keys->at("UP") = false;
    _keys->at("DOWN") = false;
    _keys->at("LEFT") = false;
    _keys->at("RIGHT") = false;
    _keys->at("ESC") = false;
    _keys->at("ESC") = false;
    _keys->at("ENTER") = false;

    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::Up :
                _keys->at("UP") = true;
                break;
            case sf::Keyboard::Down :
                _keys->at("DOWN") = true;
                break;
            case sf::Keyboard::Left :
                _keys->at("LEFT") = true;
                break;
            case sf::Keyboard::Right :
                _keys->at("RIGHT") = true;
                break;
            case sf::Keyboard::Escape :
                _keys->at("ESC") = true;
                break;
            case sf::Keyboard::Return :
                _keys->at("ENTER") = true;
                break;
            default:
                break;
            }
        }
    }
}

void graphic::Sfml::drawText(const std::string &text, const int &x, const int &y, bool selected)
{
    sf::Text textToDraw = sf::Text(text, *_font, 24);

    textToDraw.setPosition(x * 40, y * 40);
    if (selected) {
        textToDraw.setFillColor(sf::Color::Red);
    }
    _window->draw(textToDraw);
}

void graphic::Sfml::flushscreen()
{
    _window->clear();
}

std::tuple<short, short, short, short> graphic::Sfml::intToRgb(unsigned int color)
{
    short a = (color >> 24) & 0xFF; // Correctly masks the alpha component
    short r = (color >> 16) & 0xFF; // Correctly masks the red component
    short g = (color >> 8) & 0xFF;  // Correctly masks the green component
    short b = color & 0xFF;         // Correctly masks the blue component

    return std::make_tuple(a, r, g, b);
}

sf::Color graphic::Sfml::intToSfColor(unsigned int colorpat)
{
    short a, r, g, b;
    std::tie(a, r, g, b) = intToRgb(colorpat); // Assume intToRgb returns the correct RGBA values
    return sf::Color(r, g, b, a); // Create an SFML color from the RGBA components
}

void graphic::Sfml::createPixels(std::size_t x, std::size_t y, short pixel_form, unsigned int colorpat)
{
    sf::Color color = intToSfColor(colorpat);
    int scale = 1;
    int rectSize = 10 * scale;

    for (int i = 0; i < 16; i++) {
        sf::RectangleShape rectangle(sf::Vector2f(rectSize, rectSize));

        rectangle.setPosition((x * 4 + i % 4) * rectSize, (y * 4 + i / 4) * rectSize);

        if (pixel_form & (1 << i)) {
            rectangle.setFillColor(color);
        } else {
            rectangle.setFillColor(sf::Color::Black);
        }
        _window->draw(rectangle);
    }
}

std::queue<std::tuple<EventType, eventData>> graphic::Sfml::draw()
{
    std::size_t x, y = 0;
    std::string type = "";

    _window->clear();
    for (auto &item : _draw) {
        std::size_t x, y;
        short pixel;
        unsigned int color;
        std::tie(x, y, pixel, color) = item;
        createPixels(x, y, pixel, color);
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
    return std::queue<std::tuple<EventType, eventData>>();
}