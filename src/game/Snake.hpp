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
            std::vector<std::tuple<std::size_t, std::size_t>> changeSnakePos();
            void changeDirection();
            bool checkCollision();
            void checkFood();
            void generateFood();

        private:
            std::size_t _ticks;
            std::size_t _score;
            std::tuple<std::size_t, std::size_t> _lastTailPos;
            std::tuple<std::size_t, std::size_t> _direction;
            std::vector<std::tuple<std::size_t, std::size_t>> _snake;
            std::tuple<std::size_t, std::size_t> _food;
    };
};

#endif /* !SNAKE_HPP_ */
