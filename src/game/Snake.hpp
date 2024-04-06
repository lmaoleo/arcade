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
#include <chrono>

namespace game {
    class Snake : public AGame {
        public:
            Snake(std::shared_ptr<std::map<std::string, bool>> &key);
            ~Snake();
            std::queue<std::tuple<EventType, eventData>> tick(double delta);
            std::vector<std::tuple<std::size_t, std::size_t>> changeSnakePos();
            void add_food_to_events(std::queue<std::tuple<EventType, eventData>> &events);
            void add_score_to_events(std::queue<std::tuple<EventType, eventData>> &events);
            void changeDirection();
            bool checkCollision();
            void checkFood();
            void generateFood();
            static void add_snake_to_map(std::vector<std::string> &map, std::vector<std::tuple<std::size_t, std::size_t>> snake);
            std::queue<std::tuple<EventType, eventData>> transform_map_to_events(std::vector<std::string> map);

        private:
            std::shared_ptr<std::map<std::string, bool>> _keys;
            std::size_t _ticks;
            std::size_t _score;
            std::tuple<std::size_t, std::size_t> _lastTailPos;
            std::tuple<std::size_t, std::size_t> _direction;
            std::string _headDirection;
            std::vector<std::tuple<std::size_t, std::size_t>> _snake;
            std::tuple<std::size_t, std::size_t> _food;
            std::queue<std::tuple<EventType, eventData>> _events;
            double _moveTime;
            bool _lose = false;
    };
};

static unsigned int rgbToInt(unsigned int a, unsigned short r, unsigned short g, unsigned short b);

#endif /* !SNAKE_HPP_ */
