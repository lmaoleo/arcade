/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual
** File description:
** Snake
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include "AGame.hpp"
#include <queue>

namespace game {
    class Snake : public AGame {
        public:
            Snake();
            ~Snake();
            std::queue<state::Event> tick();

            void transform_map_to_events(std::vector<std::string> map);

        private:
            std::shared_ptr<state::Keybinds> _keys;
            std::size_t _ticks;
    };
};

#endif /* !SNAKE_HPP_ */
