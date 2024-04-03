/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "AGame.hpp"
#include <queue>

namespace game {
    class Pacman : public AGame {
        public:
            Pacman(std::shared_ptr<std::map<std::string, bool>> &key);
            ~Pacman();
            std::queue<std::tuple<EventType, eventData>> tick();
            void changePacmanPos();
            std::vector<std::tuple<std::size_t, std::size_t, bool>> generateFood();
            void add_score_to_events(std::queue<std::tuple<EventType, eventData>> &events);
            void changeDirection();
            bool checkCollision(std::tuple<std::size_t, std::size_t> pos);
            void checkFood();
            std::queue<std::tuple<EventType, eventData>> transform_map_to_events(std::vector<std::string> map);

        private:
            std::shared_ptr<std::map<std::string, bool>> _keys;
            std::size_t _ticks;
            std::size_t _score;
            std::tuple<std::size_t, std::size_t> _direction;
            std::string _headDirection;
            std::tuple<std::size_t, std::size_t> _Pacman;
            std::vector<std::tuple<std::size_t, std::size_t, bool>> _food;
            std::vector<std::tuple<std::size_t, std::size_t>> _ghosts;
    };
};

#endif /* !Pacman_HPP_ */
