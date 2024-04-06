/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual [WSL: Fedora]
** File description:
** Sfml
*/

#include "Sfml.hpp"

std::map<sf::Keyboard::Key, std::string> _keyMap;

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
    _keyMap = {
    {sf::Keyboard::Up, "UP"}, {sf::Keyboard::Down, "DOWN"},{sf::Keyboard::Left, "LEFT"},
    {sf::Keyboard::Right, "RIGHT"}, {sf::Keyboard::Escape, "ESC"}, {sf::Keyboard::Enter, "ENTER"},
    {sf::Keyboard::Space, "SPACE"}, {sf::Keyboard::A, "A"}, {sf::Keyboard::Z, "Z"},
    {sf::Keyboard::E, "E"},{sf::Keyboard::R, "R"},{sf::Keyboard::T, "T"},
    {sf::Keyboard::Y, "Y"}, {sf::Keyboard::U, "U"}, {sf::Keyboard::I, "I"},
    {sf::Keyboard::O, "O"}, {sf::Keyboard::P, "P"}, {sf::Keyboard::Q, "Q"},
    {sf::Keyboard::S, "S"}, {sf::Keyboard::D, "D"}, {sf::Keyboard::F, "F"},
    {sf::Keyboard::G, "G"}, {sf::Keyboard::H, "H"}, {sf::Keyboard::J, "J"},
    {sf::Keyboard::K, "K"}, {sf::Keyboard::L, "L"}, {sf::Keyboard::M, "M"},
    {sf::Keyboard::W, "W"}, {sf::Keyboard::X, "X"}, {sf::Keyboard::C, "C"},
    {sf::Keyboard::V, "V"}, {sf::Keyboard::B, "B"}, {sf::Keyboard::N, "N"},
    {sf::Keyboard::Tab, "TAB"}, {sf::Keyboard::F1, "F1"}, {sf::Keyboard::F2, "F2"},
    {sf::Keyboard::F3, "F3"}, {sf::Keyboard::F4, "F4"}
};
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
    for (auto& key : *_keys) {
            key.second = false;
    }

    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            auto it = _keyMap.find(event.key.code);
            if (it != _keyMap.end()) {
                if (_keys->find(it->second) != _keys->end()) {
                    _keys->at(it->second) = true;
                }
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