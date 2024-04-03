/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual [WSL: Fedora]
** File description:
** Sfml
*/

#include "Sfml.hpp"

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
