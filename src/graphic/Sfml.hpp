/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual
** File description:
** Sfml
*/

#pragma once

#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include "AGraphic.hpp"

namespace graphic {
    class Sfml : public graphic::AGraphic {
    public:
        Sfml(std::shared_ptr<state::Keybinds> &key);
        ~Sfml();
        void updateKeybinds() final;
        void drawGameElement(sf::RenderWindow &window, const sf::IntRect &rect, const std::string &elementType);
        void drawText(const std::string &text, const int &x, const int &y, bool selected);
        std::queue<state::Event> draw() final;

    private:
        std::shared_ptr<state::Keybinds> _keys;
        sf::RenderWindow *_window;
        sf::Font *_font;
    };
}
