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
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include "AGraphic.hpp"

namespace graphic {
    class Sfml : public graphic::AGraphic {
    public:
        Sfml(std::shared_ptr<std::map<std::string, bool>> &key);
        ~Sfml();
        void updateKeybinds() final;
        void drawGameElement(sf::RenderWindow &window, const sf::IntRect &rect, const std::string &elementType);
        sf::Texture *loadSprite(const std::string &filePath);
        void loadSprites();
        void drawText(const std::string &text, const int &x, const int &y, bool selected);
        std::queue<std::tuple<EventType, eventData>> draw() final;

    private:
        std::shared_ptr<std::map<std::string, bool>> _keys;
        sf::RenderWindow *_window;
        sf::Font *_font;
    };
}
