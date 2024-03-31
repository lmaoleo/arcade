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
            Snake(std::shared_ptr<state::Keybinds> &key);
            ~Snake();
            std::queue<state::Event> tick();
            std::vector<std::tuple<std::size_t, std::size_t>> changeSnakePos();
            void add_food_to_events(std::queue<state::Event> &events);
            void add_snake_to_events(std::queue<state::Event> &event);
            void add_score_to_events(std::queue<state::Event> &events);
            void changeDirection();
            bool checkCollision();
            void checkFood();
            void generateFood();
            std::queue<state::Event> transform_map_to_events(std::vector<std::string> map);

        private:
            std::shared_ptr<state::Keybinds> _keys;
            std::size_t _ticks;
            std::size_t _score;
            std::tuple<std::size_t, std::size_t> _lastTailPos;
            std::tuple<std::size_t, std::size_t> _direction;
            std::string _headDirection;
            std::vector<std::tuple<std::size_t, std::size_t>> _snake;
            std::tuple<std::size_t, std::size_t> _food;
    };
};

#endif /* !SNAKE_HPP_ */
