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
            Snake(std::shared_ptr<std::map<std::string, bool>> &key);
            ~Snake();
            std::queue<std::tuple<EventType, eventData>> tick();
            std::vector<std::tuple<std::size_t, std::size_t>> changeSnakePos();
            void add_food_to_events(std::queue<std::tuple<EventType, eventData>> &events);
            void add_snake_to_events(std::queue<std::tuple<EventType, eventData>> &event);
            void add_score_to_events(std::queue<std::tuple<EventType, eventData>> &events);
            void changeDirection();
            bool checkCollision();
            void checkFood();
            void generateFood();
            std::string determine_body_orientation(int i);
            std::string determine_tail_orientation(int i);
            std::queue<std::tuple<EventType, eventData>> transform_map_to_events(std::vector<std::string> map);
            std::queue<std::tuple<std::size_t, std::variant<std::nullopt_t, std::string, std::size_t, double, bool>>> transform_map_to_events_te(std::vector<std::string> map);

        private:
            std::shared_ptr<std::map<std::string, bool>> _keys;
            std::size_t _ticks;
            std::size_t _score;
            std::tuple<std::size_t, std::size_t> _lastTailPos;
            std::tuple<std::size_t, std::size_t> _direction;
            std::string _headDirection;
            std::vector<std::tuple<std::size_t, std::size_t>> _snake;
            std::tuple<std::size_t, std::size_t> _food;
            bool _lose = false;
    };
};

#endif /* !SNAKE_HPP_ */
