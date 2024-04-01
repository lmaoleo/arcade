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
    sf::Event event;

    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            for (auto &key : _keys.get()->_binds /* <- domage :( */ ) { // sans accès à _binds, on peut pas check les touches sans hardcoder
                if (event.key.code == key.second) {
                    _keys.get()->keyPressed(key.first, true);
                }
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            for (auto &key : _keys.get()->_binds) {
                if (event.key.code == key.second) {
                    _keys.get()->keyPressed(key.first, false);
                }
            }
        }
    }
}
