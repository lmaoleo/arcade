/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_
#include "AGame.hpp"
#include <queue>

namespace game {
    class Menu : public AGame {
        public:
            Menu(std::shared_ptr<state::Keybinds> &key);
            ~Menu();
            std::queue<state::Event> tick();
            std::vector<std::tuple<std::size_t, std::size_t>> changeSnakePos();
            void add_food_to_events(std::queue<state::Event> &events);
            void add_snake_to_events(std::queue<state::Event> &event);
            void changeDirection();
            bool checkCollision();
            void checkFood();
            void generateFood();
            std::queue<state::Event> transform_map_to_events(std::vector<std::string> map);

        private:
            std::shared_ptr<state::Keybinds> _keys;
            std::size_t _ticks;
            std::string _selected_game;
            std::string _selected_graphic;
    };
};

#endif /* !MENU_HPP_ */
